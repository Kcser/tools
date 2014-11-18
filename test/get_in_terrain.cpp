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
