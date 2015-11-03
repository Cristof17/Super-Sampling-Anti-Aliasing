#!/bin/bash

echo "gri resize 2,3,8 thread 1"
./homework in/lenna_bw.pgm cristof_lenna.pgm 2 1
./homework in/lenna_bw.pgm cristof_lenna.pgm 3 1
./homework in/lenna_bw.pgm cristof_lenna.pgm 8 1

echo "color resize 2,3,8 thread 1"
./homework in/lenna_color.pnm color_cristof_lenna.pnm 2 1
./homework in/lenna_color.pnm color_cristof_lenna.pnm 3 1
./homework in/lenna_color.pnm color_cristof_lenna.pnm 8 1

echo "gri resize 2,3,8 thread 1 reluare "
./homework in/lenna_bw.pgm cristof_lenna.pgm 2 1
./homework in/lenna_bw.pgm cristof_lenna.pgm 3 1
./homework in/lenna_bw.pgm cristof_lenna.pgm 8 1

echo "gri resize 2,3,8 thread 1 reluare"
./homework in/lenna_color.pnm color_cristof_lenna.pnm 2 1
./homework in/lenna_color.pnm color_cristof_lenna.pnm 3 1
./homework in/lenna_color.pnm color_cristof_lenna.pnm 8 1

echo "renderer 1"
./homework1 cristof_100 100 1
./homework1 cristof_10000 10000 1

echo "renderer 1 reluare"
./homework1 cristof_100 100 1
./homework1 cristof_10000 10000 1

