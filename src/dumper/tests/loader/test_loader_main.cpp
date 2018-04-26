//#include <iostream>
#include "gtest/gtest.h"


class CLoader {
public:
	CLoader() { m_isok = true; }
   ~CLoader() {}
	
    bool 	isok() { return m_isok; }
	u_int	size() { return 10; } 
 
	int m_isok;
}; 

TEST(SquareRootTest, PositiveNos) { 
    EXPECT_TRUE(true);
}

class CLoaderTest : public ::testing::Test {
protected:
	CLoaderTest() {}
	virtual void SetUp() {}

	virtual void TearDown() {}

	CLoader m_loader;
};

TEST_F(CLoaderTest, CheckSize) {
	EXPECT_EQ(10, m_loader.size());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
  //
  //return 0;
}
