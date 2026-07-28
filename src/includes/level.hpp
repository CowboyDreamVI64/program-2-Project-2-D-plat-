class Level {
	public:
		string levelID;
		
		string levelName;
		TileMap tilemap;
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
			tilemap.loadFromMemory(assets["assets/levels/" + levelID + "/TileMap.txt"].data(), assets["assets/levels/" + levelID + "/TileMap.txt"].size());
			
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
		
		Level(const string& inputLevelID) : levelID(inputLevelID) {}
};