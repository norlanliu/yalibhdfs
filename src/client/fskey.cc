/*
 * =====================================================================================
 *
 *       Filename:  fskey.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/21/2015 10:22:27 AM
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

#include "fskey.h"

#include <sstream>
#include <algorithm>

#include <libxml/uri.h>

#include "exception.h"
#include "exception_internal.h"

namespace hdfs{

	FSKey::FSKey (const std::string& uri, const char* user ){
		xmlURIPtr uriobj;
		std::stringstream ss;
		ss.imbue(std::locale::classic());
		uriobj = xmlParseURI(uri.c_str());

		try {
			if (!uriobj || uriobj->server == NULL || 0 == strlen(uriobj->server)) {
				THROW(InvalidParameter,
					  "Invalid input: uri: %s is not a valid URI type.", uri.c_str());
			}

			_host = uriobj->server;

			if (NULL == uriobj->scheme || 0 == strlen(uriobj->scheme)) {
				_scheme = "hdfs";
			} else {
				_scheme = uriobj->scheme;
			}

			if (strcasecmp(_scheme.c_str(), "hdfs")) {
				THROW(InvalidParameter,
					  "Invalid input: uri is not a valid URI type.");
			}

			if (user && strlen(user) > 0) {
				//user = User(u);
			} else if (NULL == uriobj->user || 0 == strlen(uriobj->user)) {
				_user = User::LocalUser();
			} else {
				//user = UserInfo(uriobj->user);
			}

			ss << _user.getClientUser();

			if (uriobj->port == 0) {
				ss << "@" << uriobj->server;
			} else {
				std::stringstream s;
				s.imbue(std::locale::classic());
				s << uriobj->port;
				_port = s.str();
				ss << "@" << uriobj->server << ":" << uriobj->port;
			}

			_authority = ss.str();
		} catch (...) {
			if (uriobj) {
				xmlFreeURI(uriobj);
			}

			throw;
		}

		xmlFreeURI(uriobj);
		std::transform(_authority.begin(), _authority.end(), _authority.begin(), tolower);
		std::transform(_scheme.begin(), _scheme.end(), _scheme.begin(), tolower);
	}
}
