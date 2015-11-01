#ifndef HOMEWORK_H
#define HOMEWORK_H
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>

#define GAUSSIAN_KERNEL_SIZE 3
#define GAUSSIAN_KERNEL_ELEMENT_SUMM 16

// extern int GAUSSIAN_KERNEL_SIZE;
// extern int GAUSSIAN_KERNEL_ELEMENT_SUMM;

typedef struct Gray{

	unsigned char gr; //gray color value

}gray;
	
typedef struct Color{

	unsigned char r ; //red color value
	unsigned char g; //green color value
	unsigned char b; //blue color value

}color;


typedef struct ImageGrey{
	int type ;  //type of the image P5 or P6
	int width; //width of the image
	int height; //height of the image
	int colorMax; //maximum value a pixel can hava
	int resizeFactor; //resize factor of the image
	
	color * colorPixels ; //matrix of color pixels
	gray * grayPixels ; //matrix of grey pixels

}image;

/*
 *  The array of elements that compose the gaussianKernel
 */
extern int gaussianKernel[]; 

/*
 * Reads from the file and puts the contents of the file
 * in the image structure given as parameter for future processing
 */
void readInput(const char * fileName, image * img);

/*
 * Writes the contents of the image given as parameter
 * into the file 
 */
void writeData(const char * fileName, image *img);

/*
 * Reduces the size of the "in" image transmitted as parameter
 * and stores the result in the "out" image transmitted as parameter
 */
void resize(image *in, image * out);

#endif