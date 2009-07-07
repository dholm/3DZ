/*
 *  Matrix.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-28.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_MATRIX_HPP
#define TDZ_MATRIX_HPP

#include <iosfwd>

namespace TDZ {
	
	template <std::size_t M, std::size_t N, typename ComponentT>
	class Matrix {
	public:
		explicit Matrix(const ComponentT& value = ComponentT(0)) :
			m_matrix()
		{
			for (std::size_t row = 0; row < M; ++row) {
				for (std::size_t col = 0; col < N; ++col) {
					m_matrix[row][col] = value;
				}
			}
		}

		explicit Matrix(const ComponentT* components) :
			m_matrix()
		{
			memcpy(m_matrix, components, M * N * sizeof(ComponentT));
		}
		
		operator const ComponentT*() const {
			return &m_matrix[0][0];
		}
		
		inline const ComponentT& operator()(std::size_t row, std::size_t column) const {
			return m_matrix[row][column];
		}

		inline ComponentT& operator()(std::size_t row, std::size_t column) {
			return m_matrix[row][column];
		}

		Vector<M, ComponentT> operator*(const Vector<M, ComponentT>& vec) const {
			Vector<M, ComponentT> result;
			for (std::size_t row = 0; row < M; ++row) {
				for (std::size_t col = 0; col < N; ++col) {
					result[row] += m_matrix[row][col] * vec[row];
				}
			}
			return result;
		}
		
		template <std::size_t DstN>
		Matrix<M, DstN, ComponentT> operator*(const Matrix<N, DstN, ComponentT>& rhs) const {
			Matrix<M, DstN, ComponentT> result;
			for (std::size_t row = 0; row < M; ++row) {
				for (std::size_t col = 0; col < DstN; ++col) {
					for (std::size_t r = 0; r < N; ++r) {
						result(row, col) += m_matrix[row][r] * rhs(r, col);
					}
				}
			}
			return result;
		}

		friend std::ostream& operator<<(std::ostream& outStream, const Matrix<M, N, ComponentT>& matrix) {
			for (std::size_t row = 0; row < M; ++row) {
				outStream << "[";
				for (std::size_t col = 0; col < N; ++col) {
					outStream << matrix.m_matrix[row][col];
					if (col < (N - 1)) {
						outStream << ",";
					}
				}
				outStream << "]";
				if (row < (M - 1)) {
					outStream << std::endl;
				}
			}
			return outStream;
		}

	private:
		ComponentT __attribute__ ((packed)) m_matrix[M][N] __attribute__ ((aligned (16)));
	};
	
	template<std::size_t M, typename ComponentT>
	struct IdentityMatrix {
		static Matrix<M, M, ComponentT> create() {
			Matrix<M, M, ComponentT> matrix;
			for (std::size_t i = 0; i < M; ++i) {
				matrix[i][i] = ComponentT(1);
			}
			return matrix;
		}
	};

} // TDZ

#endif /* TDZ_MATRIX_HPP */
