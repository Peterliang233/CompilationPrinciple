//
// Created by lyp on 2021/11/19.
//

#ifndef EXPIREMENT1_HEADER_H
#define EXPIREMENT1_HEADER_H
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#define SIZE 10000
#define FILENAME "test.md"
#define KEYWORDFILENAME "keyWord.txt"
#define OPERATORFILENAME "operator.txt"
#define RESULTFILENAME "result.txt"
using namespace std;


map<string,bool> keyword;
map<char,bool> symbol;

#endif //EXPIREMENT1_HEADER_H
