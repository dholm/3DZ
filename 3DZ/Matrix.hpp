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

#include <3DZ/Vector.hpp>

namespace TDZ {

	template <std::size_t M, std::size_t N, typename ComponentT> class Matrix;
	
	template <std::size_t M, std::size_t N, typename ComponentT>
	class Matrix {
	public:
		typedef Vector<N, ComponentT> Column;
		
		Matrix() :
			m_row() { }

		Matrix(const ComponentT* components) :
			m_row()
		{
			for (std::size_t row = 0; row < M; ++row) {
				m_row[row].col = Column(&components[row * N]);
			}
		}
		
		const Column& operator[](std::size_t row) const {
			return m_row[row].col;
		}

		Vector<M, ComponentT> operator*(const Vector<M, ComponentT>& vec) const {
			Vector<M, ComponentT> result;
			for (std::size_t i = 0; i < M; ++i) {
				result[i] = m_row[i].col * vec;
			}
			return result;
		}
		
		friend std::ostream& operator<<(std::ostream& outStream, const Matrix<M, N, ComponentT>& matrix) {
			for (std::size_t row = 0; row < M; ++row) {
				outStream << "[";
				for (std::size_t col = 0; col < N; ++col) {
					outStream << matrix.m_row[row].col[col];
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
		struct {
			Column col;
		} m_row[M] __attribute__ ((aligned (16)));
	};

} // TDZ

#endif /* TDZ_MATRIX_HPP */
