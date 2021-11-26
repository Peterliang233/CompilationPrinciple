#include "header.h"
#include "judge.cpp"


// init 执行初始化操作
void init() {
    // 读入关键字
    string filename = KEYWORDFILENAME;
    ifstream fin(filename.c_str());
    string line;
    while(getline(fin, line)){
        keyword[line]=true;
    }
    fin.close();


    // 读入运算符和界符
    filename = OPERATORFILENAME;
    ifstream op(filename.c_str());
    symbol[' ']=true;
    while(getline(op, line)){
        symbol[line[0]]=true;
    }
    op.close();
}



void check(string line){
    string now="";
    //cout<<line<<endl;
    line+=" ";
    for(auto x:line){
        // 如果是界符
        if(symbol[x]){
            if(now.size()==0){
                if(x!=' '){
                    cout<<"("<<x<<",-)"<<endl;
                }
                continue;
            }
            //cout<<"now:"<<now<<endl;
            // 检查目前这个now字符串是那种类型
            // 是否为关键字
            if(keyword[now]){
                cout<<"("<<now<<",-)"<<endl;
            }else{
                // 检查是否是标识符
                if(now[0]<='9'&&now[0]>='0'){
                    if(now[0]=='0'){
                        if(now.size()==1){
                            cout<<"(1,0)"<<endl;
                        }else{
                            if(now[1]<='7'&&now[1>='1']){
                                if(judgeOctal(now)){
                                    cout<<"(2,"<<now<<")"<<endl;
                                }else{
                                    cout<<"程序存在词法错误"<<endl;
                                    exit(0);
                                }
                            }else if(now[1]=='x'){
                                if(judgeHexadecimal(now)){
                                    cout<<"(3,"<<now<<")"<<endl;
                                }else{
                                    cout<<"程序存在词法错误"<<endl;
                                    exit(0);
                                }
                            }else{
                                cout<<"程序存在词法错误"<<endl;
                                exit(0);
                            }
                        }
                    }else{
                        if(judgeDecimal(now)){
                            cout<<"(1,"<<now<<")"<<endl;
                        }else{
                            cout<<"程序存在词法错误"<<endl;
                            exit(0);
                        }
                    }
                }else{
                    if(judgeIdentifier(now)){
                        cout<<"(0,"<<now<<")"<<endl;
                    }else{
                        cout<<"程序存在词法错误"<<endl;
                        exit(0);
                    }
                }
            }
            if(x!=' '){
                cout<<"("<<x<<",-)"<<endl;
            }
            now="";
        }else{
            now+=x;
        }
    }
}

