#include<iostream>
#include<fstream>
#include<map>

using namespace std;

void count(string & line, int & n2, int & n3){
 
 map<char, int> counts;
 
 for(char & c : line)
   if(counts.find(c) == counts.end())
     counts[c] = 1;
   else
     counts[c]++;
 
 bool has_n2 = false;
 bool has_n3 = false;
 
 for(pair<char const, int> & e : counts)
   if(e.second == 2)
     has_n2 = true;
   else if(e.second == 3)
     has_n3 = true;
 
 n2 += has_n2;
 n3 += has_n3;

}

int main(){
  
  string line;
 
  ifstream in_file("input.txt");

  int n2 = 0;
  int n3 = 0;

  while(getline(in_file, line))
    count(line, n2, n3);

  cout << n2 * n3 << endl;
    
}
