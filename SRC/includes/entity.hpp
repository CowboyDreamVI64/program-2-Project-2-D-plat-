//  A class that stores details about entities and simulates their physics.
class Entity {
	protected:
		//  Mutable boolean checks for certain movement types and triggers.
		bool UP = false;
		bool UP_TRIGGERED = false;
		bool LEFT = false;
		bool LEFT_TRIGGERED = false;
		bool DOWN = false;
		bool DOWN_TRIGGERED = false;
		bool RIGHT = false;
		bool RIGHT_TRIGGERED = false;
		bool JUMP = false;
		bool JUMP_TRIGGERED = false;
		bool SPRINT = false;
		bool SPRINT_TRIGGERED = false;
		bool ON_GROUND = false;
		bool ON_GROUND_TRIGGERED = false;
		bool IS_JUMPING = false;
		bool IS_JUMPING_TRIGGERED = false;
		bool IS_SPRINTING = false;
		bool IS_SPRINTING_TRIGGERED = false;
		bool IS_SKIDDING = false;
		bool IS_SKIDDING_TRIGGERED = false;
		size_t JUMP_BUFFER = 0;
		
		double maxSpeed = 0.0;
	public:
		//  Read-only versions of the boolean checks above.
		inline bool up() const {
			return UP;
		}
		inline bool left() const {
			return LEFT;
		}
		inline bool down() const {
			return DOWN;
		}
		inline bool right() const {
			return RIGHT;
		}
		inline bool jump() const {
			return JUMP;
		}
		inline bool sprint() const {
			return SPRINT;
		}
		inline bool up_triggered() const {
			return UP_TRIGGERED;
		}
		inline bool left_triggered() const {
			return LEFT_TRIGGERED;
		}
		inline bool down_triggered() const {
			return DOWN_TRIGGERED;
		}
		inline bool right_triggered() const {
			return RIGHT_TRIGGERED;
		}
		inline bool jump_triggered() const {
			return JUMP_TRIGGERED;
		}
		inline bool sprint_triggered() const {
			return SPRINT_TRIGGERED;
		}
		inline bool onGround() const {
			return ON_GROUND;
		}
		inline bool isJumping() const {
			return IS_JUMPING;
		}
		inline bool is_sprinting() const {
			return IS_SPRINTING;
		}
		inline size_t jumpFrames() const {
			return JUMP_BUFFER;
		}
		inline bool on_ground_triggered() const {
			return ON_GROUND_TRIGGERED;
		}
		inline bool is_jumping_triggered() const {
			return IS_JUMPING_TRIGGERED;
		}
		inline bool is_sprinting_triggered() const {
			return IS_SPRINTING_TRIGGERED;
		}
		inline bool isSkidding() const {
			return IS_SKIDDING;
		}
		inline bool is_skidding_triggered() const {
			return IS_SKIDDING_TRIGGERED;
		}
		
		Vec2 hitbox;
		Vec2 acceleration_const;
		Vec2 acceleration = {0.0, 0.0};
		Vec2 velocity = {0.0, 0.0};
		Vec2 position;
		
		//  If true, the entity will not accelerate towards their max speed or to a halt.
		bool snapToSpeed = false;
		
		//  A multiplier applied to the entity's constant acceleration (which is usually gravity) when jumping.
		Vec2 accelerationConstJumpingMultiplier = 1.0;
		
		//  A coefficient that slows the entity's x velocity down if they are on the ground.
		double frictionCoefficient;
		
		//  The multiplier for friction slowdown when the entity is in the air.
		double frictionCoefficientAirMultiplier = 0.0;
		
		//  A coefficient that slows the entity's y velocity down.
		double dragCoefficient;
		
		//  The multiplier for drag when the entity is jumping up.
		double dragCoefficientJumpingMultiplier = 0.1;
		
		//  The speed reduction multiplier for when the entity is moving too fast and wants to turn around.
		double skidMultiplier = 0.0;
		
		//  The base speed the entity can go
		double speed;
		
		//  The multiplier applied to the base speed above when the entity is sprinting.
		double sprintSpeedMultiplier = 2;
		
		//  The strength of the entity's jump.
		double jumpForce;
		
		//  The multiplier applied to the entity's jump force when moving faster than base speed.
		double jumpForceSprintingMultiplier = 1.15;
		
		//  If true, the entity can hold the jump input to keep jumping; else, the entity will need to stop inputting jump then reinput jump again.
		bool autoJump = true;
		
		//  The number of frames the entity's jump is valid for since input before the entity needs to reinput jump.
		//  Only effective if autoJump is false.
		size_t maxJumpBufferFrames = 0;
	
		//  The default boolean array of input for the entity; setting any of these boolean values to "true" will make the corresponding movement
		//  register as input when no keybinds are passed through "receiveInput."
		std::array<bool, 6> constInput;
	
		//  Takes a list of booleans as input.
		Entity& receiveInput(const std::array<bool, 6>& booleans) {
			UP_TRIGGERED = false;
			LEFT_TRIGGERED = false;
			DOWN_TRIGGERED = false;
			RIGHT_TRIGGERED = false;
			JUMP_TRIGGERED = false;
			SPRINT_TRIGGERED = false;
			
			if (booleans[0]) {
				if (!UP) {
					UP_TRIGGERED = true;
				}
				UP = true;
			} else {
				UP = false;
			}
			if (booleans[1]) {
				if (!LEFT) {
					LEFT_TRIGGERED = true;
				}
				LEFT = true;
			} else {
				LEFT = false;
			}
			if (booleans[2]) {
				if (!DOWN) {
					DOWN_TRIGGERED = true;
				}
				DOWN = true;
			} else {
				DOWN = false;
			}
			if (booleans[3]) {
				if (!RIGHT) {
					RIGHT_TRIGGERED = true;
				}
				RIGHT = true;
			} else {
				RIGHT = false;
			}
			if (booleans[4]) {
				if (!JUMP) {
					JUMP_TRIGGERED = true;
				}
				JUMP = true;
			} else {
				JUMP = false;
			}
			if (booleans[5]) {
				if (!SPRINT) {
					SPRINT_TRIGGERED = true;
				}
				SPRINT = true;
			} else {
				SPRINT = false;
			}
			return *this;
		}
		
		//  Takes the boolean list "constInput" as input.
		Entity& receiveInput() {
			return receiveInput(constInput);
		}
		
		//  Takes the passed keybinds, checks whether each key is being registered in the passed window, and uses the corresponding checks as input.
		Entity& receiveInput(const ExtendedWindow& window, const KeyBind& inputKeyBinds) {
			return receiveInput(inputKeyBinds.getInputBool(window));
		}
		
		//  A bunch of physics and math that calculates the momentum and position of the entity as well as changing some triggers.
		Entity& tickPhysics(const size_t& TPS) {
			//  True if the entity just touched the ground.
			ON_GROUND_TRIGGERED = false;
			
			//  True if the entity just jumped.
			IS_JUMPING_TRIGGERED = false;
			
			//  True if the entity is sprinting.
			IS_SPRINTING_TRIGGERED = false;
			
			//  Sets the jump buffer to the max if the entity inputted jump; else, decrements the jump buffer.
			if (JUMP_TRIGGERED) {
				JUMP_BUFFER = maxJumpBufferFrames;
			} else if (JUMP_BUFFER > 0) {
				--JUMP_BUFFER;
			}
			
			
			//  Checks if the player can actually sprint
			if (SPRINT && (LEFT || RIGHT)) {
				if (!IS_SPRINTING) {
					IS_SPRINTING_TRIGGERED = true;
				}
				IS_SPRINTING = true;
			} else {
				IS_SPRINTING = false;
			}
			
			//  Sets the maximum move speed of the entity based on the sprint speed multiplier.
			maxSpeed = speed * (IS_SPRINTING ? sprintSpeedMultiplier : 1.0);
			
			
			if (JUMP) {
				if (ON_GROUND && (autoJump || JUMP_TRIGGERED || JUMP_BUFFER != 0)) {
					IS_JUMPING_TRIGGERED = true;
					
					//  True if the entity is in a jump at the moment.
					IS_JUMPING = true;
					ON_GROUND = false;
					
					//  Calculates the addition to the player's y velocity when the player jumped.
					velocity.y += jumpForce * (velocity.x_abs() > speed*1.05 ? jumpForceSprintingMultiplier : 1.0);
				}
			} else {
				IS_JUMPING = false;
			}
			
			//  True if the player starts skidding.
			IS_SKIDDING_TRIGGERED = false;
			if (ON_GROUND && ((LEFT && !RIGHT && velocity.x > speed*1.05) || (RIGHT && !LEFT && velocity.x < -speed*1.05))) {
				if (!IS_SKIDDING) {
					IS_SKIDDING_TRIGGERED = true;
				}
				//  True if the player is currently skidding.
				IS_SKIDDING = true;
			} else if (!ON_GROUND || ((LEFT && !RIGHT && velocity.x > 0.0) || (RIGHT && !LEFT && velocity.x < 0.0))) {
				IS_SKIDDING = false;
			}
			
			//  Math and control structures that control how to apply speed to velocity.
			if (!snapToSpeed || velocity.x_abs() > maxSpeed) {
				if (LEFT && !RIGHT && velocity.x > -maxSpeed) {
					//  This pushes the player leftwards.
					acceleration.x -= (IS_SKIDDING ? 1.0 - skidMultiplier : 1.0)*maxSpeed*(ON_GROUND ? (velocity.x_abs() > speed ? 2.2 : 1.8) : velocity.x_abs() > speed ? 0.7 : 1.6);
				}
				if (RIGHT && !LEFT && velocity.x < maxSpeed) {
					//  This pushes the player rightwards.
					acceleration.x += (IS_SKIDDING ? 1.0 - skidMultiplier : 1.0)*maxSpeed*(ON_GROUND ? (velocity.x_abs() > speed ? 2.2 : 1.8) : velocity.x_abs() > speed ? 0.7 : 1.6);
				}
			} else {
				//  If the player's speed snaps, this sets their speed to 0.0 when they are below their maximum speed.
				velocity.x = 0.0;
				if (LEFT && !RIGHT) {
				//  If the player's speed snaps, this sets their speed to max towards the left.
					velocity.x = -maxSpeed;
				}
				if (RIGHT && !LEFT) {
				//  If the player's speed snaps, this sets their speed to max towards the right.
					velocity.x = maxSpeed;
				}
			}
			
			
			//  Applies a multiplier to gravity when the player is jumping.
			if (IS_JUMPING && velocity.y > 0) {
				acceleration -= (Vec2(1.0) - accelerationConstJumpingMultiplier)*acceleration_const;
			}
			
			//  This applies acceleration to velocity.
			velocity += acceleration/TPS;
			
			//  This modifies velocity to account for friction and drag.
			if (velocity.x_abs() > maxSpeed*0.6/TPS) {
				velocity.x *= exp(-frictionCoefficient*(ON_GROUND ? 1.0 : frictionCoefficientAirMultiplier)/TPS);
			} else {
				velocity.x = 0.0;
			}
			velocity.y *= exp(-dragCoefficient*(IS_JUMPING && velocity.y > 0 ? dragCoefficientJumpingMultiplier : 1.0)/TPS);
			
			//  This applies velocity to position.acceleration_const
			position += velocity/TPS;
			
			//  This resets acceleration to acceleration_const.
			acceleration = acceleration_const;
			
			//  This is a temporary "ground" that has been set until block loading and collision have been established.
			const double GROUND_HEIGHT = 0.7;
			if (position.y < GROUND_HEIGHT + hitbox.y/2) {
				position.y = GROUND_HEIGHT + hitbox.y/2;
				velocity.y = 0.0;
				if (!ON_GROUND) {
					ON_GROUND_TRIGGERED = true;
				}
				ON_GROUND = true;
			}
			
			return *this;
		}
	
		//  The default Entity constructor
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