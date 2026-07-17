//  --- ASSET LOADING PREPROCESSOR DIRECTIVES ---
//  
//  This is a preprocessor directive. You can use these to make specific sections of code
//  only compile when something is or isn't defined. This preprocessor directive defines
//  either LOAD_FROM_FILE or LOAD_FROM_MEMORY. LOAD_FROM_FILE requires the final executable
//  to have all of its files stored in a folder named "assets/". LOAD_FROM_MEMORY instead
//  uses a .cpp file containing arrays of assets to compile with the program so that the
//  program does not need to have an "assets/" folder with it.
//  
//  I have the tool that converts assets/ data to an assets.cpp file but we won't use it
//  yet so for now keep this at LOAD_FROM_FILE
//  
//  You can do #define DEFINITION VALUE (or just #define DEFINITION) and then later you can
//  do #ifdef DEFINITION, then put some code under that #ifdef, then put #endif. This will
//  work so that if, and only if, DEFINITION is defined somewhere, THEN the code between the
//  #ifdef and #endif will be compiled by the compiler. If DEFINITION is NOT defined, then
//  that code will be skipped.
//  
//  You can also use #ifndef for if a definition does NOT exist.
//  
//  -------------------------------------------------------------------------------------------------------
//  
#define LOAD_FROM_FILE  //  Options: 'LOAD_FROM_FILE', 'LOAD_FROM_MEMORY'


#ifdef LOAD_FROM_FILE
string replaceall(string inputString, const string& replaceString, const string& replaceWith) {
	if (replaceString == "") {
		return inputString;
	}
	size_t currentIndex = 0;
	while ((currentIndex = inputString.find(replaceString, currentIndex)) != string::npos) {
		inputString.replace(currentIndex, replaceString.size(), replaceWith);
		currentIndex += replaceWith.size();
	}
	return inputString;
}


short readfromfile(ifstream& inputFile, vector<unsigned char>& outputVector) {
	if (!inputFile.is_open()) {
		return -1;
	}
	inputFile.seekg(0, std::ios::end);
	streampos fileSize = inputFile.tellg();
	inputFile.seekg(0, ios::beg);
	outputVector = vector<unsigned char>(fileSize);
	inputFile.read(reinterpret_cast<char*>(outputVector.data()), fileSize);
	if (inputFile.fail() && !inputFile.eof()) {
		return -2;
	}
	return 0;
}


vector<string> printdir(const string& directory, const unsigned short& fileNameMode = 0, const unsigned short& filter = 0, const bool& useForwardSlash = false) {
    vector<string> fileNames;
    const filesystem::path directoryObject = directory;
    if (filesystem::exists(directoryObject) && filesystem::is_directory(directoryObject)) {
	  	for (const filesystem::directory_entry& currentFilePath : filesystem::directory_iterator(directoryObject)) {
    		if (filter == 0 || (filter == 1 && filesystem::is_regular_file(currentFilePath)) || (filter == 2 && filesystem::is_directory(currentFilePath))) {
                if (fileNameMode == 3) {
                    fileNames.push_back(filesystem::path(currentFilePath.path().string()).extension().string() + (filesystem::is_directory(currentFilePath) ? (useForwardSlash ? "/" : "\\") : ""));
                } else if (fileNameMode == 2) {
                    fileNames.push_back(filesystem::path(currentFilePath.path().string()).stem().string());
                } else if (fileNameMode == 1) {
                    fileNames.push_back(filesystem::path(currentFilePath.path().string()).filename().string() + (filesystem::is_directory(currentFilePath) ? (useForwardSlash ? "/" : "\\") : ""));
                } else {
                    fileNames.push_back(currentFilePath.path().string() + (filesystem::is_directory(currentFilePath) ? (useForwardSlash ? "/" : "\\") : ""));
                }
	        }
	    }
    }
    return fileNames;
}

vector<string> getFileDirectories(const string& initialDirectory, const bool& useForwardSlash = false) {
	vector<string> fileDirectories = printdir(initialDirectory), newDirectories;
	for (size_t i = 0; i < fileDirectories.size(); ++i) {
		if (fileDirectories[i][fileDirectories[i].size() - 1] == (useForwardSlash ? '/' : '\\')) {
			newDirectories.push_back(fileDirectories[i]);
			fileDirectories.erase(fileDirectories.begin() + i);
			--i;
		}
	}
	for (size_t i = 0; i < newDirectories.size(); ++i) {
		vector<string> fileSubdirectories = getFileDirectories(newDirectories[i]);
		for (size_t j = 0; j < fileSubdirectories.size(); ++j) {
			fileDirectories.push_back(fileSubdirectories[j]);
		}
	}
	return fileDirectories;
}
			
unordered_map<string, vector<unsigned char>> loadSubfilesToMap(string initialDirectory, bool keysUseForwardSlash = true, const bool& useForwardSlash = false) {
	if (useForwardSlash) {
		initialDirectory = replaceall(initialDirectory, "\\", "/");
	} else {
		initialDirectory = replaceall(initialDirectory, "/", "\\");
	}
	if ((initialDirectory[0] == '\"' && initialDirectory[initialDirectory.size() - 1] == '\"') || (initialDirectory[0] == '\'' && initialDirectory[initialDirectory.size() - 1] == '\'')) {
		initialDirectory.erase(initialDirectory.end() - 1);
		initialDirectory.erase(initialDirectory.begin());
	}
	if (initialDirectory[initialDirectory.size() - 1] != (useForwardSlash ? '/' : '\\')) {
		initialDirectory += (useForwardSlash ? "/" : "\\");
	}
	vector<string> fileDirectories = getFileDirectories(initialDirectory);
	unordered_map<string, vector<unsigned char>> outputAssets;
	size_t pathStartingIndex = (initialDirectory.substr(0,initialDirectory.size() - 1).rfind((useForwardSlash ? '/' : '\\')) != string::npos) ? initialDirectory.substr(0,initialDirectory.size() - 1).rfind((useForwardSlash ? '/' : '\\')) + 1 : 0;
	for (size_t i = 0; i < fileDirectories.size(); ++i) {
		ifstream inputFile(fileDirectories[i], ios::binary);
		if (inputFile.is_open()) {
			vector<unsigned char> bytes;
			readfromfile(inputFile, bytes);
			outputAssets.insert_or_assign(keysUseForwardSlash ? replaceall(fileDirectories[i].substr(pathStartingIndex, fileDirectories[i].size() - pathStartingIndex), "\\", "/") : replaceall(fileDirectories[i].substr(pathStartingIndex, fileDirectories[i].size() - pathStartingIndex), "/", "\\"), bytes);
		}
	}
	return outputAssets;
}

unordered_map<string, vector<unsigned char>> assets = loadSubfilesToMap("assets\\", true);
vector<string> findAssetsWithPrefix(const string& prefix) {
	vector<string> output;
	for (const auto& [key, value] : assets) {
		if (key.substr(0, prefix.size()) == prefix) {
			output.push_back(key.substr(prefix.size(), key.size() - prefix.size()));
		}
	}
	return output;
}
#endif
#ifdef LOAD_FROM_MEMORY
#include "assets.cpp"
vector<string> findAssetsWithPrefix(const string& prefix) {
	vector<string> output;
	for (size_t i = 0; i < assets.size(); ++i) {
		if (assets.data[i].key.substr(0, prefix.size()) == prefix) {
			output.push_back(string(assets.data[i].key.substr(prefix.size(), assets.data[i].key.size() - prefix.size())));
		}
	}
	
	return output;
}
#endif