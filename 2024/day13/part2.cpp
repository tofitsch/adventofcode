#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

long const offset = 10'000'000'000'000;

struct Equation {

	// a0*a + b0*b = p0 //eq0
	// a1*a + b1*b = p1 //eq1

	long a0, a1, b0, b1, p0, p1, a, b;

	bool has_solution;

	void solve () {

		// solve eq0 for a
		// a = (p0 - b0*b) / a0 //eq2
		
		// substitute a from eq2 into eq1
		// a1/a0*(p0 - b0*b) + b1*b = p1
		
		// expand
		// a1/a0*p0 + b*(b1 - a1/a0*b0) = p1

		// solve for b
		// b = (p1 - a1/a0*p0) / (b1 - a1/a0*b0);

		// re-arrange to avoid floating point division
		// b = (a0 * p1 - a1 * p0) / (a0 * b1 - a1 * b0);

		// substitute into eq2
		// a = (p0 - b0*b) / a0;

		long denominator_b = a0 * b1 - a1 * b0;
		long numerator_b = a0 * p1 - a1 * p0;

		has_solution = (

					denominator_b != 0                      // no division by 0
			&&	numerator_b % denominator_b == 0        // is integer
			&&	(b = numerator_b / denominator_b) >= 0  // is positive

	  );

		if (!has_solution)
			return;

		long denominator_a = a0;
		long numerator_a = p0 - b0 * b;

		has_solution &= (

					denominator_a != 0                      // no division by 0
			&&	numerator_a % denominator_a == 0        // is integer
			&&	(a = numerator_a / denominator_a) >= 0  // is positive

	  );

	}

};

void parse(string const& line, long & x, long & y) {

	smatch match;
	regex re("(\\d+)\\D+(\\d+)");

	regex_search(line, match, re);

	x = stol(match[1].str());
	y = stol(match[2].str());

}

vector<Equation> read_equations(string const& in_file_name) {

	ifstream in_file(in_file_name);

	string line;

	vector<Equation> equations;
	
	while (getline(in_file, line)) {

		if (line.size() == 0)
			continue;

		// X+a0, Y+a1
    // X+b0, Y+b1
    // X=p0, Y=p1

		switch (line[7]) {

			case 'A':
				equations.push_back({});
				parse(line, equations.back().a0, equations.back().a1);
				break;

			case 'B':
				parse(line, equations.back().b0, equations.back().b1);
				break;
			case 'X':
				parse(line, equations.back().p0, equations.back().p1);
				equations.back().p0 += offset;
				equations.back().p1 += offset;
				break;

		};

	}

	return move(equations);

}


int main() {

	vector<Equation> equations = read_equations("input.txt");

	long sum = 0;

	for (auto & eq : equations) {

		eq.solve();

		if (eq.has_solution) {
			sum += eq.a * 3 + eq.b;
		}

	}

	cout << sum << endl;

}
