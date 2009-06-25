/*
 *  StringUtils.cpp
 *  3DZ
 *
 *  Created by David Holm on 2009-06-14.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "StringUtils.hpp"

namespace TDZ {

	std::string trim(const std::string& str)
	{
		if (!str.length()) {
			return str;
		}
	
		std::string::size_type start = str.find_first_not_of(" \t\r\n\v");	
		if (start == std::string::npos) {
			return "";
		}

		std::string::size_type end = str.find_last_not_of(" \t\r\n\v");

		return std::string(str, start, end - start + 1);
	}

} // TDZ
