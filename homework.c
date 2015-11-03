#include "homework.h"


/*
 * extern variable whose value is set from the main function
 * stores the number if threads that will be created in the
 * parallel section
 */
int num_threads;

/*
 * extern variable whose value is set from the main function
 * stores the number of pixels whose values need to be calculated
 * into one pixel
 */
int resize_factor;

/*
 * The gaussianKernel matrix
 */
int gaussianKernel[9] = {1,2,1,2,4,2,1,2,1};



void readInput(const char * fileName, image * img) {

	/*
	 * 	setting the number of threads that will be created 
	 * in the parallel region
	 */
	omp_set_num_threads(num_threads);

	/*
	 * 	the input file opened for tranmitting information
	 * from the file to an image structur(received as parameter)
	 */
	FILE * file = fopen(fileName,"r");

	/*
	 * local copy of the image that will store the information
	 * from the file 	
	 */
	image * local; 

	local = (image *)malloc(sizeof(image));

	//get 5 or 6 following P
	fseek(file,1, SEEK_SET); //set the pointer after P letter
	fscanf(file,"%d\n", &local->type); //get the type of the image
	fscanf(file,"%d%d\n",&local->width,&local->height); //get the width and height of the image
	fscanf(file,"%d\n" ,&local->colorMax); //get the maximum value for a given pixel

	if(local->type == 5){
		//grey color image
		local->grayPixels = (gray *)malloc (local->width * local->height * sizeof(gray));

		//fill the pixels matrix
		fread(local->grayPixels , sizeof(gray) , local->width * local->height , file);

		//copy the local declared image to the image struct given as parameter
		*img = *local;
	}


	else if(local->type == 6){
		//color image

		local->colorPixels = (color *)malloc(local->width * local->height * sizeof(color));

		//fill the pixels matrix
		fread(local->colorPixels , sizeof(color) , local->width * local->height , file);

		//copy the local declared image to the image struct given as parameter
		*img = *local;
	}
	
	free(local);
	fclose(file);

}

void writeData(const char * fileName, image *img) {

	FILE * file;
	file = fopen (fileName,"w"); //open the file for writing

	fprintf(file,"P%d\n",img->type); //write the type of the image P5 or P6
	fprintf(file,"%d %d\n",img->width,img->height); //write the width and the height of the image
	fprintf(file,"%d\n",img->colorMax); //write the maximum value the colors can take


	//writing the pixels matrix

	//read the array of bytes that form the gray image
	if(img->type == 5){	
		fwrite(img->grayPixels , sizeof(gray) , img->width * img->height, file);
	}

	//read the array of bytes that form the color image
	else if(img->type == 6){
		fwrite(img->colorPixels , sizeof(color) ,  img->width * img->height , file);
	}

	fflush(file);
	fclose(file);

}

void resize(image *in, image * out) { 

	int type = in->type;

	//local variable which holds the resized image
	//image * local = (image *)malloc(sizeof (image));

	if(resize_factor % 2 == 0){

		if(type == 5){

			int i,j,lineOffset,colOffset;
			int localPosition = 0; //the location at which the average of pixels is held
			int summ = 0;
			int average = 0;

			
			out->type = in->type;
			out->width = in->width/resize_factor;
			out->height = in->height/resize_factor;
			out->colorMax = in->colorMax;
			out->resizeFactor = in->resizeFactor;

			out->grayPixels = (gray *)malloc(out->width * out->height * sizeof(gray));

			/*
			 * The private variables that need to be private are the variables that iterate
			 * through the original image (i and j) and the variables that iterate through
			 * the line and columns of the matrix of size resize_factor * resizefactor 
			 * (lineOffset , colOffset).
			 */
			#pragma omp parallel for collapse(2)\
					 private(i,j,lineOffset,colOffset,average,localPosition,summ)
			for (j = 0 ; j < in->height ; j+= resize_factor){
				for(i = 0 ; i < in->width ; i+= resize_factor){

					
					summ = 0 ;

					/*
					 * Iterating through each element of the matrix defined by
					 * resize_factor * resize_factor
					 */
					for(lineOffset = 0 ; lineOffset < resize_factor ; lineOffset ++){

						/*
						 * This is for not creating another thread which will access memory location 
						 * greater than in->width or in->height or in->width * in->height
						 */
						if(j + resize_factor > in->height){
							break;
						}

						for(colOffset = 0 ; colOffset < resize_factor ; colOffset ++){

							if(i + colOffset >= in->width || j + lineOffset >= in->height )
								continue;

							summ += in->grayPixels[ i + colOffset + (in->width * (j + lineOffset))].gr;
						}
					}


					average = summ/(resize_factor * resize_factor);
					/*
					 * The position in the output image that receives the average pixel values
					 */
					localPosition = (i/resize_factor) + (out->width * (j/resize_factor));
					out->grayPixels[localPosition].gr = average;

				}
			}

			free(in -> grayPixels);
		}

		else if (type == 6){

			int i = 0,j = 0 ,lineOffset = 0,colOffset = 0;
			int localPosition = 0;
			int summRed = 0; //summ of the red color pixers value from the matrix defined by refactor_size * refactor_size
			int summGreen = 0; //summ of the green color pixers value from the matrix defined by refactor_size * refactor_size
			int summBlue = 0; //summ of the blue color pixers value from the matrix defined by refactor_size * refactor_size
			int averageRed = 0; 
			int averageGreen = 0;
			int averageBlue = 0;

			out->type = in->type;
			out->width = in->width/resize_factor;
			out->height = in->height/resize_factor;
			out->colorMax = in->colorMax;
			out->resizeFactor = in->resizeFactor;

			out->colorPixels = (color *)malloc( sizeof(color) * ((in->width * in->height) / (resize_factor * resize_factor)));

			#pragma omp parallel for collapse(2) private(i,j,lineOffset,colOffset\
							,localPosition)\
							firstprivate(\
							summRed,summGreen,summBlue\
							,averageRed,averageGreen,averageBlue)
			for (j = 0 ; j < in->height ; j +=  resize_factor){
				for(i = 0 ; i < in->width ; i += resize_factor){

					summRed = 0 ;
					summGreen = 0 ;
					summBlue = 0 ;


					/*
					 * Iterating through each element of the matrix defined by
					 * resize_factor * resize_factor
					 */
					for(lineOffset = 0 ; lineOffset < resize_factor ; lineOffset ++ ){

						/*
						 * This is for not creating another thread which will access memory location 
						 * greater than in->width or in->height or in->width * in->height
						 */
						if(j + resize_factor > in->height){
							break;
						}

						for(colOffset = 0 ; colOffset < resize_factor ; colOffset ++){

							if(i + colOffset >= in->width || j + lineOffset >= in->height)
								continue;


							summRed += in->colorPixels[i + colOffset + (in->width * (j + lineOffset))].r;
							summGreen += in->colorPixels[i + colOffset + (in->width * (j + lineOffset))].g;
							summBlue += in->colorPixels[i + colOffset + (in->width * (j + lineOffset))].b;
						}
					}

					averageRed = summRed/(resize_factor * resize_factor);
					averageGreen = summGreen/(resize_factor * resize_factor);
					averageBlue = summBlue/(resize_factor * resize_factor);

					/*
					 * The position in the output image that receives the average pixel values
					 */
					localPosition = (i/resize_factor) + (out->width * (j/resize_factor));

					out->colorPixels[localPosition].r = averageRed;
					out->colorPixels[localPosition].g = averageGreen;
					out->colorPixels[localPosition].b = averageBlue;


				}
			}

		free(in -> colorPixels);
		}

	}


	else if(resize_factor % 3 == 0){

		if(type == 5){

			int i = 0, j = 0;
			int lineOffset = 0;
			int colOffset = 0;
			int localPosition = 0;
			int summ = 0; 
			int average = 0;

			out->type = in->type;
			out->width = in->width/resize_factor;
			out->height = in->height/resize_factor;
			out->colorMax = in->colorMax;
			out->resizeFactor = in->resizeFactor;

			out->grayPixels = (gray *)malloc(out->width * out->height * sizeof(gray));

			#pragma omp parallel for collapse(2)\
					private(i,j,lineOffset,colOffset,localPosition,summ,average)
			for (j = 0 ; j < in->height ; j+= resize_factor){
				for(i = 0 ; i < in->width ; i+= resize_factor){

					summ = 0 ;

					/*
					 * Iterating through each element of the matrix defined by
					 * resize_factor * resize_factor
					 */
					for(lineOffset = 0 ; lineOffset < resize_factor ; lineOffset ++){
						for(colOffset = 0 ; colOffset < resize_factor ; colOffset ++){

							/*
							 * This is for not creating another thread which will access memory location 
							 * greater than in->width or in->height or in->width * in->height
							 */
							if(j + resize_factor >= in->height){
								break;
							}

							if(i + colOffset >= in->width || j + lineOffset >= in->height )
								continue;

							summ += (in->grayPixels[ i + colOffset + (in->width * (j + lineOffset))].gr * 
									gaussianKernel[colOffset + GAUSSIAN_KERNEL_SIZE * lineOffset]);

						}
					}

					average = summ/GAUSSIAN_KERNEL_ELEMENT_SUMM;
					/*
					 * The position in the output image that receives the average pixel values
					 */
					localPosition = (i/resize_factor) + (out->width * (j/resize_factor));
					out->grayPixels[localPosition].gr = average;
					}
			}
			free(in -> grayPixels);
		}

		if(type == 6){

			int i,j,lineOffset,colOffset,localPosition = 0;
			int summRed = 0; 
			int summGreen = 0;
			int summBlue = 0;
			int averageRed = 0;
			int averageGreen = 0;
			int averageBlue = 0;

			out->type = in->type;
			out->width = in->width/resize_factor;
			out->height = in->height/resize_factor;
			out->colorMax = in->colorMax;
			out->resizeFactor = in->resizeFactor;

			out->colorPixels = (color *)malloc( sizeof(color) * ((in->width * in->height) / (resize_factor * resize_factor)));


			#pragma omp parallel for collapse(2) private(i,j,lineOffset,colOffset\
							,localPosition)\
							firstprivate(\
							summRed,summGreen,summBlue\
							,averageRed,averageGreen,averageBlue)
			for (j = 0 ; j < in->height ; j+= resize_factor){
				for(i = 0 ; i < in->width ; i+= resize_factor){

					summRed = 0 ;
					summGreen = 0;
					summBlue = 0;


					for(lineOffset = 0 ; lineOffset < resize_factor ; lineOffset ++){
						for(colOffset = 0 ; colOffset < resize_factor ; colOffset ++){

							if(i + colOffset >= in->width || j + lineOffset >= in->height )
								continue;

							summRed += (in->colorPixels[ i + colOffset + (in->width * (j + lineOffset))].r * 
									gaussianKernel[colOffset + GAUSSIAN_KERNEL_SIZE * lineOffset]);
							summGreen += (in->colorPixels[ i + colOffset + (in->width * (j + lineOffset))].g * 
									gaussianKernel[colOffset + GAUSSIAN_KERNEL_SIZE * lineOffset]);
							summBlue += (in->colorPixels[ i + colOffset + (in->width * (j + lineOffset))].b * 
									gaussianKernel[colOffset + GAUSSIAN_KERNEL_SIZE * lineOffset]);

						}
					}

					localPosition = (i/resize_factor) + (out->width * (j/resize_factor));

					averageRed = summRed/GAUSSIAN_KERNEL_ELEMENT_SUMM;
					averageGreen = summGreen/GAUSSIAN_KERNEL_ELEMENT_SUMM;
					averageBlue = summBlue/GAUSSIAN_KERNEL_ELEMENT_SUMM;

					out->colorPixels[localPosition].r = averageRed;
					out->colorPixels[localPosition].g = averageGreen;
					out->colorPixels[localPosition].b = averageBlue;

				}
			}
			free(in -> colorPixels);

		}


	}
}
