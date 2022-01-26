#include <iostream>
//#include "stringops.h"
#include "matrix.h"

using namespace std::literals;

int main() {
	try {
		nonstd::matrix<uint16_t, 2, 2> matrixFrom1D = { 3, 4, 5, 6 };
		nonstd::matrix<double, 3, 4> matrixDouble = { { 1.1, 2.1, 4.5, 5.9 }, { 5.8, 8.9, 3.998, 33.8 }, { 0.12, 3.14, 7.24, 76.89 } };
		nonstd::matrix<std::string, 2, 2> matrixStr = { {"kewk"s, "bonk"s}, {"bruh"s, "kek"s} };

		nonstd::matrix<uint32_t, 5, 4> matrix =
		{
			{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16},
			{17, 18, 19, 20}
		};
		std::cout << matrix;
		std::cout << matrix.transpose();
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
		std::cout << matrix.slice<5, 2>({ }, { 0, 2 });

		std::cout << std::endl << matrix.size() << ' ' << matrix.row_size() << ' ' << matrix.column_size();
		std::cout << std::endl;

		nonstd::matrix<uint16_t, 4, 2> matrixOpTest1 = { { 1, 2 }, { 3, 4 }, {5, 6}, { 7, 8 } };
		nonstd::matrix<uint16_t, 2, 3> matrixOpTest2 = { { 3, 4, 5 }, { 6, 8, 10 } };

		std::cout << matrixOpTest1 * matrixOpTest2;
		std::cout << matrixOpTest1 + matrixOpTest1;
		std::cout << matrixOpTest1 - matrixOpTest1;
		std::cout << matrixOpTest1 + 8Ui16;
		std::cout << matrixOpTest2 - 2Ui16;
		std::cout << 8Ui16 + matrixOpTest1;
		std::cout << 8Ui16 * matrixOpTest1;
		std::cout << matrixOpTest1 * 8Ui16;

		// nonstd::matrix<uint16_t, 2, 1> matrix_2_1_Test = { { 35 }, { 610 } };

		// std::cout << std::endl << matrix_2_1_Test;
	}
	catch (const std::length_error& e) {
		std::cerr << e.what() << '\n';
	}
	catch (const std::out_of_range& e) {
		std::cerr << e.what() << '\n';
	}

	return 0;
}
