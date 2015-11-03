#!/bin/bash

echo "gri resize 2,3,8 thread 2"
./homework in/lenna_bw.pgm cristof_lenna.pgm 2 2
./homework in/lenna_bw.pgm cristof_lenna.pgm 3 2
./homework in/lenna_bw.pgm cristof_lenna.pgm 8 2

echo "color resize 2,3,8 thread 2"
./homework in/lenna_color.pnm color_cristof_lenna.pnm 2 2
./homework in/lenna_color.pnm color_cristof_lenna.pnm 3 2
./homework in/lenna_color.pnm color_cristof_lenna.pnm 8 2


echo "gri resize 2,3,8 thread 2 reluare"
./homework in/lenna_bw.pgm cristof_lenna.pgm 2 2
./homework in/lenna_bw.pgm cristof_lenna.pgm 3 2
./homework in/lenna_bw.pgm cristof_lenna.pgm 8 2

echo "color resize 2,3,8 thread 2 reluare"
./homework in/lenna_color.pnm color_cristof_lenna.pnm 2 2
./homework in/lenna_color.pnm color_cristof_lenna.pnm 3 2
./homework in/lenna_color.pnm color_cristof_lenna.pnm 8 2


