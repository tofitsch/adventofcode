#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct Coord {

	int y, x;

	bool const operator < (Coord const& other) const {
		return tie(y, x) < tie(other.y, other.x);
	}

};

class pad {

	public:

		string type(string const& str) {

			for (char const c : str) {

				move(c);

				path += 'A';

			}

			position = mapping['A'];

			return std::move(path);

		}

	private: 

		string path{""};

	protected:

		Coord position;

		map<char, Coord> mapping;

		pad(map<char, Coord> const& m) : mapping(m) {

			position = mapping['A'];

		}

		virtual void move(char const to) = 0;

		void move_up(char const to) {
			while (position.y > mapping[to].y) {path += "^"; position.y--;}
		}

		void move_down(char const to) {
			while (position.y < mapping[to].y) {path += "v"; position.y++;}
		}

		void move_right(char const to) {
			while (position.x < mapping[to].x) {path += ">"; position.x++;}
		}

		void move_left(char const to) {
			while (position.x > mapping[to].x) {path += "<"; position.x--;}
		}

};

class numeric_pad final : public pad {

	public:

		numeric_pad() : pad({

			{'A', {3, 2}},
			{'0', {3, 1}},
			{'1', {2, 0}},
			{'2', {2, 1}},
			{'3', {2, 2}},
			{'4', {1, 0}},
			{'5', {1, 1}},
			{'6', {1, 2}},
			{'7', {0, 0}},
			{'8', {0, 1}},
			{'9', {0, 2}},

		}) {}

	private:

		// To minimize the path on the upstream directional_pad,
		// keys should be ordered by their distance from 'A'
		// on the directional_pad in decreasing order of distance: <v^>
		// Except if this would mean passing over a tile without key
		// On the numeric_pad this is avoided by doing:
		// up before left; rigth before down
		void move(char const to) override {

			// try except if passing over tile without key
			if (position.y != 3 || mapping[to].x != 0)
				move_left(to);
			if (position.x != 0 || mapping[to].y != 3)
				move_down(to);

			// always ok
			move_up(to);
			move_right(to);

			// in case it was avoided above due to tile without key
			move_left(to);
			move_down(to);

		}

};

class directional_pad final : public pad {

	public:

		directional_pad() : pad({

			{'A', {0, 2}},
			{'^', {0, 1}},
			{'<', {1, 0}},
			{'v', {1, 1}},
			{'>', {1, 2}},

		}) {}
	
	private:

		// To minimize the path on the upstream directional_pad,
		// keys should be ordered by their distance from 'A'
		// on the directional_pad in decreasing order of distance: <v^>
		// Except if this would mean passing over a tile without key
		// On the directional_pad this is avoided by doing:
		// right before up ;  down before left
		void move(char const to) override {

			// try except if passing over tile without key
			if (position.y != 0 || mapping[to].x != 0)
				move_left(to);
			if (position.x != 0 || mapping[to].y != 0)
				move_up(to);

			// always ok
			move_down(to);
			move_right(to);

			// in case it was avoided above due to tile without key
			move_left(to);
		  move_up(to);

		}

};

int complexity(string line, string const& path) {

	line.pop_back();

	return stoi(line) * path.size();

}

int main() {

	string line;

	ifstream in_file("input.txt");

	int sum = 0;

	numeric_pad n;
	directional_pad d1, d2;

	while (getline(in_file, line))
		sum += complexity(line, d2.type(d1.type(n.type(line))));

	cout << sum << endl;

}
