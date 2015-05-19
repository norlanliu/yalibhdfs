/*
 * =====================================================================================
 *
 *       Filename:  ev_net.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/18/2015 12:36:36 AM
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


#ifndef  NET_EV_NET_H_
#define  NET_EV_NET_H_

#include "net_base.h"

struct event_base;
struct bufferevent;
struct addrinfo;

namespace hdfs{

/*
 * =====================================================================================
 *        Class:  EVNet
 *  Description:  data-transfering class with libevent
 * =====================================================================================
 */
class EVNet : public NetBase
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		EVNet ();                             /* constructor */
		virtual ~EVNet ();                    /* destructor */

		/* ====================  OPERATORS     ======================================= */
		int Connect ( const char* host, const char* port, int timeout );

		int Connect ( struct addrinfo* addr, int timeout );

		void Close();

	private:
		/* ====================  METHODS       ======================================= */
		static void ConnectedEventCB(struct bufferevent* bev, short events, void* arg);

		/* ====================  DATA MEMBERS  ======================================= */
		struct event_base* _ev_base;
		struct bufferevent* _buffer_event;

}; /* -----  end of class EVNet  ----- */


}
#endif   /* ----- #ifndef NET_EV_NET_H_----- */
