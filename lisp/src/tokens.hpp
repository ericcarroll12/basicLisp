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
   * This object takes a line, and moves through it using getNext() to consume the next item in the line and return its token.
   * 
   */
  string line;
  ofstream fout;
  ifstream fin;
  void advance() {
    while ((line.length()==0 || Tokenizer::peekNext(line).getType()==EOL) && !done() ) {
      linenumber++;
      getline(fin,line);
    }
  }
  public:
  //constructors
  Tokens(string iFilename,string oFilename) {
    linenumber=0;
    success=true;
    line="";
    filename=iFilename;

    fin.open(iFilename);
    fout.open(oFilename);
    if (!fin.is_open() || !fout.is_open()){
      cout << "could not open file" << endl;
      return;
    } 
    advance();
  }

  bool isOpen() { return fin.is_open(); }
  //functions
  string getLine() { return line; }

  bool done() {return fin.eof(); }

  Token getNext(){ 
    advance();
    Token t=Tokenizer::getNext(line);
    if (t.getType()==EOL && done()) {
      cout << "DONE" << endl;
      return Token(DONE);
      }   
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
