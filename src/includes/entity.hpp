
namespace EntityBehaviorTypes {
	constexpr short Default = 0;
	constexpr short Player = 1;
	constexpr short Enemy = 2;
}

struct CollisionContext {
	public:
		bool collision = false;
		bool collisionUp = false;
		bool collisionDown = false;
		bool collisionLeft = false;
		bool collisionRight = false;
		
		
		CollisionContext(const array<bool, 5>& collisionResults = array<bool, 5>()) :
			collision(collisionResults[0]),
			collisionUp(collisionResults[1]),
			collisionDown(collisionResults[2]),
			collisionLeft(collisionResults[3]),
			collisionRight(collisionResults[4])
		{};
		
		static CollisionContext resolve(const Vec2 targetPosition, const Vec2 targetSize, const Vec2 sourcePosition, const Vec2 sourceSize = 1.0) {
			CollisionContext outputResults;
			
			if (targetPosition.x + targetSize.x/2 > sourcePosition.x - sourceSize.x/2 && targetPosition.x - targetSize.x/2 < sourcePosition.x + sourceSize.x/2 && targetPosition.y + targetSize.y/2 > sourcePosition.y - sourceSize.y/2 && targetPosition.y - targetSize.y/2 < sourcePosition.y + sourceSize.y/2) {
				outputResults.collision = true;
				
				Vec2 overlap(
					targetPosition.x < sourcePosition.x ? targetPosition.x + targetSize.x/2 - sourcePosition.x + sourceSize.x/2 : sourcePosition.x + sourceSize.x/2 - targetPosition.x + targetSize.x/2,
					targetPosition.y < sourcePosition.y ? targetPosition.y + targetSize.y/2 - sourcePosition.y + sourceSize.y/2 : sourcePosition.y + sourceSize.y/2 - targetPosition.y + targetSize.y/2
				);
				
				if (overlap.x < overlap.y) {
					//  Right collision
					if (targetPosition.x < sourcePosition.x) {
						outputResults.collisionRight = true;
					} else {
					//  Left collision
						outputResults.collisionLeft = true;
					}
				} else {
					if (targetPosition.y < sourcePosition.y) {
						//  Top collision
						outputResults.collisionUp = true;
					} else {
						//  Bottom collision
						outputResults.collisionDown = true;
					}
				}
			}
			
			return outputResults;
		}
};

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
		bool IS_IN_AIR_FROM_JUMPING = false;
		bool IS_SPRINTING = false;
		bool IS_SPRINTING_TRIGGERED = false;
		bool IS_SKIDDING = false;
		bool IS_SKIDDING_TRIGGERED = false;
		bool IS_CROUCHING = false;
		bool IS_CROUCHING_TRIGGERED = false;
		bool IS_UNCROUCHING_TRIGGERED = false;
		bool UNCROUCH_BLOCKED = false;
		bool HEAD_HIT_OBJECT_TRIGGERED = false;
		bool DAMAGE_TRIGGERED = false;
		bool ENEMY_DEFEAT_TRIGGERED = false;
		bool COIN_COLLECTED_TRIGGERED = false;
		bool HEART_COLLECTED_TRIGGERED = false;
		bool LIFE_COLLECTED_TRIGGERED = false;
		bool GOAL = false;
		bool GOAL_TRIGGERED = false;
		size_t JUMP_BUFFER = 0;
		size_t INVINCIBILITY_FRAMES = 0;
		
		double DEATH_TIME = 0.0;
		
		double GROUND_TIME = 0.0;
		
		double HEALTH = 0.0;
		
		bool FACING_DIRECTION = true;  //  true is for rightwards facing
		
		Vec2 HITBOX;
		
		Vec2 LAST_SAFE_POSITION;
		
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
		inline bool on_ground() const {
			return ON_GROUND;
		}
		inline bool is_jumping() const {
			return IS_JUMPING;
		}
		inline bool is__in_air_from_jumping() const {
			return IS_IN_AIR_FROM_JUMPING;
		}
		inline bool is_sprinting() const {
			return IS_SPRINTING;
		}
		inline size_t jump_frames() const {
			return JUMP_BUFFER;
		}
		inline size_t invincibility_frames() const {
			return INVINCIBILITY_FRAMES;
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
		inline bool is_skidding() const {
			return IS_SKIDDING;
		}
		inline bool is_skidding_triggered() const {
			return IS_SKIDDING_TRIGGERED;
		}
		inline bool is_crouching() const {
			return IS_CROUCHING;
		}
		inline bool is_crouching_triggered() const {
			return IS_CROUCHING_TRIGGERED;
		}
		inline bool is_uncrouching_triggered() const {
			return IS_UNCROUCHING_TRIGGERED;
		}
		inline bool uncrouch_blocked() const {
			return UNCROUCH_BLOCKED;
		}
		inline bool head_hit_object_triggered() const {
			return HEAD_HIT_OBJECT_TRIGGERED;
		}
		inline bool is_facing_left() const {
			return !FACING_DIRECTION;
		}
		inline bool is_facing_right() const {
			return FACING_DIRECTION;
		}
		inline Vec2 hitbox() const {
			return HITBOX;
		}
		inline bool damage_triggered() const {
			return DAMAGE_TRIGGERED;
		}
		inline bool enemy_defeat_triggered() const {
			return ENEMY_DEFEAT_TRIGGERED;
		}
		inline bool coin_collected_triggered() const {
			return COIN_COLLECTED_TRIGGERED;
		}
		inline bool heart_collected_triggered() const {
			return HEART_COLLECTED_TRIGGERED;
		}
		inline bool goal() const {
			return GOAL;
		}
		inline bool goal_triggered() const {
			return GOAL_TRIGGERED;
		}
		inline double health() const {
			return HEALTH;
		}
		inline double death_time() const {
			return DEATH_TIME;
		}
		
		Vec2 baseHitbox;
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
		array<bool, 6> constInput = array<bool, 6>();
		
		short behaviorType;
		
		//  Takes a list of booleans as input.
		Entity& receiveInput(const std::array<bool, 6>& booleans) {
			UP_TRIGGERED = false;
			LEFT_TRIGGERED = false;
			DOWN_TRIGGERED = false;
			RIGHT_TRIGGERED = false;
			JUMP_TRIGGERED = false;
			SPRINT_TRIGGERED = false;
			IS_CROUCHING_TRIGGERED = false;
			IS_UNCROUCHING_TRIGGERED = false;
			
			if (INVINCIBILITY_FRAMES > 0) {
				--INVINCIBILITY_FRAMES;
			}
			
			if (ON_GROUND) {
				if (GROUND_TIME >= 0.2) {
					GROUND_TIME = 0.0;
					if (behaviorType == EntityBehaviorTypes::Player) {
						LAST_SAFE_POSITION = position;
					}
				}
				if (DOWN) {
					if (!IS_CROUCHING) {
						IS_CROUCHING_TRIGGERED = true;
					}
					IS_CROUCHING = true;
				} else {
					if (!UNCROUCH_BLOCKED) {
						if (IS_CROUCHING) {
							IS_UNCROUCHING_TRIGGERED = true;
						}
						IS_CROUCHING = false;
					}
				}
			}
			
			HITBOX = baseHitbox * Vec2(1.0, 1.0 - 0.5*IS_CROUCHING);
			if (IS_CROUCHING_TRIGGERED) {
				position.y -= baseHitbox.y/4;
			} else if (IS_UNCROUCHING_TRIGGERED) {
				position.y += baseHitbox.y/4;
			}
			
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
			if (booleans[4] || (behaviorType == EntityBehaviorTypes::Player && booleans[0])) {
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
			ENEMY_DEFEAT_TRIGGERED = false;
			COIN_COLLECTED_TRIGGERED = false;
			HEART_COLLECTED_TRIGGERED = false;
			LIFE_COLLECTED_TRIGGERED = false;
			GOAL_TRIGGERED = false;
			
			if (behaviorType == EntityBehaviorTypes::Enemy && HEALTH <= 0.0) {
				speed = 0;
				velocity = 0;
				acceleration_const = 0;
			}
			
			if (HEALTH <= 0.0) {
				DEATH_TIME += 1.0/TPS;
			}
			
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
			if (SPRINT && (LEFT || RIGHT) && !(IS_CROUCHING && ON_GROUND)) {
				if (!IS_SPRINTING) {
					IS_SPRINTING_TRIGGERED = true;
				}
				IS_SPRINTING = true;
			} else {
				IS_SPRINTING = false;
			}
			
			//  Sets the maximum move speed of the entity based on the sprint speed multiplier.
			maxSpeed = speed * (IS_SPRINTING ? sprintSpeedMultiplier : 1.0);
			
			if (ON_GROUND) {
				GROUND_TIME += 1.0/TPS;
				IS_IN_AIR_FROM_JUMPING = false;
			} else {
				GROUND_TIME = 0;
			}
			
			if (JUMP) {
				if (ON_GROUND && (autoJump || JUMP_TRIGGERED || JUMP_BUFFER != 0)) {
					IS_JUMPING_TRIGGERED = true;
					IS_IN_AIR_FROM_JUMPING = true;
					
					//  True if the entity is in a jump at the moment.
					IS_JUMPING = true;
					ON_GROUND = false;
					JUMP_BUFFER = 0;
					
					//  Calculates the addition to the player's y velocity when the player jumped.
					velocity.y += jumpForce * (velocity.x_abs() > speed*1.05 ? jumpForceSprintingMultiplier : 1.0);
				}
			} else {
				IS_JUMPING = false;
			}
			
			//  True if the player starts skidding.
			IS_SKIDDING_TRIGGERED = false;
			if (ON_GROUND && ((LEFT && !RIGHT && !(IS_CROUCHING && ON_GROUND) && velocity.x > speed*1.05) || (RIGHT && !LEFT && !(IS_CROUCHING && ON_GROUND) && velocity.x < -speed*1.05))) {
				if (!IS_SKIDDING) {
					IS_SKIDDING_TRIGGERED = true;
				}
				//  True if the player is currently skidding.
				IS_SKIDDING = true;
			} else if (!ON_GROUND || IS_CROUCHING || LEFT == RIGHT || (LEFT && velocity.x <= 0.0 || RIGHT && velocity.x >= 0.0)) {
				IS_SKIDDING = false;
			}
			
			//  Math and control structures that control how to apply speed to velocity.
			if (!snapToSpeed || velocity.x_abs() > maxSpeed) {
				if (LEFT && !RIGHT && !(IS_CROUCHING && ON_GROUND) && velocity.x > -maxSpeed) {
					//  This pushes the player leftwards.
					acceleration.x -= (IS_SKIDDING ? 1.0 - skidMultiplier : 1.0)*maxSpeed*(ON_GROUND ? (velocity.x_abs() > speed ? 2.2 : 1.8) : velocity.x_abs() > speed ? 0.7 : 1.6);
				}
				if (RIGHT && !LEFT && !(IS_CROUCHING && ON_GROUND) && velocity.x < maxSpeed) {
					//  This pushes the player rightwards.
					acceleration.x += (IS_SKIDDING ? 1.0 - skidMultiplier : 1.0)*maxSpeed*(ON_GROUND ? (velocity.x_abs() > speed ? 2.2 : 1.8) : velocity.x_abs() > speed ? 0.7 : 1.6);
				}
			} else {
				//  If the player's speed snaps, this sets their speed to 0.0 when they are below their maximum speed.
				velocity.x = 0.0;
				if (LEFT && !RIGHT && !(IS_CROUCHING && ON_GROUND)) {
				//  If the player's speed snaps, this sets their speed to max towards the left.
					velocity.x = -maxSpeed;
				}
				if (RIGHT && !LEFT && !(IS_CROUCHING && ON_GROUND)) {
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
				velocity.x *= exp(-frictionCoefficient*((LEFT == RIGHT) && !IS_CROUCHING && velocity.x_abs() < maxSpeed/2 ? 4 : 1.0)*(ON_GROUND ? 1.0 : frictionCoefficientAirMultiplier)/TPS);
			} else {
				velocity.x = 0.0;
			}
			velocity.y *= exp(-dragCoefficient*(IS_JUMPING && velocity.y > 0 ? dragCoefficientJumpingMultiplier : 1.0)/TPS);
			
			//  This applies velocity to position.acceleration_const
			position += velocity/TPS;
			
			//  This resets acceleration to acceleration_const.
			acceleration = acceleration_const;
			
			if (position.x < -0.3 + HITBOX.x/2) {
				position.x = -0.3 + HITBOX.x/2;
				if (velocity.x < 0) {
					velocity.x = 0;
				}
			}
			
			if (ON_GROUND) {
				if (LEFT && !RIGHT) {
					FACING_DIRECTION = false;
				} else if (RIGHT && !LEFT) {
					FACING_DIRECTION = true;
				}
			}
			
			ON_GROUND = false;
			ON_GROUND_TRIGGERED = false;
			UNCROUCH_BLOCKED = false;
			HEAD_HIT_OBJECT_TRIGGERED = false;
			DAMAGE_TRIGGERED = false;
			
			return *this;
		}
		
		double minHealth = 0;
		double maxHealth = 1;
		
		size_t maximumInvincibilityFrames = 0;
		
		Entity& heal(const double healAmount = 1.0) {
			HEALTH += healAmount;
			if (HEALTH > maxHealth) {
				HEALTH = maxHealth;
			}
			
			return *this;
		}
		
		Entity& damage(const double healAmount = 1.0, const bool overrideInvincibility = false) {
			if (HEALTH > 0 && (overrideInvincibility || INVINCIBILITY_FRAMES == 0)) {
				DAMAGE_TRIGGERED = true;
				
				HEALTH -= healAmount;
				INVINCIBILITY_FRAMES = maximumInvincibilityFrames;
				if (HEALTH < minHealth) {
					HEALTH = minHealth;
				}
			}
			
			return *this;
		}
		
		Entity& resolveBlockCollision(const TileMap& inputTileMap) {
			const array<array<size_t, 2>, 2> entityIndexRangeContext = inputTileMap.resolveIndexRangeContext(position, HITBOX);
			
			for (size_t Y = entityIndexRangeContext[0][1]; Y < entityIndexRangeContext[1][1]; ++Y) {
				for (size_t X = entityIndexRangeContext[0][0]; X < entityIndexRangeContext[1][0]; ++X) {
					if (IS_CROUCHING && inputTileMap.getTileCopy(X,Y).isSolid()) {
						if (CollisionContext::resolve(position, HITBOX, Vec2(X,Y - HITBOX.y/2) + 0.5, 1.0).collisionUp) {
							if (position.y < Y + 0.5 + HITBOX.y/2) {
								UNCROUCH_BLOCKED = true;
							}
						}
					}
					
					const CollisionContext currentTileCollision = CollisionContext::resolve(position, HITBOX, Vec2(X,Y) + 0.5, 1.0);
					if (currentTileCollision.collision) {
						if (behaviorType == EntityBehaviorTypes::Player && inputTileMap.getTileCopy(X,Y).isGoal()) {
							if (!GOAL) {
								GOAL_TRIGGERED = true;
							}
							GOAL = true;
						} else if (behaviorType == EntityBehaviorTypes::Player && inputTileMap.getTileCopy(X,Y).isHazard()) {
							damage(1.0);
							if (HEALTH > 0.0) {
								if (behaviorType == EntityBehaviorTypes::Player) {
									position = LAST_SAFE_POSITION;
								}
							}
							velocity = 0.0;
						} else if (inputTileMap.getTileCopy(X,Y).isSolid() || (behaviorType == EntityBehaviorTypes::Enemy && inputTileMap.getTileCopy(X,Y).isHazard())) {
							if (currentTileCollision.collisionLeft && !(inputTileMap.getTileCopy(X + 1,Y).isSolid() || (behaviorType == EntityBehaviorTypes::Enemy && inputTileMap.getTileCopy(X + 1,Y).isHazard()))) {
								if (behaviorType == EntityBehaviorTypes::Enemy) {
									constInput[1] = false;
									constInput[3] = true;
								}
								position.x = X + 1.0 + HITBOX.x/2;
								velocity.x = 0;
							}
							if (currentTileCollision.collisionRight && !(inputTileMap.getTileCopy(X - 1,Y).isSolid() || (behaviorType == EntityBehaviorTypes::Enemy && inputTileMap.getTileCopy(X - 1,Y).isHazard()))) {
								if (behaviorType == EntityBehaviorTypes::Enemy) {
									constInput[3] = false;
									constInput[1] = true;
								}
								position.x = X - HITBOX.x/2;
								velocity.x = 0;
							}
							if (currentTileCollision.collisionUp) {
								position.y = Y - HITBOX.y/2;
								velocity.y *= velocity.y > 0 ? -0.2 : 1;
								HEAD_HIT_OBJECT_TRIGGERED = true;
							}
							if (currentTileCollision.collisionDown) {
								position.y = Y + 1.0 + HITBOX.y/2;
								velocity.y = 0;
								if (!ON_GROUND) {
									ON_GROUND_TRIGGERED = true;
								}
								ON_GROUND = true;
							}
						}
					}
				}
			}
			return *this;
		}
		
		Entity& resolveEntityCollision(Entity& inputEntity) {
			const CollisionContext currentEntityCollision = CollisionContext::resolve(position, HITBOX, inputEntity.position, inputEntity.hitbox());
			if (currentEntityCollision.collision) {
				if (inputEntity.behaviorType == EntityBehaviorTypes::Enemy) {
					if (behaviorType == EntityBehaviorTypes::Enemy) {
						if (currentEntityCollision.collisionLeft) {
							constInput[1] = false;
							constInput[3] = true;
							position.x = inputEntity.position.x + inputEntity.hitbox().x/2 + HITBOX.x/2;
							velocity.x = 0;
						}
						if (currentEntityCollision.collisionRight) {
							constInput[3] = false;
							constInput[1] = true;
							position.x = inputEntity.position.x - inputEntity.hitbox().x/2 - HITBOX.x/2;
							velocity.x = 0;
						}
					} else if (behaviorType == EntityBehaviorTypes::Player && inputEntity.health() > 0) {
						if (currentEntityCollision.collisionDown) {
							TOTAL_SCORE += ENEMY_DEFEAT_SCORE;
							inputEntity.damage(1);
							ENEMY_DEFEAT_TRIGGERED = true;
							position.y = inputEntity.position.y + inputEntity.hitbox().y + HITBOX.y/2;
							velocity.y = jumpForce*jumpForceSprintingMultiplier;
							IS_JUMPING = true;
							IS_IN_AIR_FROM_JUMPING = true;
						} else if (currentEntityCollision.collisionLeft) {
							damage(1);
							velocity = Vec2(6, 12);
						} else if (currentEntityCollision.collisionRight) {
							damage(1);
							velocity = Vec2(-6, 12);
						} else if (currentEntityCollision.collisionUp) {
							damage(1);
							velocity.y *= velocity.y > 0.0;
						}
					}
				}
			}
			
			return *this;
		}
		
		Entity& resolveEntityCollision(vector<Entity>& inputEntities) {
			for (Entity& collisionEntity : inputEntities) {
				if (this == &collisionEntity) {
					continue;
				}
				resolveEntityCollision(collisionEntity);
			}
			return *this;
		}
		
		Entity& resolveCollectableCollision(Collectable& inputCollectable) {
			if (behaviorType == EntityBehaviorTypes::Player && !inputCollectable.collected) {
				const CollisionContext currentCollectableCollision = CollisionContext::resolve(position, HITBOX, inputCollectable.position, 0.5);
				if (currentCollectableCollision.collision) {
					if (inputCollectable.isCoin()) {
						++TOTAL_COINS;
						TOTAL_SCORE += COIN_SCORE;
						while (TOTAL_COINS >= 100) {
							TOTAL_SCORE += LIFE_SCORE;
							LIFE_COLLECTED_TRIGGERED = true;
							++TOTAL_LIVES;
							TOTAL_COINS -= 100;
						}
						COIN_COLLECTED_TRIGGERED = true;
						inputCollectable.collected = true;
					} else if (inputCollectable.isHeart()) {
						TOTAL_SCORE += HEART_SCORE;
						heal(1.0);
						HEART_COLLECTED_TRIGGERED = true;
						inputCollectable.collected = true;
					}
				}
			}
			
			return *this;
		}
		
		Entity& resolveCollectableCollision(vector<Collectable>& inputCollectables) {
			if (behaviorType == EntityBehaviorTypes::Player) {
				for (Collectable& collisionCollectable : inputCollectables) {
					resolveCollectableCollision(collisionCollectable);
				}
			}
			return *this;
		}
	
		//  The default Entity constructor
		Entity(
			const short inputBehaviorType = EntityBehaviorTypes::Default,
			const double inputMaxHealth = 1.0,
			const Vec2& inputPosition = {0.0, 0.0},
			const Vec2& inputHitbox = {1.0, 1.0},
			const Vec2& inputAccelerationConst = {0.0, -36.0},
			const double& inputSpeed = 8,
			const double& inputJumpForce = 8,
			const double& inputFrictionCoefficient = 2.0,
			const double& inputDragCoefficient = 2
		) :
			behaviorType(inputBehaviorType),
			maxHealth(inputMaxHealth),
			HEALTH(inputMaxHealth),
			position(inputPosition),
			baseHitbox(inputHitbox),
			acceleration_const(inputAccelerationConst),
			speed(inputSpeed),
			jumpForce(inputJumpForce),
			frictionCoefficient(inputFrictionCoefficient),
			dragCoefficient(inputDragCoefficient)
		{};
		
		AnimationState animation_state;
		
		Entity& tickAnimation(const size_t& TPS) {
			if (behaviorType == EntityBehaviorTypes::Player && animation_state.getAnimationID() == "walking") {
				animation_state.tick(1.0/TPS * ON_GROUND * (velocity.x_abs() > speed ? 2 : 1.0));
			} else {
				animation_state.tick(1.0/TPS);
			}
			return *this;
		}
		
		Entity& updateAnimationState() {
			string finalState;
			
			if (HEALTH <= 0) {
				finalState = "death";
			} else if (IS_CROUCHING) {
				finalState = "crouching";
			} else if (IS_SKIDDING) {
				finalState = "skidding";
			} else if (IS_IN_AIR_FROM_JUMPING) {
				finalState = "jumping";
			} else if (!(velocity.x_abs() < speed/15 && ON_GROUND) || LEFT != RIGHT) {
				finalState = "walking";
			} else {
				finalState = "idle";
			}
			
			if (animation_state.getAnimationID() != finalState) {
				animation_state.setAnimationID(finalState);
			}
			
			return *this;
		}
		
};