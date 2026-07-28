//  --- PLAYER STATS ---
//  
//  This struct stores every player-based global variable that needs to persist across levels
//  (health, coins, points, lives), separate from any one Entity instance. This is what the HUD
//  reads from and what gets written to/read from the save file.
//  
//  USAGE FOR COLLISION/COLLECTIBLE/ENTITY CODE:
//  Whenever the player picks up a coin, gets hurt by a hazard/enemy, or dies, call the
//  corresponding method on the global "playerStats" object below, e.g.:
//  	playerStats.addCoins(1);
//  	playerStats.damage(1);
//  	if (playerStats.isDead()) { playerStats.loseLife(); }
//  -------------------------------------------------------------------------------------------------------
struct PlayerStats {
	int health = 3;
	int maxHealth = 3;
	int coins = 0;
	int points = 0;
	int lives = 3;
	int maxLives = 99;
	
	inline bool isDead() const {
		return health <= 0;
	}
	inline bool isGameOver() const {
		return lives <= 0;
	}
	
	//  Adds (or removes, if negative) coins; clamps at 0.
	PlayerStats& addCoins(const int amount = 1) {
		coins += amount;
		if (coins < 0) {
			coins = 0;
		}
		return *this;
	}
	
	//  Adds (or removes, if negative) points; clamps at 0.
	PlayerStats& addPoints(const int amount) {
		points += amount;
		if (points < 0) {
			points = 0;
		}
		return *this;
	}
	
	//  Heals the player; clamps at maxHealth.
	PlayerStats& heal(const int amount = 1) {
		health += amount;
		if (health > maxHealth) {
			health = maxHealth;
		}
		return *this;
	}
	
	//  Damages the player; clamps at 0. Does NOT automatically remove a life -- check isDead()
	//  after calling this and call loseLife() yourself if you want that behavior.
	PlayerStats& damage(const int amount = 1) {
		health -= amount;
		if (health < 0) {
			health = 0;
		}
		return *this;
	}
	
	//  Removes one life and resets health back to full. Intended to be called once the player
	//  entity has been confirmed dead (e.g. after a death animation finishes).
	PlayerStats& loseLife() {
		if (lives > 0) {
			--lives;
		}
		health = maxHealth;
		return *this;
	}
	
	//  Adds (or removes, if negative) lives; clamps between 0 and maxLives.
	PlayerStats& addLives(const int amount = 1) {
		lives += amount;
		if (lives > maxLives) {
			lives = maxLives;
		}
		if (lives < 0) {
			lives = 0;
		}
		return *this;
	}
	
	//  Resets every stat back to a fresh, brand-new-game state.
	PlayerStats& reset() {
		health = maxHealth;
		coins = 0;
		points = 0;
		lives = 3;
		return *this;
	}
};

//  The single global instance of the player's persistent stats. Everything (HUD, collision,
//  collectibles, save/load) should read from and write to this same object.
PlayerStats playerStats;

//  --- SAVE / LOAD ---
//  
//  These write/read the player's stats to/from a simple, human-readable "key=value" text file so
//  it's easy to debug (and edit by hand for testing) if something looks wrong.
//  -------------------------------------------------------------------------------------------------------

//  Saves the passed stats to a file. Returns true on success. Creates the parent folder(s) of the
//  save path if they don't already exist.
inline bool savePlayerStats(const PlayerStats& stats, const string& path = "save/save.txt") {
	const filesystem::path saveFilePath(path);
	if (saveFilePath.has_parent_path()) {
		std::error_code errorCode;
		filesystem::create_directories(saveFilePath.parent_path(), errorCode);
	}
	
	ofstream outputFile(path, ios::trunc);
	if (!outputFile.is_open()) {
		return false;
	}
	
	outputFile << "health=" << stats.health << '\n';
	outputFile << "maxHealth=" << stats.maxHealth << '\n';
	outputFile << "coins=" << stats.coins << '\n';
	outputFile << "points=" << stats.points << '\n';
	outputFile << "lives=" << stats.lives << '\n';
	outputFile << "maxLives=" << stats.maxLives << '\n';
	
	return !outputFile.fail();
}

//  Loads the passed stats from a file. Returns true if the file was found and read; if the file
//  doesn't exist yet (e.g. first time the game is ever run), this returns false and leaves "stats"
//  completely untouched, so the caller keeps whatever default values the struct started with.
inline bool loadPlayerStats(PlayerStats& stats, const string& path = "save/save.txt") {
	ifstream inputFile(path);
	if (!inputFile.is_open()) {
		return false;
	}
	
	string line;
	while (getline(inputFile, line)) {
		const size_t equalsIndex = line.find('=');
		if (equalsIndex == string::npos) {
			continue;
		}
		const string key = line.substr(0, equalsIndex);
		const string value = line.substr(equalsIndex + 1);
		
		try {
			if (key == "health") {
				stats.health = stoi(value);
			} else if (key == "maxHealth") {
				stats.maxHealth = stoi(value);
			} else if (key == "coins") {
				stats.coins = stoi(value);
			} else if (key == "points") {
				stats.points = stoi(value);
			} else if (key == "lives") {
				stats.lives = stoi(value);
			} else if (key == "maxLives") {
				stats.maxLives = stoi(value);
			}
		} catch (...) {
			//  If a value on this line failed to parse as an integer, just skip that line instead
			//  of crashing or aborting the whole load.
			continue;
		}
	}
	
	return true;
}
