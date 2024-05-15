#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <cstdlib>
#include <string>

#include "request.h"

using namespace std;

/**
 * @file WebServer.h
 * @brief Contains the WebServer class declaration.
 */

/**
 * @class WebServer
 * @brief Represents a web server.
 *
 * This class handles incoming requests and provides methods for processing requests
 * and checking their completion status.
 */
class WebServer {
public:
    /**
     * @brief Constructor for WebServer.
     * @param server_id The identifier for the server.
     */
    WebServer(char server_id);

    /**
     * @brief Process an incoming request.
     * @param request Pointer to the incoming request.
     * @param current_cycle The current cycle of the server.
     */
    void processRequest(Request* request, int current_cycle);

    /**
     * @brief Get the server's identifier.
     * @return The server's identifier.
     */
    char getServerId();

    /**
     * @brief Create a new request.
     * @return A pointer to the newly created request.
     */
    Request* newRequest();

    /**
     * @brief Check if the request has been completed.
     * @param current_cycle The current cycle of the server.
     * @return True if the request is completed; otherwise, false.
     */
    bool requestCompleted(int current_cycle);

private:
    Request* request;           ///< @brief Pointer to the current request.
    int request_start_time;     ///< @brief The start time of the current request.
    char server_id;             ///< @brief The server's identifier.
};

#endif