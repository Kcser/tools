/*Modified by 
 * 	Zengshi Huang
 * 	Time :2014 11.10
 * 	this file is used to compute the left bottom corner
 * 	in latitude and longitude of a tile from tile level
 * 	and tile coordinate.
 */

#include "../inc/head.h"

POINT_LATLON tilexyz2latlon(TILE_XYZ tile)
{
	POINT_LATLON result;
	double tile_num = 1 << tile.n; 
	double lat_rad = atan(sinh(PI * (1 - 2 * tile.y / tile_num)));
	double lon_deg = tile.x / tile_num * 360.0 - 180.0;
	result.lat_deg = lat_rad * 180.0 / PI;
	result.lon_deg = lon_deg;
	return result;
}

