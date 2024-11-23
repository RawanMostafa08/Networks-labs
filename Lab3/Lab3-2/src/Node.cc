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

Define_Module(Node);

void Node::initialize()
{
    EV << "Starting Node " << getIndex() << endl;

    if (getIndex() == 0) {
            cMessage *explorationMsg = new cMessage("exploration");
            explorationMsg->setKind(1);
            send(explorationMsg, "out");
        }
}

void Node::handleMessage(cMessage *msg)
{
    if (strcmp(msg->getName(), "exploration") == 0) {
            int count = msg->getKind();

            if (getIndex() == 0) {
                EV << "Number of nodes in the network: " << count << endl;
                delete msg;
                endSimulation();
            } else {
                msg->setKind(count + 1);
                send(msg, "out");
            }
        }
}
