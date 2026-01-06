#include <bits/stdc++.h>
#include <sys/wait.h> 
#include <unistd.h>
#include <fcntl.h>

using namespace std;

string line;
bool active = true;
vector<string> builtin = {"echo", "exit","type","pwd","cd"};
vector<string> word;
vector<char*> argv;
int len;
string val;
vector<string > directory;
pair<int,char> redirection={-1,'\0'}; // base case to check if redir is present or not

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
  argv.clear();
  cout << "$ ";
  getline(cin, line);

  directory=dir(getenv("PATH"));

  bool single_quote=false;
  bool double_quote=false;
  string temp = "";
  for (int i=0;i<line.size();i++) {
    char c=line[i];
    if(c=='\\'){
      if(single_quote){
        temp+=c;
        continue;
      }else if(double_quote){
        if(line[i+1]=='"'||line[i+1]=='\\'){
          i++;
          temp+=line[i];
        }else temp+=c;
      }
      else{
        i++;
        temp+=line[i];
        continue;
      }
    }

    else if(c=='"'&&(!single_quote)){
      double_quote=!double_quote;
    }

    else if(c=='\''&&(!double_quote)){
      single_quote=!single_quote;
    }

    else if (c == ' '&&(!single_quote&&!double_quote)) {
      if (!temp.empty()) word.push_back(temp);
      temp = "";
    } 
    
    else temp += c;
  }
  if (!temp.empty()) word.push_back(temp);

  len = word.size();

  for(auto &s:word){
    argv.push_back(s.data());
  }
  argv.push_back(nullptr);

  // for(int i=0;i<len;i++){
  //   if(word[i]==">"||word[i]=="1>"){
  //     redirection.push_back({i,'>'});
  //   }else if(word[i]=="<"||word[i]=="<1"){
  //     redirection.push_back({i,'<'});
  //   }
  // }
  for(int i=0;i<len;i++){
    if(word[i]==">"||word[i]=="1>"){
      redirection={i,'>'};
      break;
    }else if(word[i]=="<"||word[i]=="<1"){
      redirection={i,'<'};
      break;
    }
  }
}

void eval() {
  if (word.empty()) return;

  int pid=-1;
  string file_name;
  if(redirection.first!=-1){
    pid=fork();
    file_name=word[redirection.first+1];

    for(int i=redirection.first;i<len;i++){
      word.erase(word.begin()+i);
    }

  }

  if(pid>0){
    wait(NULL);
    return;
  }

  int fd;
  if(pid==0){
    if(redirection.second=='>'){
      fd=open(file_name.c_str(),O_WRONLY|O_CREAT);
      dup2(fd,STDOUT_FILENO);
    }
    else{
      fd=open(file_name.c_str(),O_RDONLY);
      dup2(fd,STDIN_FILENO);
    }
  }

  if(find(builtin.begin(), builtin.end(), word[0])!=builtin.end()){
    
    if (word[0] == "exit") {
      active = false;
      if(pid==0) exit(0);
      return;
    }
  
    if (word[0] == "echo") {
      val = "";
      print(1, len);
      if(pid==0) exit(0);
      return;
    }

    if(word[0]=="pwd"){
      char cwd[PATH_MAX];
      if(getcwd(cwd,sizeof(cwd))){
        cout<<cwd<<endl;
      }
      if(pid==0) exit(0);
      return;
    }

    if(word[0]=="cd"){

      if(argv[1]==nullptr||strcmp(argv[1],"~")==0){ // cd ~
        char* HOME= getenv("HOME");
        if(chdir(HOME)==0) return;
        else cout<<"cd: "<<argv[1]<<": No such file or directory"<<endl;
        if(pid==0) exit(0);
        return;
      }

      if(chdir(argv[1])==0) {
        if(pid==0) exit(0);
        return;
      }
      else cout<<"cd: "<<argv[1]<<": No such file or directory"<<endl;
      if(pid==0) exit(0);
      return;

    }
  
    if (word[0] == "type") {
      if (len < 2) {
        cout << "type: missing argument" << endl;
        if(pid==0) exit(0);
        return;
      }
      auto it = find(builtin.begin(), builtin.end(), word[1]);
      if (it != builtin.end()) {
        cout << word[1] << " is a shell builtin" << endl;
        if(pid==0) exit(0);
        return;
      }
      for(auto d:directory){
        d=d+"/"+word[1];
        if(access(d.c_str(),X_OK)==0){
          cout<<word[1]<<" is "<<d<<endl;
          if(pid==0) exit(0);
          return;
        }
      }
      cout<<word[1]<<": not found"<<endl;
      if(pid==0) exit(0);
      return;
    }
    cout<<"not a builting func"<<endl;
  }
  // not builtin
  for(auto d:directory){
    d=d+"/"+word[0];
    if(access(d.c_str(),X_OK)==0){
      int pid = fork();
      if (pid==0){
        execv(d.c_str(), argv.data()); 
        perror("execvp"); exit(1);
      }else if(pid>0){
        wait(NULL);
      } 
      if(pid==0) exit(0);
      return;
    }
  }
  cout<<word[0]<<": command not found"<<endl;
  if(pid==0) exit(0);
  return;
}

int main() {
  cout << std::unitbuf;
  cerr << std::unitbuf;

  while (active) {
    read();
    eval();
  }
}
