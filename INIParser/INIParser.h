#pragma once
/*
* What pragma once does
* #ifndef INIPARSER_H
* #define INIPARSER_H
*/



#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef void(*ini_callback)(const char* section, const char* key, const char* value);

void ini_parseIniFromFile(const char* filePath, const char* logFilePath, ini_callback callback);
void ini_parseIni(const char* iniData, const char* logFilePath, ini_callback callback);
void ini_appendBuffer(char* buffer, char c);
void ini_stripeBuffer(char* buffer);