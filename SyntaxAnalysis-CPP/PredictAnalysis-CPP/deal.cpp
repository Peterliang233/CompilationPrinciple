#include "header.h"


void dfsFirst(char c){
    bool flag=false; // 如果一旦出现终结符，这个flag就是true
    for(auto x:mp[c]){
       // 如果这个是终结符，那么就加到First集合里面
        if(op[x[0]]){
            first[c].insert(x[0]);
        }else{
            // 如果最开始的是非终结符，那么我们就从头开始遍历
            // 对于P->XXXXY,如果Y的前面都是非终结符，同时都包含#，那么把Y的first集合也加入到P的first集合里面
            for(auto y:x){
                if(op[y]){
                    flag=true;
                }
                if(!flag){
                    dfsFirst(y);
                    for(auto x:first[y]){
                        first[c].insert(x);
                    }
                    // 说明y这个非终结符的first集合里面没有空，那么后面也无需遍历了
                    if(first[y].find('#')==first[y].end()){
                        flag=true;
                    }
                }else{
                    break;
                }
            }
        }
    }
}


// void dfsFollow(char c){
//     for(auto x:mp[c]){
//         if(op[x[0]]){
//             follow[c].insert(x[0]);
//         }else{
//             dfsFollow(x[0]);
//             for(auto y:follow[x[0]]){
//                 follow[c].insert(y);
//             }
//         }
//     }
// }


void getFirstAndFollow(){
    // 遍历mp里面的所有的非终结符
    // 得到First集合
    for(auto x:mp){
        dfsFirst(x.first);
    }
    for(auto x:mp){
        for(auto y:first[x.first]){
            cout<<x.first<<" "<<y<<endl;
        }
    }
    // 得到follow集合
    // for(auto x:mp){
    //     dfsFollow(x.first);
    // }
}


void init(){
    string filename = INPUT;
    ifstream fin(filename.c_str());
    string line;
    while(getline(fin,line)){
        removeLeftCursion(line);
    }

    fin.close();
    filename = OP;
    ifstream fin1(filename.c_str());
    while(getline(fin1,line)){
        op[line[0]]=true;
    }
    getFirstAndFollow();

    // for(auto x:mp){
    //     for(auto y:x.second){
    //         cout<<x.first<<" "<<y<<endl;
    //     }
    // }
    // 接下来就是求First和Follow集合

    // 求预测分析表

}


void removeLeftCursion(string line){
    line+="|";
    int n=line.size();
    char key=line[0];
    string tmp="";
    bool flag=false;
    // 先进行一遍检查是否有多递归，如果存在，那么就消除左递归，否则就不处理
    for(int i=3;i<n;i++){
        if(line[i]=='|'){
            if(key==tmp[0]){
                flag=true;
                break;
            }
            tmp="";
        }else{
            tmp+=line[i];
        }
    }
    tmp="";
    for(int i=3;i<n;i++){
        if(line[i]=='|'){
            // 得到一个文法，先检查这个文法的首字符是否是key，如果是，说明要消除左递归
            if(key==tmp[0]){
                // 存在左递归,那么久消除左递归，同时插入一个空
                string remain=tmp.substr(1,tmp.size()-1);
                if(key=='E'){
                    mp['X'].insert(remain+"X");
                    mp['X'].insert("#");
                }else if(key=='T'){
                    mp['Y'].insert(remain+"Y");
                    mp['Y'].insert("#");
                }else if(key=='F'){
                    mp['Z'].insert(remain+"Z");
                    mp['Z'].insert("#");
                }
            }else{
                if(flag==false){
                    mp[key].insert(tmp);
                }else{
                    // 没有左递归
                    if(key=='E'){
                        mp[key].insert(tmp+"X");
                    }else if(key=='T'){
                        mp[key].insert(tmp+"Y");
                    }else if(key=='F'){
                        mp[key].insert(tmp+"Z");
                    }
                }
            }
            tmp="";
        }else{
            tmp+=line[i];
        }
    }
}