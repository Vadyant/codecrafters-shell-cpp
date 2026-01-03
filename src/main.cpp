#include <bits/stdc++.h>
using namespace std;

string line;
bool active = true;
vector<string> builtin = {"echo", "exit", "type"};
vector<string> word;
int len;
string val;
vector<string > directory;

vector<string> dir(const char* p){
  vector<string> d;
  string word;
  stringstream ss(p);
  while(getline(ss,word,':')){
    d.push_back(word);
  }
  return d;
}

void print(int a, int b) {
  if (a >= b) {
    cout << endl;
    return;
  }
  for (int i = a; i < b - 1; i++) {
    cout << word[i] << ' ';
  }
  cout << word[b - 1] << val << endl;
}

void read() {
  word.clear();
  cout << "$ ";
  getline(cin, line);

  directory=dir(getenv("PATH"));

  string temp = "";
  for (char c : line) {
    if (c == ' ') {
      if (!temp.empty()) word.push_back(temp);
      temp = "";
    } else temp += c;
  }
  if (!temp.empty()) word.push_back(temp);

  len = word.size();
}

void eval() {
  if (word.empty()) return;

  if (word[0] == "exit") {
    active = false;
    return;
  }

  if (word[0] == "echo") {
    val = "";
    print(1, len);
    return;
  }

  if (word[0] == "type") {
    if (len < 2) {
      cout << "type: missing argument" << endl;
      return;
    }
    auto it = find(builtin.begin(), builtin.end(), word[1]);
    if (it != builtin.end()) {
      cout << word[1] << " is a shell builtin" << endl;
      return;
    }
    for(auto d:directory){
      d=d+"/"+word[1];
      if(access(d.c_str(),X_OK)==0){
        cout<<word[1]<<" is "<<d<<endl;
        return;
      }
    }
    cout<<word[1]<<": not found"<<endl;
    return;
  }

  cout << line << ": command not found" << endl;
}

int main() {
  cout << std::unitbuf;
  cerr << std::unitbuf;

  while (active) {
    read();
    eval();
  }
}
