#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Block {int id, size, position;};

vector<Block> get_blocks(string const& line) {

	vector<Block> blocks;

	bool is_file = true;

	int id = 0;
	int position = 0;
	
	for (char const& c : line) {

		int size = c - '0';

	  blocks.push_back({is_file ? id++ : -1, size, position});

		position += size;

		is_file ^= true;

	}

	return move(blocks);

}

void compress(vector<Block> & blocks) {

	Block *r = &blocks.back();

	do {

	  Block *l = &blocks.front();

	  while (++l <= r && (l->id >= 0 || l->size < r->size));

		if (l < r) {

			r->position = l->position;
			l->position += r->size;
			l->size -= r->size;

		}

	} while ((r -= 2) > &blocks.front());

}

long checksum(vector<Block> const& blocks) {

	long sum = 0;

	for (Block const &b : blocks)
		if (b.id > 0)
			for (int i = 0; i < b.size; i++)
				sum += b.id * (b.position + i);

	return sum;

}

int main() {

	ifstream in_file("input.txt");

	string line;

	getline(in_file, line);

	vector<Block> blocks = get_blocks(line);

	compress(blocks);

	cout << checksum(blocks) <<  endl;

}
