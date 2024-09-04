#include<iostream>
#include<fstream>
#include<map>
#include<cmath>

using namespace std;

#define MAX_X 5
#define MAX_Y 5

int count_neighbours(bool grid[MAX_Y][MAX_X], int y, int x) {

	int count = 0;

	if(x > 0 && grid[y][x-1]) count++;
	if(x < 4 && grid[y][x+1]) count++;
	if(y > 0 && grid[y-1][x]) count++;
	if(y < 4 && grid[y+1][x]) count++;

	return count;

}

void update_grid(bool grid[MAX_Y][MAX_X]) {

	bool new_grid[MAX_Y][MAX_X];

	for(int y=0; y<MAX_Y; y++) {
		for(int x=0; x<MAX_X; x++) {

			int count = count_neighbours(grid, y, x);

			new_grid[y][x] = (grid[y][x] && count == 1)
				|| (!grid[y][x] && (count == 1 || count == 2));

		}
	}

	for(int y=0; y<MAX_Y; y++)
		for(int x=0; x<MAX_X; x++)
			grid[y][x] = new_grid[y][x];

}

int hash_grid(bool grid[MAX_Y][MAX_X]) {

	int h = 0;

	for(int y=0; y<MAX_Y; y++)
		for(int x=0; x<MAX_X; x++)
			if(grid[y][x])
				h += pow(2, y*MAX_X + x);

	return h;

}

int main() {

	string line;

	ifstream in_file("input.txt");

	bool grid[MAX_Y][MAX_X];

	int y = 0;

	while(getline(in_file, line)) {

		int x = 0;

		for(char &c : line)
			grid[y][x++] = c == '#';

		y++;

	}

	in_file.close();

	map<int, bool> seen;

	int score;

	do {

		seen[score] = true;

		score = hash_grid(grid);

		update_grid(grid);


	} while (!seen[score]);

	cout << score << endl;

}
