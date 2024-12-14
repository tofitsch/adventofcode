#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

int const n_steps = 100;
int const n_x = 101;
int const n_y = 103;

struct Bot {

  int x, y, vx, vy;

	Bot(string const& line) {
		
		smatch match;

		regex static const re("=(-*\\d+),(-*\\d+).*=(-*\\d+),(-*\\d+)");

		regex_search(line, match, re);

		x = stoi(match[1].str());
		y = stoi(match[2].str());
		vx = stoi(match[3].str());
		vy = stoi(match[4].str());

	}

	void move() {

		x += vx;
		y += vy;

		x %= n_x;
		y %= n_y;

		if (x < 0)
			x += n_x;

		if (y < 0)
			y += n_y;

	}

};

int score (vector<Bot> const& bots) {

	vector<int> quadrant_counts(4, 0);

	for (auto const& b : bots) {

		if (b.x < n_x / 2 && b.y < n_y / 2)
			quadrant_counts[0]++;

		else if (b.x > n_x / 2 && b.y < n_y / 2)
			quadrant_counts[1]++;

		else if (b.x < n_x / 2 && b.y > n_y / 2)
			quadrant_counts[2]++;

		else if (b.x > n_x / 2 && b.y > n_y / 2)
			quadrant_counts[3]++;

	}

	for (int i = 1; i < 4; i++)
		quadrant_counts[0] *= quadrant_counts[i];

	return quadrant_counts[0];

}

int main() {

	ifstream in_file("input.txt");

	string line;

	vector<Bot> bots;

	while (getline(in_file, line))
		bots.push_back(line);

	for (int i = 0; i < n_steps; i++)
		for (Bot & bot : bots)
			bot.move();

	cout << score(bots) << endl;

}
