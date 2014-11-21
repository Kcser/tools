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

double area(POINT_LATLON p1, POINT_LATLON p2, POINT_LATLON p3)
{
	double a_x = p1.lon_deg;
	double a_y = p1.lat_deg;
	double b_x = p2.lon_deg;
	double b_y = p2.lat_deg;
	double c_x = p3.lon_deg;
	double c_y = p3.lat_deg;
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
	double lat_rad = point.coord.lat_deg * PI /180.0;
	double lon_rad = point.coord.lon_deg * PI /180.0;
	double z_order = point.z;
	result.x = (R + z_order)*cos(lat_rad)*sin(lon_rad);
	result.y = (R + z_order)*sin(lat_rad);
	result.z = (R + z_order)*cos(lat_rad)*cos(lon_rad);	
	return result;
}
POINT_XYZ p_latlon_z2p_xyz(POINT_LATLON point, double z)
{
	POINT_XYZ result;
	double lat_rad = point.lat_deg * PI /180.0;
	double lon_rad = point.lon_deg * PI /180.0;
	double z_order = z;
	result.x = (R + z_order)*cos(lat_rad)*sin(lon_rad);
	result.y = (R + z_order)*sin(lat_rad);
	result.z = (R + z_order)*cos(lat_rad)*cos(lon_rad);	
	return result;
}
double p_insert_face(POINT_LATLON_Z p1, POINT_LATLON_Z p2, POINT_LATLON_Z p3, POINT_LATLON p)
{
	double x1 = p1.coord.lon_deg;
	double y1 = p1.coord.lat_deg;
	double z1 = p1.z;
	double x2 = p2.coord.lon_deg;
	double y2 = p2.coord.lat_deg;
	double z2 = p2.z;
	double x3 = p3.coord.lon_deg;
	double y3 = p3.coord.lat_deg;
	double z3 = p3.z;
	double x = p.lon_deg;
	double y = p.lat_deg;
	
	double a=(y2-y1)*(z3-z1)-(y3-y1)*(z2-z1);
	double b=(z2-z1)*(x3-x1)-(z3-z1)*(x2-x1);
	double c=(x2-x1)*(y3-y1)-(x3-x1)*(y2-y1);
	double d=a*(-1)*x1-b*y1-c*z1;
	double h=(a*x+b*y+d)/((-1)*c);

	return h;
}

int equal(double a, double b)
{
	if(fabs(a-b) < 0.0000001)
		return 1;
	else
		return 0;
}
int check_p_face(const POINT_LATLON a,const POINT_LATLON b, const POINT_LATLON c, POINT_LATLON p)
{
	double all = area(a,b,c);
	double s1 = area(a,b,p);
	double s2 = area(a,c,p);
	double s3 = area(b,c,p);
	double s = s1 + s2 + s3;
	if(equal(all, s))
		return 1;
	else
		return 0;
}

POINT_XYZ p_in_faces(const POINT_LATLON_Z *p, int p_len, const int *index, int index_len, POINT_LATLON in_point)
{
	POINT_XYZ result;
	result = latlon2xyz(in_point);
	for(int i =0; i < index_len; i+=4)
	{
		if(check_p_face(p[index[i]].coord, p[index[i+1]].coord, p[index[i+2]].coord, in_point))
		{
			double height = p_insert_face(p[index[i]], p[index[i+1]], p[index[i+2]], in_point);
			result = p_latlon_z2p_xyz(in_point, height);
			return result;
		}
		
	}
	return result;
}

double p_in_faces1(const POINT_LATLON_Z *p, int p_len, const int *index, int index_len, POINT_LATLON in_point)
{
	double result = 0;
	for(int i =0; i < index_len; i+=4)
	{
		if(check_p_face(p[index[i]].coord, p[index[i+1]].coord, p[index[i+2]].coord, in_point))
		{
			result = p_insert_face(p[index[i]], p[index[i+1]], p[index[i+2]], in_point);
			return result;
		}
		
	}
	return result;
}


