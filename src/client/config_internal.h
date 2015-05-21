/*
 * =====================================================================================
 *
 *       Filename:  Config.h
 *
 *    Description:  Parse the configure file
 *
 *        Version:  1.0
 *        Created:  05/20/2015 06:52:20 PM
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

#ifndef CLIENT_CONFIG_INTERNAL_H_
#define CLIENT_CONFIG_INTERNAL_H_

#include <string>
#include "exception.h"
#include "exception_internal.h"

namespace hdfs{
	
	class Configuration;
	/*
	 * =====================================================================================
	 *        Class:  ConfigurationInternal
	 *  Description:  
	 * =====================================================================================
	 */
	class ConfigurationInternal
	{
		public:
			/* ====================  LIFECYCLE     ======================================= */
			ConfigurationInternal (const Configuration& conf);			/* constructor */

			 /*
			 * rpc configure
			 */

			int32_t getRpcConnectTimeout() const {
				return rpcConnectTimeout;
			}

			int32_t getRpcMaxIdleTime() const {
				return rpcMaxIdleTime;
			}

			int32_t getRpcMaxRetryOnConnect() const {
				return rpcMaxRetryOnConnect;
			}

			void setRpcMaxRetryOnConnect(int32_t rpcMaxRetryOnConnect) {
			  this->rpcMaxRetryOnConnect = rpcMaxRetryOnConnect;
			}

			int32_t getRpcPingTimeout() const {
				return rpcPingTimeout;
			}

			int32_t getRpcReadTimeout() const {
				return rpcReadTimeout;
			}

			bool isRpcTcpNoDelay() const {
				return rpcTcpNoDelay;
			}

			int32_t getRpcWriteTimeout() const {
				return rpcWriteTimeout;
			}

			/*
			 * FileSystem configure
			 */
			const std::string & getDefaultUri() const {
				return defaultUri;
			}

			int32_t getDefaultReplica() const {
				return defaultReplica;
			}

			int64_t getDefaultBlockSize() const {
				return defaultBlockSize;
			}

			/*
			 * InputStream configure
			 */
			int32_t getLocalReadBufferSize() const {
				return localReadBufferSize;
			}

			int32_t getInputReadTimeout() const {
				return inputReadTimeout;
			}

			int32_t getInputWriteTimeout() const {
				return inputWriteTimeout;
			}

			int32_t getInputConnTimeout() const {
				return inputConnTimeout;
			}

			int32_t getPrefetchSize() const {
				return prefetchSize;
			}

			bool isReadFromLocal() const {
				return readFromLocal;
			}

			int32_t getMaxGetBlockInfoRetry() const {
				return maxGetBlockInfoRetry;
			}

			int32_t getMaxLocalBlockInfoCacheSize() const {
				return maxLocalBlockInfoCacheSize;
			}

			/*
			 * OutputStream configure
			 */
			int32_t getDefaultChunkSize() const {
				return chunkSize;
			}

			int32_t getDefaultPacketSize() const {
				if (packetSize % chunkSize != 0) {
					THROW(HdfsConfigInvalid,
						  "output.default.packetsize should be larger than 0 "
						  "and be the multiple of output.default.chunksize.");
				}

				return packetSize;
			}

			int32_t getBlockWriteRetry() const {
				return blockWriteRetry;
			}

			int32_t getOutputConnTimeout() const {
				return outputConnTimeout;
			}

			int32_t getOutputReadTimeout() const {
				return outputReadTimeout;
			}

			int32_t getOutputWriteTimeout() const {
				return outputWriteTimeout;
			}

			bool canAddDatanode() const {
				return addDatanode;
			}

			int32_t getHeartBeatInterval() const {
				return heartBeatInterval;
			}

			int32_t getRpcMaxHaRetry() const {
				return rpcMaxHARetry;
			}

			void setRpcMaxHaRetry(int32_t rpcMaxHaRetry) {
				rpcMaxHARetry = rpcMaxHaRetry;
			}

			const std::string & getRpcAuthMethod() const {
				return rpcAuthMethod;
			}

			void setRpcAuthMethod(const std::string & rpcAuthMethod) {
				this->rpcAuthMethod = rpcAuthMethod;
			}

			const std::string & getKerberosCachePath() const {
				return kerberosCachePath;
			}

			void setKerberosCachePath(const std::string & kerberosCachePath) {
				this->kerberosCachePath = kerberosCachePath;
			}

			int32_t getRpcSocketLingerTimeout() const {
				return rpcSocketLingerTimeout;
			}

			void setRpcSocketLingerTimeout(int32_t rpcSocketLingerTimeout) {
				this->rpcSocketLingerTimeout = rpcSocketLingerTimeout;
			}


			int32_t getPacketPoolSize() const {
				return packetPoolSize;
			}

			void setPacketPoolSize(int32_t packetPoolSize) {
				this->packetPoolSize = packetPoolSize;
			}

			int32_t getCloseFileTimeout() const {
				return closeFileTimeout;
			}

			void setCloseFileTimeout(int32_t closeFileTimeout) {
				this->closeFileTimeout = closeFileTimeout;
			}

			int32_t getRpcTimeout() const {
				return rpcTimeout;
			}

			void setRpcTimeout(int32_t rpcTimeout) {
				this->rpcTimeout = rpcTimeout;
			}

			bool doesNotRetryAnotherNode() const {
				return notRetryAnotherNode;
			}

			void setIFNotRetryAnotherNode(bool notRetryAnotherNode) {
				this->notRetryAnotherNode = notRetryAnotherNode;
			}

			int32_t getMaxReadBlockRetry() const {
				return maxReadBlockRetry;
			}

			void setMaxReadBlockRetry(int32_t maxReadBlockRetry) {
				this->maxReadBlockRetry = maxReadBlockRetry;
			}

			bool doUseMappedFile() const {
				return useMappedFile;
			}

			void setUseMappedFile(bool useMappedFile) {
				this->useMappedFile = useMappedFile;
			}

			bool isLegacyLocalBlockReader() const {
				return legacyLocalBlockReader;
			}

			void setLegacyLocalBlockReader(bool legacyLocalBlockReader) {
				this->legacyLocalBlockReader = legacyLocalBlockReader;
			}

			const std::string& getDomainSocketPath() const {
				return domainSocketPath;
			}

			void setDomainSocketPath(const std::string& domainSocketPath) {
				this->domainSocketPath = domainSocketPath;
			}

			int32_t getMaxFileDescriptorCacheSize() const {
				return maxFileDescriptorCacheSize;
			}

			void setMaxFileDescriptorCacheSize(int32_t maxFileDescriptorCacheSize) {
				this->maxFileDescriptorCacheSize = maxFileDescriptorCacheSize;
			}

			int32_t getSocketCacheExpiry() const {
			  return socketCacheExpiry;
			}

			int32_t getSocketCacheCapacity() const {
			  return socketCacheCapacity;
			}

		public:
			/*
			 * rpc configure
			 */
			int32_t rpcMaxIdleTime;
			int32_t rpcPingTimeout;
			int32_t rpcConnectTimeout;
			int32_t rpcReadTimeout;
			int32_t rpcWriteTimeout;
			int32_t rpcMaxRetryOnConnect;
			int32_t rpcMaxHARetry;
			int32_t rpcSocketLingerTimeout;
			int32_t rpcTimeout;
			bool rpcTcpNoDelay;
			std::string rpcAuthMethod;

			/*
			 * FileSystem configure
			 */
			std::string defaultUri;
			std::string kerberosCachePath;
			int32_t defaultReplica;
			int64_t defaultBlockSize;

			/*
			 * InputStream configure
			 */
			bool useMappedFile;
			bool readFromLocal;
			bool notRetryAnotherNode;
			bool legacyLocalBlockReader;
			int32_t inputConnTimeout;
			int32_t inputReadTimeout;
			int32_t inputWriteTimeout;
			int32_t localReadBufferSize;
			int32_t maxFileDescriptorCacheSize;
			int32_t maxGetBlockInfoRetry;
			int32_t maxLocalBlockInfoCacheSize;
			int32_t maxReadBlockRetry;
			int32_t prefetchSize;
			int32_t socketCacheCapacity;
			int32_t socketCacheExpiry;
			std::string domainSocketPath;

			/*
			 * OutputStream configure
			 */
			bool addDatanode;
			int32_t chunkSize;
			int32_t packetSize;
			int32_t blockWriteRetry; //retry on block not replicated yet.
			int32_t outputConnTimeout;
			int32_t outputReadTimeout;
			int32_t outputWriteTimeout;
			int32_t packetPoolSize;
			int32_t heartBeatInterval;
			int32_t closeFileTimeout;
	}; /* -----  end of class ConfigurationInternal  ----- */

}

#endif
