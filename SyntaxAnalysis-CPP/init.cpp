#include "header.h"

void init();  // init 初始化一些读入的参数
void eliminateLeftRecursion();  // 消除左递归
void deal(string s);  // 对从文件读入的字符串进行处理
void ExecuteLeftCommonFactor(); // 提取左公因子函数

void init(){
    string filename = OUTPUT;
    ifstream fin(filename.c_str());
    string line;
    while(getline(fin,line)){
        // 对每个文法进行读入处理
        deal(line);
    }

    fin.close();

    eliminateLeftRecursion();

    // for(auto x:v){
    //     cout<<x<<":"<<endl;
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
            if(c[0]<='Z'&&c[0]>='A'){
                vis[make_pair(key,c[0])]=true;
            }
            c="";
        }else{
            c+=s[i];
        }
    }
    if(c[0]<='Z'&&c[0]>='A'){
        vis[make_pair(key,c[0])]=true;
    }
    grammar[key].insert(c);
}



void eliminateLeftRecursion(){ 
    int num=v.size();
    string remain;
    // 遍历每一个非终结符
    for(int i=0;i<num;i++){
        // 遍历每个非终结符对应的文法
        for(int j=0;j<i;j++){
            // 遍历v[i]的每个文法
            for(auto x:grammar[v[i]]){
                if(x[0]==v[j]){
                    // 先获取后半部分的字符串
                    remain="";
                    for(int k=1;k<x.size();k++){
                        remain+=x[k];
                    }
                    for(auto y:grammar[x[0]]){
                        grammar[v[i]].insert(y+remain);
                    }
                    grammar[v[i]].erase(x);
                }
            }
        }
        // for(auto x:grammar[v[i]]){
        //     cout<<v[i]<<" "<<x<<endl;
        // }
    }
    
    // 遍历最后一个非终结符号
    for(auto x:grammar[v[num-1]]){
        if(x[0]!=v[num-1]){
            cout<<v[num-1]<<"->"<<x<<"T"<<endl;
        }else{
            string remain="";
            for(int i=1;i<x.size();i++){
                remain+=x[i];
            }
            cout<<"T->"<<remain+"T"<<endl;
        }
    }

}

void ExecuteLeftCommonFactor() {
        

}
