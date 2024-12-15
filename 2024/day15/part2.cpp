#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Coord {int y, x;};

string widen(string const& line) {

	string out = "";

	for (char c : line)
		switch (c) {
			case '.': out += ".."; break;
			case '#': out += "##"; break;
			case 'O': out += "[]"; break;
			case '@': out += "@."; break;
		};

	return out;

}

void read_file (string const& file_name, vector<string> & grid, string & moves, Coord & bot) {

	ifstream in_file(file_name);

	string line;

	moves = "";

	while (getline(in_file, line)) {
		if (line.size() > 0) {

			if(line[0] == '#')
				grid.push_back(line);
			else
				moves += line;

		}
	}

	for (string & line : grid)
		line = widen(line);

	for (bot.y = 0; bot.y < grid.size(); bot.y++) {

		 bot.x = grid[bot.y].find('@');

		 if (bot.x != string::npos)
			 break;

	}

}

void undo(char const c, Coord const coord, vector<string> & grid) {

	Coord next = coord;

	switch (c) {
		case '^': next.y++; break;
		case 'v': next.y--; break;
	};

	grid[next.y][next.x] = grid[coord.y][coord.x];
	grid[coord.y][coord.x] = '.';

}

bool move(char const c, Coord const coord, vector<string> & grid, Coord * bot = nullptr) {

	char const tile = grid[coord.y][coord.x];

	if (tile == '.')
		return true;

	Coord next = coord;

	switch (c) {
		case '^': next.y--; break;
		case '>': next.x++; break;
		case 'v': next.y++; break;
		case '<': next.x--; break;
	};

	if (grid[next.y][next.x] == '#')
		return false;

	bool moved = move(c, next, grid);

	bool moved2 = true;

	if (moved && (c == '^' || c == 'v')) {

	  if (tile == '[')
	  	moved2 = move(c, {coord.y, coord.x + 1}, grid);

	  else if (tile == ']')
	  	moved2 = move(c, {coord.y, coord.x - 1}, grid);

	}

	if (moved && !moved2) {

		undo(c, next, grid);

		return false;

	}

	if (moved && moved2) {

		grid[next.y][next.x] = grid[coord.y][coord.x];
		grid[coord.y][coord.x] = '.';

		if (bot != nullptr)
			*bot = next;

		return true;

	}

	return false;

}

int score(vector<string> const& grid) {

	int sum = 0;

	for (int y = 0; y < grid.size(); y++)
		for (int x = 0; x < grid[0].size(); x++)
			if (grid[y][x] == '[' || grid[y][x] == ']')
				sum += 100 * y + x;

	return sum;

}

void print(vector<string> const& grid) {

	for (string const& line : grid)
		cout << line << endl;

}

int main () {

	vector<string> grid;
	string moves;
	Coord bot;

	read_file("example.txt", grid, moves, bot);

	print(grid);

	for (char c : moves) {
	  print(grid);
		move(c, bot, grid, & bot);
		cin.get();
	}

	print(grid);

	cout << score(grid) << endl;

}
