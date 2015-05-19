/*
 * =====================================================================================
 *
 *       Filename:  error_code.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/18/2015 08:41:04 AM
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


#ifndef  UTILITY_ERROR_CODE_H_
#define  UTILITY_ERROR_CODE_H_

namespace hdfs{


/*
 * =====================================================================================
 *        Class:  ErrorCode
 *  Description:  Error code class
 * =====================================================================================
 */
class ErrorCode
{
	public:

		//Net base
		const static int EV_NET_RESOLVE_ADDREE_ERROR = -1000;
		const static int EV_NET_SOCKET_CONNECT_ERROR = -1001;
		const static int EV_NET_CONNECT_TIMEOUT_ERROR	 = -1002;
		const static int EV_NET_BEV_EVENT_ERROR		 = -1003;
		const static int EV_NET_BEV_EVENT_UNKNOWN_ERROR = -1004;
}; /* -----  end of class ErrorCode  ----- */

}
#endif   /* ----- #ifndef UTILITY_ERROR_CODE_H_  ----- */
