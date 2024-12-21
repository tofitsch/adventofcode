#include <iostream>
#include <fstream>
#include <sstream>
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

		using io = map<string, long>;

		io type(io const& in) {

			io out;

			for (auto const &[str, n] : in) {

				string field;

				stringstream stream(str);

				while (getline(stream, field, 'A')) {

					field += 'A';

					path = "";

					for (char const c : field) {

						move(c);

						path += 'A';

					}

					position = mapping['A'];

					if (out.find(path) == out.end())
						out[path] = n;
					else
						out[path] += n;

				}

			}

			return out;

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

long complexity(string line, pad::io const& path) {

	line.pop_back();

	long ctr = 0;

	for (auto const &[key, n] : path)
		ctr += n * key.size();

	return stoi(line) * ctr;

}

int main() {

	string line;

	ifstream in_file("input.txt");

	long sum = 0;

	numeric_pad n;
	directional_pad d;

	while (getline(in_file, line)) {

		pad::io out = n.type({{line, 1}});

		for (int i = 0; i < 25; i++)
			out = d.type(out);

		sum += complexity(line, out);

	}

	cout << sum << endl;

}
