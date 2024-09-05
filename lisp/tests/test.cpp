#include <gtest/gtest.h>
#include <vector>
#include "../src/token.hpp"
#include "../src/AST.hpp"
#include "../src/tokens.hpp"
#include "../src/parser.hpp"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
//Tests for Token class
TEST(Token, constructorTest){
    Token t;
    EXPECT_EQ(t.getType(), ERROR);
    EXPECT_EQ(t.getValue(),"");
    EXPECT_EQ(t.str(),"ERROR");
}

//Tests for ASTNode class
TEST(AST, constructorTest){
    ASTNode a;
    EXPECT_EQ(a.getChildrenSize(),0);

}

//tests for Tokenizer class
TEST(Tokenizer, basicTest){
  vector <Token>expected;
  vector <Token>actual;
  string sampleString = "symbol * 2";
  expected.push_back(Token(SYMBOL));
  expected.push_back(MULTIPLYING);
  expected.push_back(INTEGER);
  Tokenizer tokenizer;
  while(sampleString.length()>0){
    actual.push_back(tokenizer.getNext(sampleString));
  }

  for (int i=0; i<expected.size(); i++){
    string tokenExpected=expected[i].str();
    string tokenActual=actual[i].str();
    ASSERT_EQ(tokenExpected,tokenActual);
  }
  
}
TEST(Tokenizer, newLineTest){
vector <Token>expected ={Token(SYMBOL),Token(MULTIPLYING),Token(INTEGER),Token(SYMBOL),Token(EOL)};
  vector <Token>actual;
  string sampleString = "symbol * 2  bob";
  Tokenizer tokenizer;
  bool running=true;
  while(running){
    actual.push_back(tokenizer.getNext(sampleString));
    if (actual.back().getType()==EOL) running=false;
  }
  ASSERT_EQ(actual.size(),expected.size());
  for (int i=0; i<actual.size(); i++){
    string tokenExpected=expected[i].str();
    string tokenActual=actual[i].str();
    ASSERT_EQ(tokenExpected,tokenActual);
  }
}

TEST(Tokenizer, removeWhiteSpace){
  Tokenizer t1;
  Tokenizer t2;
  Tokenizer t3;
  string test1= "(test)";
  string test2=" ( test ) ";
  string test3="  (   test  )   ";
  vector<Token> expected = {Token(OPENPAREN), Token(SYMBOL), Token(CLOSEPAREN), Token(EOL)};
  vector<Token> actual1;
  vector<Token> actual2;
  vector<Token> actual3;
  bool running=true;
  while (running){
    actual1.push_back(t1.getNext(test1));
    if (actual1.back().getType() == EOL) running=false;
  }
  running=true;
  while (running){
    actual2.push_back(t2.getNext(test2));
    if (actual2.back().getType() == EOL) running=false;
  }
  running=true;
  while (running){
    actual3.push_back(t3.getNext(test3));
    if (actual3.back().getType() == EOL) running=false;
  }
  for (int i=0;i<actual1.size();i++){
    ASSERT_EQ(actual1.size(), 4);
    ASSERT_EQ(actual1[i].str(),expected[i].str());
  }
    for (int ii=0; ii<actual2.size(); ii++){
    ASSERT_EQ(actual2.size(), 4);
    ASSERT_EQ(actual2[ii].str(),expected[ii].str());
  }
  for (int iii=0; iii<actual3.size(); iii++){
    ASSERT_EQ(actual3.size(), 4);
    ASSERT_EQ(actual3[iii].str(),expected[iii].str());
  }
}


TEST(Tokens, constructorTest1){

  ifstream in("tests/inputs/4.lisp");
  ASSERT_TRUE(in.is_open());
  
  Tokens tokens("tests/inputs/4.lisp","tests/outputs/testoutput1.s");
  ASSERT_EQ(tokens.getLine(),"line 1");
}

TEST(Tokens, getNextTest){
  string inpath = "tests/inputs/4.lisp";
  ifstream testIn(inpath);
  ASSERT_TRUE(testIn.is_open());
  Tokens tokens(inpath, "tests/outputs/testToknes.out");
  ASSERT_TRUE(tokens.isOpen());
  
  ASSERT_EQ(tokens.getNext().getType(), SYMBOL);
  ASSERT_EQ(tokens.getLine(), " 1");
  ASSERT_EQ(tokens.getNext().getType(), INTEGER);
  ASSERT_EQ(tokens.getLine(), "");
  ASSERT_EQ(tokens.getNext().getType(), SYMBOL);
  ASSERT_EQ(tokens.getLine(), " 5");
  ASSERT_EQ(tokens.getNext().getType(), INTEGER);
  ASSERT_EQ(tokens.getLine(), "");
  ASSERT_EQ(tokens.getNext().getType(), DONE);
}

TEST(Tokens, getLineTest){
  string expected = "line 1";
  string inpath ="tests/inputs/4.lisp";
  ifstream in(inpath);
  ASSERT_TRUE(in.is_open());
  Tokens tokens(inpath, "tests/testTokens.out");
  ASSERT_TRUE(tokens.isOpen());
  ASSERT_EQ(expected, tokens.getLine());
  
}
TEST(Parser, atomTest){
  ASTNode *tree = new ASTNode();
  string inpath = "tests/inputs/2.lisp";
  ifstream testIn(inpath);
  ASSERT_TRUE(testIn.is_open());
  Tokens tokens(inpath, "tests/outputs/testTokens.out");
  ASSERT_TRUE(tokens.isOpen());
  ASSERT_TRUE(atom(tokens, tree));
}
TEST(Parser, listTest){
  ASTNode *tree = new ASTNode();
  string inpath = "tests/inputs/1.lisp";
  ifstream testIn(inpath);
  ASSERT_TRUE(testIn.is_open());
  Tokens tokens(inpath, "tests/outputs/testTokents.out");
  ASSERT_TRUE(tokens.isOpen());
  ASSERT_TRUE(list(tokens,tree));
  
}
//Tests for Tokens class
