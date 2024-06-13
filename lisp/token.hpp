#pragma once
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

enum TokenType {OPENPAREN,CLOSEPAREN,MULTIPLYING,ADDING,EOL,DONE,
                RELATIONAL,/*IDENTIFIER,*/VARIABLE,INTEGER,REAL,
                MINUS,ERROR};
class Token {
  TokenType token;
  string value;
  public:
  Token(TokenType newToken=ERROR,string newValue="") {
    token=newToken;
    value=newValue;
  }
  string getValue() { return value;}
  TokenType getType() {return token;}
  string str() {
    switch(token) {
      case MULTIPLYING: return "MULTIPLYING";
      case ADDING: return "ADDING";
      case RELATIONAL: return "RELATIONAL";
     // case IDENTIFIER: return "IDENTIFIER";
      case OPENPAREN: return "OPENPAREN";
      case CLOSEPAREN: return "CLOSEPAREN";
      case VARIABLE: return "VARIABLE";
      case INTEGER: return "INTEGER";
      case REAL: return "REAL";
      case ERROR: return "ERROR";
      case MINUS: return "MINUS";
      case EOL: return "EOL";
      case DONE: return "DONE";
      default: return "UNRECOGNIZED";
    }
  }
  friend ostream & operator <<(ostream &out,Token t) {
    return out << t.str() << " " << t.value;
  }
};

class Tokenizer {
  public:
  Token peekNext(string line) {
    return getNext(line);
  }
  Token getNext(string &line) {
    string realReg="^[-+]?\\d+\\.\\d+(E[-+]?\\d+)?"; // UnsignedReal
    regex rexp(realReg);
    string intReg="^[-+]?\\d+";
    regex iexp(intReg);    // Unsigned Integers
    string numReg = "[0-9]+";
    regex numexp(numReg);
    string identReg="^[a-zA-Z]\\w*";
    regex idexp(identReg);
    smatch sm;
    Token t;
    bool changed=true;
    while (changed) {
      changed=false;
      while (line[0]==' ' || line[0]=='\t') {  // remove whitespace
        line=line.substr(1);
        changed=true;
      }
      while (line[0]=='{') {  // remove comments
        line=line.substr(1);
        while (line[0]!='}' && line.length()>0) line=line.substr(1);
        line=line.substr(1);
        changed=true;
      }
      if (line.length()==0) return Token(EOL);
    }
    string f1=line.substr(0,1);
    string f2=line.substr(0,2);
    string f3=line.substr(0,3);
    if (regex_search(line,sm,rexp)) t=Token(REAL,sm[0]);
    else if (regex_search(line,sm,iexp)) t=Token(INTEGER,sm[0]);
    else if (f1=="-") t=Token(MINUS,f1);
    else if (f3=="div" || f3=="and" || f3=="mod") t=Token(MULTIPLYING,f3);
    else if (f2=="or" ) t=Token(ADDING,f2);
    else if (regex_search(line,sm,idexp)) t=Token(VARIABLE,sm[0]);
    else if (f1=="*" || f1=="/") t=Token(MULTIPLYING,f1);
    else if (f1=="+" ) t=Token(ADDING,f1);
    else if (f2=="<=" || f2==">=" || f2=="<>" || f2=="in") t=Token(RELATIONAL,f2);
    else if (f1=="<" || f1==">" || f1=="=") t=Token(RELATIONAL,f1);
    else if (f1=="(") t=Token(OPENPAREN,f1);
    else if (f1==")") t=Token(CLOSEPAREN,f1);
   // else if (f1.length()==0) t=Token(EOL);
    else t=Token(ERROR,f1);
    line=line.substr(t.getValue().length());
    return t;
  }
};

