/*
 *  Radian.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-19.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_RADIAN_HPP
#define TDZ_RADIAN_HPP

namespace TDZ {

	template <typename ComponentT> class Degree;

	template <typename ComponentT>
	class Radian {
	public:
		explicit Radian(const ComponentT& radian) :
			m_radian(radian)
		{
		}
		
		Radian<ComponentT>& operator-=(const Radian<ComponentT>& rhs) {
			m_radian -= rhs.m_radian;
			return *this;
		}
		
		Radian<ComponentT>& operator+=(const Radian<ComponentT>& rhs) {
			m_radian += rhs.m_radian;
			return *this;
		}
		
		operator Degree<ComponentT>() const {
			return Degree<ComponentT>(m_radian * ComponentT(180.0 / M_PI));
		}
		
		operator const ComponentT&() const {
			return m_radian;
		}
		
	private:
		ComponentT m_radian;
	};
	
} // TDZ

#endif /* TDZ_RADIAN_HPP */
