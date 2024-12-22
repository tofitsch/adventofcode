#include <iostream>
#include <fstream>

using namespace std;

long mix(long a, long b) {
	return a ^ b;
}

long prune(long a) {
	return a % 16777216;
}

void increment(long & a) {

	a = prune(mix(a, a * 64));
	a = prune(mix(a, a / 32));
	a = prune(mix(a, a * 2048));

}

int main() {

	string line;

	ifstream in_file("input.txt");

	long sum = 0;

	while (getline(in_file, line)) {

		long x = stol(line);

		for (int i = 0; i < 2000; i++)
			increment(x);

		sum += x;

	}

	cout << sum << endl;

}
