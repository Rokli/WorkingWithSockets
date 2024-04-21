#ifndef WORKINGWITHSERVER_H
#define WORKINGWITHSERVER_H
#include <sys/socket.h>
#include <sys/types.h>
class WorkingWtihServer{
public:
    void Start(){
        int s = socket(PF_INET,SOCK_STREAM,0);
    }
};

#endif // WORKINGWITHSERVER_H
