/*
 * =====================================================================================
 *
 *       Filename:  user.h
 *
 *    Description:  user 
 *
 *        Version:  1.0
 *        Created:  05/21/2015 09:48:47 AM
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

#ifndef CLIENT_USER_H_
#define CLIENT_USER_H_

#include <string>

namespace hdfs{
	
	/*
	 * =====================================================================================
	 *        Class:  User
	 *  Description:  
	 * =====================================================================================
	 */
	class User
	{
		public:
			/* ====================  LIFECYCLE     ======================================= */
			User ();                             /* constructor */

			/* ====================  ACCESSORS     ======================================= */
			void setClientUser(const std::string& user);

			const std::string& getClientUser() const{
				return _client_user;
			}

			/* ====================  MUTATORS      ======================================= */

			/* ====================  OPERATORS     ======================================= */

			static User LocalUser();

		private:
			/* ====================  DATA MEMBERS  ======================================= */
			std::string _client_user;

	}; /* -----  end of class User  ----- */

}

#endif
