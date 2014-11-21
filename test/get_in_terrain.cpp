#include "terrain.h"


int split(const string line, std::vector<POINT_LATLON_Z> *points)
{
	std::vector<string> str;
	POINT_LATLON_Z point;
	boost::split(str, line, boost::is_any_of(" "));
	point.coord.lon_deg = boost::lexical_cast<double>(*str.begin());
	point.coord.lat_deg = boost::lexical_cast<double>(*(str.begin()+1));
	point.z = boost::lexical_cast<double>(*(str.begin()+2));
	points->push_back(point);
	return 0;
}





int vector_2_array(std::vector<POINT_LATLON_Z> p_vector, POINT_LATLON_Z **p_array, int *p_len)
{
	int len = p_vector.size();
	POINT_LATLON_Z *array = (POINT_LATLON_Z *)malloc(len * sizeof(POINT_LATLON_Z));
	int i = 0;
	for(std::vector<POINT_LATLON_Z>::iterator it = p_vector.begin();
			it != p_vector.end();
			it ++)
	{
		array[i] = *it;
		i++;
	}
	*p_array = array;
	*p_len = len;
	return 0;
}



int get_in_terrain(const char *in_file, POINT_LATLON_Z **t_array, int *t_len)
{
	std::ifstream in(in_file);
	string input;
	std::vector<POINT_LATLON_Z> points;
	while(getline(in, input)){
		split(input, &points);
	}
	vector_2_array(points, t_array, t_len);
	in.close();
	return 0;
}

int get_in_terrain(const char *in_file, std::vector<POINT_LATLON_Z> *points)
{
	std::ifstream in(in_file);
	string input;
	while(getline(in, input)){
		split(input, points);
	}
	in.close();
	return 0;
}
int test_output(std::vector<POINT_LATLON_Z> *points)
{
	for(std::vector<POINT_LATLON_Z>::iterator it = points->begin();
			it != points->end();
			++it)
	{
		std::cout<<it->coord.lon_deg<<std::endl;
		std::cout<<it->z<<std::endl;

	}
	return 0;
}

/*
int main()
{
	std::vector<POINT_LATLON_Z> points;
	get_in_terrain("../data/terrain/31.8_117.2", &points);
	test_output(&points);
	return 0;
}
*/
