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

	template <std::size_t ComponentN, typename ComponentT> class Vector;

	template <std::size_t ComponentN, typename ComponentT>
	class Vector {
	public:
		Vector() :
			m_store()
		{
			memset(&m_store.a[0], 0UL, sizeof(m_store));
		}
		
		Vector(const ComponentT* values) :
			m_store()
		{
			for (std::size_t i = 0; i < ComponentN; ++i) {
				m_store.a[i] = values[i];
			}
		}
		
		virtual ~Vector() {
		}
		
		inline const ComponentT& operator[](const std::size_t i) const {
			assert(i < ComponentN);
			return m_store.a[i];
		}

		inline ComponentT& operator[](const std::size_t i) {
			assert(i < ComponentN);
			return m_store.a[i];
		}
		
		ComponentT operator*(const Vector<ComponentN, ComponentT>& vector) const {
			ComponentT scalar = 0;
			for (std::size_t i = 0; i < ComponentN; ++i) {
				scalar += m_store.a[i] * vector[i];
			}
			return scalar;
		}
		
		friend std::ostream& operator<<(std::ostream& outStream, const Vector<ComponentN, ComponentT>& vector) {
			outStream << "[";
			for (std::size_t i = 0; i < ComponentN; ++i) {
				outStream << vector[i];
				if (i < (ComponentN - 1)) {
					outStream << ", ";
				}
			}
			outStream << "]";
			return outStream;
		}
		
	private:
		union {
			ComponentT a[ComponentN] __attribute__ ((packed));
		} m_store __attribute__ ((aligned (16)));
	};
		
} // TDZ

#endif /* TDZ_VECTOR_HPP */
