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


int score(vector<string> const& grid) {

	int sum = 0;

	for (int y = 0; y < grid.size(); y++)
		for (int x = 0; x < grid[0].size(); x++)
			if (grid[y][x] == '[' || grid[y][x] == ']')
				sum += 100 * y + x;

	return sum;

}

bool move_box(char const c, Coord const coord, vector<string> & grid) {

	int dy = c == '^' ? -1 : 1;

	int x = coord.x;
	int y = coord.y;

	vector<Coord> dependencies;

	switch (grid[y + dy][x]) {
		case '[': dependencies.push_back({y + dy, x}); break;
		case ']': dependencies.push_back({y + dy, x - 1}); break;
		case '#': return false;
	};

	switch (grid[y + dy][x + 1]) {
		case '[': dependencies.push_back({y + dy, x + 1}); break;
		case '#': return false;
	};

	bool movable = true;

	for (Coord const& d : dependencies)
		movable &= move_box(c, d, grid);

	if (movable) {

		grid[y + dy][x] = grid[y][x];
		grid[y + dy][x + 1] = grid[y][x + 1];

		grid[y][x] = '.';
		grid[y][x + 1] = '.';

		return true;

	}

	return false;

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

	if (c == '^' || c == 'v') {

		if (tile == '[')
			return move_box(c, coord, grid);

		else if (tile == ']')
			return move_box(c, {coord.y, coord.x - 1}, grid);

	}

	if (move(c, next, grid)) {

		grid[next.y][next.x] = tile;
		grid[coord.y][coord.x] = '.';

		if (bot != nullptr)
			*bot = next;

		return true;

	}

	return false;

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
