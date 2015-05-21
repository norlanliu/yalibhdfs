/*
 * =====================================================================================
 *
 *       Filename:  namenodeinfo.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/21/2015 08:50:20 PM
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

/********************************************************************
 * Copyright (c) 2013 - 2014, Pivotal Inc.
 * All rights reserved.
 *
 * Author: Zhanwei Wang
 ********************************************************************/
/********************************************************************
 * 2014 -
 * open source under Apache License Version 2.0
 ********************************************************************/
/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _HDFS_LIBHDFS_SERVER_NAMENODEINFO_H_
#define _HDFS_LIBHDFS_SERVER_NAMENODEINFO_H_

#include <string>
#include <vector>

namespace hdfs {

class Configuration;

class NamenodeInfo {
public:
    NamenodeInfo();

    const std::string & getHttpAddr() const {
        return _http_addr;
    }

    void setHttpAddr(const std::string & httpAddr) {
        _http_addr = httpAddr;
    }

    const std::string & getRpcAddr() const {
        return _rpc_addr;
    }

    void setRpcAddr(const std::string & rpcAddr) {
        _rpc_addr = rpcAddr;
    }

    static std::vector<NamenodeInfo> GetHANamenodeInfo(const std::string & service, const Configuration & conf);

private:
    std::string _rpc_addr;
    std::string _http_addr;
};

}

#endif /* _HDFS_LIBHDFS_SERVER_NAMENODEINFO_H_ */

