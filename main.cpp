#include <iostream>
#include "stringops.h"
#include "matrix.h"

int main() {
	try {
		nonstd::matrix<uint32_t, 5, 4> matrix = 
		{
			{1, 2, 3, 4}, 
			{5, 6, 7, 8}, 
			{9, 10, 11, 12}, 
			{13, 14, 15, 16}, 
			{17, 18, 19, 20} 
		};
		matrix.print();
		matrix.transpose<4, 5>().print();
	}
	catch (const std::length_error& e) {
		std::cerr << e.what() << '\n';
	}
	catch (const std::out_of_range& e) {
		std::cerr << e.what() << '\n';
	}

	nonstd::matrix<std::string, 2, 2> matrixStr = { {"ahoj", "cau"}, {"bruh", "kek"} };
	nonstd::matrix<std::string, 10, 10> testM = std::string("ahoj");

	matrixStr.print();
	matrixStr.transpose<2, 2>().print();
	matrixStr.print();
	testM.print();

	return 0;
}
