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

	sort(l.begin(), l.end());
	sort(r.begin(), r.end());

	int sum = 0;

	for (int i = 0; i < l.size(); i++)
		sum += abs(l[i] - r[i]);

	cout << sum << endl;

}
