#include "header.h"

// JudgeAnnotation 判断是否是注释
bool judgeAnnotation(string line){
    string str;
    for(auto x:line){
        if(x==' '){
            continue;
        }else{
            str+=x;
        }
    }
    if(str[0]=='/'&&str[1]=='/'){
        return true;
    }

    return false;
}

// judgeIdentifier 检查是否为合法的标识符
bool judgeIdentifier(string str){
    if(str[0]=='_'
    ||str[0]<='z'&&
    str[0]>='a'||
    str[0]<='Z'&&str[0]>='A'){
        if(str.size()<=247){
            int len=str.size();
            for(int i=1;i<len;i++){
                if(str[i]=='_'||
                str[i]<='z'&&str[i]>='a'||
                str[i]<='Z'&&str[i]>='A'||
                str[i]<='9'&&str[i]>='0'){
                    continue;
                }else{
                // 如果里面的字母不是下划线，英文字母或者数字
                    return false;
                }
            }
            return true;
        // 如果长度超过了247
        }else{
            return false;
        }
    // 如果首字母不是下划线或者不是英文字母
    }else{
        return false;
    }
}

// judgeNumber 判断是否是合法的十进制
bool judgeDecimal(string s){
    for(auto x:s){
        if(x<='9'&&x>='0'){
            continue;
        }else{
            return false;
        }
    }
    return true;
}

// judgeOctal 判断是否是合法的八进制
bool judgeOctal(string s){
    int len=s.size();
    for(int i=2;i<len;i++){
        if(s[i]<='7'&&s[i]>='0'){
            continue;
        }else{
            return false;
        }
    }

    return true;
}

// judgeHexadecimal 判读是否是合法的十六进制
bool judgeHexadecimal(string s){
    if(s[0]=='0'&&s[1]=='x'){
        int len=s.size();
        for(int i=2;i<len;i++){
            if(s[i]<='9'&&s[i]>='0'||s[i]<='f'&&s[i]>='a'){
                continue;
            }else{
                return false;
            }
        }

        return true;
    }else{
        return false;
    }
}