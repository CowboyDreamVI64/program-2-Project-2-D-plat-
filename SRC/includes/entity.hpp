class Entity {
	protected:
		bool __UP = false;
		bool __UP_TRIGGERED = false;
		bool __LEFT = false;
		bool __LEFT_TRIGGERED = false;
		bool __DOWN = false;
		bool __DOWN_TRIGGERED = false;
		bool __RIGHT = false;
		bool __RIGHT_TRIGGERED = false;
		bool __JUMP = false;
		bool __JUMP_TRIGGERED = false;
		bool __SPRINT = false;
		bool __SPRINT_TRIGGERED = false;
		bool __ON_GROUND = false;
		bool __ON_GROUND_TRIGGERED = false;
		bool __IS_JUMPING = false;
		bool __IS_JUMPING_TRIGGERED = false;
		bool __IS_SKIDDING = false;
		bool __IS_SKIDDING_TRIGGERED = false;
		size_t __JUMP_FRAMES = 0;
		
		double maxSpeed = 0.0;
	public:
		const bool& up = __UP;
		const bool& left = __LEFT;
		const bool& down = __DOWN;
		const bool& right = __RIGHT;
		const bool& jump = __JUMP;
		const bool& sprint = __SPRINT;
		
		const bool& up_triggered = __UP_TRIGGERED;
		const bool& left_triggered = __LEFT_TRIGGERED;
		const bool& down_triggered = __DOWN_TRIGGERED;
		const bool& right_triggered = __RIGHT_TRIGGERED;
		const bool& jump_triggered = __JUMP_TRIGGERED;
		const bool& sprint_triggered = __SPRINT_TRIGGERED;
		
		const bool& onGround = __ON_GROUND;
		const bool& isJumping = __IS_JUMPING;
		const size_t& jumpFrames = __JUMP_FRAMES;
		
		const bool& on_ground_triggered = __ON_GROUND_TRIGGERED;
		const bool& is_jumping_triggered = __IS_JUMPING_TRIGGERED;
		
		const bool& isSkidding = __IS_SKIDDING;
		const bool& is_skidding_triggered = __IS_SKIDDING_TRIGGERED;
		
		Vec2 hitbox;
		Vec2 acceleration_const;
		Vec2 acceleration = {0.0, 0.0};
		Vec2 velocity = {0.0, 0.0};
		Vec2 position;
		bool snapToSpeed = false;
		
		double accelerationConstYJumpingMultiplier = 1.0;
		
		double frictionCoefficient;
		double frictionCoefficientAirMultiplier = 0.0;
		double dragCoefficient;
		double dragCoefficientJumpingMultiplier = 0.1;
		double skidMultiplier = 0.0;
		
		double speed;
		double sprintSpeedMultiplier = 2;
		
		double jumpForce;
		double jumpForceSprintingMultiplier = 1.15;
		size_t maxJumpFrames = 0;
		bool holdToJump = true;
	
		std::array<bool, 6> constInput;
	
		Entity& receiveInput(const std::array<bool, 6>& booleans = std::array<bool, 6>()) {
			__UP_TRIGGERED = false;
			__LEFT_TRIGGERED = false;
			__DOWN_TRIGGERED = false;
			__RIGHT_TRIGGERED = false;
			__JUMP_TRIGGERED = false;
			__SPRINT_TRIGGERED = false;
			
			if (booleans[0]) {
				if (!__UP) {
					__UP_TRIGGERED = true;
				}
				__UP = true;
			} else {
				__UP = false;
			}
			if (booleans[1]) {
				if (!__LEFT) {
					__LEFT_TRIGGERED = true;
				}
				__LEFT = true;
			} else {
				__LEFT = false;
			}
			if (booleans[2]) {
				if (!__DOWN) {
					__DOWN_TRIGGERED = true;
				}
				__DOWN = true;
			} else {
				__DOWN = false;
			}
			if (booleans[3]) {
				if (!__RIGHT) {
					__RIGHT_TRIGGERED = true;
				}
				__RIGHT = true;
			} else {
				__RIGHT = false;
			}
			if (booleans[4]) {
				if (!__JUMP) {
					__JUMP_TRIGGERED = true;
				}
				__JUMP = true;
			} else {
				__JUMP = false;
			}
			if (booleans[5]) {
				if (!__SPRINT) {
					__SPRINT_TRIGGERED = true;
				}
				__SPRINT = true;
			} else {
				__SPRINT = false;
			}
			return *this;
		}
		Entity& receiveInput() {
			return receiveInput(constInput);
		}
		Entity& receiveInput(ExtendedWindow& window, const KeyBind& inputKeyBinds) {
			return receiveInput(inputKeyBinds.getInputBool(window));
		}
		
		
			
		Entity& tickPhysics(const size_t& TPS) {
			__ON_GROUND_TRIGGERED = false;
			__IS_JUMPING_TRIGGERED = false;
			
			
			if (jump_triggered) {
				__JUMP_FRAMES = maxJumpFrames;
			} else if (__JUMP_FRAMES > 0) {
				--__JUMP_FRAMES;
			}
			
			
			maxSpeed = speed * (sprint ? sprintSpeedMultiplier : 1.0);
			
			
			if (jump) {
				if (onGround && (holdToJump || jump_triggered || jumpFrames != 0)) {
					__IS_JUMPING_TRIGGERED = true;
					__IS_JUMPING = true;
					__ON_GROUND = false;
					velocity.y += jumpForce * (velocity.x_abs() > speed ? jumpForceSprintingMultiplier : 1.0);
				}
			} else {
				__IS_JUMPING = false;
			}
			
			
			__IS_SKIDDING_TRIGGERED = false;
			if (onGround && ((left && !right && velocity.x > speed*0.8) || (right && !left && velocity.x < -speed*0.8))) {
				if (!__IS_SKIDDING) {
					__IS_SKIDDING_TRIGGERED = true;
				}
				__IS_SKIDDING = true;
			} else {
				__IS_SKIDDING = false;
			}
			
			
			if (!snapToSpeed || velocity.x_abs() > maxSpeed) {
				if (left && !right && velocity.x > -maxSpeed) {
					acceleration.x -= (isSkidding ? 1.0 - skidMultiplier : 1.0)*maxSpeed*(onGround ? (velocity.x_abs() > speed ? 2.2 : 1.8) : velocity.x_abs() > speed ? 0.7 : 1.6);
				}
				if (right && !left && velocity.x < maxSpeed) {
					acceleration.x += (isSkidding ? 1.0 - skidMultiplier : 1.0)*maxSpeed*(onGround ? (velocity.x_abs() > speed ? 2.2 : 1.8) : velocity.x_abs() > speed ? 0.7 : 1.6);
				}
			} else {
				velocity.x = 0.0;
				if (left && !right) {
					velocity.x = -maxSpeed;
				}
				if (right && !left) {
					velocity.x = maxSpeed;
				}
			}
			
			
			
			if (isJumping && velocity.y > 0) {
				acceleration.y -= (1.0 - accelerationConstYJumpingMultiplier)*acceleration_const.y;
			}
			
			
			velocity += acceleration/TPS;
			
			
			velocity.x *= exp(-frictionCoefficient*(onGround ? 1.0 : frictionCoefficientAirMultiplier)/TPS);
			velocity.y *= exp(-dragCoefficient*(isJumping && velocity.y > 0 ? dragCoefficientJumpingMultiplier : 1.0)/TPS);
			
			position += velocity/TPS;
			
			acceleration = acceleration_const;
			
			
			const double GROUND_HEIGHT = 0.7;
			if (position.y < GROUND_HEIGHT + hitbox.y/2) {
				position.y = GROUND_HEIGHT + hitbox.y/2;
				velocity.y = 0.0;
				if (!__ON_GROUND) {
					__ON_GROUND_TRIGGERED = true;
				}
				__ON_GROUND = true;
			}
			
			
			return *this;
		}
	
		Entity(
			const Vec2& inputPosition = {0.0, 0.0},
			const Vec2& inputHitbox = {1.0, 1.0},
			const Vec2& inputAccelerationConst = {0.0, -36.0},
			const double& inputSpeed = 8,
			const double& inputJumpForce = 8,
			const double& inputFrictionCoefficient = 2.0,
			const double& inputDragCoefficient = 2
		) :
			position(inputPosition),
			hitbox(inputHitbox),
			acceleration_const(inputAccelerationConst),
			speed(inputSpeed),
			jumpForce(inputJumpForce),
			frictionCoefficient(inputFrictionCoefficient),
			dragCoefficient(inputDragCoefficient)
		{};
};