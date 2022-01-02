#include "header.h"


void scan() {
    string filename = INPUT;
    ifstream fin(filename.c_str());
    string line;
    while(getline(fin,line)){
        dealString(line);    
    }
    output();
}


void dealString(string line) {
    string left="";
    string right="";
    bool flag=false;
    for(auto x:line){
        if(x=='-'||x=='>') {
            flag=true;
            continue;
        }
        if(flag){
            right+=x;
        }else{
            left+=x;
        }
    }
    //cout<<left<<" "<<right<<endl;
    if(mp[left]==0){
        mp[left]=++cnt;
        v1[mp[left]].push_back(left);
    }
    v1[mp[left]].push_back(right);
}


void output() {
    freopen(OUTPUT, "w", stdout);
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
    freopen(RESULT, "w",stdout);
}