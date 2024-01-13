#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>

using namespace std;

long search(vector<long> & terms){
  
  long sum = 0;

  vector<long> sums;

  while(true){
    
    for(long term : terms){
      
      sum += term; 

      if(find(sums.begin(), sums.end(), sum) != sums.end())
        return sum;

      sums.push_back(sum);

    }

  }

}

int main(){
  
  string line, field;

  ifstream in_file("input.txt");

  vector<long> terms;

  while(getline(in_file, line)){
    
    stringstream line_stream(line);

    while(getline(line_stream, field, ' '))
      terms.push_back(stoi(field));

  }

  cout << search(terms) << endl;
 
}
