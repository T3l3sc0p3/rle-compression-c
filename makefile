CXX=gcc
BIN=bin

all: rle-compression

rle-compression: src/RunLength.c
	mkdir -p $(BIN)
	$(CXX) -O3 $< -o $(BIN)/rle-compression
