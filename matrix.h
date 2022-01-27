#pragma once

#include <cstdint>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <type_traits>
#include <initializer_list>
#include <string>

namespace nonstd {
	template<class T, size_t M, size_t N>
	class matrix;

	template<class T, size_t M, size_t N>
	std::ostream& operator<<(std::ostream&, const matrix<T, M, N>&);

	template<class T, size_t M, size_t N>
	matrix<T, M, N> operator+(const matrix<T, M, N>&, const matrix<T, M, N>&);

	template<class T, size_t M, size_t N>
	matrix<T, M, N> operator+(const matrix<T, M, N>&, const T&);

	template<class T, size_t M, size_t N>
	matrix<T, M, N> operator+(const T&, const matrix<T, M, N>&);

	template<class T, size_t M, size_t N>
	matrix<T, M, N> operator-(const matrix<T, M, N>&, const matrix<T, M, N>&);

	template<class T, size_t M, size_t N>
	matrix<T, M, N> operator-(const matrix<T, M, N>&, const T&);

	template<class T_, size_t M_, size_t N_, size_t S_>
	matrix<T_, M_, N_> operator*(const matrix<T_, M_, S_>&, const matrix<T_, S_, N_>&);

	template<class T, size_t M, size_t N>
	matrix<T, M, N> operator*(const matrix<T, M, N>&, const T&);

	template<class T, size_t M, size_t N>
	matrix<T, M, N> operator*(const T&, const matrix<T, M, N>&);

	template<class T, size_t M, size_t N>
	class matrix {
	public:
		matrix(std::initializer_list<T>);
		matrix(std::vector<T>);
		matrix(T);
		matrix() = default;
		~matrix() = default;

		matrix(const matrix&) = default;
		matrix& operator=(const matrix&) = default;
		std::vector<T> operator[](size_t) const;

		template<size_t newM, size_t newN>
		matrix<T, newM, newN> slice(const std::pair<size_t, size_t>&, const std::pair<size_t, size_t>&);

		template<size_t newM, size_t newN>
		matrix<T, newM, newN> resize();

		void clear();
		bool empty() const;
		size_t size() const;
		size_t column_size() const;
		size_t row_size() const;
		matrix<T, N, M> transpose();
		std::vector<T> flatten();
	private:
		std::vector<T> data;

		friend std::ostream& operator<< <>(std::ostream&, const matrix&);
		friend matrix operator+ <>(const matrix&, const matrix&);
		friend matrix operator+ <>(const matrix&, const T&); 
		friend matrix operator+ <>(const T&, const matrix&);
		friend matrix operator- <>(const matrix&, const matrix&);
		friend matrix operator- <>(const matrix&, const T&);
		friend matrix operator* <>(const matrix&, const T&);
		friend matrix operator* <>(const T&, const matrix&);
		template<class T_, size_t M_, size_t N_, size_t S_>
		friend matrix<T_, M_, N_> operator*(const matrix<T_, M_, S_>&, const matrix<T_, S_, N_>&);
	};

	/*
	* Constructors
	*/

	// Constructor from initializer list.
	template<class T, size_t M, size_t N>
	matrix<T, M, N>::matrix(std::initializer_list<T> data_) {
		if (M * N != data_.size()) {
			throw std::length_error(
				"list of size " + std::to_string(data_.size()) +
				" cannot be converted to a " + std::to_string(M) +
				"x" + std::to_string(N) + " matrix"
			);
		}
		data = std::vector<T>(data_.begin(), data_.end());
	}

	// Constructor from vector.
	template<class T, size_t M, size_t N>
	matrix<T, M, N>::matrix(std::vector<T> data_) {
		if (M * N != data_.size()) {
			throw std::length_error(
				"vector of size " + std::to_string(data_.size()) +
				" cannot be converted to a " + std::to_string(M) +
				"x" + std::to_string(N) + " matrix"
			);
		}
		data = data_;
	}

	// Constructor from a value.
	template<class T, size_t M, size_t N>
	matrix<T, M, N>::matrix(T value) {
		data.resize(M * N);
		std::fill(data.begin(), data.end(), value);
	}

	/*
	* Operators
	*/

	// Subscript operator.
	template<class T, size_t M, size_t N>
	std::vector<T> matrix<T, M, N>::operator[](size_t row) const {
		return std::vector<T>(
			data.begin() + (row * N), 
			data.begin() + (row * N) + N
		);
	}

	// Stream insertion operator.
	template<class T, size_t M, size_t N>
	std::ostream& operator<<(std::ostream& out, const matrix<T, M, N>& rhs) {
		for (size_t i = 0; i < M; i++) {
			for (size_t j = 0; j < N; j++) {
				out << std::setw(5) << rhs.data.at(i * N + j) << std::setw(5);
			}
			out << '\n';
		}
		return out;
	}
	
	// Addition operator #1.
	template<class T, size_t M, size_t N>
	matrix<T, M, N> operator+(const matrix<T, M, N>& lhs, const matrix<T, M, N>& rhs) {
		static_assert(std::is_arithmetic<T>::value, "matrix types not numeric");

		std::vector<T> result;

		for (size_t i = 0; i < M * N; i++) {
			result.push_back(lhs.data[i] + rhs.data[i]);
		}

		return matrix<T, M, N>(result);
	}

	// Addition operator #2.
	template<class T, size_t M, size_t N>
	matrix<T, M, N> operator+(const matrix<T, M, N>& lhs, const T& rhs) {
		static_assert(std::is_arithmetic<T>::value, "matrix type not numeric");

		std::vector<T> result;

		for (size_t i = 0; i < M * N; i++) {
			result.push_back(lhs.data[i] + rhs);
		}

		return matrix<T, M, N>(result);
	}

	// Addition operator #3.
	template<class T, size_t M, size_t N>
	matrix<T, M, N> operator+(const T& lhs, const matrix<T, M, N>& rhs) {
		static_assert(std::is_arithmetic<T>::value, "matrix type not numeric");

		std::vector<T> result;

		for (size_t i = 0; i < M * N; i++) {
			result.push_back(lhs + rhs.data[i]);
		}

		return matrix<T, M, N>(result);
	}

	// Subtraction operator #1.
	template<class T, size_t M, size_t N>
	matrix<T, M, N> operator-(const matrix<T, M, N>& lhs, const matrix<T, M, N>& rhs) {
		static_assert(std::is_arithmetic<T>::value, "matrix types not numeric");

		std::vector<T> result;

		for (size_t i = 0; i < M * N; i++) {
			result.push_back(lhs.data[i] - rhs.data[i]);
		}

		return matrix<T, M, N>(result);
	}

	// Subtraction operator #2.
	template<class T, size_t M, size_t N>
	matrix<T, M, N> operator-(const matrix<T, M, N>& lhs, const T& rhs) {
		static_assert(std::is_arithmetic<T>::value, "matrix type not numeric");

		std::vector<T> result;

		for (size_t i = 0; i < M * N; i++) {
			result.push_back(lhs.data[i] - rhs);
		}

		return matrix<T, M, N>(result);
	}

	// Multiplication operator #1.
	template<class T_, size_t M_, size_t N_, size_t S_>
	matrix<T_, M_, N_> operator*(const matrix<T_, M_, S_>& lhs, const matrix<T_, S_, N_>& rhs) {
		static_assert(std::is_arithmetic<T_>::value, "matrix types not numeric");

		std::vector<T_> result(M_ * N_, T_(0));

		for (size_t i = 0; i < M_; i++) {
			for (size_t j = 0; j < N_; j++) {
				result[i * N_ + j] = T_(0);
				for (size_t k = 0; k < S_; k++) {
					result[i * N_ + j] = lhs.data[i * S_ + k] + rhs.data[k * N_ + j];
				}
			}
		}

		return matrix<T_, M_, N_>(result);
	}

	// Multiplication operator #2.
	template<class T, size_t M, size_t N>
	matrix<T, M, N> operator*(const matrix<T, M, N>& lhs, const T& rhs) {
		static_assert(std::is_arithmetic<T>::value, "matrix type not numeric");

		std::vector<T> result;

		for (size_t i = 0; i < M * N; i++) {
			result.push_back(lhs.data[i] * rhs);
		}

		return matrix<T, M, N>(result);
	}

	// Multiplication operator #3.
	template<class T, size_t M, size_t N>
	matrix<T, M, N> operator*(const T& lhs, const matrix<T, M, N>& rhs) {
		static_assert(std::is_arithmetic<T>::value, "matrix type not numeric");

		std::vector<T> result;

		for (size_t i = 0; i < M * N; i++) {
			result.push_back(lhs * rhs.data[i]);
		}

		return matrix<T, M, N>(result);
	}

	/*
	* Member functions
	*/

	/*
	* Function that creates a sliced matrix of dimensions newM * newN.
	* Returns: new sliced matrix.
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
	template<size_t newM, size_t newN>
	matrix<T, newM, newN> matrix<T, M, N>::resize() {
		if (data.empty()) {
			return matrix<T, newM, newN>();
		}

		if (newM * newN != data.size()) {
			throw std::length_error(
				"cannot resize " + std::to_string(M) + "x" + std::to_string(N) + 
				" matrix to " + std::to_string(newM) + "x" + std::to_string(newN)
			);
		}

		return matrix<T, newM, newN>(data);
	}

	/* 
	* Function that transposes matrices from M * N to N * M.
	* Returns: new transposed matrix.
	*/
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

	/*
	* Function for flattening matrices.
	* Returns: 1D vector from the matrix.
	*/
	template<class T, size_t M, size_t N>
	std::vector<T> matrix<T, M, N>::flatten() {
		return data;
	}

	template<class T, size_t M, size_t N>
	size_t matrix<T, M, N>::size() const {
		return data.size();
	}

	template<class T, size_t M, size_t N>
	size_t matrix<T, M, N>::column_size() const {
		return M;
	}

	template<class T, size_t M, size_t N>
	size_t matrix<T, M, N>::row_size() const {
		return N;
	}

	template<class T, size_t M, size_t N>
	bool matrix<T, M, N>::empty() const {
		return data.empty();
	}

	template<class T, size_t M, size_t N>
	void matrix<T, M, N>::clear() {
		data.clear();
	}
}
