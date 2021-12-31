#include "header.h"

void scan();  // 读入表达式

void deal(string line); // 求这个表达式的逆波兰式

void scan(){
    string filename = OPERATION;
    ifstream fin1(filename.c_str());
    string line;
    while(getline(fin1,line)){
        // 将合法的操作符读到一个map里面进行哈希存储
        vis[line[0]]=true;
    }
    fin1.close();
    filename = INPUT;
    ifstream fin(filename.c_str());
    while(getline(fin,line)){
        deal(line);
        cout<<st.top()<<endl;
    }
}

void deal(string line){
    //cout<<line<<endl;
    int len=line.size();
    int index=0;
    string ans="";
    while(index<len){
        if(line[index]=='('){
            string tmp="";
            ++index;
            while(line[index]!=')'){
                tmp+=line[index];
                ++index;
            }
            ++index;
            deal(tmp);
        }
        if(index>=len){
            break;
        }
        if(vis[line[index]]){
            // 如果这个是一个操作符号，那么我们就放进op里面
            op.push(line[index]);
            index++;
        }else{
            string c="";
            while(index<len&&line[index]<='9'&&line[index]>='0'){
                c+=line[index];
                index++;
            }
            // 获得一个数字字符串，将这个字符串放进st里面
            st.push(c);
            //cout<<"c: "<<c<<endl;
            if(!op.empty()&&(op.top()=='*'||op.top()=='/')){
                string first=st.top();st.pop();
                string second=st.top();st.pop();
                char operation=op.top();op.pop();
                //cout<<"debug: "<<second+first+operation<<endl;
                st.push(second+"," + first+","+ operation);
            }
        }
    }
    if(!op.empty()&&index==len){
        string first=st.top();st.pop();
        string second=st.top();st.pop();
        char operation=op.top();op.pop();
        //cout<<"test: "<<second+first+operation<<endl;
        st.push(second+"," + first+","+ operation);
    }
    return;
}