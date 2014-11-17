/*Modified by
 * 	Zengshi Huang
 * 	Time : 2014 11.10
 * 	this file is used to compute the tile number
 * 	in x y z from a point in longitude and latitude
 */

#include "../inc/head.h"

TILE_XYZ latlon2tilexyz(int32_t n, POINT_LATLON point)
{
	TILE_XYZ result;
	result.n = n;
	double lon_deg = point.lon_deg;
	double lat_rad = point.lat_deg * PI /180.0;
	int32_t tile_num = 1 << n; 
	int32_t xtile = tile_num * ((lon_deg + 180) / 360);
	int32_t ytile = tile_num * (1 - (log(tan(lat_rad) + 1 / cos(lat_rad)) / PI)) / 2;
	result.x = xtile;
	result.y = ytile;
	return result;
}

