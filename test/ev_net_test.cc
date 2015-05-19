/*
 * =====================================================================================
 *
 *       Filename:  TestEVNet.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/18/2015 10:48:11 PM
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
#include <stdio.h>
#include <memory>
#include "network/net_base.h"
#include "network/ev_net.h"
#include "common.h"

using namespace hdfs;

int main(int argc, char** argv){
	hdfs::Initialize(argc, argv);
	std::shared_ptr<NetBase> net(new EVNet());
	int ret = net->Connect("localhost", "9000", 6000);
	printf("%d\n", ret);
}
