#include <thread>
#include <vector>
#include <string>

class Server
{
private:
    Server() {}
    static Server *instance;
    int server_fd, new_socket;
    int opt = 1;

public:
    std::vector<std::string> paths = {"/instrumentation/airspeed-indicator/indicated-speed-kt", "/sim/time/warp", "/controls/switches/magnetos", "/instrumentation/heading-indicator/offset-deg", "/instrumentation/altimeter/indicated-altitude-ft", "/instrumentation/altimeter/pressure-alt-ft", "/instrumentation/attitude-indicator/indicated-pitch-deg", "/instrumentation/attitude-indicator/indicated-roll-deg", "/instrumentation/attitude-indicator/internal-pitch-deg", "/instrumentation/attitude-indicator/internal-roll-deg", "/instrumentation/encoder/indicated-altitude-ft", "/instrumentation/encoder/pressure-alt-ft", "/instrumentation/gps/indicated-altitude-ft", "/instrumentation/gps/indicated-ground-speed-kt", "/instrumentation/gps/indicated-vertical-speed", "/instrumentation/heading-indicator/indicated-heading-deg", "/instrumentation/magnetic-compass/indicated-heading-deg", "/instrumentation/slip-skid-ball/indicated-slip-skid", "/instrumentation/turn-indicator/indicated-turn-rate", "/instrumentation/vertical-speed-indicator/indicated-speed-fpm", "/controls/flight/aileron", "/controls/flight/elevator", "/controls/flight/rudder", "/controls/flight/flaps", "/controls/engines/engine/throttle", "/controls/engines/current-engine/throttle", "/controls/switches/master-avionics", "/controls/switches/starter", "/engines/active-engine/auto-start", "/controls/flight/speedbrake", "/sim/model/c172p/brake-parking", "/controls/engines/engine/primer", "/controls/engines/current-engine/mixture", "/controls/switches/master-bat", "/controls/switches/master-alt", "/engines/engine/rpm"};
    void SplitLine(std::string s, std::vector<double> &values);
    void ListeningToSimulator();
    void launchFG();
    std::thread t1;
    std::thread t2;
    void Connect(int port, const char *ip);
    static Server *getInstance();
};
