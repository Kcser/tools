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

typedef struct point_latlon_z{
	POINT_LATLON coord;
	double z;
} POINT_LATLON_Z;

typedef struct tile_size{
	double lon_deg;
	double lat_deg;
} TILE_SIZE;


TILE_XYZ latlon2tilexyz(int32_t n, POINT_LATLON point);
POINT_XYZ latlon2xyz(POINT_LATLON point);
TILE_SIZE tilesize(int32_t n);
POINT_LATLON tilexyz2latlon(TILE_XYZ tile);
POINT_XYZ p_latlon_z2p_xyz(POINT_LATLON_Z point);
POINT_XYZ p_insert_face(POINT_LATLON_Z p1, POINT_LATLON_Z p2, POINT_LATLON_Z p3, POINT_LATLON p);
int check_p_face(const POINT_LATLON a,const POINT_LATLON b, const POINT_LATLON c, POINT_LATLON p);
POINT_XYZ p_in_faces(const POINT_LATLON_Z *p, int p_len, const int *index, int index_len, POINT_LATLON in_point);
