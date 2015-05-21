/*
 * =====================================================================================
 *
 *       Filename:  configuration.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/20/2015 07:10:59 PM
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

#ifndef CLIENT_CONFIGURATION_H_
#define CLIENT_CONFIGURATION_H_

#include <stdint.h>
#include <string>
#include <map>
#include <sstream>

namespace hdfs{

	/*
	 * =====================================================================================
	 *        Class:  Configuration
	 *  Description:  parser xml file
	 * =====================================================================================
	 */
	class Configuration
	{
		public:
			/* ====================  LIFECYCLE     ======================================= */
			Configuration (const char* path);			/* constructor */

			 /**
			 * Parse the configure file.
			 * @throw HdfsBadConfigFoumat
			 */
			void update(const char * path);

			/**
			 * Get a string with given configure key.
			 * @param key The key of the configure item.
			 * @return The value of configure item.
			 * @throw HdfsConfigNotFound
			 */
			const char * getString(const char * key) const;

			/**
			 * Get a string with given configure key.
			 * Return the default value def if key is not found.
			 * @param key The key of the configure item.
			 * @param def The defalut value.
			 * @return The value of configure item.
			 */
			const char * getString(const char * key, const char * def) const;

			/**
			 * Get a string with given configure key.
			 * @param key The key of the configure item.
			 * @return The value of configure item.
			 * @throw HdfsConfigNotFound
			 */
			const char * getString(const std::string & key) const;

			/**
			 * Get a string with given configure key.
			 * Return the default value def if key is not found.
			 * @param key The key of the configure item.
			 * @param def The defalut value.
			 * @return The value of configure item.
			 */
			const char * getString(const std::string & key,
								   const std::string & def) const;

			/**
			 * Get a 64 bit integer with given configure key.
			 * @param key The key of the configure item.
			 * @return The value of configure item.
			 * @throw HdfsConfigNotFound
			 */
			int64_t getInt64(const char * key) const;

			/**
			 * Get a 64 bit integer with given configure key.
			 * Return the default value def if key is not found.
			 * @param key The key of the configure item.
			 * @param def The defalut value.
			 * @return The value of configure item.
			 */
			int64_t getInt64(const char * key, int64_t def) const;

			/**
			 * Get a 32 bit integer with given configure key.
			 * @param key The key of the configure item.
			 * @return The value of configure item.
			 * @throw HdfsConfigNotFound
			 */
			int32_t getInt32(const char * key) const;

			/**
			 * Get a 32 bit integer with given configure key.
			 * Return the default value def if key is not found.
			 * @param key The key of the configure item.
			 * @param def The defalut value.
			 * @return The value of configure item.
			 */
			int32_t getInt32(const char * key, int32_t def) const;

			/**
			 * Get a double with given configure key.
			 * @param key The key of the configure item.
			 * @return The value of configure item.
			 * @throw HdfsConfigNotFound
			 */
			double getDouble(const char * key) const;

			/**
			 * Get a double with given configure key.
			 * Return the default value def if key is not found.
			 * @param key The key of the configure item.
			 * @param def The defalut value.
			 * @return The value of configure item.
			 */
			double getDouble(const char * key, double def) const;

			/**
			 * Get a boolean with given configure key.
			 * @param key The key of the configure item.
			 * @return The value of configure item.
			 * @throw HdfsConfigNotFound
			 */
			bool getBool(const char * key) const;

			/**
			 * Get a boolean with given configure key.
			 * Return the default value def if key is not found.
			 * @param key The key of the configure item.
			 * @param def The default value.
			 * @return The value of configure item.
			 */
			bool getBool(const char * key, bool def) const;

			/**
			 * Set a configure item
			 * @param key The key will set.
			 * @param value The value will be set to.
			 */
			template<typename T>
			void set(const char * key, T const & value) {
				std::stringstream ss;
				ss.imbue(std::locale::classic());
				ss << value;
				kv[key] = ss.str();
			}

		private:
			std::string path;
			std::map<std::string, std::string> kv;

	}; /* -----  end of class Configuration  ----- */
}
#endif
