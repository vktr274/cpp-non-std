#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <utility>

namespace nonstd {
	enum class range {
		rows, columns
	};

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
		std::vector<T> operator[](size_t);

		void print();
		size_t size();
		size_t column_size();
		size_t row_size();
		matrix<T, N, M> transpose();
		std::vector<T> flatten();

		template<size_t newM, size_t newN>
		matrix<T, newM, newN> slice(const std::pair<size_t, size_t>&, const std::pair<size_t, size_t>&);
	private:
		std::vector<T> data;
	};

	/*
	* Constructors
	*/

	// Constructor from initializer list
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

	
	// Constructor from a value
	template<class T, size_t M, size_t N>
	matrix<T, M, N>::matrix(T value) {
		data.resize(M * N);
		std::fill(data.begin(), data.end(), value);
	}


	// Constructor from vector
	template<class T, size_t M, size_t N>
	matrix<T, M, N>::matrix(std::vector<T> vector) {
		data = vector;
	}

	/*
	* Operators
	*/

	// Subscript operator
	template<class T, size_t M, size_t N>
	std::vector<T> matrix<T, M, N>::operator[](size_t row) {
		return std::vector<T>(
			data.begin() + (row * N), 
			data.begin() + (row * N) + N
		);
	}

	/*
	* Member functions
	*/

	template<class T, size_t M, size_t N>
	template<size_t newM, size_t newN>
	matrix<T, newM, newN> matrix<T, M, N>::slice(
		const std::pair<size_t, size_t>& row_interval, 
		const std::pair<size_t, size_t>& column_interval
	) {
		std::pair<size_t, size_t> row_interval_copy = row_interval;
		std::pair<size_t, size_t> column_interval_copy = column_interval;

		if (row_interval_copy.first == 0 && row_interval_copy.second == 0) {
			row_interval_copy.second = M;
		}

		if (column_interval_copy.first == 0 && column_interval_copy.second == 0) {
			column_interval_copy.second = N;
		}

		static_assert(newM <= M, "sliced matrix dimensions are invalid");
		static_assert(newN <= N, "sliced matrix dimensions are invalid");
		static_assert(1 <= newM, "sliced matrix dimensions are invalid");
		static_assert(1 <= newN, "sliced matrix dimensions are invalid");

		if (
			row_interval_copy.second - row_interval_copy.first != newM || 
			column_interval_copy.second - column_interval_copy.first != newN
		) {
			throw std::length_error(
				"sliced matrix dimensions are " + std::to_string(newM) + 
				"x" + std::to_string(newN) + " - should be " + 
				std::to_string(row_interval_copy.second - row_interval_copy.first) + "x" +
				std::to_string(column_interval_copy.second - column_interval_copy.first)
			);
		}

		std::vector<T> sliced_matrix;

		for (size_t i = row_interval_copy.first; i < row_interval_copy.second; i++) {
			std::vector<T> sliced_row(
				data.begin() + (i * N) + column_interval_copy.first,
				data.begin() + (i * N) + column_interval_copy.first + column_interval_copy.second
			);
			sliced_matrix.insert(sliced_matrix.end(), sliced_row.begin(), sliced_row.end());
		}

		return matrix<T, newM, newN>(sliced_matrix);
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
	matrix<T, N, M> matrix<T, M, N>::transpose() {
		std::vector<T> transposed;

		for (size_t j = 0; j < N; j++) {
			for (size_t i = 0; i < M; i++) {
				transposed.push_back(data.at(i * N + j));
			}
		}

		return matrix<T, N, M>(transposed);
	}

	template<class T, size_t M, size_t N>
	std::vector<T> matrix<T, M, N>::flatten() {
		return data;
	}

	template<class T, size_t M, size_t N>
	size_t matrix<T, M, N>::size() {
		return data.size();
	}

	template<class T, size_t M, size_t N>
	size_t matrix<T, M, N>::column_size() {
		return M;
	}

	template<class T, size_t M, size_t N>
	size_t matrix<T, M, N>::row_size() {
		return N;
	}
}
