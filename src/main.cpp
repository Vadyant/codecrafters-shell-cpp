#include<bits/stdc++.h>
using namespace std;

string line;
bool active = true;

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
  if(line=="exit") return;
  string v="invalid";
  print(line,v);
}

int main() {
  // Flush after every std::cout / std:cerr
  cout << std::unitbuf;
  cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  while (active) {  
    read();
    eval();
  }
  return 0;
}