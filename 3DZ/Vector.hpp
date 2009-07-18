/*
 *  Vector.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_VECTOR_HPP
#define TDZ_VECTOR_HPP

#include <iostream>
#include <cassert>

namespace TDZ {

	template <std::size_t N, typename ComponentT>
	class Vector {
	public:
		explicit Vector(const ComponentT& value = 0) :
			m_vector()
		{
			for (std::size_t i = 0; i < N; ++i) {
				m_vector.a[0] = value;
			}
		}
		
		explicit Vector(const ComponentT* values) :
			m_vector()
		{
			memcpy(m_vector.a, values, N * sizeof(ComponentT));
		}
		
		virtual ~Vector() {
		}
		
		inline const ComponentT& operator[](const std::size_t i) const {
			assert(i < N);
			return m_vector.a[i];
		}

		inline ComponentT& operator[](const std::size_t i) {
			assert(i < N);
			return m_vector.a[i];
		}
		
		ComponentT length() const {
			ComponentT scalar = 0;
			for (std::size_t i = 0; i < N; ++i) {
				scalar += (m_vector.a[i] * m_vector.a[i]);
			}
			return sqrt(scalar);
		}
		
		Vector<N, ComponentT> normalize() const {
			Vector<N, ComponentT> result(*this);
			ComponentT len(length());
			if (ComponentT(0) < len) {
				for (std::size_t i = 0; i < N; ++i) {
					result[i] /= len;
				}
			}
			return result;
		}
		
		Vector<N, ComponentT> operator-(const Vector<N, ComponentT>& rhs) const {
			Vector<N, ComponentT> result(*this);
			for (std::size_t i = 0; i < N; ++i) {
				result[i] -= rhs[i];
			}
			return result;
		}
		
		ComponentT dot(const Vector<N, ComponentT>& vector) const {
			ComponentT scalar = 0;
			for (std::size_t i = 0; i < N; ++i) {
				scalar += m_vector.a[i] * vector[i];
			}
			return scalar;
		}
		
		Vector<N, ComponentT> cross(const Vector<N, ComponentT>& vector) const {
			Vector<N, ComponentT> result;
			for (std::size_t i = 0; i < N; ++i) {
				result[i] = m_vector.a[i] * vector[i];
			}
			return result;
		}
		
		friend std::ostream& operator<<(std::ostream& outStream, const Vector<N, ComponentT>& vector) {
			outStream << "[";
			for (std::size_t i = 0; i < N; ++i) {
				outStream << vector[i];
				if (i < (N - 1)) {
					outStream << ", ";
				}
			}
			outStream << "]";
			return outStream;
		}
		
	private:
		union {
			ComponentT a[N] __attribute__ ((packed));
		} m_vector __attribute__ ((aligned (16)));
	};
		
} // TDZ

#endif /* TDZ_VECTOR_HPP */
