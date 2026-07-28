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
//  Returns the result of replacing all instances of replaceString in inputString with replaceWith.
string replaceall(string inputString, const string& replaceString, const string& replaceWith) {
	//  If the replaceString is empty, just return the inputString.
	if (replaceString == "") {
		return inputString;
	}
	
	//  This iterates through each instance of replaceString but only AFTER a latest index since starting
	//  at index 0 again for a search after a replacement is done may accidentally replace contents of
	//  replaceWith if replaceWith contains instances of replaceString itself.
	size_t currentIndex = 0;
	while ((currentIndex = inputString.find(replaceString, currentIndex)) != string::npos) {
		inputString.replace(currentIndex, replaceString.size(), replaceWith);
		currentIndex += replaceWith.size();
	}
	return inputString;
}

//  Copies all bytes of a file into a passed outputVector.
short readfromfile(ifstream& inputFile, vector<unsigned char>& outputVector) {
	//  If the input file isn't open, return -1 for error-checking.
	if (!inputFile.is_open()) {
		return -1;
	}
	
	//  This moves the file-reading location to the end of the file.
	inputFile.seekg(0, std::ios::end);
	
	//  This stores the current file-reading location to fileSize. Since the location was moved to the end of
	//  the file using seekg, the file-reading location exactly represents the number of bytes in the file.
	streampos fileSize = inputFile.tellg();
	
	//  This moves the file-reading location back to the beginning of the file.
	inputFile.seekg(0, ios::beg);
	outputVector = vector<unsigned char>(fileSize);
	
	//  This reads ALL contents of the file up to fileSize and stores the results contiguously at the data
	//  pointer of the vector.
	inputFile.read(reinterpret_cast<char*>(outputVector.data()), fileSize);
	
	//  If the previous operation failed, just return -2.
	if (inputFile.fail() && !inputFile.eof()) {
		return -2;
	}
	
	//  If all succeeded, return 0.
	return 0;
}

//  This gets the list of files in a directory as a vector of strings.
vector<string> printdir(string directory) {
	//  This changes all backslashes in the input directory to forward slashes.
	directory = replaceall(directory, "\\", "/");
	
    vector<string> fileNames;
    
    //  This creates a new std::filesystem::path object to look into the passed directory.
    const filesystem::path directoryObject = directory;
    
    //  If the directory DOES exist and the directory is a directory rather than a file, this executes.
    if (filesystem::exists(directoryObject) && filesystem::is_directory(directoryObject)) {
    	//  This is a special kind of for loop with the pseudo syntax "for (A in B)"; this loop executes for every
    	//  file found in the directory.
	  	for (const filesystem::directory_entry& currentFilePath : filesystem::directory_iterator(directoryObject)) {
	  		//  This adds the name of the file to the list of file names after replacing all backslashes with
			//  forward slashes and appends a forward slash at the end of the file name if it is a folder.
            fileNames.push_back(replaceall(currentFilePath.path().string(), "\\", "/") + (filesystem::is_directory(currentFilePath) ? "/" : ""));
	    }
    }
    return fileNames;
}

//  This gets all file and subfile paths at a specific path and puts them into a vector of strings.
vector<string> getFileDirectories(const string& initialDirectory) {
	//  This uses the above function to get all files and folders at the directory.
	vector<string> fileDirectories = printdir(initialDirectory), newDirectories;
	
	//  This iterates through each file path got from the above function.
	for (size_t i = 0; i < fileDirectories.size(); ++i) {
		//  If the current file path is a folder (indicated by the forward slash at the end of the path),
		//  move the path from fileDirectories to newDirectories (to search for subfiles within these
		//  directories).
		if (fileDirectories[i][fileDirectories[i].size() - 1] == '/') {
			newDirectories.push_back(fileDirectories[i]);
			fileDirectories.erase(fileDirectories.begin() + i);
			--i;
		}
	}
	
	//  This iterates through the folders got from the above loop.
	for (size_t i = 0; i < newDirectories.size(); ++i) {
		//  This gets all the files within the current folder.
		//  NOTE: This uses something called "recursion," which is where you call a function within itself.
		//        This is done here so that the subdirectories got this time call the function again to get
		//        their OWN subdirectories and subfiles, and those subdirectories will get their OWN
		//        subdirectories and files, and so on.
		vector<string> fileSubdirectories = getFileDirectories(newDirectories[i]);
		
		//  This adds the subfiles back to the main list of file directories.
		for (size_t j = 0; j < fileSubdirectories.size(); ++j) {
			fileDirectories.push_back(fileSubdirectories[j]);
		}
	}
	return fileDirectories;
}

//  This complex function creates an unordered map of bytes. This acts as a data accessor via string ID. Basically,
//  when you input a file path, the function uses the above function to get the path to every single file and
//  subfile within the path, then gets all file data for each of these files, and stores the file data into their
//  own vectors. These vectors will then contain the exact data of the files. Then, the vectors are put into a
//  key-value unordered map where the key is the file's path and the value is the file's binary data in the form
//  of a vector.
unordered_map<string, vector<unsigned char>> loadSubfilesToMap(string initialDirectory) {
	//  These replace all the backslashes in the directory string with forward slashes, then appends a forward
	//  slash if there's no forward slash at the front of the directory.
	initialDirectory = replaceall(initialDirectory, "\\", "/");
	if (initialDirectory[initialDirectory.size() - 1] != '/') {
		initialDirectory += "/";
	}
	
	//  This gets all file and subfile directories.
	vector<string> fileDirectories = getFileDirectories(initialDirectory);
	unordered_map<string, vector<unsigned char>> outputAssets;
	
	//  This is just some complex code that just gets the index where the very LAST folder in the path starts, so
	//  that, later in the code, we can make it so that instead of keys being some long file path like
	//  "C:/users/ME/projects/initialDirectory/your/path/to/file.txt", it's "initialDirectory/your/path/to/file.txt"
	//  instead.
	size_t pathStartingIndex = (initialDirectory.substr(0,initialDirectory.size() - 1).rfind('/') != string::npos) ? initialDirectory.substr(0,initialDirectory.size() - 1).rfind('/') + 1 : 0;
	
	//  This iterates through each file and subfile directory.
	for (size_t i = 0; i < fileDirectories.size(); ++i) {
		//  This opens the file at the directory in "binary mode" instead of "text mode," since we're just getting
		//  the data for the files.
		ifstream inputFile(fileDirectories[i], ios::binary);
		
		//  If the file is opened (this only happens when no errors have occurred), store the file's binary into a
		//  vector that will go into the unordered map.
		if (inputFile.is_open()) {
			vector<unsigned char> bytes;
			
			//  This uses the earlier defined function to read all the binary contents of the file into the bytes
			//  vector.
			readfromfile(inputFile, bytes);
			
			//  This assigns the key of the key-value pair to the directory of the file but only starting at the
			//  first folder of the initial directory, and assigns the value to the actual file's data.
			// 
			//  NOTE: std::unordered_map::insert_or_assign(key, value) is an unordered map method that either adds
			//        a new key-value pair if the key doesn't exist or replaces an existing key-value pair with this
			//        key-value pair if the key already exists.
			outputAssets.insert_or_assign(replaceall(fileDirectories[i].substr(pathStartingIndex, fileDirectories[i].size() - pathStartingIndex), "\\", "/"), bytes);
		}
	}
	return outputAssets;
}

//  This assigns a global variable "assets" to the result of using the previous function for the path "assets/."
unordered_map<string, vector<unsigned char>> assets = loadSubfilesToMap("assets/");
#endif

//  If we ever want to load assets from memory (so that the .exe file doesn't need to carry an assets folder with
//  it everywhere), we'll need to use a special tool I created to convert all that data inti a .cpp file we can
//  include.
#ifdef LOAD_FROM_MEMORY
#include "assets.cpp"
#endif