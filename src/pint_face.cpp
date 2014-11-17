#include "../inc/head.h"

double min(double a,double b){
	if(a < b)
		return a;
	else
		return b;
}
double max(double a,double b){
	if(a> b)
		return a;
	else
		return b;
}

double area(POINT_LATLON a, POINT_LATLON b, POINT_LATLON c)
{
	double a_x = a.lon_deg;
	double a_y = a.lat_deg;
	double b_x = b.lon_deg;
	double b_y = b.lat_deg;
	double c_x = c.lon_deg;
	double c_y = c.lat_deg;
	double a=sqrt((a_x-b_x)*(a_x-b_x)+(a_y-b_y)*(a_y-b_y));
	double b=sqrt((a_x-c_x)*(a_x-c_x)+(a_y-c_y)*(a_y-c_y));
	double c=sqrt((b_x-c_x)*(b_x-c_x)+(b_y-c_y)*(b_y-c_y));
	double p=(a+b+c)/2;
	double s=sqrt(p*(p-a)*(p-b)*(p-c));
	return s;
}
POINT_XYZ p_latlon_z2p_xyz(POINT_LATLON_Z point)
{
	POINT_XYZ result;
	double lat_rad = point.lat_deg * PI /180.0;
	double lon_rad = point.lon_deg * PI /180.0;
	double z_order = point.z;
	result.x = (R + z_order)*cos(lat_rad)*cos(lon_rad);
	result.y = (R + z_order)*sin(lat_rad);
	result.z = (R + z_order)*cos(lat_rad)*sin(lon_rad);	
	return result;
}
POINT_XYZ p_in_triangle(POINT_LATLON_Z p1, POINT_LATLON_Z p2, POINT_LATLON_Z p3, POINT_LATLON p)
{
	POINT_XYZ result;


	return result;
}


.


