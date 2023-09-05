#include <stdio.h>
#include <stdlib.h>

typedef enum
{
	CoordinateDimension2D = 2,
	CoordinateDimension3D = 3,
} CoordinateDimension;

typedef struct
{
	CoordinateDimension dimension;
	union
	{
		struct
		{
			int x;
			int y;
			int z;
		} d3;

		struct
		{
			int x;
			int y;
		} d2;
	};
} Cordinate;

Cordinate makeCordinate2D(int x, int y)
{
	Cordinate c;
	c.dimension = CoordinateDimension2D;
	c.d2.x = x;
	c.d2.y = y;
	return c;
}

Cordinate makeCordinate3D(int x, int y, int z)
{
	Cordinate c;
	c.dimension = CoordinateDimension3D;
	c.d3.x = x;
	c.d3.y = y;
	c.d3.z = z;
	return c;
}

void doWork(Cordinate c)
{
	if (c.dimension == CoordinateDimension2D)
	{
		printf_s("Cordinate 2D: x: %i y %i\n", c.d2.x, c.d2.y);
	}
	else if (c.dimension == CoordinateDimension3D)
	{
		printf_s("Cordinate 3D: x: %i y %i z: %i\n", c.d3.x, c.d3.y, c.d3.z);
	}
}

int main() 
{
	doWork(makeCordinate2D(5, 5));
	doWork(makeCordinate3D(5, 5, -5));
}