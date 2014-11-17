/*modified by 
 * 	Zengshi Huang 
 * 	Time : 2014 11.10
 * this file is used to compute the point 
 * in xyz from latitude and longitude
 */

#include "../inc/head.h"

POINT_XYZ latlon2xyz(POINT_LATLON point){
	POINT_XYZ result;
	double lat_rad = point.lat_deg * PI / 180.0 ;
	double lon_rad = point.lon_deg *PI / 180.0;
	result.x = R * cos(lat_rad) * sin(lon_rad);
	result.y = R * sin(lat_rad);
	result.z = R * cos(lat_rad) * cos(lon_rad);
	return result;
}

