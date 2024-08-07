#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <iomanip>

using namespace std;

#include "IDEerror.hpp"
#include "token.hpp"
#include "tokens.hpp"
#include "AST.hpp"
/*
BNF notation for Lisp

s_expression = atomic_symbol \
               / "(" s_expression "."s_expression ")" \
               / list 
   
list = "(" s_expression < s_expression > ")"

atomic_symbol = letter atom_part

atom_part = empty / letter atom_part / number atom_part

letter = "a" / "b" / " ..." / "z"

number = "1" / "2" / " ..." / "9"

empty = " "

*/



bool expression(Tokens &tokens,ASTNode *tree);

bool atom(Tokens &tokens,ASTNode *tree) {
  /*
    checks to see if tokens object has encountered an atom.
  */
    cout << "Atom " << tokens.getLine() << endl;
    Token t = tokens.peekNext();
    if (t.getType() == INTEGER || t.getType()==REAL){
        *tree = ASTNode(tokens.getNext());
        return true;
    }else if (t.getType() == SYMBOL){
        *tree = ASTNode(tokens.getNext());
        return true;
    }else if (t.getType() == ADDING || t.getType() == MINUS || t.getType() == MULTIPLYING){
        *tree = ASTNode(tokens.getNext());
        return true;
    }
  return false;
}

bool list(Tokens &tokens,ASTNode *tree) {
/*
  checks to see if the tokens object has encountered a list. A list is valid if it has ( expression )
*/
    cout << "List " << tokens.getLine() << endl;
    Token t=tokens.peekNext();

    if (t.getType()==OPENPAREN){
      tokens.getNext();
      t=tokens.peekNext();
      bool running = true;
      bool first = true;
      while (running){
        ASTNode *subtree = new ASTNode;  
        bool express=expression(tokens,subtree);      
        if(!express) return false;
        if(express && first){ 
          *tree=*subtree;
        }else if(express && !first){
          tree->add(subtree);
        }
        first=false;        
        t=tokens.peekNext();
        if (t.getType()==CLOSEPAREN){
          tokens.getNext();
          return true;
        }
      }
    }else return false;
  }
    /*
    bool done = false;
    bool retval = false;
    bool first = true;
    ASTNode *lsubtree = new ASTNode();
    ASTNode *rsubtree = new ASTNode();
    Token temp;
    Token t = tokens.peekNext();
    
    if (t.getType() == OPENPAREN){

      
      int count = 0;
      do{
        count++;
        tokens.getNext();
        t = tokens.peekNext();
        if (t.getType() == CLOSEPAREN){
          return true;
        }
        if(first){  
        temp = t;      
        }else if(count == 2){  
          retval = expression(tokens, lsubtree);
        }else if(count ==3){
          retval = expression(tokens,rsubtree);
        }
        if (retval && first){
          *tree = ASTNode(t,lsubtree);
        }else if (retval && !first){
          *tree= ASTNode(t,rsubtree);
        } 
        *tree = ASTNode(temp,lsubtree,rsubtree);  
        first=false;
        
      } while (!done);
      
    }else{
      cout << t.str() << endl;
     return false;
     
    }*/
  

bool expression(Tokens &tokens,ASTNode *tree) {
  /*
    Function to determine if the tokens object has encountered an expression. 
    In lisp an expression is valid if it is an atom or a list.
  */
  cout << "Expression " << tokens.getLine() << endl;
  if (atom(tokens, tree)) return true;
  else if(list(tokens,tree)) return true;
  return false;
}

bool program(Tokens &tokens, ASTNode *tree){
  /*
    Function to check if the source is a valid lisp program. If it is an expression it passes.
 
  bool ex = true;
  do{   
    ex = expression(tokens, tree);
  }while(ex);
  return true; */
  return expression(tokens,tree);
}
