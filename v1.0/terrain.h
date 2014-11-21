#include<iostream>
#include<vector>
#include<iomanip>
#include<boost/algorithm/string.hpp>
#include<boost/lexical_cast.hpp>
#include<fstream>
#include "../inc/head.h"

typedef std::string string;
int get_in_terrain(const char *in_file, std::vector<POINT_LATLON_Z> *points);
int get_in_terrain(const char *in_file, POINT_LATLON_Z **t_array, int *t_len);
