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
#include "fskey.h"
#include "config_internal.h"

namespace hdfs{

	class NameNode;
	
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
			FileSystemImpl (const FSKey& key, const Configuration& conf);                             /* constructor */
			~FileSystemImpl();

			/* ====================  OPERATORS     ======================================= */
			void connect();

		private:
			/* ====================  METHODS       ======================================= */

			/* ====================  DATA MEMBERS  ======================================= */
			FSKey _key;
			ConfigurationInternal _conf_inter;
			NameNode* _name_node;

	}; /* -----  end of class FileSystemImpl  ----- */

}

#endif
