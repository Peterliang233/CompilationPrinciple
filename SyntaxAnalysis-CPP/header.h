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
#define OUTPUT "output.txt"
#define RESULT "result.txt"
#define ANSWER "answer.txt"
#define N 100000
using namespace std;

map<char,set<string> > grammar; // 用来存储每个非终结符对应的右边的产生式
vector<char> v;  // 用来存储文法的非终结符
map<char,bool> has; // 用来标记这个非终结符是否出现了
map<pair<char,char>, bool> vis; // 标记某两个字符是否是对应的，比如S->Qc，那么mp[make_pair(S,Q)]=true;





map<string,int> mp; // 用来记录每个出现的产生式左边的非终结符的下标
vector<string> v1[N];  // 用来记录非终结符的右边的字符串
int cnt; // 记录v1数组的有效的游标范围

void scan();  // 从文本文件里面读取文法
void dealString(string line); // 处理读入的字符串，转化为一个合法的文法
void output();  // 将文法输出到一个文件里面
void init();  // init 初始化一些读入的参数
void removeLeftRecursion();  // 消除左递归
void deal(string s);  // 对从文件读入的字符串进行处理
void removeLeftGene(); // 提取左公因子函数


#endif