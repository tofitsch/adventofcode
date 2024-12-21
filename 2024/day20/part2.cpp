#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int const min_saving = 100;
int const radius = 20;

struct Coord {

	int y, x;

	bool const operator < (Coord const& other) const {
		return tie(y, x) < tie(other.y, other.x);
	}

	bool const operator != (Coord const& other) const {
		return y != other.y || x != other.x;
	}

};

void read_path(string const& file_name, map<Coord, int> & path, Coord & start, Coord & end) {

	fstream in_file(file_name);

	string line;

	int y = 0;

	while (getline(in_file, line)) {

		int x = 0;

		for (char c : line) {

			if (c == 'S')
				start = {y, x};

			if (c == 'E')
				end = {y, x};

			if (c != '#')
				path[{y, x}] = 0;

			x++;

		}

		y++;

	}

}

vector<Coord> get_neighbors(Coord const& coord) {

	return {
		{coord.y - 1, coord.x},
		{coord.y, coord.x + 1},
		{coord.y + 1, coord.x},
		{coord.y, coord.x - 1},
	};

}

void traverse(Coord const& coord, Coord const& prev, map<Coord, int> & path, int dist) {

	path[coord] = dist;

	for (Coord const &neighbor : get_neighbors(coord))
		if (path.find(neighbor) != path.end() && neighbor != prev)
			return traverse(neighbor, coord, path, dist + 1);
}

int n_shortcuts(Coord const& coord, map<Coord, int> & path) {

	set<Coord> shortcuts;

	for (int y = 0; y <= radius; y++)
		for (int x = 0; x + y <= radius; x++)
			for (Coord const c : vector<Coord>{
					{coord.y + y, coord.x + x},
					{coord.y - y, coord.x + x},
					{coord.y + y, coord.x - x},
					{coord.y - y, coord.x - x},
			})
				if (c != coord && path.find(c) != path.end())
					if (path[c] - path[coord] - x - y >= min_saving)
						shortcuts.insert(c);

	return shortcuts.size();

}

int count_shortcuts(map<Coord, int> & path) {

	int ctr = 0;

	for (auto const& [coord, dist] : path)
		ctr += n_shortcuts(coord, path);

	return ctr;

}

int main() {

	map<Coord, int> path;

	Coord start, end;
	
	read_path("input.txt", path, start, end);

	traverse(start, start, path, 0);

	cout << count_shortcuts(path) << endl;

}
