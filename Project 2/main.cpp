#include "loadbalancer.h"
#include "request.h"

#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>
#include <unistd.h>

using namespace std;

const int serverChar = 65;
const int newRequestModifier = 15;
const int minRequestRuntime = 3;
const int maxRequestRuntime = 500;
const int requestMax = 10;
const int requestMin = 5;

/**
 * @brief Create a random new request with a random request time.
 * @return A pointer to the newly created Request.
 */
Request* createRandomNewRequest() {
    Request* newRequest = new Request();
    newRequest->request_time = minRequestRuntime + (rand() % (maxRequestRuntime - minRequestRuntime + 1));
    return newRequest;
}

int main() {

    srand(time(0));

    int serverCount = 0;
    int loadBalancerCycles = 0;
    int requestsGenerated = 0;

    int fileId = 1;
    string logFileName = "LogFile" + to_string(fileId) + ".txt";

    // File should exist and allow read permission
    while (access(logFileName.c_str(), R_OK) == 0) {
        fileId = fileId + 1;
        logFileName = "LogFile" + std::to_string(fileId) + ".txt";
    }

    // Output stream for log file always starts with an empty file
    ofstream ofs(logFileName, ios::out | ios::trunc);

    std::cout << "How many servers?: ";
    cin >> serverCount;
    std::cout << "How much time to run load balancer?: ";
    cin >> loadBalancerCycles;

    ofs << "There will be " << serverCount << " servers running for " << loadBalancerCycles << " clock cycles" << endl;

    LoadBalancer* loadBalancer = new LoadBalancer();

    // Pushed a full queue of requests
    int requestQueueSize = serverCount * 5; // specified in the project description
    for (int i = 0; i < requestQueueSize; i++) {
        Request* randomRequest = createRandomNewRequest();
        loadBalancer->pushRequest(randomRequest);
    }

    ofs << "The request queue size to start with is " << loadBalancer->getQueueSize() << endl;
    ofs << endl;

    int requestsDiscarded = 0;
    int requestsProcessed = 0;

    // Will manage and access currServers readily using vector
    vector<WebServer*> webServers(serverCount, nullptr);
    for (int i = 0; i < serverCount; i++) {
        char serverId = char(serverChar + i);
        WebServer* newServer = new WebServer(serverId);
        ofs << "A server " << serverId << " has been added." << endl;
        newServer->processRequest(loadBalancer->popRequest(), loadBalancer->getTimeRunning());
        webServers[i] = newServer;
    }

    int activeServers = serverCount;
    
    int minTaskTime = webServers[0]->newRequest()->request_time;
    int maxTaskTime = webServers[0]->newRequest()->request_time;

    // Implement load balancing for the currentTime specified by the user

    while (loadBalancer->getTimeRunning() < loadBalancerCycles) {
        for (int i = 0; i < webServers.size(); i++) {

            int currentTime = loadBalancer->getTimeRunning();

            WebServer* currServer = webServers[i];

            // Request processed when request exists and is complete
            if (currServer->newRequest() != nullptr && currServer->requestCompleted(currentTime)) {
                Request* request = currServer->newRequest();

                if (request->request_time < minTaskTime) {
                    minTaskTime = request->request_time;
                } else if (request->request_time > maxTaskTime) {
                    maxTaskTime = request->request_time;
                }

                ofs << "A request from IP " << request->ip_in << " has been processed by server " << currServer->getServerId() << " at time " << currentTime << std::endl;
                
                requestsProcessed++;
                
                // Load the current server with a new request
                currServer->processRequest(loadBalancer->popRequest(), currentTime);
                
                loadBalancer->incrementTimeRunning();

            } else if (currServer->newRequest() == nullptr) { // server has no request or is waiting on a request
                currServer->processRequest(loadBalancer->popRequest(), currentTime);
                requestsProcessed++;
                loadBalancer->incrementTimeRunning();
            } 

            if (rand() % newRequestModifier == 0) { // randomly generates requests
                if (loadBalancer->getQueueSize() < requestMax) {
                    loadBalancer->pushRequest(createRandomNewRequest());    
                } else if (loadBalancer->getQueueSize() >= requestMax) {
                    ofs << "A new request has been discarded." << endl;
                    requestsDiscarded++;
                }                
            }

            if (loadBalancer->getQueueSize() == requestMax) { // max requests require one extra server
                char serverId = char(serverChar + i);
                WebServer* newServer = new WebServer(serverId);
                ofs << "A server " << serverId << " has been added." << endl;
                newServer->processRequest(loadBalancer->popRequest(), loadBalancer->getTimeRunning());
                webServers[i] = newServer;
            }

            if ((loadBalancer->getQueueSize() < requestMin) || (loadBalancer->getQueueSize() < activeServers)) {
                // Generate more requests automatically
                for (int i = 0; i < requestQueueSize; i++) {
                    Request* randomRequest = createRandomNewRequest();
                    loadBalancer->pushRequest(randomRequest);
                }

                // Pop the last server
                WebServer* webServer = webServers.back();
                webServers.pop_back();
                ofs << "A server " << webServer->getServerId() << " has been deleted." << endl;
                activeServers--;
            }

            if (webServers.size() == 0) {
                for (int i = 0; i < serverCount; i++) {
                    char serverId = char(serverChar + i);
                    WebServer* newServer = new WebServer(serverId);
                    ofs << "A server " << serverId << " has been added." << endl;
                    newServer->processRequest(loadBalancer->popRequest(), loadBalancer->getTimeRunning());
                    webServers[i] = newServer;
                }
                activeServers += serverCount;
            }

            loadBalancer->incrementTimeRunning();
        }
    }

    ofs << std::endl << "Number of active servers: " << to_string(activeServers) << endl;
    ofs << "Number of requests in the queue (current): " << to_string(loadBalancer->getQueueSize()) << endl;
    ofs << "Number of total discarded requests: " << to_string(requestsDiscarded) << endl;
    ofs << "Number of total processed requests: " << to_string(requestsProcessed) << endl;
    ofs << "Range of task times: [" << minTaskTime << ", " << maxTaskTime << "]" << endl;

    return 0;
}
