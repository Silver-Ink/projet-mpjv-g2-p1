#include <iostream>
#include <cstdio>

#define GREEN "\033[42m"
#define RED	  "\033[41m"
#define RESET "\033[0m"

#define INIT_TEST()\
unsigned int testId = 0;

#define ASSERT(expression)\
{\
	testId++;\
	if (expression)\
		std::cout << "Test n " << testId << " " GREEN "SUCCEDED" RESET " : " "\t" #expression << std::endl;\
	else\
		std::cout << "Test n " << testId << " " RED "FAILED" RESET " : " "\t" #expression << std::endl;\
}

class TestClass
{
public:
	static bool s_floatComp(float a, float b) { return fabs(a - b) < .001f; }
	static void s_testVec3();
};