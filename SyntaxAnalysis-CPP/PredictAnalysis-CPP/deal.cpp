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


void getFollow1(char c){
    // 先把#加入到follow集合里面
    follow[c].insert('#');
    // 遍历c的每个文法
    bool flag=false; // 表示的是这个字符后续都是一个空的
    for(auto x:mp[c]){
        int n=x.size();
        // 把每个非终结符后面的非终结符的first集合加入到这个非终结符的follow集合里面
        for(int i=0;i<n-1;i++){
            // 如果两个都是非终结符
            if(!op[x[i]]){
                if(!op[x[i+1]]){
                    for(auto y:first[x[i+1]]){
                        follow[x[i]].insert(y);
                    }
                }else{
                    follow[x[i]].insert(x[i+1]);
                }
                
            }
        }
    }
}

void getFollow2(char c){
    for(auto x:mp[c]){
        int n=x.size();
        for(int i=n-1;i>=0;i--){
            // 如果遇到了终结符，那么第三条规则就失效了
            if(op[x[i]]){
                break;
            }
            for(auto y:follow[c]){
                follow[x[i]].insert(y);
            }
        }
    }
}


void getFirstAndFollow(){
    // 遍历mp里面的所有的非终结符
    // 得到First集合
    for(auto x:mp){
        dfsFirst(x.first);
    }
    // for(auto x:mp){
    //     for(auto y:first[x.first]){
    //         cout<<x.first<<" "<<y<<endl;
    //     }
    // }

    // 得到follow集合
    for(auto x:mp){
        getFollow1(x.first);
    }

    for(auto x:mp){
        getFollow2(x.first);
    }

    // for(auto x:mp){
    //     for(auto y:follow[x.first]){
    //         cout<<x.first<<" "<<y<<endl;
    //     }
    // }
}


void getPredictTable(){
    // 遍历所有的非终结符
    for(auto x:mp){
        // 遍历这个非终结符的first集合
        for(auto y:first[x.first]){
            if(y=='#'){
                table[make_pair(x.first,y)]="#";
            }else{
                // 遍历这个x.first的所有的产生式，包含字符y的就是了
                bool flag=false;
                string tmp="";
                for(auto z:mp[x.first]){
                    tmp=z;
                    if(z.find(y)!=string::npos){
                        table[make_pair(x.first,y)]=z;
                        flag=true;
                        break;
                    }
                }
                if(!flag){
                    table[make_pair(x.first,y)]=tmp;
                }
            }
        }
        // 执行第三条规则，如果first集合里面有#，那么所有的follow的元素都需要加上这个
        if(first[x.first].find('#')!=first[x.first].end()){
            for(auto y:follow[x.first]){
                table[make_pair(x.first,y)]="#";
            }
        }
    }


    // for(auto x:table){
    //     cout<<x.first.first<<" "<<x.first.second<<" "<<x.second<<endl;
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
    // 接下来就是求First和Follow集合
    getFirstAndFollow();

    // for(auto x:mp){
    //     for(auto y:x.second){
    //         cout<<x.first<<" "<<y<<endl;
    //     }
    // }
    // 求预测分析表
    getPredictTable();

    filename = EXPRESSION;

    ifstream fin2(filename.c_str());

    while(getline(fin2,line)){
        // 对每个表达式进行预测分析
        analysisString(line);
    }
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

void analysisString(string line){
    while(!st.empty()){
        st.pop();
    }
    // 先对每个表达式进行处理，都用i进行替换
    string c="";
    string tmp="";
    for(auto x:line){
        if(op[x]){
            if(tmp.size()==0){
                c+=x;
            }else{
                c+="i";
                c+=x;
            }
            tmp="";
        }else{
            tmp+=x;
        }
    }

    if(tmp.size()!=0){
        c+="i";
    }

    st.push('#');
    st.push('E');
    int id=0;
    c+="#";
    bool flag=true;
    cout<<c<<endl;
    while(flag){
        char top=st.top();st.pop();
        //cout<<top<<" "<<c[id]<<endl;
        if(op[top]&&top!='#'){
            if(top==c[id]){
                id++;
            }else{
                puts("false");
                return;
            }
            continue;
        }
        //cout<<top<<" "<<c[id]<<" "<<table[make_pair(top,c[id])]<<endl;
        if(top=='#'){
            if(top==c[id]) flag=false;
            else{
                puts("false");
                return;
            }
            continue;
        }
        if(table.count(make_pair(top,c[id]))==0){
            // 如果没有，那么就是错的表达式，抛出即可
            puts("false");
            return;
        }
        string e=table[make_pair(top,c[id])];
        // 如果是空，那么跳过即可
        if(e=="#"){
            continue;
        }
        int n=e.size();
        for(int i=n-1;i>=0;i--){
            st.push(e[i]);
        }
    }
    puts("true");
}