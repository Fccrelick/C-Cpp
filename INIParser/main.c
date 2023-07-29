#include "INIParser.h"

void iniDataReady(const char* section, const char* key, const char* value)
{
	printf_s("[%s] \n%s = %s\n\n", section, key, value);
}

int main(int argc, char** argv)
{
	// Validate argument1 count
	if (argc < 2 || argc > 3)
	{
		printf_s("usage: INIParser [PathToIniFile] <OPTIONAL:PathToLogFile>");
		return -1;
	}

	// Check logfile path
	const char* logfile = NULL;
	if (argc >= 3)
	{
		logfile = argv[2];
	}

	// Parse the ini file
	ini_parseIniFromFile(argv[1], logfile, iniDataReady);


	// HEX 0 to indicate end of the string
	char edit[256];
	edit[0] = 'L';
	edit[1] = 'O';
	edit[2] = 'L';
	edit[3] = '\0';

	printf(edit);
}
