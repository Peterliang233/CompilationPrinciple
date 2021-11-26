#include <cstdio>
#include<cstdlib>
#include "header.h"
#include "deal.cpp"

void Scan() {
    string filename = FILENAME;
    ifstream  fin(filename.c_str());
    string line;
    while(getline(fin, line)) {
        if(!judgeAnnotation(line)){
            check(line);
        }
    }
    fin.close();
}



int main() {
    freopen(RESULTFILENAME, "w", stdout);
    init();
    Scan();
    fclose(stdout);
    return 0;
}

