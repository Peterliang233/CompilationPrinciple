#include "header.h"


void init(); // 初始化读入字符串

void InsertFirst(char key, char val); // 执行First插入操作
void InsertLast(char key,char val);  // 执行Last插入操作

void getFirst(); // 获得First集合
void getLast(); // 获得Last集合

void getPriorityTable(); // 获取优先分析表


bool judge(string line); // 对程序进行判断，是否是指定的文法对应的表达式


void init(){
    string filename = INPUT;
    ifstream fin(filename.c_str());
    string line;
    while(getline(fin,line)){
        string c="";
        // 对输入的文法进行处理，将或的情况分为单一的文法
        int len=line.size();
        string pre=line.substr(0,3);
        for(int i=3;i<len;i++){
            if(line[i]=='|'){
                v.push_back(pre+c);
                c="";
            }else{
                c+=line[i];
            }
        }
        v.push_back(pre+c);
    }
    fin.close();
    // 对每个文法进行处理,得到一个pre数组和一个suf数组
    for(auto x:v){
        suf[x[3]].push_back(x[0]);
        suf1[x[x.size()-1]].push_back(x[0]);
    }


    filename = END;
    // 得到终结符集合
    ifstream fin1(filename.c_str());
    while(getline(fin1,line)){
        op[line[0]]=true;
        ed.push_back(line[0]);
    }

    fin1.close();

    // 得到非终结符集合
    filename = UEND;
    ifstream fin2(filename.c_str());
    while(getline(fin2,line)){
        ued.push_back(line[0]);
    }
    fin2.close();



    getFirst();
    getLast();
    getPriorityTable();

    // 得到归约哈希, 全部都替换成X的形式
    for(auto x:v){
        int len=x.size();
        string tmp="";
        for(int i=3;i<len;i++){
            if(op[x[i]]){
                tmp+=x[i];
            }else{
                tmp+="X";
            }
        }
        g[tmp]='X';
    }

    filename = EXPRESSION;
    ifstream fin3(filename.c_str());
    while(getline(fin3,line)){
        // 对每个字符串进行处理，判断是否是合法的字符串
       // judge(line);
        cout<<line<<": "<<(judge(line)?"true":"false")<<endl;
    }
    fin3.close();
}



void InsertFirst(char key,char val){
    if(first[make_pair(key,val)]==false){
        first[make_pair(key,val)]=true;
        st.push(make_pair(key,val));
    }
}


void getFirst(){
    // 求First集合

    // 进行初始化操作
    for(auto x:ued){
        for(auto y:ed){
            first[make_pair(x,y)]=false;
        }
    }

    for(auto s:v){
        // 对于P->a或者是P->Qa的，我们直接推进栈里面
        if(op[s[3]]){
            InsertFirst(s[0],s[3]);
        }
        // P->Qa的情况
        if(op[s[3]]==false&&op[s[4]]){
            InsertFirst(s[0],s[4]);
        }
    }

    // 对栈的数据进行拓展即可
    while(!st.empty()){
        auto top=st.top();
       // cout<<top.first<<" "<<top.second<<endl;
        st.pop();
        for(auto x:suf[top.first]){
            InsertFirst(x,top.second);
        }
    }


    // 对结果进行检查
    for(auto x:ued){
        for(auto y:ed){
            //cout<<x<<" "<<y<<" "<<first[make_pair(x,y)]<<endl;
            if(first[make_pair(x,y)]){
                firstV[x].push_back(y);
            }
        }
    }
}


void InsertLast(char key,char val){
    if(last[make_pair(key,val)]==false){
        last[make_pair(key,val)]=true;
        st.push(make_pair(key,val));
    }
}

void getLast(){
    // 求Last集合

    // 进行初始化操作
    for(auto x:ued){
        for(auto y:ed){
            last[make_pair(x,y)]=false;
        }
    }

    for(auto s:v){
        int n=s.size();
        // 对于P->...a，我们直接推进栈里面
        if(op[s[n-1]]){
            InsertLast(s[0],s[n-1]);
        }
        // P->...aQ的情况
        if(op[s[n-1]]==false&&op[s[n-2]]){
            InsertLast(s[0],s[n-2]);
        }
    }

    // 对栈的数据进行拓展即可
    while(!st.empty()){
        auto top=st.top();
        st.pop();
        for(auto x:suf1[top.first]){
           // cout<<"x:"<<x<<endl;
            InsertLast(x,top.second);
        }
    }


    //对结果进行检查
    for(auto x:ued){
        for(auto y:ed){
           // cout<<x<<" "<<y<<" "<<last[make_pair(x,y)]<<endl;
            if(last[make_pair(x,y)]){
                lastV[x].push_back(y);
            }
        }
    }
}

void getPriorityTable(){
    for(auto x:ed){
        for(auto y:ed){
            table[make_pair(x,y)]=table[make_pair(y,x)]=-2;
        }
    }
    for(auto x:v){
        int n=x.size();
        for(int i=3;i<n;i++){
            if(i+1<n&&op[x[i]]&&op[x[i+1]]){
                table[make_pair(x[i],x[i+1])]=0;
            }
            if(i+2<n&&op[x[i]]&&op[x[i+2]]&&op[x[i+1]]==false){
                table[make_pair(x[i],x[i+2])]=0;
            }
            if(i+1<n&&op[x[i]]&&op[x[i+1]]==false){
                for(auto y:firstV[x[i+1]]){
                    table[make_pair(x[i],y)]=-1;
                }
            }
            if(i+1<n&&op[x[i]]==false&&op[x[i+1]]){
                for(auto y:lastV[x[i]]){
                    table[make_pair(y,x[i+1])]=1;
                }
            }
        }
    }

    for(auto y:firstV[k]){
        table[make_pair('#', y)]=-1;
    }
    for(auto y:lastV[k]){
        table[make_pair(y,'#')]=1;
    }

    table[make_pair('#','#')]=0;

    // for(auto x:ed){
    //     for(auto y:ed){
    //         cout<<x<<" "<<y<<" "<<table[make_pair(x,y)]<<endl;
    //     }
    // }
}


bool judge(string s){
    // 先对每个字符串进行处理，转化为统一的符号表示的形式
    string str="";
    string tmpString="";
    for(auto c:s){
        // 如果遇到的这个字符是一个终结符,那么我们就先判断之前的tmp字符串是否为空，如果为空，那么就不处理，否则就用一个i替代
        if(op[c]){
            if(tmpString.size()==0){
                str+=c;
            }else{
                str+="i";
                str+=c;
            }
            tmpString="";
        }else{
            tmpString+=c;
        }
    }
    if(op[s[s.size()-1]]==false){
        // 如果最后一个字符不是终结符，那么就用一个i替换tmp
        str+="i";
    }

    str+="#";
    //cout<<str<<endl;
    // 处理好了每个表达式之后，我们需要对字符串进行处理，判断是否是合法的表达式
    sk[0]='#';
    int k=0; // k表示的是栈顶的位置
    int id=0;  // id表示的是当前的游标的位置
    int n=str.size();
    while(id<n){
        //cout<<"id: "<<str[id]<<endl;
        char a=str[id];
        int j;
        // 如果栈顶指向的是终结符
        if(op[sk[k]]){
            j=k;
        }else{
            j=k-1;
        }
        // 如果sk[j]>a
        while(table[make_pair(sk[j],a)]==1){
            char Q;
            while(1){
                Q=sk[j];
                if(op[sk[j-1]]){
                    j-=1;
                }else{
                    j-=2;
                }
                if(table[make_pair(sk[j],Q)]==-1){
                    break;
                }
            }
            //cout<<j<<" "<<k<<endl;
            // 进行归约操作sk[j+1]...sk[k],规约成一个X
            string tmpc="";
            for(int t=j+1;t<=k;t++){
                tmpc+=sk[t];
            }
            //cout<<"tmpc: "<<tmpc<<endl;
            k=j+1;
            if(g.count(tmpc)==0){
                return false;
            }
            sk[k]=g[tmpc];
            // cout<<"ans: ";
            // for(int t=0;t<=k;t++){
            //     cout<<sk[t];
            // }
            // cout<<endl;
        }
        if(table[make_pair(sk[j],a)]==-1||table[make_pair(sk[j],a)]==0){
            k=k+1;
            sk[k]=str[id];
            id++;
        }else{
            return false;
        }
    }

    return true;
}