#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <string.h>

int main()
{
	int32_t arrayA[32];
	int32_t arrayB[32];

	// Init Arrays
	for (int32_t i = 0; i < 32; i++)
	{
		arrayA[i] = i * 11;
	}
	// 0xFF == -1 || 0x00 == 0
	memset(arrayB, 0xFF, 32 * sizeof(int32_t));

	// Compared Arrays (compared memory directly)
	int32_t abEqual = memcmp(arrayA, arrayB, 32 * sizeof(int32_t)) == 0;
	printf("Arrays Equal before copy: %i", abEqual);

	// Copy arrays (copying memory directly)
	memcpy(arrayB, arrayA, 32 * sizeof(int32_t));

	// Compared Arrays (compared memory directly)
	abEqual = memcmp(arrayA, arrayB, 32 * sizeof(int32_t)) == 0;
	printf("Arrays Equal after copy: %i", abEqual);
}