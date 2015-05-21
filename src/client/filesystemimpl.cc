/*
 * =====================================================================================
 *
 *       Filename:  filesystemimpl.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/21/2015 11:27:40 AM
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

#include "filesystemimpl.h"

#include <stdlib.h>

#include <sstream>
#include <locale>

#include "hdfs/namenodeinfo.h"

namespace hdfs{

	FileSystemImpl::FileSystemImpl (const FSKey& key, const Configuration& conf):
		_key(key), _conf_inter(conf), _name_node(NULL){
	}
	FileSystemImpl::~FileSystemImpl(){

	}

	void FileSystemImpl::connect(){
		std::string host, port, uri, token;
		std::vector<NamenodeInfo> namenode_infos;
		if(_name_node){
			return;
		}

		host = _key.getHost();
		port = _key.getPort();
		uri += _key.getScheme() + "://" + host;

		if(port.empty()){

		}else{
			std::stringstream ss;
			ss.imbue(std::locale::classic());
			ss << host << ":" << port;
			namenode_infos.resize(1);
			namenode_infos[0].setRpcAddr(ss.str());
			token = namenode_infos[0].getRpcAddr();
		}
	}
}
