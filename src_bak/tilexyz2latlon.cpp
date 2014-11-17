#include <stdio.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include<stdint.h>

#define PI 3.1415926535898
typedef struct tile_xyz{
	int32_t n;
	int32_t x;
	int32_t y;
} TILE_XYZ;

typedef struct latlon{
	double lat_deg;
	double lon_deg;
} LAT_LON;


LAT_LON latlon2tilexyz(TILE_XYZ tile)
{
	LAT_LON result;
	double tile_num = 1 << tile.n; 
	double lat_rad = atan(sinh(PI * (1 - 2 * tile.y / tile_num)));
	double lon_deg = tile.x / tile_num * 360.0 - 180.0;
	result.lat_deg = lat_rad * 180.0 / PI;
	result.lon_deg = lon_deg;
	return result;
}


int main()
{
	TILE_XYZ tile;
	tile.n = 18;
	tile.x = 216452;
 	tile.y = 106593;	
	for(int i = 4; i < 20; i++)
	{
		LAT_LON ustc = latlon2tilexyz(tile);
		printf("%f %f \n", ustc.lat_deg, ustc.lon_deg);
	}
	return 0;
}
