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
		matrix.transpose().print();
		auto flattened = matrix.flatten();

		for (size_t i = 0; i < flattened.size(); i++) {
			std::cout << flattened[i];
			if (i != flattened.size() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
		std::cout << matrix[2][2] << '\n';

		auto row = matrix[2];
		for (const auto& value : row) {
			std::cout << value << ' ';
		}
		std::cout << std::endl;
		matrix.slice<1, 4>({ 1, 2 }, { 0, 4 });
	}
	catch (const std::length_error& e) {
		std::cerr << e.what() << '\n';
	}
	catch (const std::out_of_range& e) {
		std::cerr << e.what() << '\n';
	}

	std::cout << std::endl;

	nonstd::matrix<std::string, 2, 2> matrixStr = { {"ahoj", "cau"}, {"bruh", "kek"} };
	nonstd::matrix<double, 10, 10> testM = 3.14;

	matrixStr.print();
	matrixStr.transpose().print();
	matrixStr.print();
	testM.print();

	return 0;
}
