#!/bin/sh

CC=g++ -g
SRC = src
TARGET = bin/libGis.a
CGAL_FLAG = -frounding-math -O3 -DNDEBUG -rdynamic -L/usr/local/lib -lmpfr -lgmp /usr/local/lib/libCGAL_Core.so /usr/local/lib/libCGAL.so -lboost_thread-mt -lboost_system-mt /usr/local/lib/libCGAL_Core.so /usr/local/lib/libCGAL.so -lboost_thread-mt -lboost_system-mt -Wl,-rpath,/usr/local/lib 

$(TARGET):latlon2tile.o tile2latlon.o tilesize.o latlon2xyz.o point_in_face.o\
	nest_index.o polygon_triangle.o
	ar -crs $@ $?
	rm *.o
latlon2tile.o: $(SRC)/latlon2tilexyz.cpp
	$(CC) -c $(SRC)/latlon2tilexyz.cpp -o latlon2tile.o
tile2latlon.o: $(SRC)/tilexyz2latlon.cpp
	$(CC) -c $(SRC)/tilexyz2latlon.cpp -o tile2latlon.o
tilesize.o: $(SRC)/tilesize.cpp
	$(CC) -c $(SRC)/tilesize.cpp -o tilesize.o
latlon2xyz.o: $(SRC)/latlon2xyz.cpp
	$(CC) -c $(SRC)/latlon2xyz.cpp -o latlon2xyz.o
point_in_face.o: $(SRC)/point_in_face.cpp
	$(CC) -c $(SRC)/point_in_face.cpp -o point_in_face.o
nest_index.o: $(SRC)/nest_index.cpp
	$(CC) -c $(SRC)/nest_index.cpp -o nest_index.o
polygon_triangle.o: $(SRC)/polygon_triangle.cpp
	$(CC) -c $? -o $@

clean:
	rm *.o
