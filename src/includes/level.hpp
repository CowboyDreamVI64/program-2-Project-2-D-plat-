class Level {
	public:
		string levelID;
		
		string levelName;
		TileMap tilemap;
		vector<Entity> entities;
		double musicLoopStart;
		double musicVolume;
		string musicPath;
		sf::Color darknessTint;
		
		Vec2 playerStartPosition = 0;
		
		inline Level& setLevelID(const std::string& inputLevelID) {
			levelID = inputLevelID;
			return *this;
		}
		
		string getLevelID() const {
			return levelID;
		}
		
		Level& loadLevel() {
			unordered_map<string, string> levelData = parseKeyValueText(getAssetsText("assets/levels/" + levelID + "/data.txt"));
			tilemap.loadFromMemory(assets["assets/levels/" + levelID + "/tilemap.txt"].data(), assets["assets/levels/" + levelID + "/tilemap.txt"].size());
			
			for (size_t Y = 0; Y < tilemap.maxHeight; ++Y) {
				for (size_t X = 0; X < tilemap.maxWidth; ++X) {
					if (tilemap.getTileCopy(X, Y).isEnemy()) {
						Entity newEnemy = Entity(EntityBehaviorTypes::Enemy, 1.0, Vec2(X, Y) + 0.5, {0.9, 0.6}, {0.0, -48.0}, 2.5, 14.2);
						newEnemy.snapToSpeed = true;
						
						if (frandom() > 0.5) {
							newEnemy.constInput[1] = true;
						} else {
							newEnemy.constInput[3] = true;
						}
						newEnemy.animation_state = AnimationState({
							{ "idle",
								Animation({
									AnimationFrame("enemy.knight.walk.0", 0.13, {1.0, 1.0}, {0.0, 0.5 - newEnemy.baseHitbox.y/2 - 0.1}),
									AnimationFrame("enemy.knight.walk.1", 0.13, {1.0, 1.0}, {0.0, 0.5 - newEnemy.baseHitbox.y/2 - 0.1}),
									AnimationFrame("enemy.knight.walk.2", 0.13, {1.0, 1.0}, {0.0, 0.5 - newEnemy.baseHitbox.y/2 - 0.1}),
									AnimationFrame("enemy.knight.walk.1", 0.13, {1.0, 1.0}, {0.0, 0.5 - newEnemy.baseHitbox.y/2 - 0.1}),
									AnimationFrame("enemy.knight.walk.0", 0.13, {1.0, 1.0}, {0.0, 0.5 - newEnemy.baseHitbox.y/2 - 0.1}),
									AnimationFrame("enemy.knight.walk.3", 0.13, {1.0, 1.0}, {0.0, 0.5 - newEnemy.baseHitbox.y/2 - 0.1}),
									AnimationFrame("enemy.knight.walk.4", 0.13, {1.0, 1.0}, {0.0, 0.5 - newEnemy.baseHitbox.y/2 - 0.1}),
									AnimationFrame("enemy.knight.walk.3", 0.13, {1.0, 1.0}, {0.0, 0.5 - newEnemy.baseHitbox.y/2 - 0.1})
								}, true)
							},
							{ "death",
								Animation({
									AnimationFrame("enemy.knight.squish.0", 0.03, {1.0, 1.0}, {0.0, 0.5 - newEnemy.baseHitbox.y/2 - 0.1}),
									AnimationFrame("enemy.knight.squish.1", 0.03, {1.0, 1.0}, {0.0, 0.5 - newEnemy.baseHitbox.y/2 - 0.1}),
									AnimationFrame("enemy.knight.squish.2", 0.03, {1.0, 1.0}, {0.0, 0.5 - newEnemy.baseHitbox.y/2 - 0.1}),
									AnimationFrame("enemy.knight.squish.3", 0.03, {1.0, 1.0}, {0.0, 0.5 - newEnemy.baseHitbox.y/2 - 0.1})
								}, false)
							}
						}, "idle");
						
						entities.push_back(newEnemy);
						
						tilemap.setTile(X, Y, TileType::Air);
					}
				}
			}
			
			if (levelData.count("musicID") != 0) {
				musicPath = "assets/sounds/music/" + levelData.at("musicID") + ".ogg";
				if (levelData.count("musicLoopStart") != 0) {
					try {
						musicLoopStart = stod(levelData.at("musicLoopStart"));
					} catch (...) {
						musicLoopStart = 0;
					}
				} else {
					musicLoopStart = 0;
				}
			} else {
				musicPath = "assets/sounds/music/overworld.ogg";
				musicLoopStart = 2.3986;
			}
			
			if (levelData.count("musicVolume") != 0) {
				try {
					musicVolume = stod(levelData.at("musicVolume"));
					musicVolume = musicVolume > 1.0 ? 1.0 : musicVolume;
					musicVolume *= musicVolume > 0.0;
				} catch (...) {
					musicVolume = 0;
				}
			} else {
				musicVolume = 1.0;
			}
			
			if (levelData.count("darknessTint") != 0) {
				vector<string> darknessTints = parseCommaList(levelData.at("darknessTint"));
				try {
					darknessTint = sf::Color(stoi(darknessTints.at(0)), stoi(darknessTints.at(1)), stoi(darknessTints.at(2)), 255);
				} catch (...) {
					musicVolume = 0;
				}
			} else {
				musicVolume = 1.0;
			}
			
			if (levelData.count("name") != 0) {
				levelName = levelData.at("name");
			} else {
				levelName = levelID;
			}
			
			for (size_t Y = 0; Y < tilemap.maxHeight; ++Y) {
				for (size_t X = 0; X < tilemap.maxWidth; ++X) {
					if (tilemap.getTile(X, Y).type == TileType::PlayerStart) {
						playerStartPosition = Vec2(X + 0.5, Y);
						tilemap.setTile(X, Y, TileType::Air);
					}
				}
			}
			
			return *this;
		}
		
		Level& cleanEntities() {
			for (size_t i = 0; i < entities.size(); ++i) {
				if (entities[i].death_time() > 0.7) {
					entities.erase(entities.begin() + i);
					--i;
				}
			}
			return *this;
		}
		
		Level(const string& inputLevelID) : levelID(inputLevelID) {}
};