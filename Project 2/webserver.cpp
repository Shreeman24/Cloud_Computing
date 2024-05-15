#include "webserver.h"

#include <iostream>

/**
 * @brief Constructor for WebServer.
 * @param server_id The identifier for the server.
 */
WebServer::WebServer(char server_id) {
    this->server_id = server_id;
    this->request_start_time = 0;
}

/**
 * @brief Process an incoming request.
 * @param request Pointer to the incoming request.
 * @param current_cycle The current cycle of the server.
 */
void WebServer::processRequest(Request* request, int current_cycle) {
    this->request = request;
    this->request_start_time = current_cycle;
}

/**
 * @brief Get the server's identifier.
 * @return The server's identifier.
 */
char WebServer::getServerId() {
    return this->server_id;
}

/**
 * @brief Get the current request.
 * @return A pointer to the current request.
 */
Request* WebServer::newRequest() {
    return this->request;
}

/**
 * @brief Check if the request has been completed.
 * @param current_cycle The current cycle of the server.
 * @return True if the request is completed; otherwise, false.
 */
bool WebServer::requestCompleted(int current_cycle) {
    return (current_cycle >= (this->request->request_time + request_start_time));
}