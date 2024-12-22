#include <iostream>
#include <fstream>
#include <vector>
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

	using History = vector<vector<int>>;

	vector<vector<int>> prices;
	vector<History> histories;

  Market(string const& in_file_name);
  int revenue(vector<int> const& strategy);

};

int Market::revenue(vector<int> const& strategy) {

	int sum = 0;
	
	for (int i = 0; i < prices.size(); i++) {

		History const& history = histories[i];

	  auto it = find(history.begin(), history.end(), strategy);

		if (it != history.end()) {

			int idx = distance(history.begin(), it);

			sum += prices[i][idx];

		}

	}

	return sum;

}

Market::Market(string const& in_file_name) {

	string line;

	ifstream in_file(in_file_name);

	while (getline(in_file, line)) {

		long x = stol(line);

		prices.push_back({});
		histories.push_back({});

		deque<int> q{0};

		for (int i = 0; i < 2000; i++) {

			q.push_back(price_increment(x));

			if (q.size() > 4) {

				q.pop_front();

				prices.back().push_back(x % 10);

				histories.back().push_back({q[0], q[1], q[2], q[3]});

			}

		}

	}

}


int main() {
	
	Market market("example.txt");

	cout << market.revenue({-2, 1, -1, 3}) << endl;

}
