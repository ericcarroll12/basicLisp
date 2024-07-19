#include <gtest/gtest.h>
#include "../token.hpp"
#include "../AST.hpp"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
TEST(Token, constructorTest){
    Token t;
    EXPECT_EQ(t.getType(), ERROR);
    EXPECT_EQ(t.getValue(),"");
    EXPECT_EQ(t.str(),"ERROR");
}
TEST(AST, constructorTest){
    ASTNode a;
    EXPECT_EQ(a.getChildrenSize(),0);

}