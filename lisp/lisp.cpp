#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

#include "token.hpp"
#include "tokens.hpp"
#include "IDEerror.hpp"
#include "parser.hpp"


string uniqueLabel() {
  static int labelCount=0;
  string s=to_string(labelCount);
  string retval="Comp"+s;
  labelCount++;
  return retval;
}

void compile(ASTNode *root,string &assembly) {
  /*Recursive compilation function. Takes an abstract syntax tree, uses right hand recursion to compile function to assembly
   */
  switch(root->getToken().getType()) {
    case RELATIONAL:
      if (root->left()==NULL || root->right()==NULL) {
        cerr << "Relational with out two operands" << endl;
        return;
      } else {
        stringstream piece;
        string a,b;
        compile(root->left(),a);
        compile(root->right(),b);
        piece << b ;
        piece << a ;
        piece << "    pop %rax\n";
        piece << "    pop %rbx\n";
        piece << "    cmp %rbx,%rax\n";
        piece << "    mov  $1,%rax\n";
        string label=uniqueLabel();
        if(root->getToken().getValue()=="<") {
            piece << "    jl "<< label << "\n";
        } else if(root->getToken().getValue()==">"){
            piece << "    jg "<< label << "\n";
        }else if(root->getToken().getValue()=="<=") {
            piece << "    jle "<< label << "\n";
        }else if(root->getToken().getValue()==">=") {
            piece << "    jge "<< label << "\n";
        }else if(root->getToken().getValue()=="<>") {
            piece << "    jne "<< label << "\n";
        }else if(root->getToken().getValue()=="="){
            piece << "    jeq "<< label << "\n";
        }else if(root->getToken().getValue()=="in"){
            
        }
        piece << "    mov $0,%rax " << "\n";
        piece << label <<":\n";
        piece << "    push %rax " << "\n";
        assembly=piece.str();
      }
      break;
    case INTEGER:
        {
        stringstream piece;
        piece << "    mov $"<<root->getToken().getValue()<<",%rax"<<endl;
        piece << "    push %rax"<<endl;
        assembly=piece.str();
        }
      break;
    case MULTIPLYING:
      if (root->left()==NULL || root->right()==NULL) {
        cerr << "Multiply with out two operands" << endl;
        return;
      } else {
        string a,b;
        compile(root->left(),a);
        compile(root->right(),b);
        if(root->getToken().getValue()=="*"){
          stringstream piece;
          piece <<b;
          piece <<a;
          piece << "    pop %rax"<<endl;
          piece << "    pop %rbx"<<endl;
          piece << "    mul %rbx"<<endl;
          piece << "    push %rax"<<endl;
          assembly=piece.str();
        }else if(root->getToken().getValue()=="/" ||
          root->getToken().getValue()=="mod" ||
          root->getToken().getValue()=="div"){
          stringstream piece;
          piece <<b;
          piece <<a;
          piece << "    pop %rax"<<endl;
          piece << "    pop %rbx"<<endl;
          piece << "    xor %rdx,%rdx" << endl;
          if (root->getToken().getValue()=="/") {
              piece << "    div %rbx"<<endl;
          }
          if (root->getToken().getValue()=="mod") {
              piece << "    idiv %rbx"<<endl;
              piece << "    mov %rdx,%rax" << endl;
          }
          if (root->getToken().getValue()=="div") {
              piece << "    idiv %rbx"<<endl;
          }
          piece << "    push %rax"<<endl;
          assembly=piece.str();
        }else  if(root->getToken().getValue()=="and"){
          stringstream piece;
          piece <<b;
          piece <<a;
          piece << "    pop %rax"<<endl;
          piece << "    pop %rbx"<<endl;
          piece << "    and %rbx,%rax"<<endl;
          piece << "    push %rax"<<endl;
          assembly=piece.str();
        }
      } 
      break;
    case ADDING:
      if (root->left()==NULL || root->right()==NULL) {
        cerr << "Adding with out two operands" << endl;
        return;
      } else {
        string a,b;
        compile(root->left(),a);
        compile(root->right(),b);
        if(root->getToken().getValue()=="+"){
          stringstream piece;
          piece <<b;
          piece <<a;
          piece << "    pop %rax"<<endl;
          piece << "    pop %rbx"<<endl;
          piece << "    add %rbx,%rax"<<endl;
          piece << "    push %rax"<<endl;
          assembly=piece.str();
        }else if(root->getToken().getValue()=="or") {
          stringstream piece;
          piece <<b;
          piece <<a;
          piece << "    pop %rax"<<endl;
          piece << "    pop %rbx"<<endl;
          piece << "    or %rbx,%rax"<<endl;
          piece << "    push %rax"<<endl;
          assembly=piece.str();
        }
      }
      break;
    case MINUS:
        if (root->left()==NULL && root->right()==NULL) {
          cerr << "Adding with out two operands" << endl;
          return;
        } else {
          string a,b;
          compile(root->left(),a);
          if (root->right()!=NULL) compile(root->right(),b);
          if (root->right()!=NULL) {
            stringstream piece;
            piece <<b;
            piece <<a;
            piece << "    pop %rax"<<endl;
            piece << "    pop %rbx"<<endl;
            piece << "    sub %rbx,%rax"<<endl;
            piece << "    push %rax"<<endl;
            assembly=piece.str();            
          }
          else{
            stringstream piece;
            piece << a;
            piece << "    pop %rax"<<endl;
            piece << "    neg %rax"<<endl;
            piece << "    push %rax"<<endl;
            assembly=piece.str(); 
          }
        }
      break;
    default:
      break;
  }
}

void compileHelper(ASTNode *root,string &assembly) {
  /*
    Compilation wrapper function to add preamble and posamble code to a compilation. This is the usual entrypoint to compile
  */
  string preAmble=
    "    .data\n"
    "    .align 4\n"
    "  	.section	.rodata\n"
    "  format: .string	\"%li\\n\"\n"
    "  	.text\n"
    "  	.globl	main\n"
    "  main:\n"
    "  	endbr64\n"
    "  	push	%rbp\n";
  string codeAssembly;
  compile(root,codeAssembly);
    string postAmble=
    "    pop  %rax\n"
    "    mov	%rax, %rsi\n"
	  "    lea	format(%rip), %rax\n"
	  "    mov	%rax, %rdi\n"
	  "    mov	$0, %rax\n"
	  "    call	printf@PLT\n"
    "    mov	$0, %rax\n"
    "    pop	%rbp\n"
    "    ret\n"
    "    .section	.note.GNU-stack,\"\",@progbits\n";
  assembly=preAmble+codeAssembly+postAmble;
}

void interpret(ASTNode *root,double &result) {
/* 
  Recursive interpreter function to handle live interpretation instead of compilation. Right hand recursive just like compile.
  Takes in an abstract syntax tree, tokenizes, parses, and computes the answer.
*/

  switch(root->getToken().getType()) {
    case RELATIONAL:
      if (root->left()==NULL || root->right()==NULL) {
        cerr << "Relational with out two operands" << endl;
        return;
      } else {
        double a,b;
        interpret(root->left(),a);
        interpret(root->right(),b);
        if(root->getToken().getValue()=="<") {
            if (a<b) result=1.0;
            else result=0.0;
        } else if(root->getToken().getValue()==">"){
            if (a>b) result=1.0;
            else result=0.0;
        }else if(root->getToken().getValue()=="<=") {
            if (a<=b) result=1.0;
            else result=0.0;
        }else if(root->getToken().getValue()==">=") {
            if (a>=b) result=1.0;
            else result=0.0;
        }else if(root->getToken().getValue()=="<>") {
            if (a!=b) result=1.0;
            else result=0.0;
        }else if(root->getToken().getValue()=="="){
            if (a==b) result=1.0;
            else result=0.0;
        }else if(root->getToken().getValue()=="in"){
              result=0.0; 
        }
      }
      break;
    case INTEGER:
        result=stoi(root->getToken().getValue());
      break;
    case MULTIPLYING:
      if (root->left()==NULL || root->right()==NULL) {
        cerr << "Multiply with out two operands" << endl;
        return;
      } else {
        double a,b;
        interpret(root->left(),a);
        interpret(root->right(),b);
        if(root->getToken().getValue()=="*"){
          result=a*b;
        }else if(root->getToken().getValue()=="/" ||
          root->getToken().getValue()=="mod" ||
          root->getToken().getValue()=="div"){
          if (b==0.0) {
            cerr << "Divide by zero almost occurred" << endl;
            return ;
          }
          if (root->getToken().getValue()=="/") result=a/b;
          if (root->getToken().getValue()=="mod") result=(int)a%(int)b;
          if (root->getToken().getValue()=="div") result=(int)a/(int)b;
        }else  if(root->getToken().getValue()=="and"){
          if (a!=0.0 && b!=0.0) result=1.0;
          else result=0.0;
        }
      } 
      break;
    case ADDING:
      if (root->left()==NULL || root->right()==NULL) {
        cerr << "Adding with out two operands" << endl;
        return;
      } else {
        double a,b;
        interpret(root->left(),a);
        interpret(root->right(),b);
        if(root->getToken().getValue()=="+"){
          result=a+b;
        }else if(root->getToken().getValue()=="or") {
          if (a!=0.0 || b!=0.0) result=1.0;
          else result=0.0;
        }
      }
      break;
    case MINUS:
        if (root->left()==NULL && root->right()==NULL) {
          cerr << "Adding with out two operands" << endl;
          return;
        } else {
          double a,b;
          interpret(root->left(),a);
          if (root->right()!=NULL) interpret(root->right(),b);
          if (root->right()!=NULL) result=a-b;
          else result=-a;
        }
      break;
    default:
      break;
  }
}

int main(int argc,char **argv) {
  /*
    driver code
  */
    if (argc<3) {
    cout << "Usage: pascal.exe <input.pas> <output.pas>"<<endl;
    cout << "<input.pas> is a text file that is the pascal source code." <<endl;
    cout << "<output.s> is the name of the assembly code source"<<endl;
  } else {
    Tokens tokens(argv[1],argv[2]);
    ASTNode *root=new ASTNode();
    cout << "Before Parsing " << endl;
    bool b=program(tokens,root);
    if (b) {
      cout << "Success Your Code parses"<<endl;
      cout << root << endl;
      double x;
      interpret(root,x);
      cout << "The result is " << x << endl;
      string assemblySource;
      compileHelper (root,assemblySource);
      ofstream out;
      out.open(argv[2]);
      out << assemblySource;
      out.close();
    }
    else cout << "Error" << endl;
  }
  //testAST();
}