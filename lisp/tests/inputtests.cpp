#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "../src/token.hpp"


int main(){

    ifstream in("input.l");
    vector <string> tokens;
    string line;
    Tokenizer t;
    bool running = true;
    for (line; getline(in,line);){
        while(line.length()>0){
            cout << t.getNext(line).str() << endl;
        }
    }
    for (int i; i<tokens.size(); i++){
        cout << tokens[i] << endl;
    }

    return 0;
}