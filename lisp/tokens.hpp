#pragma once
#include <iostream>
#include <fstream>

using namespace std;

#include "IDEerror.hpp"
#include "token.hpp"

// Iterator class
// begin();
// end();
// ++ operator
class Tokens:public Tokenizer{
  /**Class for an object of tokens. Has properties of a tokenizer.
   * This object takes a line,
   * 
   */
  string line;
  ofstream fout;
  ifstream fin;
  void advance() {
    //cout << "Advance current line <" << line <<">"<< endl;
    // if (done()) cout << "Done" << endl;
    while ((line.length()==0 || Tokenizer::peekNext(line).getType()==EOL) && !done() ) {
      linenumber++;
      getline(fin,line);
    }
  }
  public:
  string getLine() { return line; }
  bool done() {return fin.eof(); }
  Tokens(string iFilename,string oFilename) {
    linenumber=0;
    success=true;
    line="";
    filename=iFilename;
    fin.open(iFilename);
    fout.open(oFilename);
    advance();
  }
  Token getNext(){ 
    advance();
    Token t=Tokenizer::getNext(line);
    if (t.getType()==EOL && done()) return Token(DONE);   
    return t;
  }
  Token peekNext() {
    string tempLine=line;
    int tempLinenumber=linenumber;
    int filePos=fin.tellg();
    advance();
    Token tempToken=Tokenizer::peekNext(line);
    if (tempToken.getType()==EOL && done()) return Token(DONE);
    line=tempLine;
    linenumber=tempLinenumber;
    fin.seekg(filePos,ios_base::beg);
    return tempToken;
  }
  ~Tokens() {
     fin.close();
     fout.close();
  }
};
