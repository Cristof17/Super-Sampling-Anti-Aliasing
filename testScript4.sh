#!/bin/bash

echo "gri resize 2,3,8 thread 4"
./homework in/lenna_bw.pgm cristof_lenna.pgm 2 4
./homework in/lenna_bw.pgm cristof_lenna.pgm 3 4
./homework in/lenna_bw.pgm cristof_lenna.pgm 8 4

echo "color resize 2,3,8 thread 4"
./homework in/lenna_color.pnm color_cristof_lenna.pnm 2 4
./homework in/lenna_color.pnm color_cristof_lenna.pnm 3 4
./homework in/lenna_color.pnm color_cristof_lenna.pnm 8 4


echo "gri resize 2,3,8 thread 4 reluare"
./homework in/lenna_bw.pgm cristof_lenna.pgm 2 4
./homework in/lenna_bw.pgm cristof_lenna.pgm 3 4
./homework in/lenna_bw.pgm cristof_lenna.pgm 8 4

echo "color resize 2,3,8 thread 4 reluare"
./homework in/lenna_color.pnm color_cristof_lenna.pnm 2 4
./homework in/lenna_color.pnm color_cristof_lenna.pnm 3 4
./homework in/lenna_color.pnm color_cristof_lenna.pnm 8 4

echo "renderer 4"
./homework1 cristof_100 100 4
./homework1 cristof_10000 10000 4

echo "renderer 4 reluare"
./homework1 cristof_100 100 4
./homework1 cristof_10000 10000 4


