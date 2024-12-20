#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int const min_saving = 100;

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

			switch (c) {
				case '#': break;
				case 'S': start = {y, x};
				case 'E': end = {y, x};
				default: path[{y, x}] = 0;
			};

			x++;

		}

		y++;

	}

}

/*
vector<Coord> get_path_within(Coord const& coord, int radius, set<Coord> const& path_set) {

	vector<Coord> vec;

	for (int y = 0; y < radius; y++) {
		for (int y = 0; y < radius; y++) {

			if (x + y > radius)

			Coord const c{y, x};

			if (c != coord && path_set.find(c) != path_set.end())
				neighbors.push_back(c);

		}
	}

	return vec;

}
*/

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

int main() {

	map<Coord, int> path;

	Coord start, end;
	
	read_path("example.txt", path, start, end);

	traverse(start, start, path, 0);

	cout << path[end] << endl;

//	int ctr = 0;
//
//	for (Coord const& shortcut : shortcuts)
//		if (get_saving(shortcut, nodes) >= min_saving)
//			ctr++;
//
//	cout << ctr << endl;
	
}
