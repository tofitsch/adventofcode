#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

long mix(long a, long b) {
	return a ^ b;
}

long prune(long a) {
	return a % 16777216;
}

int price_increment(long & a) {

	int initial_price = a % 10;

	a = prune(mix(a, a * 64));
	a = prune(mix(a, a / 32));
	a = prune(mix(a, a * 2048));

	int new_price = a % 10;

	return new_price - initial_price;

}

vector<long> read_file() {

	vector<long> secrets;

	string line;

	ifstream in_file("example.txt");

	while (getline(in_file, line))
		secrets.push_back(stol(line));

	return secrets;

}

int revenue(vector<long> const& secrets, deque<int> const& Q) {

	int sum = 0;

	for (long x : secrets) {

		deque<int> q{0};

		for (int i = 0; i < 2000; i++) {

			q.push_back(price_increment(x));

			if (q.size() > 4) {

				q.pop_front();

				if (q == Q) {

					sum += x % 10;

					break;

				}

			}

		}

	}

	return sum;

}

int main() {
	
	vector<long> const secrets = read_file();

	int max = 0;

	for (int a = -9; a <= 9; a++)
		for (int b = -9; b <= 9; b++)
			for (int c = -9; c <= 9; c++)
				for (int d = -9; d <= 9; d++) {

					int rev = revenue(secrets, {a, b, c, d});

					if (rev > max)
						max = rev;

				}

	cout << max << endl;

}
