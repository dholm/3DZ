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
#include <cmath>
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
		
		Vector<N, ComponentT> normalized() const {
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
		
		Vector<N, ComponentT> operator+(const Vector<N, ComponentT>& rhs) const {
			Vector<N, ComponentT> result(*this);
			for (std::size_t i = 0; i < N; ++i) {
				result[i] += rhs[i];
			}
			return result;
		}
		
		Vector<N, ComponentT> operator*(const ComponentT& scalar) const {
			Vector<N, ComponentT> result(*this);
			for (std::size_t i = 0; i < N; ++i) {
				result[i] *= scalar;
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
		
	protected:
		union {
			ComponentT a[N] __attribute__ ((packed));
		} m_vector __attribute__ ((aligned (16)));
	};
	
	template <typename ComponentT>
	class Vector3 : public Vector<3, ComponentT> {
	public:
		explicit Vector3(const ComponentT& x, const ComponentT& y, const ComponentT& z) :
			Vector<3, ComponentT>()
		{
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[2] = z;
		}
	};
		
	template <typename ComponentT>
	class Vector4 : public Vector<4, ComponentT> {
	public:
		explicit Vector4(const ComponentT& x, const ComponentT& y, const ComponentT& z, const ComponentT& w) :
		Vector<4, ComponentT>()
		{
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[2] = z;
			(*this)[3] = w;
		}
	};
	
	template <typename ComponentT>
	Vector<3, ComponentT> cross(const Vector<3, ComponentT>& lhs, const Vector<3, ComponentT>& rhs) {
		return Vector3<ComponentT>(
			lhs[1] * rhs[2] - lhs[2] * rhs[1],
			lhs[2] * rhs[0] - lhs[0] * rhs[2],
			lhs[0] * rhs[1] - lhs[1] * rhs[0]
		);
	}
		
} // TDZ

#endif /* TDZ_VECTOR_HPP */
