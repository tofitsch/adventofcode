#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<set>

using namespace std;

int search(vector<int> & terms){
  
  int sum = 0;

  set<int> sums;

  while(true){
    
    for(int term : terms){
      
      sum += term; 

      if(! sums.insert(sum).second)
        return sum;

    }

  }

}

int main(){
  
  string line, field;

  ifstream in_file("input.txt");

  vector<int> terms;

  while(getline(in_file, line)){
    
    stringstream line_stream(line);

    while(getline(line_stream, field, ' '))
      terms.push_back(stoi(field));

  }

  cout << search(terms) << endl;
 
}
