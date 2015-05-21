/*
 * =====================================================================================
 *
 *       Filename:  user.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/21/2015 10:10:04 AM
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

#include "user.h"

#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

#include <vector>

#include "exception.h"
#include "exception_internal.h"

namespace hdfs{


	void User::setClientUser(const std::string& user){
		this->_client_user = user;
	}
	User User::LocalUser(){
		User ret;
		uid_t uid, euid;
		long int buf_size;
		struct passwd pwd, epwd, *result = NULL;
		euid = geteuid();
		uid = getuid();

		if ((buf_size = sysconf(_SC_GETPW_R_SIZE_MAX)) == -1) {
			THROW(InvalidParameter,
				  "Invalid input: \"sysconf\" function failed to get the configure with key \"_SC_GETPW_R_SIZE_MAX\".");
		}

		std::vector<char> buffer(buf_size);

		if (getpwuid_r(uid, &pwd, &buffer[0], buf_size, &result) != 0 || !result) {
			THROW(InvalidParameter,
				  "Invalid input: real user name cannot be found with UID %u.",
				  uid);
		}

		ret.setClientUser(pwd.pw_name);
		return ret;

	}
}
