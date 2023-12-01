#include<iostream>
#include<fstream>

using namespace std;

int main(){
  
  int sum = 0;
  
  string line;

  ifstream in_file("input.txt");

  while(getline(in_file, line)){

    char first_c = ' ';
    char last_c = ' ';
    
    for(char & c : line){
      
      if(isdigit(c)){
        
        last_c = c;

        if(first_c == ' ')
          first_c = c;

      }

    }

    string num(1, first_c);
    num += last_c;

    sum += stoi(num);

  }

  cout<<sum<<endl;

}
