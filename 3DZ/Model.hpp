/*
 *  Model.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_MODEL_HPP
#define TDZ_MODEL_HPP

#include <3DZ/Vector.hpp>

/* The classes below are exported */
#pragma GCC visibility push(default)

namespace TDZ {

	class Model {
	public:
		typedef Vector<3, float> Vector3f;
		
	};
	
} // TDZ

#pragma GCC visibility pop
#endif /* TDZ_MODEL_HPP */
