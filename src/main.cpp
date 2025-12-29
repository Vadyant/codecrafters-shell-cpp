#include<bits/stdc++.h>
using namespace std;

string line;

void print(string line,string val){
  if(val=="invalid"){
    cout<<line<<": command not found"<<endl;
  }
}

void read(){
  cout << "$ ";
  getline(cin,line);
}

void eval(){
  print(line,"invalid");
}

int main() {
  // Flush after every std::cout / std:cerr
  cout << std::unitbuf;
  cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  bool active = true;
  while (active) {  
    read();
    eval();
  }
  return 0;
}