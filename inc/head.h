#include <stdio.h>
#include <math.h>
#include <stdint.h>


#define R 6370000
#define PI 3.1415926535898
typedef struct tile_xyz{
	int32_t n;
	int32_t x;
	int32_t y;
} TILE_XYZ;

typedef struct point_xyz{
	double x;
	double y;
	double z;
} POINT_XYZ;

typedef struct point_latlon{
	double lat_deg;
	double lon_deg;
} POINT_LATLON;

typedef struct tile_size{
	double lon_deg;
	double lat_deg;
} TILE_SIZE;


TILE_XYZ latlon2tilexyz(int32_t n, POINT_LATLON point);
POINT_XYZ latlon2xyz(POINT_LATLON point);
TILE_SIZE tilesize(int32_t n);
POINT_LATLON tilexyz2latlon(TILE_XYZ tile);

