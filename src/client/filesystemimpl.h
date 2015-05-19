/*
 * =====================================================================================
 *
 *       Filename:  FileSystemImpl.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/19/2015 04:08:07 PM
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

#ifndef CLIENT_FILE_SYSTEM_IMPL_H_
#define CLIENT_FILE_SYSTEM_IMPL_H_

namespace hdfs{
	
	/*
	 * =====================================================================================
	 *        Class:  FileSystemImpl
	 *  Description:  
	 * =====================================================================================
	 */
	class FileSystemImpl
	{
		public:
			/* ====================  LIFECYCLE     ======================================= */
			FileSystemImpl ();                             /* constructor */

			/* ====================  OPERATORS     ======================================= */
			void connect();

		private:
			/* ====================  METHODS       ======================================= */

			/* ====================  DATA MEMBERS  ======================================= */
			NameNode* _name_node;

	}; /* -----  end of class FileSystemImpl  ----- */

}

#endif
