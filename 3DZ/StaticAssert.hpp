/*
 *  StaticAssert.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

namespace TDZ {

	template<bool> struct StaticAssert;
	template<> struct StaticAssert<true> {};
	
#define STATIC_ASSERT(exp) (TDZ::StaticAssert< (exp) >())
	
} // TDZ
