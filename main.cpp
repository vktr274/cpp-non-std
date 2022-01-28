#include <iostream>
#include "stringops.h"
#include "matrix.h"

int main() {
	try {
		nonstd::matrix<std::string, 2, 2> matrixStr =
		{
			"kewk", "bonk",
			"bruh", "kek"
		};

		std::cout << matrixStr << '\n';

		nonstd::matrix<uint32_t, 5, 4> matrix =
		{
			1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 11, 12,
			13, 14, 15, 16,
			17, 18, 19, 20
		};
		std::cout << matrix << '\n';
		auto flattened = matrix.flatten();

		for (size_t i = 0; i < flattened.size(); i++) {
			std::cout << flattened[i];
			if (i != flattened.size() - 1) {
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
		std::cout << matrix[4][2] << '\n';

		std::cout << matrix.slice<5, 2>({ }, { 0, 2 }) << '\n';

		std::cout << matrix.size() << ' '; 
		std::cout << matrix.row_size() << ' '; 
		std::cout << matrix.column_size() << '\n';

		nonstd::matrix<uint16_t, 4, 2> matrixOpTest1 =
		{
			1, 2,
			3, 4,
			5, 6,
			7, 8
		};
		nonstd::matrix<uint16_t, 2, 3> matrixOpTest2 =
		{
			3, 4, 5,
			6, 8, 10
		};

		std::cout << matrixOpTest1 * matrixOpTest2 << '\n';
		std::cout << matrixOpTest1 + matrixOpTest1 << '\n';
		std::cout << matrixOpTest1 - matrixOpTest1 << '\n';
		std::cout << matrixOpTest1 + uint16_t(8) << '\n';
		std::cout << matrixOpTest2 - uint16_t(2) << '\n';
		std::cout << uint16_t(8) + matrixOpTest1 << '\n';
		std::cout << uint16_t(8) * matrixOpTest1 << '\n';
		std::cout << matrixOpTest1 * uint16_t(8) << '\n';

		auto newMatrix = matrix.resize<2, 10>();
		std::cout << newMatrix << '\n';
		auto transposedMatrix = newMatrix.transpose();
		std::cout << transposedMatrix << '\n';
		auto originalMatrix = transposedMatrix.transpose().resize<5, 4>();
		std::cout << originalMatrix << '\n';

		const nonstd::matrix<int32_t, 4, 3> constMatrix = { 1,2,3,4,5,6,7,8,9,10,11,12 };

		std::cout << constMatrix.empty() << '\n';
		std::cout << constMatrix.size() << ' '; 
		std::cout << constMatrix.row_size() << ' ';
		std::cout << constMatrix.column_size() << '\n';

		std::cout << constMatrix[3][2] << '\n';
	}
	catch (const std::length_error& e) {
		std::cerr << e.what() << '\n';
	}
	catch (const std::out_of_range& e) {
		std::cerr << e.what() << '\n';
	}

	return 0;
}
