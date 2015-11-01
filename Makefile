all: homework homework1

homework: homework.c homework.h main.c
	gcc -fopenmp -o homework homework.c homework.h main.c -Wall -g

homework1: homework1.c homework1.h main1.c
	gcc -fopenmp -o homework1 homework1.c homework1.h main1.c -Wall -g

clean:
	rm homework
	rm homework1
	rm out/*

runHomework:
	./homework in/lenna_bw.pgm cristof_lenna.pgm 2 4

runHomework1:
	./homework in/lenna_color.pnm color_cristof_lenna.pnm 2 4

runHomework2:
	./homework in/lenna_bw.pgm cristof_lenna.pgm 3 4

runHomework3:
	./homework in/lenna_color.pnm color_cristof_lenna.pnm 3 4

debugHomework3:
	gdb -tui --args ./homework in/lenna_color.pnm color_cristof_lenna.pnm 3 4

debugHomework2:
	gdb -tui --args ./homework in/lenna_bw.pgm cristof_lenna.pgm 3 4

debugHomework1:
	gdb -tui --args ./homework in/lenna_color.pnm color_cristof_lenna.pnm 2 4

debugHomework:
	gdb -tui --args ./homework in/lenna_bw.pgm cristof_lenna.pgm 2 4

runRenderer:
	./homework1 cristof_100 10000 4

debugRenderer:
	gdb -tui --args ./homework1 cristof_100 100 4

checkHomework:
	diff cristof_lenna.pgm out_ref/2lenna_bw.pgm

checkHomework1:
	diff color_cristof_lenna.pnm out_ref/2lenna_color.pnm

checkHomework2:
	diff cristof_lenna.pgm out_ref/3lenna_bw.pgm

checkHomework3:
	diff color_cristof_lenna.pnm out_ref/3lenna_color.pnm
