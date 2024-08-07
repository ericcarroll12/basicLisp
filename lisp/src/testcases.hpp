#pragma once

#include <iostream>
#include <fstream>

using namespace std;

#include "parser.hpp"
#include "AST.hpp"

class TestCase {
  public:
  virtual bool run()=0; // Test cases when true succeeded
};

class TestCaseFile:public TestCase {
  string filein,fileout;
  bool shouldFail;
  public:
  TestCaseFile(string newFilein,string newFileout,bool newShouldFail=false) {
    filein=newFilein;
    fileout=newFileout;
    shouldFail=newShouldFail;
  }
  bool run() {
    filename=filein;
    cout << "Testing input:tests\\"<<filein<<" to tests\\"<< fileout << endl;
    Tokens tokens("tests\\"+filein,"tests\\"+fileout);
    ASTNode *root=new ASTNode();
    bool result=expression(tokens,root);
    if (result) cout << "Success Your Code parses"<<endl;
    else cout << "Error" << endl;
    if (shouldFail && !result) result=true;
    return result;
  } 
};

vector<TestCase *> testcases;
void runTests() {
  cerr << "Running tests" << endl;
  for (auto t:testcases) {
    if (t->run()) cerr << "Success" <<endl;
    else cerr << "Failed" <<endl;
  }
}
void addTestcases() {
  testcases.push_back((TestCase *)new TestCaseFile("sortOneLineNoCommentsNoSpace.pas","sortOneLineNoCommentsNoSpace.txt"));
  testcases.push_back((TestCase *)new TestCaseFile("sortOneLineFail.pas","sortOneLineFail.txt",true));
  testcases.push_back((TestCase *)new TestCaseFile("sortOneLineNoComments.pas","sortOneLineNoComments.txt"));
  testcases.push_back((TestCase *)new TestCaseFile("sortOneLine.pas","sortOneLine.txt"));
  testcases.push_back((TestCase *)new TestCaseFile("sort.pas","sort.txt"));
}

