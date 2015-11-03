#!/bin/bash

echo "gri resize 2,3,8 thread 4"
./homework in/lenna_bw.pgm cristof_lenna.pgm 2 8
./homework in/lenna_bw.pgm cristof_lenna.pgm 3 8
./homework in/lenna_bw.pgm cristof_lenna.pgm 8 8

echo "color resize 2,3,8 thread 4"
./homework in/lenna_color.pnm color_cristof_lenna.pnm 2 8
./homework in/lenna_color.pnm color_cristof_lenna.pnm 3 8
./homework in/lenna_color.pnm color_cristof_lenna.pnm 8 8


echo "gri resize 2,3,8 thread 4 reluare"
./homework in/lenna_bw.pgm cristof_lenna.pgm 2 8
./homework in/lenna_bw.pgm cristof_lenna.pgm 3 8
./homework in/lenna_bw.pgm cristof_lenna.pgm 8 8

echo "color resize 2,3,8 thread 4 reluare"
./homework in/lenna_color.pnm color_cristof_lenna.pnm 2 8
./homework in/lenna_color.pnm color_cristof_lenna.pnm 3 8
./homework in/lenna_color.pnm color_cristof_lenna.pnm 8 8



