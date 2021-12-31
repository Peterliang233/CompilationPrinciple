#include<iostream>
#include<stack>
#include<string>
#include<map>
#include<fstream>

#define INPUT "experssion.txt"
#define OPERATION "operation.txt"

using namespace std;

stack<string> st; // 用来存储表达式的字符串
stack<char> op; // 用来存储表达式的操作符号
map<char,bool> vis; // 判断哪些是操作符
