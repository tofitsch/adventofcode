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

int score(vector<string> const& grid) {

	int sum = 0;

	for (int y = 0; y < grid.size(); y++)
		for (int x = 0; x < grid[0].size(); x++)
			if (grid[y][x] == '[')
				sum += 100 * y + x;

	return sum;

}

bool try_move_box_vertically(char const c, Coord const coord, vector<string> & grid, vector<Coord> & movers) {

	movers.push_back(coord);

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
		movable &= try_move_box_vertically(c, d, grid, movers);

	return movable;

}

void move_boxes_vertically(char const c, vector<Coord> const movers, vector<string> & grid) {

	int dy = c == '^' ? -1 : 1;

	for (Coord const& m : movers) {

		grid[m.y][m.x] = '.';
		grid[m.y][m.x + 1] = '.';

	}

	for (Coord const& m : movers) {

		grid[m.y + dy][m.x] = '['; 
		grid[m.y + dy][m.x + 1] = ']';

	}

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

	if ((c == '^' || c == 'v') && (tile == '[' || tile == ']')) {

		vector<Coord> movers;

		bool origin_moves;

		if (tile == '[') 
			origin_moves = try_move_box_vertically(c, coord, grid, movers);
		else if (tile == ']')
			origin_moves = try_move_box_vertically(c, {coord.y, coord.x - 1}, grid, movers);

		if (origin_moves)
			move_boxes_vertically(c, movers, grid);

		return origin_moves;

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

	read_file("input.txt", grid, moves, bot);

	print(grid);

	for (char c : moves) {
//	  print(grid);
		move(c, bot, grid, & bot);
//		cin.get();
	}

	print(grid);

	cout << score(grid) << endl;

}
