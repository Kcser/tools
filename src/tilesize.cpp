/*modified by 
 * 	Zengshi Huang 
 * 	Time : 2014 11.10
 * this file is used to compute the size
 * in latlon from the tile level
 */
#include "../inc/head.h"

TILE_SIZE tilesize(int32_t n)
{
	TILE_SIZE result;
	double tile_num = 1 << n;
	result.lon_deg = 360.0 / tile_num;
	result.lat_deg = 170.1022 / tile_num;
	return result;
}


