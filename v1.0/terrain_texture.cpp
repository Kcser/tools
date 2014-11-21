#include "terrain.h"


#define SIZE 30


int PRINT(POINT_LATLON point, POINT_LATLON_Z *point_z, int p_len, int *index, int index_len)
{
	POINT_XYZ result = p_in_faces(point_z, p_len, index, index_len, point);
	printf("%.2f %.2f %.2f ",result.x, result.y,result.z);
	return 0;
}

int main()
{
	//set the position
	POINT_LATLON p;
	p.lat_deg = 31.84557;
	p.lon_deg = 117.23905;
	TILE_XYZ base_tile = latlon2tilexyz(19, p);
	
	TILE_XYZ tile[SIZE][SIZE];
	int k = 18;

	
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			tile[i][j].n = k;
			tile[i][j].x = (base_tile.x>>(19-k)) + i;
			tile[i][j].y = (base_tile.y>>(19-k)) + j;
		}
	}
	//get in the terrain data
	const char *terrain_file = "../data/terrain/31.8_117.2";
	int p_len;
	POINT_LATLON_Z *p_array;
	get_in_terrain(terrain_file, &p_array, &p_len);
	int height = sqrt(p_len);
	int *index = nest_index(height, height);
	int index_len = 8 * (height - 1) * (height - 1);



	printf("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<!DOCTYPE X3D PUBLIC \"ISO//Web3D//DTD X3D 3.0//EN\" \"http://www.web3d.org/specifications/x3d-3.0.dtd\">\n<X3D xmlns:xsd='http://www.w3.org/2001/XMLSchema-instance' profile='Immersive' version='3.0' xsd:noNamespaceSchemaLocation='http://www.web3d.org/specifications/x3d-3.0.xsd'>\n<Scene>\n");
	for(int i = 0; i < SIZE-1; i++)
	{
		for(int j = 0; j < SIZE-1; j++)
		{
			printf("	<Group id='%d_%d_%d'>\n", tile[i][j].n, tile[i][j].x,tile[i][j].y);
			printf(" 		<shape>\n			<Appearance>\n				<ImageTexture repeatS='true' repeatT='true' url='http://localhost/osm_tiles/%d/%d/%d.png' />\n",tile[i][j].n, tile[i][j].x,tile[i][j].y);
			printf("			</Appearance>\n");
			printf("			<IndexedFaceSet coordIndex='");
			printf("0 1 2 3 0 -1");
			printf("'       convex='false' solid='false'>\n				<Coordinate point='\n");
			POINT_LATLON top_left = tilexyz2latlon(tile[i][j]);
			POINT_LATLON bottom_left = tilexyz2latlon(tile[i][j+1]);
			POINT_LATLON bottom_right = tilexyz2latlon(tile[i+1][j+1]);
			POINT_LATLON top_right = tilexyz2latlon(tile[i+1][j]);
			PRINT(bottom_left, p_array, p_len, index, index_len);
			PRINT(top_left, p_array, p_len, index, index_len);
			PRINT(top_right, p_array, p_len, index, index_len);
			PRINT(bottom_right, p_array, p_len, index, index_len);
			printf("'/>\n");
			printf("				<TextureCoordinate point='0.0 0.0 0.0 1.0 1.0 1.0 1.0 0.0'/>\n");
			printf("			</IndexedFaceSet>\n		</shape>\n	</Group>\n");
		}
	}	
	printf("</Scene>\n");
	printf("</X3D>");
	return 0;
}
	
