/*
 * =====================================================================================
 *
 *       Filename:  common.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/19/2015 09:25:34 AM
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

#include "common.h"

#include <glog/logging.h>
#include <google/protobuf/message.h>

#include <event2/event.h>
#include <event2/thread.h>

#if !defined(LIBEVENT_VERSION_NUMBER) || LIBEVENT_VERSION_NUMBER < 0x02001400
#error "This version of Libevent is not supported; Get 2.0.14-alpha or later."
#endif

namespace hdfs{

void EventLogToGlog(int severity, const char *msg)
{
  switch (severity) {
    case _EVENT_LOG_DEBUG:
      VLOG(1) << msg;
      break;
    case _EVENT_LOG_MSG:
      LOG(INFO) << msg;
      break;
    case _EVENT_LOG_WARN:
      LOG(WARNING) << msg;
      break;
    case _EVENT_LOG_ERR:
      LOG(ERROR) << msg;
      break;
    default:
      LOG(ERROR) << msg;
      break;
  }
}

void ProtobufLogHandler(google::protobuf::LogLevel level, const char* filename, int line,
                        const std::string& message)
{
  google::LogMessage(filename, line, level).stream() << message;
}

void EventFatal(int err)
{
  LOG(FATAL) << "libevent2 fatal " << err;
}

void Initialize(int argc, char* argv[])
{
	CHECK_GT(argc, 0);
	CHECK_NOTNULL(argv);
  google::InitGoogleLogging(argv[0]);
  ::event_set_log_callback(hdfs::EventLogToGlog);
  google::protobuf::SetLogHandler(hdfs::ProtobufLogHandler);

#if EVTHREAD_USE_WINDOWS_THREADS_IMPLEMENTED
  CHECK_EQ(::evthread_use_windows_threads(), 0);
#elif EVTHREAD_USE_PTHREADS_IMPLEMENTED
  CHECK_EQ(::evthread_use_pthreads(), 0);
#endif


  CHECK_EQ(LIBEVENT_VERSION_NUMBER, ::event_get_version_number())
    << "libevent2 version number mismatch";
}

}
