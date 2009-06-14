/*
 *  Vector.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <cassert>

namespace TDZ {

	template <int ComponentN, typename ComponentT> class Vector;

	template <typename ComponentT>
	class Vector<3, ComponentT> {
	public:
		Vector() :
			m_store()
		{
		}
		
		Vector(const ComponentT* components) :
			m_store()
		{
			m_store.s.x = components[0];
			m_store.s.y = components[1];
			m_store.s.z = components[2];
		}
		
		inline const ComponentT& operator[](const size_t i) const {
			assert(i < 3);
			return m_store.a[i];
		}

		inline ComponentT& operator[](const size_t i) {
			assert(i < 3);
			return m_store.a[i];
		}
		
	private:
		union {
			struct {
				ComponentT x;
				ComponentT y;
				ComponentT z;
			} __attribute__ ((packed)) s;
			ComponentT a[3];
		} m_store __attribute__ ((aligned (16)));
	};
} // TDZ
