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

		void move(char const to) override {

			move_up(to);
			move_left(to);
			move_right(to);
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

		void move(char const to) override {

			move_right(to);
			move_up(to);
			move_down(to);
		  move_left(to);

		}

};

int complexity(string line, string const& path) {

	line.pop_back();

	cout << stoi(line) << " * " << path.size() << endl;

	return stoi(line) * path.size();

}

int main() {

	string line;

	ifstream in_file("example.txt");

	int sum = 0;

	numeric_pad n;
	directional_pad d1, d2;

	while (getline(in_file, line))
		sum += complexity(line, d2.type(d1.type(n.type(line))));

	cout << sum << endl;

}
