/*
 *  Matrix.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-28.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <iosfwd>

#ifndef TDZ_MATRIX_HPP
#define TDZ_MATRIX_HPP

namespace TDZ {
	
	template <int M, int N, typename ComponentT>
	class Matrix {
	public:
		Matrix() :
			m_store() { }

		Matrix(const ComponentT components[N * M]) :
			m_store()
		{
			for (int i = 0; i < (N * M); ++i) {
				m_store.data[i] = components[i];
			}
		}
		
		friend std::ostream& operator<<(std::ostream& outStream, const Matrix<M, N, ComponentT>& matrix) {
			for (int n = 0; n < N; ++n) {
				outStream << "[";
				for (int m = 0; m < M; ++m) {
					outStream << matrix.m_store.data[(n * M) + m];
					if (m < (M - 1)) {
						outStream << ",";
					}
				}
				outStream << "]";
				if (n < (N - 1)) {
					outStream << std::endl;
				}
			}
			return outStream;
		}

	private:
		union {
			ComponentT data[N * M] __attribute__ ((packed));
		} m_store __attribute__ ((aligned (16)));
	};

} // TDZ

#endif /* TDZ_MATRIX_HPP */
