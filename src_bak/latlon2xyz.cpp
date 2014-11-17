/*modified by 
 * 	Zengshi Huang 
 * 	Time : 2014 11.10
 * this file is used to compute the point 
 * in xyz from latitude and longitude
 */

#include <stdio.h>
#include <math.h>

#define R 6370000
#define PI 3.1415926535898

typedef struct point_xyz{
	double x;
	double y;
	double z;
} POINT_XYZ;

typedef point_latlon{
	double lat_deg;
	double lon_deg;
} POINT_LATLON;

POINT_XYZ latlon2xyz(POINT_LATLON point){
	POINT_XYZ result;
	lat_rad = point.lat_deg * PI / 180.0 ;
	lon_rad = point.lon_deg *PI / 180.0;
	result.x = R * cos(lat_rad) * sin(lon_rad);
	result.y = R * sin(lat_rad);
	result.z = R * cos(lat_rad) * cos(lon_rad);
	return result;
}

