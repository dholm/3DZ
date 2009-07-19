/*
 *  Degree.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-19.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_DEGREE_HPP
#define TDZ_DEGREE_HPP

namespace TDZ {
	
	template <typename ComponentT> class Radian;

	template <typename ComponentT>
	class Degree {
	public:
		Degree(const ComponentT& degree) :
			m_degree(degree)
		{
		}
		
		Degree<ComponentT>& operator-=(const Degree<ComponentT>& rhs) {
			m_degree -= rhs.m_degree;
			return *this;
		}
		
		Degree<ComponentT>& operator+=(const Degree<ComponentT>& rhs) {
			m_degree += rhs.m_degree;
			return *this;
		}
		
		operator Radian<ComponentT>() const {
			return Radian<ComponentT>(m_degree * ComponentT(M_PI / 180.0));
		}
		
		operator const ComponentT&() const {
			return m_degree;
		}
		
	private:
		ComponentT m_degree;
	};
	
} // TDZ

#endif /* TDZ_DEGREE_HPP */
