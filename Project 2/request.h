#ifndef REQUEST_H
#define REQUEST_H

#include <cstdlib>
#include <string>

using namespace std;

/**
 * @file Request.h
 * @brief Contains the Request struct definition.
 */

/**
 * @struct Request
 * @brief Represents an incoming request.
 */
struct Request {
    string ip_in;         ///< @brief The IP address of the incoming request.
    int request_time;     ///< @brief The time of the incoming request.
};

#endif