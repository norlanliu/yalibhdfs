/*
 * =====================================================================================
 *
 *       Filename:  exception_internal.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/19/2015 05:23:56 PM
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

#ifndef UTILITY_EXCEPTION_INTERNAL_H_
#define UTILITY_EXCEPTION_INTERNAL_H_

#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <unistd.h>

#include <glog/logging.h>
#define PATH_SEPRATOR '/'

#define TERMINATE(throwable, fmt, ...) do{\
	hdfs::Terminate<throwable>(__FILE__, __LINE__, #throwable, fmt, ##__VA_ARGS__);\
}while(0)

#define THROW(throwable, fmt, ...) do {\
	hdfs::ThrowException<throwable>(__FILE__, __LINE__, #throwable, fmt, ##__VA_ARGS__);\
}while(0)

namespace hdfs{

	inline static const char* SkipPath(const char* path){
		int i, len = static_cast<int>(strlen(path));
		for(i = len - 1; i > 0 && path[i] != PATH_SEPRATOR; --i){
		}
		assert(i > 0 && i < len);
		return path+i+1;
	}
	template<typename throwable>
		void ThrowException(const char* file, int line, const char* name,
				const char* fmt, ...){
			va_list ap;
			va_start(ap, fmt);
			std::string buffer = name;
			buffer += ": ";
			int size = vsnprintf(NULL, 0, fmt, ap);
			va_end(ap);
			int offset = static_cast<int>(buffer.size());
			buffer.resize(offset + size + 1);
			va_start(ap, fmt);
			vsnprintf(&buffer[offset], size+1, fmt, ap);
			va_end(ap);

			throw throwable(buffer.c_str(), SkipPath(file), line);
		}
	template<typename throwable>
		void Terminate(const char* file, int line, const char* name,
				const char* fmt, ...){
			va_list ap;
			va_start(ap, fmt);
			std::string buffer = name;
			buffer += ": ";
			int size = vsnprintf(NULL, 0, fmt, ap);
			va_end(ap);
			int offset = static_cast<int>(buffer.size());
			buffer.resize(offset + size + 1);
			va_start(ap, fmt);
			vsnprintf(&buffer[offset], size+1, fmt, ap);
			va_end(ap);

			LOG(FATAL) << throwable(buffer.c_str(), SkipPath(file), line).message();
		}
}
#endif

