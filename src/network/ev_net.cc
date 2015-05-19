/*
 * =====================================================================================
 *
 *       Filename:  ev_net.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/18/2015 09:08:00 AM
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

#include "ev_net.h"

#include "error_code.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>

#include <event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>

namespace hdfs{
	static const int TIME_BASE = 1000;
	EVNet::EVNet():
		_ev_base(::event_base_new()), _buffer_event(NULL){
	}

	EVNet::~EVNet(){
		Close();
	}

	int EVNet::Connect ( const char* host, const char* port, int timeout ){
		assert(NULL != _ev_base);
		assert(NULL == _buffer_event);
		struct addrinfo hints, *results, *addr;
		int ret;
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = PF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		ret = ::getaddrinfo(host, port, &hints, &results);

		if(ret){
			return ErrorCode::EV_NET_RESOLVE_ADDREE_ERROR;
		}

		for(addr = results; NULL != addr; addr = addr->ai_next){
			ret = Connect(addr, timeout);
			if(_buffer_event != NULL)
				return ret;
		}
		return -1;
	}

	int EVNet::Connect ( struct addrinfo* addr, int timeout ){
		assert(NULL != _ev_base);
		assert(NULL == _buffer_event);
		int ret;
		int connected = 0;
		struct timeval tv;
		tv.tv_sec = timeout / TIME_BASE;
		tv.tv_usec = (timeout % TIME_BASE) * TIME_BASE;
		_buffer_event = ::bufferevent_socket_new(_ev_base, -1, BEV_OPT_CLOSE_ON_FREE);
		::bufferevent_setcb(_buffer_event, NULL, NULL, ConnectedEventCB, static_cast<void*>(&connected));
		::bufferevent_enable(_buffer_event, EV_READ | EV_WRITE | EV_PERSIST);
		::bufferevent_set_timeouts(_buffer_event, &tv, NULL);
		ret = ::bufferevent_socket_connect(_buffer_event, addr->ai_addr, addr->ai_addrlen);
		if(ret < 0){
			::bufferevent_free(_buffer_event);
			_buffer_event = NULL;
			return ErrorCode::EV_NET_SOCKET_CONNECT_ERROR ;
		}
		::event_base_dispatch(_ev_base);
		if(connected != 0)
			_buffer_event = NULL;
		::bufferevent_set_timeouts(_buffer_event, NULL, NULL);
		return connected;
	}
	void EVNet::ConnectedEventCB(struct bufferevent* bev, short events, void* arg){
		int* connected = static_cast<int*>(arg);
		if(events & BEV_EVENT_CONNECTED)
			*connected = 0;
		else if(events & BEV_EVENT_ERROR){
			*connected = ErrorCode::EV_NET_BEV_EVENT_ERROR;
			::bufferevent_free(bev);
		}else if(events & BEV_EVENT_TIMEOUT){
			*connected = ErrorCode::EV_NET_CONNECT_TIMEOUT_ERROR;
			::bufferevent_free(bev);
		}else{
			*connected = ErrorCode::EV_NET_BEV_EVENT_UNKNOWN_ERROR;
			::bufferevent_free(bev);
		}
	}
	void EVNet::Close(){
		if(_buffer_event != NULL){
			::bufferevent_free(_buffer_event);
			_buffer_event = NULL;
		}
	}
}
