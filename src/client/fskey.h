/*
 * =====================================================================================
 *
 *       Filename:  fskey.h
 *
 *    Description:  filesystem connection key
 *
 *        Version:  1.0
 *        Created:  05/21/2015 09:21:37 AM
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

#ifndef CLIENT_FSKEY_H_
#define CLIENT_FSKEY_H_
#include <string>
#include "user.h"

namespace hdfs{
	
	/*
	 * =====================================================================================
	 *        Class:  FSKey
	 *  Description:  
	 * =====================================================================================
	 */
	class FSKey
	{
		public:
			/* ====================  LIFECYCLE     ======================================= */
			FSKey (const std::string& uri, const char* user );                             /* constructor */

			/* ====================  ACCESSORS     ======================================= */
			const std::string getHost() const{
				return _host;
			}

			const std::string getPort() const{
				return _port;
			}

			const std::string getScheme() const{
				return _scheme;
			}
			/* ====================  MUTATORS      ======================================= */

			/* ====================  OPERATORS     ======================================= */

		private:
			/* ====================  DATA MEMBERS  ======================================= */
			std::string _authority; //authrity string
			std::string _port;
			std::string _host;
			std::string _scheme;
			User _user;

	}; /* -----  end of class FSKey  ----- */

}

#endif
