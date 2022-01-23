#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <array>
#include <algorithm>

namespace nonstd {
	template<class T, size_t M, size_t N>
	class matrix {
	public:
		matrix(std::initializer_list<std::initializer_list<T>>);
		matrix(std::vector<T>);
		matrix(T);
		matrix() = default;
		~matrix() = default;

		matrix(const matrix& other) = default;
		matrix& operator=(const matrix& rhs) = default;

		void print();

		template<size_t newM, size_t newN>
		matrix<T, newM, newN> transpose();
	private:
		std::vector<T> data;
	};

	template<class T, size_t M, size_t N>
	matrix<T, M, N>::matrix(std::initializer_list<std::initializer_list<T>> data_) {
		if (data_.size() != M) {
			throw std::length_error(
				"length of matrix columns is " +
				std::to_string(data_.size()) +
				" - should be " + std::to_string(M)
			);
		}
		for (const auto& row : data_) {
			if (row.size() != N) {
				throw std::length_error(
					"length of matrix row is " + 
					std::to_string(row.size()) + 
					" - should be " + std::to_string(N)
				);
			}
			for (const auto& value : row) {
				data.push_back(value);
			}
		}
	}

	template<class T, size_t M, size_t N>
	matrix<T, M, N>::matrix(T value) {
		data.resize(M * N);
		std::fill(data.begin(), data.end(), value);
	}

	template<class T, size_t M, size_t N>
	matrix<T, M, N>::matrix(std::vector<T> vector) {
		data = vector;
	}

	template<class T, size_t M, size_t N>
	void matrix<T, M, N>::print() {
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < N; j++) {
				std::cout << std::setw(5) << data.at(i * N + j) << std::setw(5);
			}
			std::cout << '\n';
		}
	}

	template<class T, size_t M, size_t N>
	template<size_t newM, size_t newN>
	matrix<T, newM, newN> matrix<T, M, N>::transpose() {
		std::vector<T> transposed;
		
		for (size_t j = 0; j < N; j++) {
			for (size_t i = 0; i < M; i++) {
				transposed.push_back(data.at(i * N + j));
			}
		}

		return matrix<T, newM, newN>(transposed);
	}
}
