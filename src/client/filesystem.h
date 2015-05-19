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

namespace hdfs{

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
			FileSystem ();                             /* constructor */
			~FileSystem();

			/* ====================  OPERATORS     ======================================= */
			void connect();

			void connect(const char* uri, const char* username);

		private:
			/* ====================  METHODS       ======================================= */

			/* ====================  DATA MEMBERS  ======================================= */

	}; /* -----  end of class FileSystem  ----- */

}

#endif
