/**
    Copyright (C) 2016 Mark Gardner

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.(called license.txt)  If not, see <http://www.gnu.org/licenses/>.
*/
#include <iostream>
#include <cstdio>

#ifndef __linux
#include <conio.h>
#endif // __linux

#ifdef __linux
extern "C" {
#endif // __linux

#include <graphics.h>

#ifdef __linux
}
#endif // __linux

#include <cstdlib>
#include <cstring>
#include <fstream>

///macros min and max
#define min(a,b) a<b?a:b
#define max(a,b) a>b?b:a

int main(int argc, char *argv[])
{
#ifdef DEBUG
	std::cout << argc<<std::endl;
#endif // DEBUG

	if (argc == 2)
		if (!std::strcmp(argv[1], "license")) {
			int c;
			std::FILE *f;
			f = std::fopen("license.txt", "r");

			if (f == NULL) {
				std::cerr << "Sadly, it would seem that you don't have license.txt here. That means that I can not read it to you. However, you can see <http://www.gnu.org/licenses/>, find the plain text version, and save it as license.txt." << std::endl;
				return 101;
			}

			while ((c = std::fgetc(f)) != EOF) { // standard C I/O file reading loop
				std::putchar(c);
			}

			return 0;
		};

	std::cout << "Welcome to smeagolthellama's random maze generator!\n This program comes with ABSOLUTELY NO WARRANTY!\nSee license.txt for lots more details, or add the option \"license\" at the end of the command.\n\n";
#ifdef DEBUG
	std::cout<<"declaring seed...\n";
#endif // DEBUG

	unsigned long seed;
#ifdef DEBUG
	std::cout<<"declaring mazeSize...\n";
#endif // DEBUG
	unsigned long mazeSize;
#ifdef DEBUG
	std::cout<<"checking for arguments...\n";
#endif // DEBUG
	if (argc != 3) {
		std::cout << "Please enter a seed (from which the random numbers can grow) :";
		std::cin >> seed;
		srand(seed);
		std::cout << "How big should the maze be? Please enter the number of squares that one side should have:";
		std::cin >> mazeSize;
	} else {
		char *p;
		seed = strtoul(argv[1], &p, 10);
		/*if(p!=NULL){
			std::cerr<<"malformed arguments"<<std::endl;
			return 1;
		}*/
		mazeSize = strtoul(argv[2], &p, 10);
		/*if(p!=NULL){
			std::cerr<<"malformed arguments"<<std::endl;
			return 1;
		}*/
	}

	std::cout << "initializing graphics..." << std::endl;
	initwindow(0, 0);
	unsigned int maxx, maxy, step;
	getch();
	maxx = getmaxx();
	maxy = getmaxy();
	step = min(maxx / (mazeSize + 2), maxy / (mazeSize + 2));
	unsigned int startx, starty;

	if (maxx > maxy) {
		startx = (maxx - step * mazeSize) / 2;
		starty = step;
	} else {
		starty = (maxx - step * mazeSize) / 2;
		startx = step;
	}

	cleardevice();
	setcolor(seed % MAXCOLORS);
	rectangle(startx, starty, startx + mazeSize * step, starty + mazeSize * step) ;
#ifdef __linux
	refresh();
#endif // __linux
	unsigned int i, j;

	for (i = 1; i < mazeSize; i++) {
		for (j = 1; j < mazeSize; j++) {
			if (rand() & 1) {
				line(startx + i * step, starty + j * step, startx + i * step, starty + (j + 1)*step);
			} else {
				line(startx + i * step, starty + j * step, startx + (i + 1)*step, starty + j * step);
			}
		}

#ifdef __linux
		refresh();
#endif // __linux
	}

	getch();
	outtextxy(10, 10, (char *)"save?(y/n)");
#ifdef __linux
	refresh();
#endif // __linux

	if (getch() == 'y') {
		writeimagefile(argv[1], startx - 10, starty - 10, startx + mazeSize * step + 10, starty + mazeSize * step + 10);
	}

	return 0;
}
