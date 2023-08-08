#include <INIParser.h>

#include <stdio.h>
#include <string.h>

#ifdef MY_DEBUG
#define  MY_NAME "Debug Fernando"
#define myGreet(name) printf_s("Debug Hello %s!\n", name);
#define debugOnly(expr) expr
#else
#define  MY_NAME "Fernando"
#define myGreet(name) printf_s("Hello %s!\n", name);
#define debugOnly(expr)
#endif

#if defined(INIEXPLORER_DEFAULT_FORMAT1) && !defined(INIEXPLORER_DEFAULT_FORMAT2)
#define INIEXPLORER_FORMAT_CALLBACK iniDataReady1
#elif defined(INIEXPLORER_DEFAULT_FORMAT2) && !defined(INIEXPLORER_DEFAULT_FORMAT1)
#define INIEXPLORER_FORMAT_CALLBACK iniDataReady2
#else
#error Please define EXACTLY one default format!
#endif




void iniDataReady1(const char* section, const char* key, const char* value)
{
	printf_s("[%s] \n%s = %s\n\n", section, key, value);
}

void iniDataReady2(const char* section, const char* key, const char* value)
{
	printf_s("%s\\%s is %s\n", section, key, value);
}

int main(int argc, char** argv)
{
	const char* name = MY_NAME;
	myGreet(name);
	debugOnly(printf_s("Test 1234 Debug\n"));
	
	// Validate argument1 count
	if (argc < 2 || argc > 4)
	{
		printf_s("usage: INIParser [PathToIniFile]  <OPTIONAL:Format(1/2)> <OPTIONAL:PathToLogFile>");
		return -1;
	}

	// Check the format
	ini_callback callback = INIEXPLORER_FORMAT_CALLBACK;
	if (argc >= 3)
	{
		switch (*argv[2])
		{
			case '1':
				callback = iniDataReady1;
				break;
			case '2':
				callback = iniDataReady2;
				break;
			default:
				printf_s("Invalid format!");
				return -1;
		}
		
	}

	// Check logfile path
	const char* logfile = NULL;
	if (argc >= 4)
	{
		logfile = argv[2];
	}

	// Parse the ini file
	ini_parseIniFromFile(argv[1], logfile, callback);


	// HEX 0 to indicate end of the string
	char edit[256];
	edit[0] = 'L';
	edit[1] = 'O';
	edit[2] = 'L';
	edit[3] = '\0';

	printf(edit);
}
