/*
 * =====================================================================================
 *
 *       Filename:  exception.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/19/2015 05:41:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   (Qi Liu), liuqi.edward@gmail.com
 *   Organization:  antq.com
 *
 *   Copyright (c) 2015, Qi Liu.
 *   All rights reserved.
 * =====================================================================================
 */

#include "exception.h"

#include <sstream>

namespace hdfs{
	HdfsException::HdfsException(const std::string& arg, const char* file,
			int line):	std::runtime_error(arg){
		std::ostringstream ss;
		ss << file <<": " << line << ": " <<arg <<std::endl;
		detail = ss.str();
	}
}
