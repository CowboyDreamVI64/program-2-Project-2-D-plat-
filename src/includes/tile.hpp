namespace TileType {
	const char Air = '.';
	const char Enemy = 'E';
	const char Ground = '#';
	const char Hazard = '^';
	const char Coin = 'C';
	const char Heart = 'H';
	const char Goal = 'G';
	const char Invalid = 'X';
	const char PlayerStart = 'P';
	
	inline bool isValidTileType(const char inputChar) {
		if (inputChar == Air || inputChar == Enemy || inputChar == PlayerStart || inputChar == Ground || inputChar == Hazard || inputChar == Coin || inputChar == Heart || inputChar == Goal) {
			return true;
		}
		return false;
	}
}

class Tile {
	public:
		char type = TileType::Air;
		
		inline bool isAir() const {
			return type == TileType::Air;
		}
		inline bool isSolid() const {
			return type == TileType::Ground;
		}
		inline bool isGround() const {
			return type == TileType::Ground;
		}
		inline bool isHazard() const {
			return type == TileType::Hazard;
		}
		inline bool isEnemy() const {
			return type == TileType::Enemy;
		}
		inline bool isCollectable() const {
			return type == TileType::Coin || type == TileType::Heart;
		}
		inline bool isCoin() const {
			return type == TileType::Coin;
		}
		inline bool isHeart() const {
			return type == TileType::Heart;
		}
		inline bool isGoal() const {
			return type == TileType::Goal;
		}
		inline bool isType(const char inputType) const {
			return type == inputType;
		}
		inline bool isInvalid() const {
			return type == TileType::Invalid;
		}
		inline bool isValid() const {
			return type != TileType::Invalid;
		}
		
		inline bool getType() const {
			return type != TileType::Invalid;
		}
		inline Tile& setType(const char inputType) {
			type = TileType::isValidTileType(inputType) ? inputType : TileType::Invalid;
			return *this;
		}
	
		Tile(const char inputType = TileType::Air) : type(inputType) {}
};

/*
Need to add:

Enemy spawner

Player spawn logic

Collectible logic

Goal logic
*/

class TileMap {
	public:
		vector<vector<Tile>> tiles = vector<vector<Tile>>();
		
		size_t maxWidth = 0;
		size_t maxHeight = 0;
		
		Tile& getTile(const size_t X, const size_t Y) {
			if (X >= maxWidth || Y >= maxHeight) {
				throw std::runtime_error("Tried \"unsigned long long X > TileMap::maxWidth || unsigned long long Y > TileMap::maxHeight\", got throw-requiring \'true\'; when executing \"std::vector<std::vector<Tile>>[unsigned long long][unsigned long long]\" (at method \"TileMap::getTile(const unsigned long long, const unsigned long long)\")");
			}
			return tiles[Y][X];
		}
		const Tile& getTile(const size_t X, const size_t Y) const {
			if (X >= maxWidth || Y >= maxHeight) {
				throw std::runtime_error("Tried \"unsigned long long X > TileMap::maxWidth || unsigned long long Y > TileMap::maxHeight\", got throw-requiring \'true\'; when executing \"std::vector<std::vector<Tile>>[unsigned long long][unsigned long long]\" (at method \"const TileMap::getTile(const unsigned long long, const unsigned long long) const\")");
			}
			return tiles[Y][X];
		}
		const Tile getTileCopy(const size_t X, const size_t Y) const {
			if (X >= maxWidth || Y >= maxHeight) {
				return Tile(TileType::Invalid);
			}
			return tiles[Y][X];
		}
		TileMap& setTile(const size_t X, const size_t Y, const char tileType) {
			if (TileType::isValidTileType(tileType) && X <= maxWidth && Y <= maxHeight) {
				tiles[Y][X].setType(tileType);
			}
			return *this;
		}
		TileMap& setTile(const size_t X, const size_t Y, const Tile inputTile) {
			if (TileType::isValidTileType(inputTile.getType()) && X <= maxWidth && Y <= maxHeight) {
				tiles[Y][X] = inputTile;
			}
			return *this;
		}
		
		TileMap& loadFromMemory(const void* void_data, const size_t size) {
			tiles = vector<vector<Tile>>();
			maxWidth = 0;
			maxHeight = 0;
			
			const char* data = static_cast<const char*>(void_data);
			
			size_t currentLine = 0;
			size_t currentWidth = 0;
			
			bool playerHasSpawnTile = false;
			array<size_t, 2> playerSpawnTileLocation = {2, 2};
			
			for (size_t i = 0; i < size; ++i) {	
				const char currentChar = *(data + i);
				
				if (currentChar == TileType::Invalid) {
					break;
				} else if (currentChar == '\n') {
					++currentLine;
					continue;
				}
				
				while (maxHeight < currentLine + 1) {
					++maxHeight;
					tiles.push_back(vector<Tile>());
					currentWidth = 0;
				}
				
				if (TileType::isValidTileType(currentChar)) {
					tiles[currentLine].push_back(Tile(currentChar));
					++currentWidth;
				}
				if (maxWidth < currentWidth) {
					maxWidth = currentWidth;
				}
			}
			
			for (size_t Y = 0; Y < tiles.size(); ++Y) {
				for (size_t X = tiles[Y].size() - 1; X < maxWidth; ++X) {
					tiles[Y].push_back(Tile(TileType::Air));
				}
			}
			
			for (size_t Y = 0; Y < tiles.size()/2; ++Y) {
				vector<Tile> table = tiles[Y];
				tiles[Y] = tiles[tiles.size() - 1 - Y];
				tiles[tiles.size() - 1 - Y] = table;
			}
			
			return *this;
		}
	
		TileMap& loadFromFile(const string& path) {
			ifstream inputFile(path);
			if (!inputFile.is_open()) {
				throw std::runtime_error("Tried \"!std::ifstream::is_open()\", got throw-requiring \'true\'; for directory \"" + path + "\" (at method TileMap::LoadFromFile(const std::string&))");
			}
			
			vector<unsigned char> fileVector;
			
			inputFile.seekg(0, std::ios::end);
			streampos fileSize = inputFile.tellg();
			inputFile.seekg(0, ios::beg);
			fileVector = vector<unsigned char>(fileSize);
			
			inputFile.read(reinterpret_cast<char*>(fileVector.data()), fileSize);
			if (inputFile.fail() || !inputFile.eof()) {
				throw std::runtime_error("Tried \"std::ifstream::fail() || !std::ifstream::eof()\", got throw-requiring \'true\'; for directory \"" + path + "\" (at method TileMap::LoadFromFile(const std::string&))");
			}
			
			return *this;
		}
		
		array<array<size_t, 2>, 2> resolveIndexRangeContext(Vec2 pos, Vec2 size = 1.0) const {
			pos += 0.5;
			size += 2;
			
			array<array<size_t, 2>, 2> output;
			//  Output: [0 for min, 1 for max][0 for x, 1 for y];
			output[0][0] = pos.x - size.x/2 < 0 ? 0 : static_cast<size_t>(pos.x - size.x/2);
			output[1][0] = pos.x + size.x/2 > maxWidth ? maxWidth : static_cast<size_t>(pos.x + size.x/2);
			
			output[0][1] = pos.y - size.y/2 < 0 ? 0 : static_cast<size_t>(pos.y - size.y/2);
			output[1][1] = pos.y + size.y/2 > maxHeight ? maxHeight : static_cast<size_t>(pos.y + size.y/2);
			
			return output;
		}
		
		TileMap() {}
};