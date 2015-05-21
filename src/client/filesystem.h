/*
 * =====================================================================================
 *
 *       Filename:  filesystem.h
 *
 *    Description:  file system class
 *
 *        Version:  1.0
 *        Created:  05/19/2015 04:03:41 PM
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
#ifndef CLIENT_FILE_SYSTEM_H_
#define CLIENT_FILE_SYSTEM_H_


#include "configuration.h"

class string;

namespace hdfs{

	class FileSystemImpl;

	/*
	 * =====================================================================================
	 *        Class:  FileSystem
	 *  Description:  
	 * =====================================================================================
	 */
	class FileSystem
	{
		public:
			/* ====================  LIFECYCLE     ======================================= */
			FileSystem (const Configuration& conf);                             /* constructor */
			~FileSystem();

			/* ====================  OPERATORS     ======================================= */
			void connect();

			void connect(const char* uri);

			void connect(const char* uri, const char* username, const char* token);

		private:

			FileSystemImpl* InitialFSImpl(const char* uri, const std::string& principal);
			/* ====================  DATA MEMBERS  ======================================= */
			FileSystemImpl* _fs_impl;

			Configuration _conf;

	}; /* -----  end of class FileSystem  ----- */

}

#endif
