#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "request.h"
#include "webserver.h"

#include <queue>

using namespace std;

/**
 * @file LoadBalancer.h
 * @brief Contains the LoadBalancer class declaration.
 */

/**
 * @class LoadBalancer
 * @brief Represents a load balancer for managing incoming requests.
 *
 * This class provides methods for adding and processing requests in a queue.
 */
class LoadBalancer {
public:
    /**
     * @brief Constructor for LoadBalancer.
     */
    LoadBalancer();

    /**
     * @brief Push a request into the load balancer's request queue.
     * @param request Pointer to the incoming request.
     */
    void pushRequest(Request* request);

    /**
     * @brief Pop a request from the load balancer's request queue.
     * @return A pointer to the popped request.
     */
    Request* popRequest();

    /**
     * @brief Get the time the load balancer has been running.
     * @return The time the load balancer has been running.
     */
    int getTimeRunning();

    /**
     * @brief Check if the request queue is empty.
     * @return True if the request queue is empty; otherwise, false.
     */
    bool isQueueEmpty();

    /**
     * @brief Get the size of the request queue.
     * @return The size of the request queue.
     */
    int getQueueSize();

    /**
     * @brief Increment the time the load balancer has been running.
     */
    void incrementTimeRunning();

private:
    queue<Request*> requestQueue; ///< @brief The queue of incoming requests.
    int time_running;             ///< @brief The time the load balancer has been running.
};

#endif
