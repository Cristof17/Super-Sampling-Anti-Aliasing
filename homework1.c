#include "homework1.h"

int num_threads;
int resolution;

void initialize(image *im) {

	image* local = (image*)malloc(sizeof(image));

	local->resolution = im->resolution;
	local->pixels = (pixel *)malloc(local->resolution * local->resolution * sizeof(pixel));
	local->type = 5;
	local->colorMax = 255;

	*im = *local;

	omp_set_num_threads(num_threads);
}


void render(image *im) {

	resolution = im->resolution;

	//image * local = (image*)malloc(sizeof(image));

	im->resolution = im->resolution;
	im->type = 5;
	im->colorMax = 255;

	if(im->pixels == NULL)
		im->pixels = (pixel *)malloc(resolution * resolution * sizeof(pixel));

	int i , j;

		#pragma omp parallel for private(i,j)
		for (j = 0 ; j < resolution ; j++){
			for(i = 0 ; i < resolution ; i++){

				if ((calculateDistance(i * (100.0/resolution) + (100.0/resolution/2), (resolution - 1 - j) * (100.0/resolution) + (100.0/resolution/2)) < 3)){
					im->pixels[i + j * resolution].color = COLOR_BLACK;
				}
				
				else {
					im->pixels[i + j * resolution].color = COLOR_WHITE;
				}
			}
		}
}

void writeData(const char * fileName, image *img) {

	FILE * file;
	file = fopen (fileName,"wb");

	// printf("%d",img->type);

	fprintf(file,"P%d\n",img->type); //write the type of the image P5 or P6
	fprintf(file,"%d %d\n",img->resolution,img->resolution); //write the width and the height of the image
	fprintf(file,"%d\n",img->colorMax); //write the maximum value the colors can take


	//writing the pixels matrix

	fwrite(img->pixels , sizeof(pixel) , img->resolution * img->resolution, file);

	fflush(file);
	fclose(file);

}


double calculateDistance(int x, int y) {
    return abs(-1 * x + 2 * y + 0)/sqrt(1 + 4);
}

