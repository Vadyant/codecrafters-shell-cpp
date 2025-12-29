#include<bits/stdc++.h>
using namespace std;

string line;
bool active = true;
vector<string> builtin={"echo","exit","type"};
vector<string>word;
int len;
string val;

void print(int a,int b){
  for(int i=a;i<b-1;i++){
    cout<<word[i]<<' ';
  }
  cout<<word[b-1]<<val<<endl;
}

void read(){
  word.clear();
  cout << "$ ";
  getline(cin,line);
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
}

void eval(){
  if(word[0]=="exit"){
    active=false;
    return;
  }
  
  if(word[0]=="echo"){
    val="";
    print(1,len);
    return;
  }
  
  if(word[0]=="type"){
    auto it = find(builtin.begin(), builtin.end(), word[1]);
    if(it != builtin.end()){
      cout<<word[1]<<" is a shell builtin"<<endl;
      return;
    }
    val=": not found";
    print(1,len);
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