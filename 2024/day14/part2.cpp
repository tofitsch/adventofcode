#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <map>

using namespace std;

int const n_x = 101;
int const n_y = 103;

struct Bot {

  int x, y, vx, vy;

  bool const operator < (Bot const& other) const {
		return y < other.y ? true : y == other.y ? x < other.x : false;
	}


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

void print(vector<Bot> const& bots) {

	vector<string> grid(n_y, string(n_x, '0'));

	for (auto const& bot : bots)
		grid[bot.y][bot.x]++;

	for (string const& row : grid) {
		for (char const& cell : row)
			if (cell == '0')
				cout << '.';
			else
				cout << cell;
		cout << endl;
	}

	cout << endl;

}

int measure (vector<Bot> const& bots) {

	int sum = 0;


  for (Bot const& bot : bots)
		sum += abs(n_x / 2 - bot.x) + abs(n_y / 2 - bot.y);

	return sum;

}


int main() {

	ifstream in_file("input.txt");

	string line;

	vector<Bot> bots;

	while (getline(in_file, line))
		bots.push_back(line);

	map<vector<Bot>, pair<int, int>> mem;
  
	while (mem.insert({bots, {measure(bots), mem.size()}}).second)
  	for (Bot & bot : bots)
		  bot.move();

	int solution, best_measure = -1;

	for (auto const& [key, val] : mem) {

		if (val.first < best_measure || best_measure < 0) {

			best_measure = val.first;
			solution = val.second;
			bots = key;

		}

	}

//	print(bots);
	cout << solution << endl;

}
