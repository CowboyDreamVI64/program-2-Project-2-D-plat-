#include "includes/all.hpp"

//  You guys can write whatever code you want here as long as it works; if you
//  want me to move it to somewhere proper, feel free to let me know.















//  This namespace will contain every state of the game, like levels and menus.
namespace frame {
	void start_application();
	void test_level();
	void end_application();
}

int main() {
	//  This prepares random number generation.
	srand(time(0));
	
	//  This starts the first state.
	frame::start_application();
	
	return 0;
}

namespace frame {
	//  This state controls what happens when the application starts.
	void start_application() {
		//  This loads font data in the format {fontID, fileDirectory}.
		//  NOTE: there is no .ttf/.otf file in assets/fonts/ yet -- drop one in there and update the
		//  path below (it must be named to match) or the HUD's text will silently fail to render.
		loadAllFonts(fonts, {
		    {"main", "assets/fonts/main.ttf"}
		});
		
		//  This loads textures in the format {textureID, fileDirectory}.
		loadAllTextures(textures, {
			{"player.idle", "assets/textures/player/idle.png"},
			{"player.crouch", "assets/textures/player/crouch.png"},
			{"player.walk.0", "assets/textures/player/walk0.png"},
			{"player.walk.1", "assets/textures/player/walk1.png"},
			{"player.walk.2", "assets/textures/player/walk2.png"},
			{"player.jump", "assets/textures/player/jump.png"},
			{"player.skid", "assets/textures/player/skid.png"},
			{"player.die", "assets/textures/player/die.png"},
			{"enemy.knight.walk.0", "assets/textures/knight/walk0.png"},
			{"enemy.knight.walk.1", "assets/textures/knight/walk1.png"},
			{"enemy.knight.walk.2", "assets/textures/knight/walk2.png"},
			{"enemy.knight.walk.3", "assets/textures/knight/walk3.png"},
			{"enemy.knight.walk.4", "assets/textures/knight/walk4.png"},
			{"enemy.knight.squish.0", "assets/textures/knight/squish0.png"},
			{"enemy.knight.squish.1", "assets/textures/knight/squish1.png"},
			{"enemy.knight.squish.2", "assets/textures/knight/squish2.png"},
			{"enemy.knight.squish.3", "assets/textures/knight/squish3.png"},
			{"sky", "assets/textures/background/sky.png"},
			{"dirt", "assets/textures/tiles/dirt.png"},
			{"grass", "assets/textures/tiles/grass.png"},
			{"horizontal_spike", "assets/textures/tiles/horizontal_spike.png"},
			{"vertical_spike", "assets/textures/tiles/vertical_spike.png"},
			{"hills1", "assets/textures/background/hills1.png"},
			{"hills2", "assets/textures/background/hills2.png"},
			{"clouds", "assets/textures/background/clouds.png"},
			{"mountains", "assets/textures/background/mountains.png"},
			{"sun", "assets/textures/sun.png"},
		    {"ui.heart", "assets/textures/heart.png"},
		    {"ui.coin", "assets/textures/coin/0.png"},
			{"ui.player", "assets/textures/player/head.png"}
		});
		
		//  This loads sound data in the format {soundBufferID, fileDirectory}.
		loadAllSoundBuffers(sound_buffers, {
			{"jump", "assets/sounds/jump.ogg"},
			{"skid", "assets/sounds/skid.ogg"},
			{"block_hit", "assets/sounds/block_hit.ogg"},
			{"damage", "assets/sounds/damage.ogg"},
			{"fatal_damage", "assets/sounds/fatal_damage.ogg"},
			{"enemy_damage", "assets/sounds/enemy_damage.ogg"},
			{"coin", "assets/sounds/coin.ogg"},
			{"power_up", "assets/sounds/power_up.ogg"},
			{"one_up", "assets/sounds/one_up.ogg"}
		});
		
		//  This stops everything from looking blurry.
		textures.setSmooth(false);
		fonts.setSmooth(false);
		
		//  These set the game icon and open the game window.
		game.setIcon(textures["player.idle"]);
		game.open();
		
		//  This clears everything (like sprites, music, and sounds) from the global buffers EXCEPT for textures, sound buffers, and fonts.
		clearall({Omit::Textures, Omit::SoundBuffers, Omit::Fonts});
		
		loadPlayerStats(playerStats);
		
		//  If the game window is stable, the state moves to test_level.
		if (game.stableState()) {
			test_level();
		}
		return;
	}
	
	//  This state is a test level.
	void test_level() {
		//  This gives us a custom boolean to set to false at any time to change the state.
		bool frameState = true;
		
		//  This gives us a custom boolean to set to true when we want the window to close instead of moving into a different state.
		bool closeWindow = false;
		
		//  This is the number of physics ticks performed per second.
		const size_t tps = 165;
		
		//  This is just the amount of time that passes between ticks.
		const double DELTA = 1.0/tps;
		
		Level level("level1");
		level.loadLevel();
		
		//  This starts a stopwatch that accumulates over the main window loop then gets analyzed in the main game loop/physics to check how many times the physics should be calculated.
		fstopwatches.start("accumulated_game_time");
		fstopwatches.start("game_freeze_time").pause();
		fstopwatches.start("death_time").pause();
		
		//  This adds a player sprite and a sky sprite.
		sprites.add("player", textures["player.idle"], 0.0).add_tag("level.darken").add_tag("player_sprite");
		sprites.add("enemy.knight", textures["enemy.knight.walk.0"], 0.1).add_tag("level_darken").add_tag("repeated_sprite").add_tag("repeated_sprite.entity").add_tag("repeated_sprite.entity.knight");
		sprites.add("ground", textures["dirt"], -1.0).add_tag("level.darken").add_tag("repeated_sprite").add_tag("repeated_sprite.tile").add_tag("repeated_sprite.tile.ground");
		sprites.add("spike", textures["vertical_spike"], -1.0).add_tag("level.darken").add_tag("repeated_sprite").add_tag("repeated_sprite.tile").add_tag("repeated_sprite.tile.spike");
		sprites.add("hills1", textures["hills1"], -2.0).add_tag("level.darken");
		sprites.add("hills2", textures["hills2"], -3.0).add_tag("level.darken");
		sprites.add("clouds1", textures["clouds"], -4.0).setOpacity(0.85).add_tag("level.darken");
		sprites.add("mountains", textures["mountains"], -5.0);
		sprites.add("clouds2", textures["clouds"], -6.0).setOpacity(0.4);
		sprites.add("sun", textures["sun"], -7.0);
		sprites.add("sky", textures["sky"], -8.0);
		
		//  This adds a new sound list to push sounds into called "jump."
		sound_lists.add("sound_effects");
		sound_lists["sound_effects"].setVolume(sounds.getVolume());
		
		sounds.play("skid", sound_buffers["skid"], 0.0, true, true);
		
		//  This plays music.
		musics.play("music", reinterpret_cast<const char*>(assets[level.musicPath].data()), assets[level.musicPath].size(), 0.3, true, true)["music"].setLoopPoints_sec(level.musicLoopStart, musics["music"].getDuration_sec(), false).setVolume(level.musicVolume * sounds.getVolume());
		
		//  This sets the camera to width 24 and position (0, 0).
		ViewPort camera = ViewPort(24, {0.0, 0.0});
		//  This sets the camera's position to half of its dimensions (this offsets the camera towards the top-right by half of its lengths).
		camera.position = camera.getPerceivedDimensions(game.resolution)/2;
		
		unordered_map<string, ParallaxInstruction> parallaxSprites = {
			{ "hills1", ParallaxInstruction("hills1", "hills1", 5, {32, 18}, 0.0, true, false).setApparentPosition({16, 9}, camera.position).fitLoopToViewPort(camera) },
			{ "hills2", ParallaxInstruction("hills2", "hills2", 10, {32, 18}, 0.0, true, false).setApparentPosition({16, 9}, camera.position).fitLoopToViewPort(camera) },
			{ "clouds1", ParallaxInstruction("clouds1", "clouds", 12, {48, 21.6}, 0.0, true, true).setApparentPosition({16, 10.8}, camera.position).fitLoopToViewPort(camera) },
			{ "mountains", ParallaxInstruction("mountains", "mountains", 35, {48, 27}, 0.0, true, false).setApparentPosition({24, 13.5}, camera.position).fitLoopToViewPort(camera) },
			{ "clouds2", ParallaxInstruction("clouds2", "clouds", 45, {24, 10.8}, 0.0, true, true).setApparentPosition({12, 5.4}, camera.position).fitLoopToViewPort(camera) },
			{ "sun", ParallaxInstruction("sun", "sun", 500, {56, 56}, 0.0, false, false).setApparentPosition({8, 6}, camera.position).fitLoopToViewPort(camera) },
			{ "sky", ParallaxInstruction("sky", "sky", 500, {64, 36}, 0.0, true, false).setApparentPosition({32, 18}, camera.position).fitLoopToViewPort(camera) }
		};
		
		//  This creates a player entity.
		Entity player = Entity(EntityBehaviorTypes::Player, 3.0, level.playerStartPosition + Vec2(0.0, 1.0), {0.7, 1.8}, {0.0, -56.0}, 8, 14.2, 1.6, 2);
		player.accelerationConstJumpingMultiplier.y = 0.32;
		player.maxJumpBufferFrames = tps/3;
		player.skidMultiplier = 0.35;
		player.autoJump = false;
		player.maximumInvincibilityFrames = 1.5*tps;
		player.animation_state = AnimationState({
			{ "idle",
				Animation({
					AnimationFrame("player.idle", 1.0, {1.0, 2.0})
				}, true)
			},
			{ "walking",
				Animation({
					AnimationFrame("player.walk.0", 0.13, {1.0, 2.0}),
					AnimationFrame("player.walk.1", 0.13, {1.0, 2.0}),
					AnimationFrame("player.walk.2", 0.13, {1.0, 2.0})
				}, true)
			},
			{ "crouching",
				Animation({
					AnimationFrame("player.crouch", 1.0, {1.0, 2.0}, {0.0, 0.5})
				}, true)
			},
			{ "jumping",
				Animation({
					AnimationFrame("player.jump", 1.0, {1.0, 2.0})
				}, true)
			},
			{ "skidding",
				Animation({
					AnimationFrame("player.skid", 1.0, {1.0, 2.0})
				}, true)
			},
			{ "death",
				Animation({
					AnimationFrame("player.die", 1.0, {1.0, 1.0})
				}, true)
			}
		}, "idle");
		
		//  Here for debugging purposes.
		bool mouseDraggingPlayer = false;
		bool JKEY = false, LKEY = false, IKEY = false, OKEY = false, UKEY = false;
		
		//  This builds every HUD sprite/text element (coin/lives icons, heart row, score text, etc)
		//  now that the required textures/font have been loaded and the sprite/text containers have
		//  been freshly cleared for this state.
		hud.build();
		
		while (game.stableState(frameState)) {
			//  This checks if the window is trying to close.
			while (optional frameEvent = game.window->pollEvent()) {
				//  If the window IS trying to close, this will evaluate to true.
				if (game.pollForClosure(frameEvent)) {
					frameState = false;
					closeWindow = true;
				}
			}
			
			//  This checks if the F11 key was pressed
			if (game.pollForF11()) {
				game.toggleFullscreen();
			}
			
			//  This checks if the Escape key was pressed
			if (game.pollForEscape()) {
				frameState = false;
				closeWindow = true;
			}
			
			//  This advances the accumulated game time by the delta of the framerate.
			fstopwatches.elapse(1.0f/game.framerate);
			
			//  This ticks the game physics depending on how much accumulated game time there is.
			while (fstopwatches["accumulated_game_time"].frame >= 1.0f/tps) {
				fstopwatches["accumulated_game_time"].subtract(1.0f/tps);
				if (fstopwatches["game_freeze_time"].frame <= 0.0f) {
					
					
	//  ------------------------------ Backend Game Loop Starts Here ------------------------------
					//  This takes the default keybind inputs and passes them to the player entity.
					if (player.health() > 0) {
						player.receiveInput(game, defaultKeyBinds);
					}
					
					//  This ticks the movement physics of the player entity.
					player.tickPhysics(tps);
					
					if (player.health() > 0) {
						player.resolveBlockCollision(level.tilemap);
						player.resolveEntityCollision(level.entities);
					}
					
					for (Entity& entity : level.entities) {
						entity.receiveInput();
						entity.tickPhysics(tps);
						entity.resolveBlockCollision(level.tilemap);
						entity.resolveEntityCollision(player);
						if (player.health() > 0) {
							entity.resolveEntityCollision(level.entities);
						}
					}
					
					if (player.health() <= 0) {
						if (player.damage_triggered()) {
							musics["music"].pause();
							fstopwatches["game_freeze_time"].set(0.6);
							player.acceleration_const.y = -40;
							player.velocity = Vec2(0, 18);
							sound_lists["sound_effects"].add(sound_buffers["fatal_damage"], 0.7f, 0.0f, 1, 1.0, true);
							fstopwatches["accumulated_game_time"].set(0);
						}
						if (!player.damage_triggered()) {
							fstopwatches["death_time"].add(1.0/tps);
						}
						player.velocity.x = 0;
					}
					
					//  ------------------------------ TEMPORARY player stat debug controls ------------------------------
					//  These let you see the HUD respond to stat changes before collision/collectibles/enemies exist to
					//  actually trigger them. Delete this block once those systems are wired up to call playerStats
					//  directly (e.g. a Coin's applyEffect() calling playerStats.addCoins(), a Hazard tile calling
					//  playerStats.damage(), etc).
				    
				    
				    if (game.pollForKey(sf::Keyboard::Key::J) && !JKEY) { playerStats.addCoins(1); }
				    JKEY = game.pollForKey(sf::Keyboard::Key::J);
				    
				    if (game.pollForKey(sf::Keyboard::Key::L) && !LKEY) { playerStats.damage(1); }
				    LKEY = game.pollForKey(sf::Keyboard::Key::L);
				    
				    if (game.pollForKey(sf::Keyboard::Key::I) && !IKEY) { playerStats.heal(1); }
				    IKEY = game.pollForKey(sf::Keyboard::Key::I);
				    
				    if (game.pollForKey(sf::Keyboard::Key::O) && !OKEY) { playerStats.addPoints(100); }
				    OKEY = game.pollForKey(sf::Keyboard::Key::O);
				    
				    if (game.pollForKey(sf::Keyboard::Key::U) && !UKEY) {
				        playerStats.damage(playerStats.health);
				        playerStats.loseLife();
				    }
				    UKEY = game.pollForKey(sf::Keyboard::Key::U);
					//  ------------------------------ TEMPORARY player stat debug controls end ------------------------------
					// This whole block is new — delete it once real collision/collectible code is calling playerStats directly.
					
	//  ------------------------------ Backend Game Loop Ends Here ------------------------------
					
					
	//  ------------------------------ Frontend Game Loop Starts Here ------------------------------
					if (player.is_jumping_triggered()) {
						sound_lists["sound_effects"].add(sound_buffers["jump"], 0.4f, 0.0f, 1, 1.0, true);
					}
					if (player.head_hit_object_triggered()) {
						sound_lists["sound_effects"].add(sound_buffers["block_hit"], 0.4f, 0.0f, 1, 1.0, true);
					}
					if (player.damage_triggered() && player.health() > 0.0) {
						sound_lists["sound_effects"].add(sound_buffers["damage"], 0.6f, 0.0f, 1, 1.0, true);
					}
					if (player.enemy_defeat_triggered()) {
						sound_lists["sound_effects"].add(sound_buffers["enemy_damage"], 1.0f, 0.0f, 1, 1.0, true);
					}
					
					parallaxSprites["clouds1"].setActualPosition(parallaxSprites["clouds1"].getActualPosition() + Vec2(2, 0)/tps);
					parallaxSprites["clouds2"].setActualPosition(parallaxSprites["clouds2"].getActualPosition() + Vec2(2, 0)/tps);
					
					player.tickAnimation(tps);
					player.updateAnimationState();
					
					for (Entity& entity : level.entities) {
						entity.tickAnimation(tps);
						entity.updateAnimationState();
					}
	//  ------------------------------ Frontend Game Loop Ends Here ------------------------------
					
					
				}
				fstopwatches["game_freeze_time"].subtract(1.0f/tps);
			}
			
//  ------------------------------ Frontend Program Loop Starts Here ------------------------------	
			level.cleanEntities();

			if (fstopwatches["death_time"].frame > 0 && player.health() <= 0.0 && !player.damage_triggered() && !musics.exists("death_music")) {
				musics.play("death_music", reinterpret_cast<const char*>(assets["assets/sounds/music/death.ogg"].data()), assets["assets/sounds/music/death.ogg"].size(), sounds.getVolume()*0.7, true, false);
			}

			//  This centers the camera position to the player position without the camera clipping out of bounds.
			if (!mouseDraggingPlayer && player.health() > 0) {
				camera.position = player.position + Vec2(0.0, player.is_crouching() ? player.hitbox().y/2 : 0.0);
				
				if (player.position.x < camera.getPerceivedDimensions(game.resolution).x/2) {
					camera.position.x = camera.getPerceivedDimensions(game.resolution).x/2;
				}
				if (camera.position.x + camera.getPerceivedDimensions(game.resolution).x/2 > level.tilemap.maxWidth) {
					camera.position.x = level.tilemap.maxWidth - camera.getPerceivedDimensions(game.resolution).x/2;
				}
				
				if (player.position.y < camera.getPerceivedDimensions(game.resolution).y/2) {
					camera.position.y = camera.getPerceivedDimensions(game.resolution).y/2;
				}
				if (camera.position.y + camera.getPerceivedDimensions(game.resolution).y/2 > level.tilemap.maxHeight) {
					camera.position.y = level.tilemap.maxHeight - camera.getPerceivedDimensions(game.resolution).y/2;
				}
				
			}
			
			if (sprites["player"].mouseLeftHeld(game)) {
				mouseDraggingPlayer = true;
			} else if (!game.mouseLeftHeld()) {
				mouseDraggingPlayer = false;
			}
			if (mouseDraggingPlayer) {
				player.velocity = (camera.getPerceivedDimensions()*game.getMousePosition()*Vec2(1.0, -0.5) + camera.position - player.position)*30;
				player.position = camera.getPerceivedDimensions()*game.getMousePosition()*Vec2(1.0, -0.5) + camera.position;
			}
			
			const AnimationFrame& playerAnimationFrame = player.animation_state.getAnimationFrame();
			camera.setInViewport(game, sprites["player"].setTexture(textures[playerAnimationFrame.TextureID]), player.position + playerAnimationFrame.offset*Vec2(player.is_facing_right() ? 1.0 : -1.0, 1.0), playerAnimationFrame.size*Vec2(player.is_facing_right() ? 1.0 : -1.0, 1.0));
			
			for (const auto& currentPS : parallaxSprites) {
				camera.setInViewport(game, sprites[currentPS.second.spriteID], currentPS.second.getApparentPosition(camera.position), currentPS.second.getApparentSize());
			}
			
			
			sounds["skid"].setVolume(player.is_skidding() ? 1.0 : 0.0);
			
			//  This clears the "jump" sound list of inactive sounds.
			if (sound_lists["sound_effects"].inactive()) {
				sound_lists["sound_effects"].clean();
			}
			//  This shifts where you hear the sounds in the "jump" sound list.
			sound_lists["sound_effects"].setPanShift(-180*(player.position.x - camera.position.x)/64);
			
			//  This refreshes every HUD element (health hearts, coins, points, lives, game over text)
			//  to match the current playerStats.
			hud.update(playerStats);
			
			vector<ExtendedSprite*> sortedSprites = sprites.getExtendedVector();
			vector<ExtendedText*> sortedTexts = texts.getExtendedVector();
		
			//  This renders sprites and texts onto the window.
			
			array<array<size_t, 2>, 2> cameraIndexRangeContext = level.tilemap.resolveIndexRangeContext(camera.position, camera.getPerceivedDimensions(game.resolution));
			
			for (ExtendedSprite*& spritePtr : sortedSprites) {
				if (spritePtr) {
					if (spritePtr->has_tag("level.darken")) {
						spritePtr->setTint(level.darknessTint.r/255.0, ColorChannel::Red);
						spritePtr->setTint(level.darknessTint.g/255.0, ColorChannel::Green);
						spritePtr->setTint(level.darknessTint.b/255.0, ColorChannel::Blue);
					}
					
					if (spritePtr->has_tag("player_sprite")) {
						if (player.invincibility_frames() > 0 && fmod(8.0*player.invincibility_frames()*1.0/tps, 1.0) > 0.5 && player.health() > 0) {
							spritePtr->hide();
						} else {
							spritePtr->unhide();
						}
					}
					
					if (spritePtr->has_tag("repeated_sprite")) {
						if (spritePtr->has_tag("repeated_sprite.entity")) {
							if (spritePtr->has_tag("repeated_sprite.entity.knight")) {
								for (Entity& entity : level.entities) {
									const AnimationFrame& entityAnimationFrame = entity.animation_state.getAnimationFrame();
									camera.setInViewport(game, sprites["enemy.knight"].setTexture(textures[entityAnimationFrame.TextureID]), entity.position + entityAnimationFrame.offset*Vec2(entity.is_facing_right() ? 1.0 : -1.0, 1.0), entityAnimationFrame.size*Vec2(entity.is_facing_right() ? 1.0 : -1.0, 1.0));
									game.ExtendedDraw(spritePtr);
								}
							}
						}
						if (spritePtr->has_tag("repeated_sprite.tile")) {
							for (size_t Y = cameraIndexRangeContext[0][1]; Y < cameraIndexRangeContext[1][1]; ++Y) {
								for (size_t X = cameraIndexRangeContext[0][0]; X < cameraIndexRangeContext[1][0]; ++X) {
									if (spritePtr->has_tag("repeated_sprite.tile.ground") && level.tilemap.getTileCopy(X, Y).isGround()) {
										if (!level.tilemap.getTileCopy(X, Y + 1).isSolid()) {	
											spritePtr->setTexture(textures["grass"]);
										} else {
											spritePtr->setTexture(textures["dirt"]);
										}
										camera.setInViewport(game, sprites["ground"], Vec2(X + 0.5, Y + 0.5));
										game.ExtendedDraw(spritePtr);
									} else if (spritePtr->has_tag("repeated_sprite.tile.spike") && level.tilemap.getTileCopy(X, Y).isHazard()) {
										bool flipHorizontally = false;
										bool flipVertically = false;
										
										if (level.tilemap.getTileCopy(X, Y - 1).isSolid()) {
											spritePtr->setTexture(textures["vertical_spike"]);
										} else if (level.tilemap.getTileCopy(X, Y + 1).isSolid()) {
											spritePtr->setTexture(textures["vertical_spike"]);
											flipVertically = true;
										} else if (level.tilemap.getTileCopy(X - 1, Y).isSolid()) {
											spritePtr->setTexture(textures["horizontal_spike"]);
										} else if (level.tilemap.getTileCopy(X + 1, Y).isSolid()) {
											spritePtr->setTexture(textures["horizontal_spike"]);
											flipHorizontally = true;
										} else {
											spritePtr->setTexture(textures["vertical_spike"]);
										}
										
										camera.setInViewport(game, sprites["spike"], Vec2(X + 0.5, Y + 0.5), Vec2(flipHorizontally ? -1.0 : 1.0, flipVertically ? -1.0 : 1.0));
										game.ExtendedDraw(spritePtr);
									}
								}
							}
						}
					} else {
						game.ExtendedDraw(spritePtr);
					}
				}
			}
			for (ExtendedText*& textPtr : sortedTexts) {
				if (textPtr->has_tag("level.darken")) {
					textPtr->setTint(level.darknessTint.r/255.0, ColorChannel::Red);
					textPtr->setTint(level.darknessTint.g/255.0, ColorChannel::Green);
					textPtr->setTint(level.darknessTint.b/255.0, ColorChannel::Blue);
				}
					
				game.ExtendedDraw(textPtr);
			}
			game.window->display();
//  ------------------------------ Frontend Program Loop Ends Here ------------------------------
			
		}
		
		//  This clears everything (like sprites, music, and sounds) from the global buffers EXCEPT for textures, sound buffers, and fonts.
		clearall({Omit::Textures, Omit::SoundBuffers, Omit::Fonts});
		for (auto& currentPS : parallaxSprites) {
			currentPS.second.clear();
		}
		
		//  This move to the next state (which is end_application for now).
		if (game.stableState(!closeWindow)) {
			end_application();
		} else if (closeWindow) {
			//  This move to the end_application state if the window is trying to close.
			end_application();
		}
		return;
	}
	
	//  This state controls what happens when the application ends.
	void end_application() {
		//  This closes the game window.
		game.close();
		
		//  This clears all global buffers.
		clearall();
		
		//  This saves the player's current stats (health, coins, points, lives) back to the save file
		//  so they persist the next time the game is launched.
		savePlayerStats(playerStats);
		
		return;
	}
}
