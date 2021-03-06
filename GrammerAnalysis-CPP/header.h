#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<vector>
#include<stack>
#include<utility>
#define INPUT "input.txt"
#define END "ed.txt"
#define UEND "ued.txt"
#define EXPRESSION "expression.txt"


using namespace std;
// 先得到first和last集合，然后根据这两个构造一个算符优先表，根据这个表，对每个表达式判断这个表是否是一个合法的表达式
map<pair<char,char>,bool> first,last; // 存储临时的firstV和lastV的对应关系
vector<char> ed,ued; // 分别表示终结符和非终结符
stack<pair<char,char>> st; // 用来存储这个一些终结符和非终结符的优先级对应关系
vector<string> tmp,v; // 用来存储输入的文法
map<char,bool> op; // 用来存储终结符
map<char,vector<char>> suf1,suf; // suf1用来存储每个P->...Q，suf用来存储每个P->Q...
map<char,vector<char>> firstV,lastV; // firstV集合和lastV集合
map<pair<char,char>,int> table; // 用来存储算符优先分析表,-1表示<,0表示=，1表示大于,-2表示没有关系
map<string,char> g; // 用户归约操作
char k='E'; // 用来存储非终结符#E#的形式的
vector<char> sk(100);