/*
 *  Scene.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-15.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_SCENE_HPP
#define TDZ_SCENE_HPP

#include <3DZ/SmartPointer.hpp>

namespace TDZ {
	
	class Scene {
	public:
		typedef SharedPointer<Scene>::Type Pointer;
		
		virtual ~Scene() { }
		
	private:
	};
	
} // TDZ

#endif /* TDZ_SCENE_HPP */
