#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstring>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <optional>
#include <type_traits>
#include <limits>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "helper.hpp"

namespace frame {
	void start_application();
	void test_level();
	void end_application();
}

int main() {
	srand(time(0));
	seed64(time(0));
	
	frame::start_application();
	
	return 0;
}

namespace frame {
	void start_application() {
		loadAllTextures(textures, {
			{"player", "assets/textures/player.png"},
			{"sky", "assets/textures/sky.png"}
		});
		loadAllSoundBuffers(sound_buffers, {
			{"jump", "assets/sounds/jump.ogg"}
		});
		
		textures.setSmooth(false);
		fonts.setSmooth(false);
		
		game.setIcon(textures["player"]);
		game.open();
		
		clearall({Omit::Textures, Omit::SoundBuffers, Omit::Fonts});
		if (game.stableState()) {
			test_level();
		}
		return;
	}
	
	void test_level() {
		bool frameState = true;
		bool closeWindow = false;
		const size_t tps = 165;
		const double DELTA = 1.0/tps;
		
		fstopwatches.start("accumulated_game_time");
		
		sprites.add("player", textures["player"], 0.0).resizeToFit(game).multiply(0.1).align(game, Align::BottomLeft, Align::TopRight);
		sprites.add("sky", textures["sky"], -1.0).resizeToFit(game).align(game, Align::BottomLeft, Align::TopRight);
		
		sound_lists.add("jump");
		sound_lists["jump"].setVolume(sounds.getVolume());
		
		musics.play("music", reinterpret_cast<const char*>(assets["assets/sounds/music.ogg"].data()), assets["assets/sounds/music.ogg"].size(), 0.3, true, true)["music"].setLoopPoints_ms(2398.6, musics["music"].getDuration_ms(), false);
		
		ViewPort camera = ViewPort(24, {0.0, 0.0});
		camera.position = camera.getPerceivedDimensions(game.resolution)/2;
		
		Entity player = Entity({1.5, 1.7}, {1.0, 2.0}, {0.0, -36.0}, 8, 14.0, 1.6, 2);
		player.accelerationConstYJumpingMultiplier = 0.5;
		player.maxJumpFrames = tps/3;
		player.skidMultiplier = 0.5;
		player.holdToJump = false;
		
		while (game.stableState(frameState)) {
			if (game.pollForF11()) {
				game.toggleFullscreen();
			}
			if (game.pollForEscape()) {
				frameState = false;
				closeWindow = true;
			}
			while (optional frameEvent = game.window->pollEvent()) {
				if (game.pollForClosure(frameEvent)) {
					frameState = false;
					closeWindow = true;
				}
			}
			
			fstopwatches.elapse(1.0f/game.framerate);
			while (fstopwatches["accumulated_game_time"].frame >= 1.0f/tps) {
				fstopwatches["accumulated_game_time"].subtract(1.0f/tps);
				
				
				
				//  Main loop here
				player.receiveInput(game, defaultKeyBinds);
				if (player.is_jumping_triggered) {
					sound_lists["jump"].add(sound_buffers["jump"], 0.4f, 0.0f, 1.0, 1.0, true);
				}
				player.tickPhysics(tps);
				
				camera.position.x = player.position.x < camera.getPerceivedDimensions(game.resolution).x/2 ? camera.getPerceivedDimensions(game.resolution).x/2 : player.position.x;
				camera.position.y = player.position.y < camera.getPerceivedDimensions(game.resolution).y/2 ? camera.getPerceivedDimensions(game.resolution).y/2 : player.position.y;
				camera.setInViewport(game, sprites["player"], player.position, {1.0, 2.0});
				camera.setInViewport(game, sprites["sky"], {32.0, 18.0}, {64, 36});
				
				
				
			}
			if (sound_lists["jump"].inactive()) {
				sound_lists["jump"].clean();
			}
			sound_lists["jump"].setPanShift(-180*(player.position.x - camera.position.x)/64);
			
			game.refresh(true, sprites);
		}
		
		clearall({Omit::Textures, Omit::SoundBuffers, Omit::Fonts});
		if (game.stableState(!closeWindow)) {
			end_application();
		} else if (closeWindow) {
			end_application();
		}
		return;
	}
	
	void end_application() {
		if (game.window) {
			game.close();
		}
		clearall();
		return;
	}
}
