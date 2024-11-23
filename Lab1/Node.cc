//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Node.h"
#include <string>

Define_Module(Node);

void Node::initialize()
{
    cMessage *msg= new cMessage("Hello from tic");
    if (strcmp(getName(),"Tic")==0){
        send(msg,"out");
    }
}

void Node::handleMessage(cMessage *msg)
{
    cMessage *reply;
        if (strcmp(getName(),"Toc")==0 && strcmp(msg->getName(),"Hello from tic")==0){
            reply= new cMessage("Hello from toc");

        } else  if (strcmp(getName(),"Tic")==0 && strcmp(msg->getName(),"Hello from toc")==0){
            reply= new cMessage("Tic_1");

        } else {
            if (msg->getId() - 1 <= 8)
                reply = new cMessage((std::string(getName()) + "_" + std::to_string(msg->getId() - 1)).c_str());
            else {
                reply = new cMessage((std::string("Goodbye from ") + getName()).c_str());
            }
        }

        if (msg->getId() - 1 == 11)
            {
            cancelAndDelete(reply);
            endSimulation();
            }

        send(reply,"out");

}


