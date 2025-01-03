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

#include "Hub.h"

Define_Module(Hub);

void Hub::initialize()
{
    scheduleAt(simTime() + exponential(2.0), new cMessage("self message"));
}

void Hub::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        cMessage *message = new cMessage("Hello from Hub");
        int n = getParentModule()->par("N").intValue();
        int m = int(uniform(0, n));
        EV << "Hub sends 'Hello from Hub' to Node " << m << endl;
        send(message, "port$o",m);
    } else {
        EV << "Hub received '" << msg->getName() << "' from " << msg->getSenderModule()->getFullName() << endl;
        scheduleAt(simTime() + exponential(2.0), new cMessage("self message"));

    }
}
