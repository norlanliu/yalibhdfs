/*
 * =====================================================================================
 *
 *       Filename:  exception.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/19/2015 05:00:05 PM
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

#ifndef UTILITY_EXCEPTION_H_
#define UTILITY_EXCEPTION_H_

#include <stdexcept>
#include <string>

namespace hdfs{

	class HdfsException: public std::runtime_error{
		public:
			HdfsException(const std::string& arg, const char* file, int line);

			~HdfsException() {
			}

			virtual const char* message() const{
				return detail.c_str();
			}
		private:
			std::string detail;
	};

	class HdfsBadNumFormat : public HdfsException {
		public:
			HdfsBadNumFormat(const std::string& arg, const char* file, int line):
				HdfsException(arg, file, line){
			}
			~HdfsBadNumFormat() throw(){
			}
	};
	class HdfsBadConfigFormat : public HdfsException {
		public:
			HdfsBadConfigFormat(const std::string& arg, const char* file, int line):
				HdfsException(arg, file, line){
			}
			~HdfsBadConfigFormat() throw(){
			}
	};
	class HdfsConfigNotFound: public HdfsException {
		public:
			HdfsConfigNotFound(const std::string& arg, const char* file, int line):
				HdfsException(arg, file, line){
			}
			~HdfsConfigNotFound() throw(){
			}
	};
	class HdfsConfigInvalid: public HdfsException {
		public:
			HdfsConfigInvalid(const std::string& arg, const char* file, int line):
				HdfsException(arg, file, line){
			}
			~HdfsConfigInvalid() throw(){
			}
	};
	class InvalidParameter: public HdfsException {
		public:
			InvalidParameter(const std::string& arg, const char* file, int line):
				HdfsException(arg, file, line){
			}
			~InvalidParameter() throw(){
			}
	};
}


#endif
