#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {

	ifstream in_file("input.txt");
  
	string line;

	vector<int> l, r;

	while(getline(in_file, line)) {

		int s = line.find(' ');

		l.push_back(stoi(line.substr(0, s)));
		r.push_back(stoi(line.substr(s + 1)));

	}

	int sum = 0;

	for (int i : l)
	  for (int j : r)
			if (i == j)
				sum += i;
  
	cout << sum << endl;

}
