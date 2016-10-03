// Collin Anderson
// CS 3370
// Instructor: Professor Wagstaff
// portsetter Test Programming Project
// File: testsetport.cpp
// Contents: testing driver for the portsetter program
// Date: 9/13/2016
// I declare that the following source code was written solely by me, or
// provided by the instructor. I understand that copying any source code,
// in whole or in part, constitutes cheating, and that I will receive a
// zero in this assignment if I am found in violation of this policy.

#include <iostream>
#include <string>
using namespace std;

// function prototypes

// Run test function
// Purpose: To run portsetter with the specified command line arguments and compare its output with expected output
// Parameters: A string with the command line arguments to use, an int for the expected return code,
// and a string containing the path to a file with the command's expected output.
// Returns: True if the test performed as expected, or false otherwise.
bool runTest(const string&, int, const string&);

// Run test function (pre-command overload)
// Purpose: To run portsetter with the specified command line arguments and compare its output with expected output.
// Parameters: A string with commands to run before portsetter, a string with the command line arguments to use with portsetter,
// an int for the expected return code, and a string containing the path to a file with the command's expected output.
// Returns: True if the test performed as expected, or false otherwise.
bool runTest(const string&, const string&, int, const string&);

// Output Result function
// Purpose: To output to the user (standard out) the results for a given test case.
// Parameters: Whether the test succeeded or not as a boolean,
// and the command line arguments used in the test as a string.
void outputResult(bool, const string&);

// main function
// Purpose: The entry-point to my C++ program.
// Returns: The error code denoting whether my program ran successfully or not.
int main() {
    // test success booleans
    bool allTests = true;
    bool indivTest = true;
    
    // run the test, output the result, and update the overall test success status
    // positive tests
    cout << "----- Positive tests -----" << endl;
    
    // usage only
    indivTest = runTest("", 0, "usage.txt");
    outputResult(indivTest, "");
    allTests &= indivTest;
    
    indivTest = runTest("-h", 0, "usage.txt");
    outputResult(indivTest, "-h");
    allTests &= indivTest;
    
    indivTest = runTest("-?", 0, "usage.txt");
    outputResult(indivTest, "-?");
    allTests &= indivTest;
    
    indivTest = runTest("--help", 0, "usage.txt");
    outputResult(indivTest, "--help");
    allTests &= indivTest;
    
    indivTest = runTest("-!", 0, "about.txt");
    outputResult(indivTest, "-!");
    allTests &= indivTest;
    
    indivTest = runTest("--about", 0, "about.txt");
    outputResult(indivTest, "--about");
    allTests &= indivTest;
    
    indivTest = runTest("-v", 0, "version.txt");
    outputResult(indivTest, "-v");
    allTests &= indivTest;
    
    indivTest = runTest("--version", 0, "version.txt");
    outputResult(indivTest, "--version");
    allTests &= indivTest;
    
    // successfully set port
    indivTest = runTest("-p 4040", 0, "success.txt");
    outputResult(indivTest, "-p 4040");
    allTests &= indivTest;
    
    indivTest = runTest("--port 4040", 0, "success.txt");
    outputResult(indivTest, "--port 4040");
    allTests &= indivTest;
    
    indivTest = runTest("-p -e", 0, "success2.txt");
    outputResult(indivTest, "-p -e");
    allTests &= indivTest;
    
    indivTest = runTest("-p -e METEOR_PORT", 0, "success2.txt");
    outputResult(indivTest, "-p -e METEOR_PORT");
    allTests &= indivTest;
    
    indivTest = runTest("--port -e", 0, "success2.txt");
    outputResult(indivTest, "--port -e");
    allTests &= indivTest;
    
    indivTest = runTest("--port -e METEOR_PORT", 0, "success2.txt");
    outputResult(indivTest, "--port -e METEOR_PORT");
    allTests &= indivTest;
    
    // negative tests
    cout << "----- Negative tests -----" << endl;
    indivTest = runTest("help", 2, "errArg.txt");
    outputResult(indivTest, "help");
    allTests &= indivTest;
    
    indivTest = runTest("-help", 2, "errArg.txt");
    outputResult(indivTest, "-help");
    allTests &= indivTest;
    
    indivTest = runTest("--h", 2, "errArg.txt");
    outputResult(indivTest, "--h");
    allTests &= indivTest;
    
    indivTest = runTest("-h --help", 2, "errArg.txt");
    outputResult(indivTest, "-h --help");
    allTests &= indivTest;
    
    indivTest = runTest("-hs", 2, "errArg.txt");
    outputResult(indivTest, "-hs");
    allTests &= indivTest;
    
    indivTest = runTest("--v", 2, "errArg.txt");
    outputResult(indivTest, "--v");
    allTests &= indivTest;
    
    indivTest = runTest("-h --about", 2, "errArg.txt");
    outputResult(indivTest, "--help");
    allTests &= indivTest;
    
    indivTest = runTest("-p --port 9", 2, "errArg.txt");
    outputResult(indivTest, "-p --port 9");
    allTests &= indivTest;
    
    indivTest = runTest("-p 77 33", 2, "errArg.txt");
    outputResult(indivTest, "-p 77 33");
    allTests &= indivTest;
    
    indivTest = runTest("-p -21", 1, "errPort.txt");
    outputResult(indivTest, "-p -21");
    allTests &= indivTest;
    
    indivTest = runTest("-p 0", 1, "errPort.txt");
    outputResult(indivTest, "-p 0");
    allTests &= indivTest;
    
    indivTest = runTest("--port", 2, "errArg.txt");
    outputResult(indivTest, "--port");
    allTests &= indivTest;
    
    indivTest = runTest("-p 90642", 1, "errPort.txt");
    outputResult(indivTest, "-p 90642");
    allTests &= indivTest;
    
    indivTest = runTest("-x 45321", 2, "errArg.txt");
    outputResult(indivTest, "-x 45321");
    allTests &= indivTest;
    
    indivTest = runTest("-P 714", 2, "errArg.txt");
    outputResult(indivTest, "-P 714");
    allTests &= indivTest;
    
    indivTest = runTest("-p -e NOT_A_VAR", 1, "errPort.txt");
    outputResult(indivTest, "-p -e NOT_A_VAR");
    allTests &= indivTest;
    
    indivTest = runTest("--port -e PORT -h", 2, "errArg.txt");
    outputResult(indivTest, "--port -e PORT -h");
    allTests &= indivTest;
    
    indivTest = runTest("-e", 2, "errArg.txt");
    outputResult(indivTest, "-e");
    allTests &= indivTest;
    
    indivTest = runTest("-e --port PORT", 2, "errArg.txt");
    outputResult(indivTest, "-e --port PORT");
    allTests &= indivTest;
    
    indivTest = runTest("-p -e SHELL", 1, "errPort.txt");
    outputResult(indivTest, "-p -e SHELL");
    allTests &= indivTest;
    
    // language tests
    cout << "----- Language tests -----" << endl;
    indivTest = runTest("export LC_MESSAGES=\"es_MX.UTF-8\"", "-p 4040", 0, "successES.txt");
    outputResult(indivTest, "-p 4040 (Spanish)");
    allTests &= indivTest;
    
    indivTest = runTest("export LC_MESSAGES=\"pl_PL\"", "-p 4040", 0, "successPL.txt");
    outputResult(indivTest, "-p 4040 (Polish)");
    allTests &= indivTest;
    
    indivTest = runTest("export LC_MESSAGES=\"pg_LATIN\"", "-tx", 2, "errArgPG.txt");
    outputResult(indivTest, "-tx (LC_MESSAGES=pg_LATIN)");
    allTests &= indivTest;
    
    // display the final result for all the tests
    cout << endl;
    outputResult(allTests, "All tests");
    if (allTests) return 0;
    else return 1;
}

bool runTest(const string& commands, int expectedReturn, const string& expectedOutputFile) {
    // run the command, and redirect its output to a file called test.txt in the same (current working) directory
    string commandLine = "setport " + commands + " > test.txt";
    int retCode = system(commandLine.c_str()) / 256;  // correct for endian-ness
    
    // compare actual output to expected output
    string differenceCommand = "diff -b test.txt ./testing/" + expectedOutputFile;
    int differenceCode = system(differenceCommand.c_str()) / 256;
    
    // return results of return code test and output test
    return (retCode == expectedReturn && differenceCode == 0);
}

bool runTest(const string& preCommands, const string& commands, int expectedReturn, const string& expectedOutputFile) {
    // run the command, and redirect its output to a file called test.txt in the same (current working) directory
    string commandLine = preCommands + " && setport " + commands + " > test.txt";
    int retCode = system(commandLine.c_str()) / 256;  // correct for endian-ness
    
    // compare actual output to expected output
    string differenceCommand = "diff -b test.txt ./testing/" + expectedOutputFile;
    int differenceCode = system(differenceCommand.c_str()) / 256;
    
    // return results of return code test and output test
    return (retCode == expectedReturn && differenceCode == 0);
}

void outputResult(bool execAsExp, const string& commands) {
    // output test case name (command arguments)
    cout << "Test case \"" << commands << "\": ";
    
    // if the test was successful, output success, else output failure
    if (execAsExp) cout << "Successful" << endl;
    else cout << "Failure" << endl;
}