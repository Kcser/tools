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


TILE_XYZ latlon2tilexyz(int32_t n, double lon_deg, double lat_rad)
{
	TILE_XYZ result;
	result.n = n;
	int32_t tile_num = 1 << n; 
	int32_t xtile = tile_num * ((lon_deg + 180) / 360);
	int32_t ytile = tile_num * (1 - (log(tan(lat_rad) + 1 / cos(lat_rad)) / PI)) / 2;
	result.x = xtile;
	result.y = ytile;
	return result;
}


int main()
{
	double lat_deg = 31.83892;
	double lon_deg = 117.25092;
	double lat_rad = lat_deg * PI / 180.0;
	for(int i = 4; i < 20; i++)
	{
		TILE_XYZ ustc = latlon2tilexyz(i, lon_deg, lat_rad);
		printf("%d %d %d \n", ustc.n, ustc.x, ustc.y);
	}
	return 0;
}
