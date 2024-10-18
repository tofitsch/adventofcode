#include<iostream>
#include<fstream>
#include<map>
#include<cmath>
#include<cstring>

#define MAX_X 5
#define MAX_Y 5
#define MAX_Z 400
#define N_STEPS 200

using namespace std;

int count_neighbours(bool grid[MAX_Z][MAX_Y][MAX_X], int z, int y, int x) {

	int count = 0;

	if(x > 0 && grid[z][y][x-1]) count++;
	if(x < 4 && grid[z][y][x+1]) count++;
	if(y > 0 && grid[z][y-1][x]) count++;
	if(y < 4 && grid[z][y+1][x]) count++;

	if(z < MAX_Z - 1) {

		if(x == 0 && grid[z+1][MAX_Y/2][MAX_X/2-1]) count++;
		if(x == MAX_X-1 && grid[z+1][MAX_Y/2][MAX_X/2+1]) count++;
		if(y == 0 && grid[z+1][MAX_Y/2-1][MAX_X/2]) count++;
		if(y == MAX_X-1 && grid[z+1][MAX_Y/2+1][MAX_X/2]) count++;

	}

	if(z > 0) {

		if(x == MAX_X/2-1 && y == MAX_Y/2)
			for(int Y=0; Y<MAX_Y; Y++)
				if(grid[z-1][Y][0]) count++;
		if(x == MAX_X/2+1 && y == MAX_Y/2)
			for(int Y=0; Y<MAX_Y; Y++)
				if(grid[z-1][Y][MAX_X-1]) count++;
		if(x == MAX_X/2 && y == MAX_Y/2-1)
			for(int X=0; X<MAX_X; X++)
				if(grid[z-1][0][X]) count++;
		if(x == MAX_X/2 && y == MAX_Y/2+1)
			for(int X=0; X<MAX_X; X++)
				if(grid[z-1][MAX_Y-1][X]) count++;

	}

	return count;

}

void update_grid(bool grid[MAX_Z][MAX_Y][MAX_X]) {

	bool new_grid[MAX_Z][MAX_Y][MAX_X];

	for(int z=0; z<MAX_Z; z++) {
		for(int y=0; y<MAX_Y; y++) {
			for(int x=0; x<MAX_X; x++) {

				if(x == MAX_X/2 && y == MAX_Y/2) {

					new_grid[z][y][x] = false;

					continue;
				}

				int count = count_neighbours(grid, z, y, x);

				new_grid[z][y][x] = (grid[z][y][x] && count == 1)
					|| (!grid[z][y][x] && (count == 1 || count == 2));

			}
		}
	}

	for(int z=0; z<MAX_Z; z++)
		for(int y=0; y<MAX_Y; y++)
			for(int x=0; x<MAX_X; x++)
				grid[z][y][x] = new_grid[z][y][x];

}

int main() {

	string line;

	ifstream in_file("input.txt");

	bool grid[MAX_Z][MAX_Y][MAX_X];
    memset(grid, 0, sizeof(grid));

	int y = 0;

	while(getline(in_file, line)) {

		int x = 0;

		for(char &c : line)
			grid[MAX_Z/2][y][x++] = c == '#';

		y++;

	}

	in_file.close();

	for (int i=0; i<N_STEPS; i++)
		update_grid(grid);

	int sum = 0;

	for(int z=0; z<MAX_Z; z++)
		for(int y=0; y<MAX_Y; y++)
			for(int x=0; x<MAX_X; x++)
				if(grid[z][y][x])
					sum++;
	
	cout << sum << endl;

}
