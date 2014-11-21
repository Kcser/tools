/*
 * to get data from database
 * by hzs
 * 
 */
//--------------------------------------------
#include<fstream>
#include<boost/algorithm/string.hpp>
#include<boost/lexical_cast.hpp>
#include "terrain.h"

typedef std::string 	string;

//building configuration
POINT_LATLON b_point[100];
POINT_XYZ floor_point[100];
POINT_XYZ roof_point[100];
int b_index[400];
int b_len;
int b_height;
int b_index_len;


//configuration for output
int count_building = 0;
std::vector<POINT_XYZ> out_roof;
string roof_index;
int count_roof = 0;
std::vector<POINT_XYZ> out_wall;
string wall_index;
int count_wall = 0;

int read_in(const string line, POINT_LATLON *point, int *p_len, int * height){
	std::vector<string> str1;
	std::vector<string> str2;
	//	string line1 = "1|((0 1,1 0))";
	boost::split(str1, line,boost::is_any_of("|"));
	//	std::cout<<*str1.begin()<<"XX"<<std::endl;
	boost::split(str2, *str1.begin(), boost::is_any_of(" "));
	//	std::cout<<*str2.begin()<<"XX"<<std::endl;
	*height = boost::lexical_cast<unsigned int>(*(str2.begin()+1));
	//	std::cout<<height<<std::endl;
	boost::split(str2, *(str1.end()-1), boost::is_any_of("(("));
	//	std::cout<<*str2.begin()<<std::endl;
	boost::split(str1, *(str2.end()-1), boost::is_any_of("))"));
	//	std::cout<<*str1.begin()<<std::endl;
	boost::split(str2, *str1.begin(), boost::is_any_of(","));
	int k = 0;
	for(std::vector<string>::iterator it = str2.begin() ;
			it != str2.end();
			++it){
		std::vector<string> locate;
		boost::split(locate, *it, boost::is_any_of(" "));
		double x = boost::lexical_cast<double>(*locate.begin());
		double y = boost::lexical_cast<double>(*(locate.begin()+1));
		point[k].lon_deg = x;
		point[k].lat_deg = y;
		k ++;
	}
	*p_len = k;
	return 0;
}

//to get output
int step_out()
{

		printf("	<Group id='roof_%d'>\n",count_building);
		printf("		<Shape>\n			<Appearance>\n				<Material ambientIntensity='0.2' diffuseColor='0.8 0.6 0.6' emissiveColor='0 0 0' shininess='0.2' specularColor='0 0 0' transparency='0.0' />\n			</Appearance>\n");
		printf("			<IndexedFaceSet coordIndex='\n");
		std::cout<<roof_index;
		printf("\n' convex='true' solid='true'>\n				<Coordinate point='\n");
		for(std::vector<POINT_XYZ>::iterator it = out_roof.begin();
				it != out_roof.end();
				it++)
		{
			std::cout<<std::setprecision(2)<<std::fixed<< it->x<<" "<<it->y<<" "<<it->z<<" ";
		}
		printf("\n'/>\n			</IndexedFaceSet>\n		</Shape>\n	</Group>\n");
		std::cout<<std::endl;
		out_roof.clear();
		count_roof = 0;
		roof_index = "";

		printf("	<Group id='wall_%d'>\n",count_building);
		printf("		<Shape>\n				<Appearance>\n				<Material ambientIntensity='0.2' diffuseColor='0.5 0.5 0.5' emissiveColor='0 0 0' shininess='0.2' specularColor='0 0 0' transparency='0.0' />\n			</Appearance>\n");
		printf("			<IndexedFaceSet coordIndex='\n");
		std::cout<<wall_index;
		printf("\n' convex='true' solid='true'>\n				<Coordinate point='\n");

		for(std::vector<POINT_XYZ>::iterator it = out_wall.begin();
				it != out_wall.end();
				it++)
		{
			std::cout<<std::setprecision(2)<<std::fixed<< it->x<<" "<<it->y<<" "<<it->z<<" ";
		}
		printf("\n'/>\n			</IndexedFaceSet>\n		</Shape>\n	</Group>\n");
		out_wall.clear();
		count_wall = 0;
		wall_index = "";


	return 0;
}
int output_head()
{
	printf("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<!DOCTYPE X3D PUBLIC \"ISO//Web3D//DTD X3D 3.0//EN\" \"http://www.web3d.org/specifications/x3d-3.0.dtd\">\n<X3D xmlns:xsd='http://www.w3.org/2001/XMLSchema-instance' profile='Immersive' version='3.0' xsd:noNamespaceSchemaLocation='http://www.web3d.org/specifications/x3d-3.0.xsd'>\n	<Scene>\n");
	return 0;
}

int output(POINT_XYZ *floor, POINT_XYZ *roof, int b_len, int *b_index, int b_index_len)
{
	count_building ++;
	if(count_building % 30 == 2)
	{
		step_out();
	}
//	printf(" %d ", b_len);
	for(int k = 1; k < b_len; k++)
	{
		
		out_roof.push_back(roof[k]);
		out_wall.push_back(floor[k]);
		out_wall.push_back(roof[k]);
		if(k < b_len-1)
		{
			int i = k - 1;
			wall_index  = wall_index + " " + boost::lexical_cast<std::string>(count_wall+i*2) + " " + boost::lexical_cast<std::string>(count_wall+i*2+1) + " " + boost::lexical_cast<std::string>(count_wall+i*2+3) + " -1 "+ boost::lexical_cast<std::string>(count_wall+i*2)+" "+boost::lexical_cast<std::string>(count_wall+i*2+3)+" "+boost::lexical_cast<std::string>(count_wall+i*2+2)+ " -1 ";
		}
	}
//	wall_index  = wall_index + " " + boost::lexical_cast<std::string>(count_wall+b_len*2-4) + " " + boost::lexical_cast<std::string>(count_wall+b_len*2-3) + " " + boost::lexical_cast<std::string>(count_wall+1) + " -1 "+ boost::lexical_cast<std::string>(count_wall+b_len*2-4)+" "+boost::lexical_cast<std::string>(count_wall+1)+" "+boost::lexical_cast<std::string>(count_wall)+ " -1 ";
	count_wall += 2*b_len - 2;

	for(int i = 0; i < b_index_len; i++)
	{
		if(b_index[i] != -1)
			roof_index = roof_index + " " + boost::lexical_cast<std::string>(count_roof+b_index[i]);
		else
			roof_index = roof_index + " -1 ";
	}
	count_roof += b_len - 1;
	return 0;
}

int output_tail()
{
	step_out();
	printf("	</Scene>\n</X3D>");
	return 0;
}

int building_model(string input, const POINT_LATLON_Z *p_terrain, int t_len, int *t_index, int t_index_len)
{
	read_in(input, b_point, &b_len, &b_height);
	polygon_traingle(b_point, b_len, b_index, &b_index_len);
	double base = 9000;
	for(int i = 0; i < b_len; i++)
	{
		
		double base1 = p_in_faces1(p_terrain, t_len, t_index, t_index_len, b_point[i]);
		if(base < base1);
		base = base1;
	}
	for(int i = 0; i < b_len; i++)
	{
		floor_point[i] = p_latlon_z2p_xyz(b_point[i], base);
		roof_point[i] = p_latlon_z2p_xyz(b_point[i], base + b_height*4);
	}

	output(floor_point, roof_point, b_len, b_index, b_index_len);
	return 0;
}


int all(const char *t_file, const char *b_file)
{
	//the base terrain
	int t_len;
	POINT_LATLON_Z *t_array;
	get_in_terrain(t_file, &t_array, &t_len);
	int *t_index;
	int t_index_len;
	int height = sqrt(t_len);
	t_index = nest_index(height, height);
	t_index_len = 8 * (height - 1) * (height - 1);

	std::ifstream in(b_file);
	string input;
	output_head();
	while(getline(in,input)){
		building_model(input, t_array, t_len, t_index, t_index_len );
	}
	output_tail();
	return 0;
}

int main()
{
	const char *b_file = "../data/building/building_ustc";
	const char *t_file = "../data/terrain/31.8_117.2";
	all(t_file, b_file);
	return 0;
}
