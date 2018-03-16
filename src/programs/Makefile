CC = g++ -O3 -Wall -Wno-empty-body
LIB = ../libim/libim.a ../jpeg/libjpeg.a -lpthread
BIN = color_histogram enhance stereo feature find_lines geometric histo_window menu notch process motion smoothing split_merge vector_median vector_median2 

all: $(BIN)

color_histogram: color_histogram.cpp
	$(CC) -o color_histogram color_histogram.cpp $(LIB)

enhance: enhance.cpp
	$(CC) -o enhance enhance.cpp $(LIB)

stereo: stereo.cpp
	$(CC) -o stereo stereo.cpp $(LIB)

feature: feature.cpp
	$(CC) -o feature feature.cpp $(LIB)

find_lines: find_lines.cpp
	$(CC) -o find_lines find_lines.cpp $(LIB)

geometric: geometric.cpp
	$(CC) -o geometric geometric.cpp $(LIB)

histo_window: histo_window.cpp
	$(CC) -o histo_window histo_window.cpp $(LIB)

menu: menu.cpp
	$(CC) -o menu menu.cpp $(LIB)

notch: notch.cpp
	$(CC) -o notch notch.cpp $(LIB)

process: process.cpp
	$(CC) -o process process.cpp $(LIB)

motion: motion.cpp
	$(CC) -o motion motion.cpp $(LIB)

smoothing: smoothing.cpp
	$(CC) -o smoothing smoothing.cpp $(LIB)

split_merge: split_merge.cpp
	$(CC) -o split_merge split_merge.cpp $(LIB)

vector_median: vector_median.cpp
	$(CC) -o vector_median vector_median.cpp $(LIB)

vector_median2: vector_median2.cpp
	$(CC) -o vector_median2 vector_median2.cpp $(LIB)

clean:
	/bin/rm -f $(BIN)
