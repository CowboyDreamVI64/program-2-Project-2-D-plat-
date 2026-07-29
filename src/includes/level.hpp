namespace LevelStatus {
	constexpr short InProgress = 0;
	constexpr short Complete = 1;
	constexpr short Failed = 2;
	constexpr short GameOver = 3;
}

class Level {
	public:
		string levelID;
		short status = LevelStatus::InProgress;
		
		string firstLevelID;
		string nextLevelID;
		
		string levelName;
		TileMap tilemap;
		vector<Entity> entities;
		vector<Collectable> collectables;
		unordered_set<string> enabledSprites;
		double musicLoopStart;
		double musicVolume;
		string musicPath;
		sf::Color darknessTint;
		sf::Color darknessTintEnd;
		
		double cameraWidth;
		double cameraHeight;
		
		string groundTextureID;
		string exposedGroundTextureID;
		
		double backgroundSpriteMultiplier;
		
		Vec2 playerStartPosition = 0;
		
		inline Level& setLevelID(const std::string& inputLevelID) {
			levelID = inputLevelID;
			return *this;
		}
		
		string getLevelID() const {
			return levelID;
		}
		
		Level& loadLevel() {
			entities = vector<Entity>();
			collectables = vector<Collectable>();
			tilemap.loadFromMemory(assets["assets/levels/" + levelID + "/tilemap.txt"].data(), assets["assets/levels/" + levelID + "/tilemap.txt"].size());
			
			unordered_map<string, string> levelData = parseKeyValueText(getAssetsText("assets/levels/" + levelID + "/data.txt"));
			
			for (size_t Y = 0; Y < tilemap.maxHeight; ++Y) {
				for (size_t X = 0; X < tilemap.maxWidth; ++X) {
					if (tilemap.getTileCopy(X, Y).isEnemy()) {
						Entity newEnemy = Entity(EntityBehaviorTypes::Enemy, 1.0, Vec2(X, Y) + 0.5, {1.0, 0.6}, {0.0, -48.0}, 2.5, 14.2);
						newEnemy.snapToSpeed = true;
						newEnemy.avoidEdge = true;
						
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
					} else if (tilemap.getTileCopy(X, Y).isCollectable()) {
						collectables.push_back(Collectable(tilemap.getTileCopy(X, Y).isHeart() ? CollectableType::Heart : CollectableType::Coin, Vec2(X, Y) + 0.5));
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
					darknessTint = sf::Color::White;
				}
			} else {
				darknessTint = sf::Color::White;
			}
			
			if (levelData.count("darknessTintEnd") != 0) {
				vector<string> darknessTintsEnd = parseCommaList(levelData.at("darknessTintEnd"));
				try {
					darknessTintEnd = sf::Color(stoi(darknessTintsEnd.at(0)), stoi(darknessTintsEnd.at(1)), stoi(darknessTintsEnd.at(2)), 255);
				} catch (...) {
					darknessTintEnd = darknessTint;
				}
			} else {
				darknessTintEnd = darknessTint;
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
			
			if (levelData.count("nextLevelID") != 0) {
				nextLevelID = levelData.at("nextLevelID");
			} else {
				nextLevelID = "END";
			}
			
			if (levelData.count("firstLevelID") != 0) {
				firstLevelID = levelData.at("firstLevelID");
			} else {
				firstLevelID = FIRST_LEVEL_ID;
			}
			
			if (levelData.count("cameraWidth") != 0) {
				try {
					cameraWidth = stod(levelData.at("cameraWidth"));
				} catch (...) {
					cameraWidth = 24;
				}
			} else {
				cameraWidth = 24;
			}
			
			if (levelData.count("cameraHeight") != 0) {
				try {
					cameraHeight = stod(levelData.at("cameraHeight"));
				} catch (...) {
					cameraHeight = 0;
				}
			} else {
				cameraHeight = 0;
			}
			
			if (levelData.count("backgroundSpriteMultiplier") != 0) {
				try {
					backgroundSpriteMultiplier = stod(levelData.at("backgroundSpriteMultiplier"));
				} catch (...) {
					backgroundSpriteMultiplier = 1;
				}
			} else {
				backgroundSpriteMultiplier = 1;
			}
			
			if (levelData.count("enabledSprites") != 0) {
				vector<string> enabledSpritesVector = parseCommaList(levelData.at("enabledSprites"));
				for (size_t i = 0; i < enabledSpritesVector.size(); ++i) {
					enabledSprites.insert(enabledSpritesVector[i]);
				}
			}
			
			if (levelData.count("groundTextureID") != 0) {
				groundTextureID = levelData.at("groundTextureID");
			} else {
				groundTextureID = "tile.dirt";
			}
			
			if (levelData.count("exposedGroundTextureID") != 0) {
				exposedGroundTextureID = levelData.at("exposedGroundTextureID");
			} else {
				exposedGroundTextureID = "tile.dirt";
			}
			
			return *this;
		}
		
		inline bool spriteIsEnabled(const string& inputSpriteID) const {
			return enabledSprites.count(inputSpriteID) != 0;
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
		
		Level(const string& inputLevelID = "level1") : levelID(inputLevelID) {}
};