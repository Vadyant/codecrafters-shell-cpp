#include<bits/stdc++.h>
using namespace std;

bool invalid_command(string line){
  cout<<line<<": command not found"<<endl;
}

int main() {
  // Flush after every std::cout / std:cerr
  cout << std::unitbuf;
  cerr << std::unitbuf;

  // TODO: Uncomment the code below to pass the first stage
  bool active = true;
  while (active) {  
    cout << "$ ";
    string line;
    getline(cin, line);
    invalid_command(line);
  }
  return 0;
}