/*
 * =====================================================================================
 *
 *       Filename:  configuration.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/20/2015 07:22:15 PM
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

#include "configuration.h"

#include <cassert>
#include <errno.h>
#include <fstream>
#include <limits>
#include <string.h>
#include <unistd.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "exception.h"
#include "exception_internal.h"

namespace hdfs{
typedef std::map<std::string, std::string>::const_iterator Iterator;
typedef std::map<std::string, std::string> Map;

static int32_t StrToInt32(const char * str) {
    long retval;
    char * end = NULL;
    errno = 0;
    retval = strtol(str, &end, 0);

    if (EINVAL == errno || 0 != *end) {
        THROW(HdfsBadNumFormat, "Invalid int32_t type: %s", str);
    }

    if (ERANGE == errno || retval > std::numeric_limits<int32_t>::max()
            || retval < std::numeric_limits<int32_t>::min()) {
        THROW(HdfsBadNumFormat, "Underflow/Overflow int32_t type: %s", str);
    }

    return static_cast<int32_t>(retval);
}

static int64_t StrToInt64(const char * str) {
    long long retval;
    char * end = NULL;
    errno = 0;
    retval = strtoll(str, &end, 0);

    if (EINVAL == errno || 0 != *end) {
        THROW(HdfsBadNumFormat, "Invalid int64_t type: %s", str);
    }

    if (ERANGE == errno || retval > std::numeric_limits<int64_t>::max()
            || retval < std::numeric_limits<int64_t>::min()) {
        THROW(HdfsBadNumFormat, "Underflow/Overflow int64_t type: %s", str);
    }

    return retval;
}

static bool StrToBool(const char * str) {
    bool retval = false;

    if (!strcasecmp(str, "true") || !strcmp(str, "1")) {
        retval = true;
    } else if (!strcasecmp(str, "false") || !strcmp(str, "0")) {
        retval = false;
    } else {
        THROW(HdfsBadNumFormat, "Invalid bool type: %s", str);
    }

    return retval;
}

static double StrToDouble(const char * str) {
    double retval;
    char * end = NULL;
    errno = 0;
    retval = strtod(str, &end);

    if (EINVAL == errno || 0 != *end) {
        THROW(HdfsBadNumFormat, "Invalid double type: %s", str);
    }

    if (ERANGE == errno || retval > std::numeric_limits<double>::max()
            || retval < std::numeric_limits<double>::min()) {
        THROW(HdfsBadNumFormat, "Underflow/Overflow int64_t type: %s", str);
    }

    return retval;
}

static void readConfigItem(xmlNodePtr root, Map & kv, const char * path) {
    std::string key, value;
    xmlNodePtr curNode;
    bool hasname = false, hasvalue = false;

    for (curNode = root; NULL != curNode; curNode = curNode->next) {
        if (curNode->type != XML_ELEMENT_NODE) {
            continue;
        }

        if (!hasname && !strcmp(reinterpret_cast<const char *>(curNode->name), "name")) {
            if (NULL != curNode->children
                    && XML_TEXT_NODE == curNode->children->type) {
                key = reinterpret_cast<const char *>(curNode->children->content);
                hasname = true;
            }
        } else if (!hasvalue
                   && !strcmp(reinterpret_cast<const char *>(curNode->name), "value")) {
            if (NULL != curNode->children
                    && XML_TEXT_NODE == curNode->children->type) {
                value = reinterpret_cast<const char *>(curNode->children->content);
                hasvalue = true;
            }
        } else {
            continue;
        }
    }

    if (hasname && hasvalue) {
        kv[key] = value;
        return;
    } else if (hasname) {
        kv[key] = "";
        return;
    }

    THROW(HdfsBadConfigFormat, "Configuration cannot parse configure file: \"%s\"",
          path);
}

static void readConfigItems(xmlDocPtr doc, Map & kv, const char * path) {
    xmlNodePtr root, curNode;
    root = xmlDocGetRootElement(doc);

    if (NULL == root || strcmp(reinterpret_cast<const char *>(root->name), "configuration")) {
        THROW(HdfsBadConfigFormat, "Configuration cannot parse configure file: \"%s\"",
              path);
    }

    /*
     * for each property
     */
    for (curNode = root->children; NULL != curNode; curNode = curNode->next) {
        if (curNode->type != XML_ELEMENT_NODE) {
            continue;
        }

        if (strcmp(reinterpret_cast<const char *>(curNode->name), "property")) {
            THROW(HdfsBadConfigFormat,
                  "Configuration cannot parse configure file: \"%s\"", path);
        }

        readConfigItem(curNode->children, kv, path);
    }
}

Configuration::Configuration(const char * p) :
    path(p) {
    update(p);
}

void Configuration::update(const char * p) {
    char msg[64];
    xmlDocPtr doc; /* the resulting document tree */
    LIBXML_TEST_VERSION
    kv.clear();
    path = p;

    if (access(path.c_str(), R_OK)) {
        strerror_r(errno, msg, sizeof(msg));
        THROW(HdfsBadConfigFormat, "Cannot read configure file: \"%s\", %s",
              path.c_str(), msg);
    }

    /* parse the file */
    doc = xmlReadFile(path.c_str(), NULL, 0);

    try {
        /* check if parsing succeeded */
        if (doc == NULL) {
            THROW(HdfsBadConfigFormat,
                  "Configuration cannot parse configure file: \"%s\"", path.c_str());
        } else {
            readConfigItems(doc, kv, path.c_str());
            /* free up the resulting document */
            xmlFreeDoc(doc);
        }
    } catch (...) {
        xmlFreeDoc(doc);
        throw;
    }
}

const char * Configuration::getString(const char * key) const {
    Iterator it = kv.find(key);

    if (kv.end() == it) {
        THROW(HdfsConfigNotFound, "Configuration key: %s not found", key);
    }

    return it->second.c_str();
}

const char * Configuration::getString(const char * key, const char * def) const {
    Iterator it = kv.find(key);

    if (kv.end() == it) {
        return def;
    } else {
        return it->second.c_str();
    }
}

const char * Configuration::getString(const std::string & key) const {
    return getString(key.c_str());
}

const char * Configuration::getString(const std::string & key,
                               const std::string & def) const {
    return getString(key.c_str(), def.c_str());
}

int64_t Configuration::getInt64(const char * key) const {
    int64_t retval;
    Iterator it = kv.find(key);

    if (kv.end() == it) {
        THROW(HdfsConfigNotFound, "Configuration key: %s not found", key);
    }

    try {
        retval = StrToInt64(it->second.c_str());
    } catch (const HdfsBadNumFormat & e) {
        TERMINATE(HdfsConfigNotFound, "Configuration key: %s not found", key);
    }

    return retval;
}

int64_t Configuration::getInt64(const char * key, int64_t def) const {
    int64_t retval;
    Iterator it = kv.find(key);

    if (kv.end() == it) {
        return def;
    }

    try {
        retval = StrToInt64(it->second.c_str());
    } catch (const HdfsBadNumFormat & e) {
        TERMINATE(HdfsConfigNotFound, "Configuration key: %s not found", key);
    }

    return retval;
}

int32_t Configuration::getInt32(const char * key) const {
    int32_t retval;
    Iterator it = kv.find(key);

    if (kv.end() == it) {
        THROW(HdfsConfigNotFound, "Configuration key: %s not found", key);
    }

    try {
        retval = StrToInt32(it->second.c_str());
    } catch (const HdfsBadNumFormat & e) {
        TERMINATE(HdfsConfigNotFound, "Configuration key: %s not found", key);
    }

    return retval;
}

int32_t Configuration::getInt32(const char * key, int32_t def) const {
    int32_t retval;
    Iterator it = kv.find(key);

    if (kv.end() == it) {
        return def;
    }

    try {
        retval = StrToInt32(it->second.c_str());
    } catch (const HdfsBadNumFormat & e) {
        TERMINATE(HdfsConfigNotFound, "Configuration key: %s not found", key);
    }

    return retval;
}

double Configuration::getDouble(const char * key) const {
    double retval;
    Iterator it = kv.find(key);

    if (kv.end() == it) {
        THROW(HdfsConfigNotFound, "Configuration key: %s not found", key);
    }

    try {
        retval = StrToDouble(it->second.c_str());
    } catch (const HdfsBadNumFormat & e) {
        TERMINATE(HdfsConfigNotFound, "Configuration key: %s not found", key);
    }

    return retval;
}

double Configuration::getDouble(const char * key, double def) const {
    double retval;
    Iterator it = kv.find(key);

    if (kv.end() == it) {
        return def;
    }

    try {
        retval = StrToDouble(it->second.c_str());
    } catch (const HdfsBadNumFormat & e) {
        TERMINATE(HdfsConfigNotFound, "Configuration key: %s not found", key);
    }

    return retval;
}

bool Configuration::getBool(const char * key) const {
    bool retval;
    Iterator it = kv.find(key);

    if (kv.end() == it) {
        THROW(HdfsConfigNotFound, "Configuration key: %s not found", key);
    }

    try {
        retval = StrToBool(it->second.c_str());
    } catch (const HdfsBadNumFormat & e) {
        TERMINATE(HdfsConfigNotFound, "Configuration key: %s not found", key);
    }

    return retval;
}

bool Configuration::getBool(const char * key, bool def) const {
    bool retval;
    Iterator it = kv.find(key);

    if (kv.end() == it) {
        return def;
    }

    try {
        retval = StrToBool(it->second.c_str());
    } catch (const HdfsBadNumFormat & e) {
        TERMINATE(HdfsConfigNotFound, "Configuration key: %s not found", key);
    }

    return retval;
}


}
