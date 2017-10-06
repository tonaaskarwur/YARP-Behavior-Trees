#ifndef YARPCONDITIONNODE_H
#define YARPCONDITIONNODE_H

#include <condition_node.h>
#include <yarp/os/all.h>
#include <stdio.h>

using namespace yarp::os;


namespace BT
{
class YARPConditionNode : public BT::ConditionNode
{
public:
    YARPConditionNode(std::string name, const char *yarp_client_name, const char *yarp_server_name);
    ~YARPConditionNode();
    BT::ReturnStatus Tick();
private:
    Network yarp_;
    yarp::os::Port port_;
    const char* client_name_;
    const char* server_name_;
    BTCmd action_server_;

};
}

#endif
