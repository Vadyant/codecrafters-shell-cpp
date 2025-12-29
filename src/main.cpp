#include<bits/stdc++.h>
using namespace std;

string line;
bool active = true;
vector<string> builtin={"echo","exit","type"};

// void print(string line,string val){
//   if(val=="invalid"){
//     cout<<line<<": command not found"<<endl;
//   }
// }

void read(){
  cout << "$ ";
  getline(cin,line);
}

void eval(){
  vector<string>word;
  string temp="";

  for(int i=0;i<line.length();i++){
    if(line[i]==' '){
      word.push_back(temp);
      temp="";
    }
    else temp+=line[i];
  }
  word.push_back(temp);
  int len=word.size();
  
  if(word[0]=="exit"){
    active=false;
    return;
  }
  
  if(word[0]=="echo"){
    for(int i=1;i<len;i++)
    cout<<word[i]<<' ';
    cout<<endl;
    return;
  }
  
  if(word[0]=="type"){
    auto it = find(builtin.begin(), builtin.end(), word[1]);
    if(it != builtin.end()){
      cout<<word[1]<<" is a shell builtin"<<endl;
      return;
    }
    for(int i=1;i<len;i++)
    cout<<word[i]<<' ';
    cout<<": not found"<<endl;
    return;
  }
  
  cout<<line<<": command not found"<<endl;
  
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