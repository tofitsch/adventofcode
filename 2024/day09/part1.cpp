#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void print(vector<int> & blocks) { //XXX

	for (int i : blocks)
		if (i >= 0)
			cout << i;
	  else
			cout << '.';

	cout << endl;

}

vector<int> get_blocks(string const& line) {

	vector<int> blocks;

	bool is_file = true;

	int id = -1;
	
	for (char const& c : line) {

		if (is_file)
		  id++;

		for (int i = 0; i < c - '0'; i++)
			blocks.push_back(is_file ? id : -1);

		is_file ^= true;

	}

	return move(blocks);

}

void compress(vector<int> & blocks) {

	int *l = &blocks.front();
	int *r = &blocks.back();

	while (true) {

	  while (*l >= 0)
	  	l++;

	  while (*r <= 0)
	  	r--;

		if(l > r)
			break;

		*l = *r;

		r--;

	}

	blocks.resize(r - &blocks.front() + 1);

}

long checksum(vector<int> const& blocks) {

	long sum = 0;

	for (int i = 0; i < blocks.size(); i++)
		sum += i * blocks.at(i);

	return sum;

}

int main() {

	ifstream in_file("input.txt");

	string line;

	getline(in_file, line);

	vector<int> blocks = get_blocks(line);

	print(blocks);

	compress(blocks);

	print(blocks);

	cout << checksum(blocks) <<  endl;

}
