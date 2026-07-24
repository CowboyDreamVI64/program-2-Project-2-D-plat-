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
		//  This loads textures in the format {textureID, fileDirectory}.
		loadAllTextures(textures, {
			{"player", "assets/textures/player.png"},
			{"goblin", "assets/textures/Goblin.png"},
			{"sky", "assets/textures/sky.png"},
			{"ground", "assets/textures/ground.png"},
			{"hills1", "assets/textures/hills1.png"},
			{"hills2", "assets/textures/hills2.png"},
			{"clouds", "assets/textures/clouds.png"},
			{"mountains", "assets/textures/mountains.png"},
			{"sun", "assets/textures/sun.png"}
		});
		
		//  This loads sound data in the format {soundBufferID, fileDirectory}.
		loadAllSoundBuffers(sound_buffers, {
			{"jump", "assets/sounds/jump.ogg"}
		});
		
		//  This stops everything from looking blurry.
		textures.setSmooth(false);
		fonts.setSmooth(false);
		
		//  These set the game icon and open the game window.
		game.setIcon(textures["player"]);
		game.open();
		
		//  This clears everything (like sprites, music, and sounds) from the global buffers EXCEPT for textures, sound buffers, and fonts.
		clearall({Omit::Textures, Omit::SoundBuffers, Omit::Fonts});
		
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
		
		//  This starts a stopwatch that accumulates over the main window loop then gets analyzed in the main game loop/physics to check how many times the physics should be calculated.
		fstopwatches.start("accumulated_game_time");
		
		//  This adds a player sprite and a sky sprite.
		sprites.add("player", textures["goblin"], 0.0);
		sprites.add("ground", textures["ground"], 1.0);
		sprites.add("hills1", textures["hills1"], -1.0);
		sprites.add("hills2", textures["hills2"], -2.0);
		sprites.add("clouds1", textures["clouds"], -3.0).setOpacity(0.85);
		sprites.add("mountains", textures["mountains"], -4.0);
		sprites.add("clouds2", textures["clouds"], -5.0).setOpacity(0.4);
		sprites.add("sun", textures["sun"], -6.0);
		sprites.add("sky", textures["sky"], -7.0);
		
		//  This adds a new sound list to push sounds into called "jump."
		sound_lists.add("jump");
		sound_lists["jump"].setVolume(sounds.getVolume());
		
		//  This plays music.
		musics.play("music", reinterpret_cast<const char*>(assets["assets/sounds/music.ogg"].data()), assets["assets/sounds/music.ogg"].size(), 0.3, true, true)["music"].setLoopPoints_ms(2398.6, musics["music"].getDuration_ms(), false);
		
		//  This sets the camera to width 24 and position (0, 0).
		ViewPort camera = ViewPort(24, {0.0, 0.0});
		//  This sets the camera's position to half of its dimensions (this offsets the camera towards the top-right by half of its lengths).
		camera.position = camera.getPerceivedDimensions(game.resolution)/2;
		
		vector<ParallaxInstruction> parallaxSprites = {
			ParallaxInstruction("ground", "ground", 1, {1, 1}, 0.0, true, false).setApparentPosition({0.5, 0.2}, camera.position).fitLoopToViewPort(camera),
			ParallaxInstruction("hills1", "hills1", 5, {32, 18}, 0.0, true, false).setApparentPosition({16, 9}, camera.position).fitLoopToViewPort(camera),
			ParallaxInstruction("hills2", "hills2", 10, {32, 18}, 0.0, true, false).setApparentPosition({16, 9}, camera.position).fitLoopToViewPort(camera),
			ParallaxInstruction("clouds1", "clouds", 12, {48, 21.6}, 0.0, true, true).setApparentPosition({16, 10.8}, camera.position).fitLoopToViewPort(camera),
			ParallaxInstruction("mountains", "mountains", 35, {48, 27}, 0.0, true, false).setApparentPosition({24, 13.5}, camera.position).fitLoopToViewPort(camera),
			ParallaxInstruction("clouds2", "clouds", 45, {24, 10.8}, 0.0, true, true).setApparentPosition({12, 5.4}, camera.position).fitLoopToViewPort(camera),
			ParallaxInstruction("sun", "sun", 200, {12, 12}, 0.0, false, false).setApparentPosition({8, 12}, camera.position).fitLoopToViewPort(camera),
			ParallaxInstruction("sky", "sky", 500, {64, 36}, 0.0, true, false).setApparentPosition({32, 18}, camera.position).fitLoopToViewPort(camera)
		};
		
		//  This creates a player entity.
		Entity player = Entity({1.5, 1.7}, {1.0, 2.0}, {0.0, -36.0}, 8, 14.0, 1.6, 2);
		player.accelerationConstJumpingMultiplier.y = 0.5;
		player.maxJumpBufferFrames = tps/3;
		player.skidMultiplier = 0.5;
		player.autoJump = false;
		
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
				
				
//  ------------------------------ Backend Game Loop Starts Here ------------------------------
				//  This takes the default keybind inputs and passes them to the player entity.
				player.receiveInput(game, defaultKeyBinds);
				
				//  This ticks the movement physics of the player entity.
				player.tickPhysics(tps);
//  ------------------------------ Backend Game Loop Ends Here ------------------------------
				
				
//  ------------------------------ Frontend Game Loop Starts Here ------------------------------
				if (player.is_jumping_triggered()) {
					sound_lists["jump"].add(sound_buffers["jump"], 0.4f, 0.0f, 1, 1.0, true);
				}
				
				parallaxSprites[3].setActualPosition(parallaxSprites[3].getActualPosition() + Vec2(2, 0)/tps);
				parallaxSprites[5].setActualPosition(parallaxSprites[5].getActualPosition() + Vec2(2, 0)/tps);
//  ------------------------------ Frontend Game Loop Ends Here ------------------------------
				
				
			}
			
			
//  ------------------------------ Frontend Program Loop Starts Here ------------------------------	
			//  This centers the camera position to the player position without the camera clipping out of bounds.
			camera.position.x = player.position.x < camera.getPerceivedDimensions(game.resolution).x/2 ? camera.getPerceivedDimensions(game.resolution).x/2 : player.position.x;
			camera.position.y = player.position.y < camera.getPerceivedDimensions(game.resolution).y/2 ? camera.getPerceivedDimensions(game.resolution).y/2 : player.position.y;
			
			//  These resize and reposition the player and sky sprites to be able to render properly in the viewport.
			//  The player sprite renders with its center at player.position and its size being 1 x 2.
			camera.setInViewport(game, sprites["player"], player.position, {1.0, 2.0});
			
			for (size_t i = 0; i < parallaxSprites.size(); ++i) {
				ParallaxInstruction& currentPS = parallaxSprites[i];
				camera.setInViewport(game, sprites[currentPS.spriteID], currentPS.getApparentPosition(camera.position), currentPS.getApparentSize());
			}
				
			//  This clears the "jump" sound list of inactive sounds.
			if (sound_lists["jump"].inactive()) {
				sound_lists["jump"].clean();
			}
			//  This shifts where you hear the sounds in the "jump" sound list.
			sound_lists["jump"].setPanShift(-180*(player.position.x - camera.position.x)/64);
			
			//  This renders sprites onto the window (leave this true here).
			game.refresh(true, sprites);
//  ------------------------------ Frontend Program Loop Ends Here ------------------------------
			
		}
		
		//  This clears everything (like sprites, music, and sounds) from the global buffers EXCEPT for textures, sound buffers, and fonts.
		clearall({Omit::Textures, Omit::SoundBuffers, Omit::Fonts});
		for (size_t i = 0; i < parallaxSprites.size(); ++i) {
			parallaxSprites[i].clear();
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
		return;
	}
}
