#include "header.h"

void init();  // init 初始化一些读入的参数
void eliminateLeftRecursion();  // 消除左递归
void deal(string s);  // 对从文件读入的字符串进行处理

void init(){
    string filename = INPUT;
    ifstream fin(filename.c_str());
    string line;
    while(getline(fin,line)){
        // 对每个文法进行读入处理
        deal(line);
    }

    eliminateLeftRecursion();

    // puts("debug");
    // for(auto x:v){
    //     for(auto y:grammar[x]){
    //         cout<<y<<endl;
    //     }
    // }
}


void deal(string s){
    if(s.size()==0) return;
    char key=s[0];
    v.push_back(key);
    has[key]=true;
    string c="";
    int len=s.size();
    for(int i=3;i<len;i++){
        if(s[i]=='|'){
            grammar[key].insert(c);
            c="";
        }else{
            c+=s[i];
        }
    }
    grammar[key].insert(c);
}



void eliminateLeftRecursion(){ 
    int num=v.size();
    for(int i=0;i<num;i++){
        for(int j=0;j<i;j++){
            // 遍历v[i]的每个文法
            for(auto x:grammar[v[i]]){
                if(has[x[0]]){
                    // 说明这个非终结符有产生式,
                    // 我们将这些产生式进行替换

                    // 先计算后面的部分
                    string remain="";
                    for(int k=1;k<x.size();k++){
                        remain+=x[k];
                    }

                    for(auto y:grammar[x[0]]){
                        grammar[v[i]].insert(y+remain);
                    }
                }
            }
        }
    }
}