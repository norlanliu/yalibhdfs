/*
 * =====================================================================================
 *
 *       Filename:  filesystem.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/21/2015 10:50:37 AM
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

#include "filesystem.h"

#include <stdlib.h>

#include <string>

#include "config_internal.h"
#include "filesystemimpl.h"
#include "fskey.h"

namespace hdfs{

	FileSystem::FileSystem(const Configuration& conf): _conf(conf),
		_fs_impl(NULL){
	}
	FileSystem::~FileSystem(){
		if(_fs_impl)
			delete _fs_impl;
	}

	void FileSystem::connect(){
		ConfigurationInternal ci(_conf);
		connect(ci.getDefaultUri().c_str(), NULL, NULL);
	}

	void FileSystem::connect(const char* uri, const char* username, const char* token){
		if(_fs_impl)
			return;

		try{
			std::string principal;
			if(username)
				principal = username;
			_fs_impl = InitialFSImpl(uri, principal);

			if(_fs_impl != NULL){
				TERMINATE(HdfsException, "File system create error");
			}

			_fs_impl->connect();
		}catch(...){

		}
	}

	FileSystemImpl* FileSystem::InitialFSImpl(const char* uri, const std::string& principal){
		if(NULL == uri || 0 == strlen(uri))
			return NULL;

		FSKey key(uri, principal.c_str());

		return new FileSystemImpl(key, _conf);
	}
}
