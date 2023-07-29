#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

uint64_t GetUIDa()
{
	static uint64_t id = 0;
	return id++;
}

uint64_t GetUIDb()
{
	static uint64_t id = 0;
	return id++;
}

int main()
{
	for (uint64_t i = 0; i < 64; i++)
	{
		uint64_t uida = GetUIDa();
		uint64_t uidb = GetUIDb();
		printf("UIDa: %"PRIu64" & UIDb: %"PRIu64"\n", uida, uidb);
	}
	const int32_t count = 64;
	const int32_t size = count * sizeof(int32_t);

	int32_t* const arrayA = malloc(size);
	int32_t* const arrayB = malloc(size);

	if (arrayA && arrayB)
	{
		// Init Arrays
		for (int32_t i = 0; i < count; i++)
		{
			arrayA[i] = i * 11;
		}
		// 0xFF == -1 || 0x00 == 0
		memset(arrayB, 0xFF, size);

		// Compared Arrays (compared memory directly)
		int32_t abEqual = memcmp(arrayA, arrayB, size) == 0;
		printf("Arrays Equal before copy: %i", abEqual);

		// Copy arrays (copying memory directly)
		memcpy(arrayB, arrayA, size);

		// Compared Arrays (compared memory directly)
		abEqual = memcmp(arrayA, arrayB, size) == 0;
		printf("Arrays Equal after copy: %i", abEqual);
	}

	// Free memory
	if (arrayA) free(arrayA);
	if (arrayB) free(arrayB);
}