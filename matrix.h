#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace nonstd {
	enum class range {
		all
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

		template<size_t newM, size_t newN>
		matrix<T, newM, newN> transpose();

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

	template<class T, size_t M, size_t N>
	template<size_t newM, size_t newN>
	matrix<T, newM, newN> matrix<T, M, N>::slice(
		const std::pair<size_t, size_t>& row_interval, 
		const std::pair<size_t, size_t>& column_interval
	) {
		if (row_interval.second - row_interval.first != newM || column_interval.second - column_interval.first != newN) {
			throw std::length_error(
				"sliced matrix dimensions are " + std::to_string(newM) + 
				"x" + std::to_string(newN) + " - should be " + 
				std::to_string(row_interval.second - row_interval.first) + "x" +
				std::to_string(column_interval.second - column_interval.first)
			);
		}

		std::vector<T> sliced_matrix;

		for (size_t i = row_interval.first; i < row_interval.second; i++) {
			std::vector<T> sliced_row(
				data.begin() + (i * N) + column_interval.first,
				data.begin() + (i * N) + column_interval.first + column_interval.second
			);
			sliced_matrix.insert(sliced_matrix.end(), sliced_row.begin(), sliced_row.end());
		}

		return matrix<T, newM, newN>(sliced_matrix);
	}

	/*
	* Member functions
	*/

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

	template<class T, size_t M, size_t N>
	std::vector<T> matrix<T, M, N>::flatten() {
		return data;
	}
}
