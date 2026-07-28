inline string getAssetsText(string assetName) {
	return string(reinterpret_cast<const char*>(assets[assetName].data()), assets[assetName].size());
}

string getWhitespaceChars() {
	string output;
	
	size_t count = 0;
	char initialValue = 0;
	char currentValue = initialValue;
	do {
		if (isspace(static_cast<unsigned char>(currentValue))) {
			output += currentValue;
			++count;
		}
		++currentValue;
	} while (currentValue != initialValue);
	
	return output;
}
const string whitespaceCharsString = getWhitespaceChars();
				
string trim(const string& inputString) {
	size_t startingIndex = inputString.find_first_not_of(whitespaceCharsString);
	size_t endingIndex = inputString.find_last_not_of(whitespaceCharsString);
	if (startingIndex == string::npos || endingIndex == string::npos) {
		return string();
	}
	return inputString.substr(startingIndex, endingIndex + 1 - startingIndex);
}
	
unordered_map<string, string> parseKeyValueText(string inputText) {
	unordered_map<string, string> finalKeyValues;
	
	while (inputText.size() != 0) {
		string currentLine = trim(inputText.substr(0, inputText.find("\n")));
		
		if (inputText.find("\n") == string::npos) {
			inputText = "";
		} else {
			inputText.erase(0, inputText.find("\n") + 1);
		}
		
		if (currentLine.size() > 2 && currentLine.find("=") != string::npos) {
			finalKeyValues.insert_or_assign(currentLine.substr(0, currentLine.find("=")), currentLine.substr(currentLine.find("=") + 1, currentLine.size() - currentLine.find("=") - 1));
		}
	}
	
	return finalKeyValues;
}

vector<string> parseCommaList(string inputText) {
	vector<string> finalElements;
	
	while (inputText.size() != 0) {
		string currentElement = inputText.substr(0, inputText.find(","));
		
		if (inputText.find(",") == string::npos) {
			inputText = "";
		} else {
			inputText.erase(0, inputText.find(",") + 1);
		}
		
		if (currentElement.size() > 0) {
			finalElements.push_back(currentElement);
		}
	}
	
	return finalElements;
}