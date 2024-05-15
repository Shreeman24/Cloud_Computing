#include "loadbalancer.h"

/**
 * @brief Constructor for LoadBalancer.
 *
 * Constructs the LoadBalancer object and sets time_running to 0.
 */
LoadBalancer::LoadBalancer() {
    this->time_running = 0;
}

/**
 * @brief Push a request into the load balancer's request queue.
 * @param request Pointer to the incoming request.
 */
void LoadBalancer::pushRequest(Request* request) {
    this->requestQueue.push(request);
}

/**
 * @brief Pop a request from the load balancer's request queue.
 * @return A pointer to the popped request, or nullptr if the queue is empty.
 */
Request* LoadBalancer::popRequest() {
    if (this->isQueueEmpty()) {
        return nullptr;
    }
    
    Request* frontRequest = this->requestQueue.front();
    this->requestQueue.pop();

    return frontRequest;
}

/**
 * @brief Get the time the load balancer has been running.
 * @return The time the load balancer has been running.
 */
int LoadBalancer::getTimeRunning() {
    return this->time_running;
}

/**
 * @brief Check if the request queue is empty.
 * @return True if the request queue is empty; otherwise, false.
 */
bool LoadBalancer::isQueueEmpty() {
    return this->requestQueue.empty();
}

/**
 * @brief Get the size of the request queue.
 * @return The size of the request queue.
 */
int LoadBalancer::getQueueSize() {
    return this->requestQueue.size();
}

/**
 * @brief Increment the time the load balancer has been running.
 */
void LoadBalancer::incrementTimeRunning() {
    this->time_running = this->time_running + 1;
}