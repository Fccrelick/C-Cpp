#include "INIx.h"

void inix_parseIniFromFile(inix_data* data, const char* filePath, const char* logFilePath)
{
	ini_parseIniFromFile(filePath, logFilePath, inix_append_kv_to_data, data);
}

void inix_parseIni(inix_data* data, const char* iniData, const char* logFilePath)
{
	ini_parseIniFromFile(iniData, logFilePath, inix_append_kv_to_data, data);
}

INI_API void inix_close(inix_data* data)
{
	if (data)
	{
		if (data->firstSection)
		{
			inix_close_section(data->firstSection);
		}
		free(data);
	}
}

int inix_section_exists(inix_data* data, const char* name)
{
	return data->firstSection && inix_get_section(data->firstSection, name);
}

int inix_key_exists(inix_data* data, const char* section, const char* key)
{
	if (data->firstSection)
	{
		inix_section* s = inix_get_section(data->firstSection, section);
		if (s)
		{
			if (s->firstKv)
			{
				return 1 && inix_get_kv(s->firstKv, key);
			}
		}
	}
	
	return 0;
}

const char* inix_get(inix_data* data, const char* section, const char* key)
{
	if (data->firstSection)
	{
		inix_section* s = inix_get_section(data->firstSection, section);
		if (s && s->firstKv)
		{
			inix_kv* kv = inix_get_kv(s->firstKv, key);
			if (kv)
			{
				return kv->value;
			}
		}
	}
	return NULL;
}

INI_API void inix_enumerate(inix_data* data, ini_callback callback, void* userdata)
{
	for (inix_section* section = data->firstSection; section; section = section->nextSection)
	{
		for (inix_kv* kv = section->firstKv; kv; kv = kv->next_kv)
		{
			callback(userdata, section->name, kv->key, kv->value);
		}
	}
}

inix_data* inix_new()
{
	inix_data* data = malloc(sizeof(inix_data));
	if (data)
	{
		data->firstSection = NULL;
	}
	return data;
}

inix_kv* inix_new_kv(const char* key, const char* value)
{
	inix_kv* kv = malloc(sizeof(inix_kv));
	if (kv)
	{
		kv->key = _strdup(key);
		kv->value = _strdup(value);
		kv->next_kv = NULL;
	}
	return kv;
}

inix_kv* inix_get_kv(inix_kv* root, const char* name)
{
	if (strcmp(root->key, name) == 0)
	{
		return root;
	}
	if (root->next_kv)
	{
		return inix_get_kv(root->next_kv, name);
	}
	return NULL;
}

void inix_append_kv(inix_kv* root, const char* key, const char* value)
{
	while (root->next_kv)
	{
		root = root->next_kv;
	}

	root->next_kv = inix_new_kv(key, value);
}

void inix_close_kv(inix_kv* kv)
{
	if (kv->next_kv)
	{
		inix_close_kv(kv->next_kv);
	}

	if(kv->key) free(kv->key);
	if(kv->value) free(kv->value);
	free(kv);
}

inix_section* inix_new_section(const char* name)
{
	inix_section* section = malloc(sizeof(inix_section));
	if (section)
	{
		section->name = _strdup(name);
		section->firstKv = NULL;
		section->nextSection = NULL;
	}
	return section;
}

inix_section* inix_append_section(inix_section* root, const char* name)
{
	while (root->nextSection)
	{
		root = root->nextSection;
	}
	
	root->nextSection = inix_new_section(name);
	return root->nextSection;
}

inix_section* inix_get_section(inix_section* root, const char* name)
{
	inix_section* foundSection = NULL;

	for (inix_section* section = root; section; section = section->nextSection)
	{
		if (strcmp(section->name, name) == 0)
		{
			foundSection = section;
			break;
		}
	}

	return foundSection;
}

void inix_append_kv_to_section(inix_section* section, const char* key, const char* value)
{
	if (section->firstKv)
	{
		inix_append_kv(section->firstKv, key, value);
	}
	else
	{
		section->firstKv = inix_new_kv(key, value);
	}
}

void inix_close_section(inix_section* section)
{
	if (section->nextSection)
	{
		inix_close_section(section->nextSection);
	}
	if (section->firstKv)
	{
		inix_close_kv(section->firstKv);
	}
	
	if (section->name) free(section->name);
	free(section);
}

inix_section* inix_ensure_section(inix_data* data, const char* name)
{
	// Check if section exists
	inix_section* foundSection = NULL;
	if (data->firstSection)
	{
		foundSection = inix_get_section(data->firstSection, name);
	}

	// Insert section if it is not existing
	if (!foundSection)
	{
		if (data->firstSection)
		{
			foundSection = inix_append_section(data->firstSection, name);
		}
		else
		{
			foundSection = data->firstSection = inix_new_section(name);
		}
	}

	return foundSection;
}

void inix_append_kv_to_data(inix_data* data, const char* section, const char* key, const char* value)
{
	inix_section* s = inix_ensure_section(data, section);
	if (s)
	{
		if (s->firstKv)
		{
			inix_kv* kv = inix_get_kv(s->firstKv, key);
			if (kv)
			{
				if (kv->value) free(kv->value);
				kv->value = _strdup(value);
			}
			else
			{
				inix_append_kv(s->firstKv, key, value);
			}
			inix_append_kv(s->firstKv, key, value);
		}
		else
		{
			s->firstKv = inix_new_kv(key, value);
		}
	}
}
