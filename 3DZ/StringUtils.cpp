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
		if (str.length() == 0) {
			return str;
		}
	
		std::string::size_type beginIndex = str.find_first_not_of(" \t\r\n\v");
		std::string::size_type endIndex = str.find_last_not_of(" \t\r\n\v");
	
		if (beginIndex == std::string::npos) {
			return "";
		}
		return std::string(str, beginIndex, endIndex - beginIndex + 1);
	}

} // TDZ
