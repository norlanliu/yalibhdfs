/*
 * =====================================================================================
 *
 *       Filename:  net_base.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/18/2015 12:17:29 AM
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

#ifndef NET_NET_BASE_H_
#define NET_NET_BASE_H_

namespace hdfs{
	/*
	 * =====================================================================================
	 *        Class:  NetBase
	 *  Description:  Net base class 
	 * =====================================================================================
	 */
	class NetBase
	{
		public:
			/* ====================  LIFECYCLE     ======================================= */
			virtual ~NetBase (){}                        /* destructor */

			/* ====================  OPERATORS     ======================================= */

			/*
			 * Connect to a server with socket 
			 */
			virtual int Connect ( const char* host, const char* port, int timeout ) = 0;


			/* 
			 * ===  FUNCTION  ======================================================================
			 *         Name:  Close
			 *  Description:  close bufferevent
			 * =====================================================================================
			 */
			virtual void Close () = 0;

	}; /* -----  end of class NetBase  ----- */

}

#endif
