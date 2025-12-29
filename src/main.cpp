#include<bits/stdc++.h>
using namespace std;

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
    cout<<line<<": command not found"<<endl;
  }
  return 0;
}