Readme-ul trebuie sa contina, descrierea solutiei voastre, metodologia de testare si descrierea sistemelor pe care ati
efectuat testele alaturi de rezultatele prin care demonstrati (sau nu) scalabilitatea.

Cristofor Rotsching 333CA

1) Solution Description

	1.1) Super Sampling Anti Aliasing

	The implementation contains in the file homework.h an "image" structure which
	contains data about an .pnm or .pgm image. (type, width, height, maxColor)
	and two pointers, one of type "gray" and the other one "color". Each one
	points to an array of structures that contain the array of pixels of the image
	being resized. If the image is P5 then I allocate memory for the gray * array.
	If the image is P6 then I allocat memory for the color * array.

	readInput() function: It's purpose is to read information from the file
	given as parameter and storing that information in the "image" structure.
	After the file is opened, I read all the specific values of the image,
	(type, width, height, maxColor), and then I do a binary read of the pixels
	array of the image, storing them in the pixels array of the "image" structure.
	In the implementation there is a local image varialble called "local", in
	which the information is first stored from the *.pnm / *.pgm file and then
	a copy is made into the image variable that came as a parameter.

	writeData() function: It's purpose is to get the data from the "image" structure
	received as a parameter and store it into a file (either .pnm if the file is P6,
	or .pgm if the file is P5). For writing the image into a file, first the 
	specific values of the image, (type, width, height, maxColor), need to be
	written, and then the array of color pixels or gray pixels is written into the 
	destination file using the "fwrite" function, which writes every character from
	the "image structure" pixel array (either gray or colored);

	resize() function: It's purpose is to create an "out" (output) image which is
	resize_factor * resize_factor smalled than the "in" (input) image.
	The implementation takes in consideration the parity of the "resize_factor" variable,
	and also the type of the image (either P5 for .pgm or P6 for .pnm).
	For the resizing algorithm, a local "image" variable is created in which the 
	resized image is written, and then at then end of the function call, it's contents
	are transfered to the output image received as a parameter.

	The resizing is done in the following manner:
		-the starting point of the image is considered top-left corner
		-along the height of the image, an iteration is made as well as on it's
		width for identifing the "resize_factor * resize_factor" matrixes.
		-each resize_factor * resize_factor matrix is being iterated through its
		elements in order to determine the average value of the pixels from that
		matrix. The resulting pixel value is stored in the "local" image structure,
		on the i/resize_factor + width * (j/resize_factor) pixel position.

	For the .pgm input file type, the resizing function takes in consideration
	when doing the average value only the gray color, thus it is calculating
	only one average value. On the other hand,for the .pnm input file type there
	are 3 average values taken into consideration(red, green, blue), because each
	pixel in the "in" image variable is composed of the 3 colors. This is why it is
	necessary to calculate the average value of each and every one of them, and then
	storing each one in the i/resize_factor + width * j/resize_factor pixel. 
	(same as the gray value)


	Each for loop iteration has been parallelized to increase efficiency. For the
	parallelization iterative variables (i, j, lineOffset, colOffset) have been
	declared private because the threads that are created need to work on their
	own copy of the variables. Also, the "summ" of the pixel values that needs to be
	calculated in each for loop has been declared private because each thread handles
	different chunks of the input image pixel matrix. Because the location in the
	output pixel array(localPosition) is dependent on i, j it needs to be declared
	private as well. The "average" variable is dependent on the "summ" variable,
	which has been declared private, and so, it needs to be declared private as well.

	1.2) Micro renderer

	For the Micro renderer, it is necessary to generate an output image based on
	a line equation in 2D space. For the representation of an image I created an
	"image" structure which holds a "resolution" variable(meaning the width and
	height) that the output image needs to have. There is also an array of "pixel"
	structures, which holds the rendered image.

	initialize() function: The function receives an "image" structure, in which
	the output of the rendering algorithm is stored. Because is can have .pnm or
	.pgm file extensions, information about the image is written in the following 
	manner:
		 -type of the image : P5 for grey image P6 for color image
		 -width and height : determined by the "resolution" variable
		 -colorMax : the maximum value a pixel can have (255 for "char" represented pixels)
		 -pixel array : the "char" values of each pixel

	The rendering algorithm is parallelized using openMP directives
	In the initialize function, the number of threads that start in the parallel
	regions of the algorith is set using omp_set_num_threads().

	render() function : This function is responsible with calculating 
	values for the output image, based on an algorithm.

	The algorithm has been parallelized, using openMP directives. It iterates through
	each value of the pixel array of an "image" structure. If the point given by
	its "i" and "j" value is fit for the line equation, then it becomes BLACK. 
	If the pixel is at a maximum distance of 3 pixels from at least one point on
	the line, then it needs to be colored BLACK. Else, the pixel color becomes WHITE
	The distance formula that has been used is implemented in the calculateDistace()
	function and it is (A*x + B*y +C)/sqrt(A*A + B*B), where A,B,C are the coefficients
	of the line equation.

	writeData() function : The function receives the "image" structure it needs to
	write in the .pnm or .pgm file. It writes the pixel data into a resolution * resolution
	sized image. 

2) Running time results & Scalability

	2.1) Super Sampling Anti Aliasing

		.pgm with resize_factor = 2

		1 thread:  0.007204
		2 threads: 0.003966
		4 threads: 0.002181
		8 threads: 0.000724

		.pnm with resize_factor = 2

		1 thread:  0.011625
		2 threads: 0.006949
		4 threads: 0.003439
		8 threads: 0.001103
 
 		.pgm with resize_factor = 3

		1 thread:  0.007331
		2 threads: 0.002975
		4 threads: 0.002003
		8 threads: 0.000733

		.pnm with resize_factor = 3

		1 thread:  0.010384
		2 threads: 0.005967
		4 threads: 0.003212
		8 threads: 0.000958

		.pgm with resize_factor = 8

		1 thread:  0.004863
		2 threads: 0.001907
		4 threads: 0.001385
		8 threads: 0.000602

		.pnm with resize_factor = 8

		1 thread:  0.008527
		2 threads: 0.004576
		4 threads: 0.002360
		8 threads: 0.000793

		The times are reduced in half with each doubling of the threads the 
		executables are ran on.

	2.2) Micro renderer

		resolution = 100

		1 thread:  0.000710
		2 threads: 0.000362
		4 threads: 0.000186
		8 threads: 0.000061

		resolution = 10000

		1 thread: 3.625162
		2 thread: 1.853283
		4 thread: 0.928290
		8 thread: 0.453274
