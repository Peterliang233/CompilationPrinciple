#include "header.h"
#include "deal.cpp"
using namespace std;


void deal(string line){
    // 对输入的字符串进行处理，将数字用i进行替换
    s="";
    string tmp="";
    for(auto x:line){
        if(x!='+'&&x!='*'&&x!='('&&x!=')'){
            tmp+=x;
        }else{
            if(tmp.size()==0){
                s+=x;
            }else{
                s+="i";
                s+=x;
            }
            tmp="";
        }
    }
    if(tmp.size()){
        s+="i";
    }
}

void init(){
    string filename = INPUT;
    ifstream fin(filename.c_str());
    string line;
    while(getline(fin,line)){
        // 对每个字符串进行判断处理
        deal(line);
        flag=true;
        id=0;
        E();
        cout<<s<<endl;
        s+="#";
        s+="\n";
        if(flag){
            puts("True");
        }else{
            puts("False");
        }
    }
}

int main(){
    init();
    return 0;
}