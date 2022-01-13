#ifndef R
#define R
#include<iostream>
#include<fstream>
#define INPUT "input.txt"

using namespace std;

void E();  // E->TX
void X();  // X->+TX|e
void T();  // T->FY
void Y();  // Y->*FY|e
void F();  // F->(E)|i

string s; // 记录我们的每个需要判断的字符串
int id;  // 记录遍历到的字符串的下标
bool flag;  // 判断是否是合法的表达式
#endif