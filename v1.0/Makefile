#!/bin/sh

CC = g++
CFLAGS = -g
CGAL_FLAG =	-frounding-math -O3 -rdynamic -L/usr/local/lib -lmpfr -lgmp /usr/local/lib/libCGAL_Core.so /usr/local/lib/libCGAL.so -lboost_thread-mt -lboost_system-mt /usr/local/lib/libCGAL_Core.so /usr/local/lib/libCGAL.so -lboost_thread-mt -lboost_system-mt -Wl,-rpath,/usr/local/lib 
target: texture nest_terrain terrain_texture building_model

texture: texture.cpp
	$(CC) $(CFLAGS) texture.cpp ../bin/libGis.a -o run_texture
nest_terrain: get_in_terrain.o nest_terrain.o
	$(CC) $(CFLAGS) get_in_terrain.o nest_terrain.o ../bin/libGis.a -o terrain
terrain_texture: get_in_terrain.o terrain_texture.o
	$(CC) $(CFLAGS) get_in_terrain.o terrain_texture.o ../bin/libGis.a -o terrain_texture
building_model: get_in_terrain.o building_model.o
	$(CC) $(CFLAGS) $^ ../bin/libGis.a -o $@ $(CGAL_FLAG)
building_model.o: building_model.cpp
	$(CC) $(CFLAGS) -c $^  -o $@
get_in_terrain.o: get_in_terrain.cpp
	$(CC) $(CFLAGS) -c get_in_terrain.cpp  -o get_in_terrain.o
nest_terrain.o: nest_terrain.cpp
	$(CC) $(CFLAGS) -c nest_terrain.cpp -o nest_terrain.o
terrain_texture.o: terrain_texture.cpp
	$(CC) $(CFLAGS) -c terrain_texture.cpp -o terrain_texture.o

polygon.o: polygon.cpp
	/usr/bin/c++    -frounding-math -O3 -DNDEBUG  -c polygon_triangulation.cpp  -o polygon_triangulation.o -rdynamic -L/usr/local/lib -lmpfr -lgmp /usr/local/lib/libCGAL_Core.so /usr/local/lib/libCGAL.so -lboost_thread-mt -lboost_system-mt /usr/local/lib/libCGAL_Core.so /usr/local/lib/libCGAL.so -lboost_thread-mt -lboost_system-mt -Wl,-rpath,/usr/local/lib 

clean:
	rm *.o
