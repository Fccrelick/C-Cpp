#include "INIParser.h"

int main()
{
	const char* iniContent =
		"; last modified 1 April 2001 by John Doe\n"
		"[owner]\n"
		"name = John Doe\n"
		"organization = Acme Widgets Inc. \n"
		"\n"
		"[database]\n"
		"; use IP address in case network name resolution is not working\n"
		"server = 192.0.2.62\n"
		"port = 143\n"
		"file = \"payroll.dat\"\n";

	printf("=== RAW INI FILE ===\n%s\n", iniContent);
	printf("=== PARSED DATA ===\n");
	ini_parseIni(iniContent);


	// HEX 0 to indicate end of the string
	char edit[256];
	edit[0] = 'L';
	edit[1] = 'O';
	edit[2] = 'L';
	edit[3] = '\0';

	printf(edit);
}