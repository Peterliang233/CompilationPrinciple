#include "header.h"


void init(){
    string filename = OUTPUT;
    ifstream fin(filename.c_str());
    string line;
    while(getline(fin,line)){
        // 对每个文法进行读入处理
        deal(line);
    }

    fin.close();

    removeLeftRecursion();

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



void removeLeftRecursion(){ 
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
            cout<<v[num-1]<<"->"<<x<<"U"<<endl;
        }else{
            string remain="";
            for(int i=1;i<x.size();i++){
                remain+=x[i];
            }
            cout<<"U->"<<remain+"U"<<endl;
        }
    }

    // 一个结尾字符文法
    cout<<"U->@"<<endl;

    // 将其他非终结符对应的文法重新输入到result.txt文件里面
    for(int i=0;i<num-1;i++){
        for(auto x:grammar[v[i]]){
            cout<<v[i]<<"->"<<x<<endl;
        }
    }

    // 将消除左递归的新的文法重新存入一个文件里面
    string filename = RESULT;
    ifstream fin1(filename.c_str());
    string line;
    // 清空之前的数据
    mp.clear();
    for(int i=1;i<=cnt;i++){
        v1[i].clear();
    }
    cnt=0;
    while(getline(fin1,line)){
        dealString(line);
    }
    // 输出到一个answer.txt文件
    freopen(ANSWER, "w", stdout);
    for(int i=1;i<=cnt;i++){
        cout<<v1[i][0]<<"->";
        for(int j=1;j<v1[i].size();j++){
            cout<<v1[i][j];
            if(j<v1[i].size()-1){
                cout<<"|";
            }
        }
        cout<<endl;
    }
}

void removeLeftGene() {
    

}
