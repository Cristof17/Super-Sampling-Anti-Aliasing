#ifndef HOMEWORK1_H
#define HOMEWORK1_H

#define COLOR_WHITE 255;
#define COLOR_BLACK 0;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>


typedef struct Pixel{
	char color;
}pixel;
 

typedef struct ImageGrey{
	
	int resolution;
	int type;
	int colorMax;
	pixel * pixels ; //matrix of grey pixels

}image;


void initialize(image *im);
void render(image *im);
void writeData(const char * fileName, image *img);
double calculateDistance (int x , int y);

#endif