#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
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

struct Market {

	using Strategy = vector<int>;

	map<Strategy, int> revenue_map;

  Market(string const& in_file_name);
  int scan();

};

Market::Market(string const& in_file_name) {

	string line;

	ifstream in_file(in_file_name);

	while (getline(in_file, line)) {

		long x = stol(line);

		set<Strategy> encountered;

		deque<int> q{0};

		for (int i = 0; i < 2000; i++) {

			q.push_back(price_increment(x));

			if (q.size() > 4) {

				q.pop_front();

				Strategy const strategy{q[0], q[1], q[2], q[3]};

				if (encountered.insert(strategy).second)
					if (revenue_map.find(strategy) == revenue_map.end())
						revenue_map[strategy] = x % 10;
					else
						revenue_map[strategy] += x % 10;

			}

		}

	}

}

int Market::scan() {

	int max = 0;

	for (int a = -9; a <= 9; a++)
		for (int b = -9; b <= 9; b++)
			for (int c = -9; c <= 9; c++)
				for (int d = -9; d <= 9; d++) {

					int rev = revenue_map[{a, b, c, d}];

					if (rev > max)
						max = rev;

				}

	return max;

}


int main() {
	
	Market market("input.txt");

	cout << market.scan() << endl;

}
