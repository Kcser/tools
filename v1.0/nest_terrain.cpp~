#include "terrain.h"



int nest_terrain(const char *in_file, std::vector<POINT_XYZ> *points, int **index, int *length)
{
	std::vector<POINT_LATLON_Z> point_z;
	get_in_terrain(in_file, &point_z);
	int p_length = 0;
	for(std::vector<POINT_LATLON_Z>::iterator it = point_z.begin();
			it != point_z.end();
			it ++){
		POINT_XYZ point = p_latlon_z2p_xyz(*it);
		points->push_back(point);
		p_length ++;
	}
	int height = sqrt(p_length);
	*length = 8*(height - 1)*(height - 1);
	int *a = nest_index(height, height );
	*index = a;
	return 0;
}

int out_put(std::vector<POINT_XYZ> *points, int *index, int length)
{
	printf("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<!DOCTYPE X3D PUBLIC \"ISO//Web3D//DTD X3D 3.0//EN\" \"http://www.web3d.org/specifications/x3d-3.0.dtd\">\n<X3D xmlns:xsd='http://www.w3.org/2001/XMLSchema-instance' profile='Immersive' version='3.0' xsd:noNamespaceSchemaLocation='http://www.web3d.org/specifications/x3d-3.0.xsd'>\n	<Scene>\n		<Shape>\n			<Appearance>\n				<Material ambientIntensity='0.2' diffuseColor='0.8 0.8 0.8' emissiveColor='0 0 0' shininess='0.2' specularColor='0 0 0' transparency='0.0' />\n				</Appearance>\n			<IndexedFaceSet coordIndex='\n");
	for(int i = 0; i < length; i ++)
	{
		std::cout<<index[i]<<" ";
	}
	std::cout<<std::endl;
	printf("			'	convex='true' solid='true' creaseangle='15.0'>\n			<Coordinate point='\n");
	for(std::vector<POINT_XYZ>::iterator it = points->begin();
			it != points->end();
			it ++)
	{
		std::cout<<std::setprecision(2)<<std::fixed<<it->x<<" "<<it->y<<" "<<it->z<<" ";
	}
	std::cout<<std::endl;
	printf("'/>\n");
	printf("			</IndexedFaceSet>\n		</Shape>\n	</Scene>\n</X3D>");
	return 0;
}

int main()
{
	std::vector<POINT_XYZ> points;
	int *index;
	int length;
	nest_terrain("../data/terrain/31.1_116.1", &points, &index, &length);
	out_put(&points, index, length);
	return 0;
}
