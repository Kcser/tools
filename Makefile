#!/bin/sh

CC=g++
SRC = src
TARGET = bin/libGis.a


$(TARGET):latlon2tile.o tile2latlon.o tilesize.o latlon2xyz.o
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

clean:
	rm *.o
