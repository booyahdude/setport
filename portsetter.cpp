// Collin Anderson
// CS 3370
// Instructor: Professor Wagstaff
// portsetter Programming Project
// File: portsetter.cpp
// Contents: main driver for the program
// I declare that the following source code was written solely by me, or
// provided by the instructor. I understand that copying any source code,
// in whole or in part, constitutes cheating, and that I will receive a
// zero in this assignment if I am found in violation of this policy.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// constants
const double VERSION_NUM = 1.2;
const int LOWEST_PORT = 1;
const int HIGHEST_PORT = 65535;
const int ERROR_PORT_CODE = 1;
const int ERROR_ARGS_CODE = 2;

// global variables
string ERROR_ARGS = "";
string ERROR_PORT = "";
string usage = "";
string about = "";
string success = "";

// function prototypes
// Read file function.
// Purpose: To read the contents of a given file from the hard disk.
// Parameter: The file to read.
// Returns: A vector containing the lines of the file.
vector<string> readFile(const string&);
// Read Environmental Variable function.
// Purpose: To read ina system environmental variable and verify that it is an int.
// Parameter: The name of the environmental variable to look up.
// Returns: The value of the environmental variable, or "" if there was none
string readEnv(const string&);
// Get Language function.
// Purpose: To get the language code to use for user messages.
// Returns: The two letter language code denoting the system language.
string getLang();
// Verify Language function.
// Purpose: To verify that a language string has a valid value.
// Parameter: The language string to check.
// Returns: Whether or not the language string represents a valid language.
bool verifyLang(const string&);
// Set Global Variables function.
// Purpose: To set the value of the global variables to the correct messages for the given language.
// Parameter: The two-letter language code to use for retrieving the localized messages.
void setGlobals(string);
// File Exists function.
// Purpose: To check whether a file exists in the filesystem.
// Parameter: The path to the file.
// Returns: Whether or not the file exists.
bool fileExists(const string&);

// main function.
// Purpose: The entry point to the C++ program.
// Parameters: The number of arguments entered on the command-line, and the arguments themsevles delimited by spaces.
int main(int argc, char* argv[]) {
   // cout << "v0.2" << endl;
    // set language
    //cout << getLang() << endl;
    setGlobals(getLang());
    
    // check to make sure that there is a valid number of arguments
    if (argc == 1) {
        cout << usage;  // no arguments specified, print usage
        return 0;
    }
    
    // check for single argument switches
    string strArg = argv[1];
    if (argc == 2) {  // check if we have a help/about/version option (if so, display appropriate data; if not, display error and usage)
        
        if (strArg == "-h" || strArg == "-?" || strArg == "--help") { // help option
            cout << usage;
            return 0;
        }
        
        if (strArg == "-!" || strArg == "--about") { // program info option
            cout << about;
            return 0;
        }
        
        if (strArg == "-v" || strArg == "--version") { // version info option
            cout << VERSION_NUM << endl;
            return 0;
        }
        
        // else invalid arg
        cout << ERROR_ARGS << endl << endl;
        cout << usage;
        return ERROR_ARGS_CODE;
    }
    
    // at this point we need to verify that we have the port switch
    // check if the first argument is the port option
    strArg = argv[1];
    if (strArg != "-p" && strArg != "--port") {  // we have a bad option, quit.
        cout << ERROR_ARGS << endl << endl;
        cout << usage;
        return ERROR_ARGS_CODE;
    }
    
    // we have a port switch, now check if we have an environmental variable
    strArg = argv[2];
    string strPort = "";
    
    if (strArg == "-e" || strArg == "--environment") { // we have an environmental variable, branch on whether the user specified a name
        if (argc > 4) { // too many args, quit
            cout << ERROR_ARGS << endl << endl;
            cout << usage;
            return ERROR_ARGS_CODE;
        }
        
        if (argc == 3) {
            strPort = readEnv("PORT"); // we need to extract the value for port from var PORT
        }
        else { // we need to extract the value from user-specified var
            strArg = argv[3];
            strPort = readEnv(strArg);
        }
        
        if (strPort == "") { // invalid port, quit
            cout << ERROR_PORT << endl << endl;
            cout << usage;
            return ERROR_PORT_CODE;
        }
    }

    // check to see if we need to read in a port still
    strArg = argv[2];
    if (strArg != "-e" && strArg != "--environment") { // we didn't have an environmental variable, we need to read in a value for the port
        // we need to make sure there aren't any extra arguments first
        if (argc > 3) { // invalid args
            cout << ERROR_ARGS << endl << endl;
            cout << usage;
            return ERROR_ARGS_CODE;
        }
        
        strPort= argv[2];
    }
    
    // try to convert the port number string to an int
    int portNum = -1; // initialize to invalid value until we read in the port
    size_t positionPortNum= 0;
    
    try {
    portNum = stoi(strPort, &positionPortNum);
    }
    catch (...) {  // invalid port arg
        cout << ERROR_PORT << endl << endl;
        cout << usage;
        return ERROR_PORT_CODE;
    }
    
    // check to make sure that there weren't any trailing chars on the port number
    if (positionPortNum != strPort.size()) {
        cout << ERROR_PORT << endl << endl;
        cout << usage;
        return ERROR_PORT_CODE;
    }
    
    // if port number is in valid range, set the port
    if (portNum >= LOWEST_PORT && portNum <= HIGHEST_PORT) cout << success << portNum << endl;
    else {  // invalid port, error
        cout << ERROR_PORT << endl << endl;
        cout << usage;
        return ERROR_PORT_CODE;
    }
    
    // things worked, return success
    return 0;
}

vector<string> readFile(const string& fileName) {
    // open the file
    ifstream inFile(fileName);
    vector<string> fileContents;
    
    // read in the file line by line
    while (inFile.good() && !inFile.eof()) {
        string tempStr;
        getline(inFile, tempStr);
        fileContents.push_back(tempStr);
    }
    
    // return all of its text as a single string.
    return fileContents;
}

string readEnv(const string& varName) {
    // try getting the value of the variable
    char* tempChar = getenv(varName.c_str());
    
    // check if anything was retrieved
    if (tempChar == nullptr) return "";
    else {
        string str = tempChar;
        return str;
    }
}

string getLang() {
    // 1. try getting the value for LANGUAGE variable
    string envValue = readEnv("LANGUAGE");
    
    // 1.a. See if we can a extract language from it, then break out if we found one
    // check for known bad values first
    if (envValue != "C.UTF-8" && envValue != "C" && envValue != "") { // check for a language
        if (verifyLang(envValue)) return envValue.substr(0,2);
        else { // bad language
            cout << "Warning: Bad language specification in environment variable LANGUAGE=" << envValue << ". Using English." << endl;
            return "en";
        }
    }

    // 2. try LC_ALL
    envValue = readEnv("LC_ALL");
    
    // 2.a. See if we can a extract language from it, then break out if we found one
    // check for known bad values first
    if (envValue != "C.UTF-8" && envValue != "C" && envValue != "") { // check for a language
        if (verifyLang(envValue)) return envValue.substr(0,2);
        else { // bad language
            cout << "Warning: Bad language specification in environment variable LC_ALL=" << envValue << ". Using English." << endl;
            return "en";
        }
    }
    
    // 3. try LC_MESSAGES
    envValue = readEnv("LC_MESSAGES");
    
    // 3.a. See if we can a extract language from it, then break out if we found one
    // check for known bad values first
    if (envValue != "C.UTF-8" && envValue != "C" && envValue != "") { // check for a language
        if (verifyLang(envValue)) return envValue.substr(0,2);
        else { // bad language
            cout << "Warning: Bad language specification in environment variable LC_MESSAGES=" << envValue << ". Using English." << endl;
            return "en";
        }
    }
    
    // 4. try LANG
    envValue = readEnv("LANG");
    
    // 4.a. See if we can a extract language from it, then break out if we found one
    // check for known bad values first
    if (envValue != "C.UTF-8" && envValue != "C" && envValue != "") { // check for a language
        if (verifyLang(envValue)) return envValue.substr(0,2);
        else { // bad language
            cout << "Warning: Bad language specification in environment variable LANG=" << envValue << ". Using English." << endl;
            return "en";
        }
    }
    
    // 5. if no language info found, default to English
    return "en";
}

bool verifyLang(const string& langCode) {
    // check to make sure that length is long enough
    if (langCode.size() < 2) return false;
    
    // check to make sure that first two letters are lowercase
    if (!islower(langCode[0]) || !islower(langCode[1])) return false;
    
    // if string is 2 chars, it is good
    if (langCode.size() == 2) return true;
    
    // if the string is longer check to make sure the third char is either '.' or '_'
    if (langCode[2] != '.' && langCode[2] != '_') return false;
    
    // make sure there are more characters to follow
    if (langCode.size() == 3) return false;
    
    if (langCode[2] == '.') { // check for UTF-8
        if (langCode.substr(3) == "UTF-8") return true;
        else return false;
    }
    
    // at this point, we know that we have the language and an '_'
    // check for locale
    if (langCode.size() < 5) return false;
    
    // check locale for uppercase
    if (!isupper(langCode[3]) || !isupper(langCode[4])) return false;
    
    // if this is the end of the string, it is good.
    if (langCode.size() == 5) return true;
    
    // there is more to the string; check UTF-8 and then quit
    if (langCode.substr(5) == ".UTF-8") return true;
    else return false;
}

void setGlobals(string langCode) {
    // check if specified language files exist first
    bool fExists = true;
    fExists &= fileExists(langCode + "/portsetter.usage_" + langCode + ".txt");
    fExists &= fileExists(langCode + "/portsetter.about_" + langCode + ".txt");
    fExists &= fileExists(langCode + "/portsetter.msg_" + langCode + ".txt");
    if (!fExists) { // if language files don't exist, print an error message and use English
        cout << "Missing " << langCode << " translation files. Using English." << endl;
        langCode = "en";
    }
    
    // set the usage
    vector<string> temp = readFile(langCode + "/portsetter.usage_" + langCode + ".txt");
    for (int i = 0; i < temp.size(); ++i) usage += temp[i] + "\n";
    // set the about
    temp = readFile(langCode + "/portsetter.about_" + langCode + ".txt");
    for (int i = 0; i < temp.size(); ++i) about += temp[i] + "\n";
    // set the messages
    temp = readFile(langCode + "/portsetter.msg_" + langCode + ".txt");
    ERROR_ARGS = temp[0];
    ERROR_PORT = temp[1];
    success = temp[2];
}

bool fileExists(const string& fName) {
    // open file and check stream state
    ifstream tester(fName);
    return tester.good();
}