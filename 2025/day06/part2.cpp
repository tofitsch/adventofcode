#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

int main(){
  
  string line, field;

  ifstream in_file("input.txt");

  vector<string> lines;

  while (getline(in_file, line))
    lines.push_back(line);

  stringstream line_stream(lines.back());

  lines.pop_back();

  vector<bool> problem_is_prod;

  while (getline(line_stream, field, ' '))
    if (field.length() > 0)
      problem_is_prod.push_back(field == "*");

  vector<size_t> problem_solutions(problem_is_prod.size());

  size_t i_problem = problem_is_prod.size() - 1;

  for (size_t i = 0; i <= i_problem; ++i)
    problem_solutions[i] = problem_is_prod[i] ? 1 : 0;

  for (int x = lines[0].length() - 1; x >= 0; --x) {

    string column{""};

    for (int y = 0; y < lines.size(); ++y)
      if (lines[y][x] != ' ')
        column += lines[y][x];

    if (column.length() == 0) {

      i_problem--;

      continue;

    }

    size_t const num = stol(column);

    if (problem_is_prod[i_problem])
      problem_solutions[i_problem] *= num;
    else
      problem_solutions[i_problem] += num;

  }

  size_t sum{0};

  for (size_t const s : problem_solutions)
    sum += s;

  cout << sum << endl;

}
