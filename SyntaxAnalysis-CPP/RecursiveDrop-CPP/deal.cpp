#include "header.h"


void E(){
    T();
    X();
}

void X(){
    if(s[id]=='+'){
        // 下一个字符
        id++;
        T();
        X();
    }
}

void T(){
    F();
    Y();
}

void Y(){
    if(s[id]=='*'){
        id++;
        F();
        Y();
    }
}

void F(){
    if(s[id]=='i'){
        id++;
    }
    else if(s[id]=='('){
        id++;
        E();
        if(s[id]==')'){
            id++;
        }else{
            flag=false;
        }
    }else{
        flag=false;
    }
}