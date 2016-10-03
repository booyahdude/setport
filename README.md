# setport Readme/Instructions

To install setport onto your system so that you can run it without going to its directory,
and without typing "./" before it each time, please do the following:

1. Edit the install.sh script, replacing "~/workspace/portsetter/setport" with the path to the setport executable on your system.
 ex. "/bin/setport"
2. Execute the install.sh script by typing "./install.sh" at a terminal window.

--OR--

1. Run the following command in a terminal: "sudo ln -s <path to setport>/setport /usr/local/bin/" where <path to setport> is the local path to the executable on your system.

_*Note that you will need sudo priviledges to do this._


### Adding Languages
1. Make a folder named with the two-digit lowercase language code of the language.
2. Duplicate the english files and change their file names so that the two-digit language code is correct.
3. Replace the English phrases with phrases in your language. Do not modify line breaks.


## Testing setport

Either compile testsetport.cpp and run it, or run the testsetport.cpp.o executable.  It will automatically run pre-defined test
cases and output the results to standard out.

#### **PREREQUISITES:**
You must have errArg.txt, errPort.txt, success.txt, success2.txt, successES.txt, successPL.txt, about.txt,
version.txt and usage.txt in the same directory as the executable. You must also have the following environmental variables*
defined on your system: PORT = 8080, METEOR_PORT = 8080, and SHELL= /bin/bash. You must also ensure that you do not have
the variable NOT_A_VAR on your system.
* You can view your system's environmental variables by typing "env" at a terminal window. To create a variable or set its
value, simply type "export MY_VARIABLE="value"" where MY_VARIABLE is your variable name and value is its value.

**RETURN CODES**: **0** for complete success, **1** if there were errors.
