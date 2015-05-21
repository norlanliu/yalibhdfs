/*
 * =====================================================================================
 *
 *       Filename:  stringutil.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/21/2015 09:01:03 PM
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

#ifndef UTILITY_STRING_UTIL_H_
#define UTILITY_STRING_UTIL_H_

#include <string.h>
#include <string>
#include <vector>
#include <cctype>

namespace hdfs {

static inline std::vector<std::string> StringSplit(const std::string & str,
        const char * sep) {
    char * token, *lasts = NULL;
    std::string s = str;
    std::vector<std::string> retval;
    token = strtok_r(&s[0], sep, &lasts);

    while (token) {
        retval.push_back(token);
        token = strtok_r(NULL, sep, &lasts);
    }

    return retval;
}

static inline std::string StringTrim(const std::string & str) {
    int start = 0, end = str.length();

    for (; start < static_cast<int>(str.length()); ++start) {
        if (!std::isspace(str[start])) {
            break;
        }
    }

    for (; end > 0; --end) {
        if (!std::isspace(str[end - 1])) {
            break;
        }
    }

    return str.substr(start, end - start);
}

}
#endif
