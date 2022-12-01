class Client
{
private:
    Client() {}
    static Client *instance;
    int sock = 0; 
public:
    static Client *getInstance();
    void Connect(int port, const char *ip);
    void Send(const char *command);  
};
