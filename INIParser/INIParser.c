#include "INIParser.h"

void ini_parseIni(const char* iniData)
{
	// Working buffer
	char buffer[256];
	*buffer = '\0';

	// Current values
	char currentSection[256];
	*currentSection = '\0';
	char currentKey[256];
	char currentValue[256];


	/*
	* 0 - Ready for INI Data
	* 1 - Comment started
	* 2 - Section Name started
	* 3 - Key started
	* 4 - Key finished
	* 5 - Ready for value
	* 6 - Value started
	* 7 - Invalid data
	*/
	int32_t state = 0;
	for (const char* c = iniData; *c; c++)
	{
		// Waiting for ini data
		switch (state)
		{
		case 0:
			switch (*c)
			{
			case ';': //Start comment
				state = 1;
				break;
			case '[': // Start section name
				state = 2;
				break;
			case ' ':
			case '\t':
			case '\n':
				break;
			default: // Start Key
				ini_appendBuffer(buffer, *c);
				state = 3;
			}
			break;

			// Reading comment
		case 1:
			if (*c == '\n') state = 0; // End Comment
			break;

			// Section name started
		case 2:
			if (*c == ']') // End section name
			{
				strcpy_s(currentSection, 256, buffer);
				*buffer = '\0';
				state = 0;
			}
			else if (*c == '\n') // Invalid section name (discard)
			{
				*buffer = '\0';
				state = 0;
			}
			else
			{
				ini_appendBuffer(buffer, *c);
			}
			break;

			// Key Started
		case 3:
			if (*c == ' ' || *c == '\t')
			{
				strcpy_s(currentKey, 256, buffer);
				*buffer = '\0';
				state = 4; // End key
			}
			else if (*c == '\n')
			{
				state = 0; // Invalid key valye pair
			}
			else
			{
				ini_appendBuffer(buffer, *c);
			}
			break;

			// End of key
		case 4:
			if (*c == '=') state = 5; // Ready for value
			else if (*c == '\n') state = 0; // Invalid key value pair
			else if (!(*c == ' ' || *c == '\t')) state = 7; // Invalid key value pair
			break;

			// Ready for value
		case 5:
			if (*c == '\n') state = 0; // Invalid key value pair
			else if (!(*c == ' ' || *c == '\t'))
			{
				ini_appendBuffer(buffer, *c);
				state = 6; // Begin key
			}
			break;

			// Start of value
		case 6:
			if (*c == '\n')
			{
				ini_stripeBuffer(buffer);
				strcpy_s(currentValue, 256, buffer);
				*buffer = '\0';
				state = 0;

				// Report out
				printf("Propertie: \"%s/%s\": \"%s\"\n", currentSection, currentKey, currentValue);
			}
			else
			{
				ini_appendBuffer(buffer, *c);
			}
			break;

			// Invalid value
		case 7:
			if (*c == '\n') state = 0;
			break;
		}
	}
}

void ini_appendBuffer(char* buffer, char c)
{
	/*
	* old implementation
	* char* cursor;
	* for (cursor = buffer; *cursor; cursor++);
	* cursor[0] = c;
	* cursor[1] = '\0';
	*/

	char str[2] = { c, '\0' };
	strcat_s(buffer, 256, str);
}

void ini_stripeBuffer(char* buffer)
{
	/*
	* old implementation
	* char* cursor;
	* for (cursor = buffer; cursor[1] != '\0'; cursor++);
	* while (*cursor == ' ' || *cursor == '\t')
	* {
	*	*cursor = '\0';
	*	cursor--;
	* }
	*/

	char* c = &buffer[strlen(buffer) - 1];
	if (*c == ' ' || *c == '\t')
	{
		*c = '\0';
		ini_stripeBuffer(buffer);
	}
}