//  --- SAVE / LOAD ---
//  
//  These write/read the player's stats to/from a simple, human-readable "key=value" text file so
//  it's easy to debug (and edit by hand for testing) if something looks wrong.
//  -------------------------------------------------------------------------------------------------------

//  Saves the passed stats to a file. Returns true on success. Creates the parent folder(s) of the
//  save path if they don't already exist.
inline bool savePlayerStats() {
	const filesystem::path saveFilePath(SAVE_DIRECTORY);
	if (saveFilePath.has_parent_path()) {
		std::error_code errorCode;
		filesystem::create_directories(saveFilePath.parent_path(), errorCode);
	}
	
	ofstream outputFile(SAVE_DIRECTORY, ios::trunc);
	if (!outputFile.is_open()) {
		return false;
	}
	
	outputFile << "TOTAL_COINS=" << TOTAL_COINS << '\n';
	outputFile << "TOTAL_SCORE=" << TOTAL_SCORE << '\n';
	outputFile << "TOTAL_LIVES=" << TOTAL_LIVES << '\n';
	outputFile << "TOTAL_HEALTH=" << TOTAL_HEALTH << '\n';
	outputFile << "CURRENT_LEVEL_ID=" << CURRENT_LEVEL_ID << '\n';
	
	return !outputFile.fail();
}

//  Loads the passed stats from a file. Returns true if the file was found and read; if the file
//  doesn't exist yet (e.g. first time the game is ever run), this returns false and leaves "stats"
//  completely untouched, so the caller keeps whatever default values the struct started with.
inline bool loadPlayerStats() {
	ifstream inputFile(SAVE_DIRECTORY);
	if (!inputFile.is_open()) {
		return false;
	}
	
	inputFile.seekg(0, ios::end);
	
	streampos fileSize = inputFile.tellg();
	
	inputFile.seekg(0, ios::beg);
	string fileString(fileSize, '\0');
	
	inputFile.read(reinterpret_cast<char*>(fileString.data()), fileSize);
	
	if (inputFile.fail() && !inputFile.eof()) {
		return false;
	}
		
	unordered_map<string, string> saveData = parseKeyValueText(fileString);
	
	if (saveData.count("TOTAL_COINS") != 0) {
		try {
			TOTAL_COINS = stoull(saveData.at("TOTAL_COINS"));
		} catch (...) {}
	}
	if (saveData.count("TOTAL_SCORE") != 0) {
		try {
			TOTAL_SCORE = stoull(saveData.at("TOTAL_SCORE"));
		} catch (...) {}
	}
	if (saveData.count("TOTAL_LIVES") != 0) {
		try {
			TOTAL_LIVES = stoull(saveData.at("TOTAL_LIVES"));
		} catch (...) {}
	}
	if (saveData.count("TOTAL_HEALTH") != 0) {
		try {
			TOTAL_HEALTH = stod(saveData.at("TOTAL_HEALTH"));
		} catch (...) {}
	}
	if (saveData.count("CURRENT_LEVEL_ID") != 0) {
		try {
			CURRENT_LEVEL_ID = saveData.at("CURRENT_LEVEL_ID");
		} catch (...) {}
	}
	
	return true;
}
