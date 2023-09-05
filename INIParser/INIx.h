#pragma once

#include "INIApi.h"
#include "INIParser.h"

#include <stdlib.h>
#include <string.h>

typedef struct __inix_kv
{
	char* key;
	char* value;

	struct __initx_kv* next_kv;
} inix_kv;

typedef struct __inix_section
{
	char* name;
	struct __initx_kv* firstKv;
	
	struct __inix_section* nextSection;
} inix_section;

typedef struct __inix_data
{
	struct __initx_section* firstSection;
	int sectionArraySize;
} inix_data;

// Public DOM api
INI_API inix_data* inix_new();
INI_API void inix_parseIniFromFile(inix_data* data, const char* filePath, const char* logFilePath);
INI_API void inix_parseIni(inix_data* data, const char* iniData, const char* logFilePath);
INI_API void inix_close(inix_data* data);
INI_API int inix_section_exists(inix_data* data, const char* name);
INI_API int inix_key_exists(inix_data* data, const char* section, const char* key);
INI_API const char* inix_get(inix_data* data, const char* section, const char* key);
INI_API void inix_enumerate(inix_data* data, ini_callback callback, void* userdata);

// Internal helper function
inix_kv* inix_new_kv(const char* key, const char* value);
inix_kv* inix_get_kv(inix_kv* root, const char* name);
void inix_append_kv(inix_kv* root, const char* key, const char* value);
void inix_close_kv(inix_kv* kv);

inix_section* inix_new_section(const char* name);
inix_section* inix_append_section(inix_section* root, const char* name);
inix_section* inix_get_section(inix_section* root, const char* name);
void inix_append_kv_to_section(inix_section* section, const char* key, const char* value);
void inix_close_section(inix_section* section);

inix_section* inix_ensure_section(inix_data* data,const char* name);
void inix_append_kv_to_data(inix_data* data, const char* section, const char* key, const char* value);