#ifndef PREDICT
#define PREDICT
#include <iostream>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <string>
#define INPUT "input.txt"
#define OP "operator.txt"

using namespace std;

map<char, set<string>> mp; // 用来存储文法，一个非终结符对应的文法
map<char,bool> op;            // 表示终结符
vector<string> v;          // 用来存储所有的文法

map<char, set<char>> first, follow; // 表示First集合和Follow集合

map<pair<char,char>,string> table; // 一个预测分析表

void init(); // 初始化从文件里面读入相应的文法

void deal(string line); // 对每个输入的文法进行处理

void removeLeftCursion(string line); // 对文法消除左递归操作

void getFirstAndFollow(); // 得到First集合得到Follow集合

void getPredictTable(); // 获得预测分析表


void dfsFirst(char c); // 进行递归操作求解first集合

void getFollow1(char c); // 进行递归操作求解follow集合第一步

void getFollow2(char); // 求follow集合第二步

#endif