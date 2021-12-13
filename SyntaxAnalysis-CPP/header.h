#ifndef SyntaxAnalysis_CPP
#define SyntaxAnalysis_CPP


#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<set>

#define INPUT "input.txt"
using namespace std;

map<char,set<string> > grammar; // 用来存储每个非终结符对应的右边的产生式
vector<char> v;  // 用来存储文法的非终结符
map<char,bool> has; // 用来标记这个非终结符是否出现了
map<pair<char,char>, bool> vis; // 标记某两个字符是否是对应的，比如S->Qc，那么mp[make_pair(S,Q)]=true;

#endif