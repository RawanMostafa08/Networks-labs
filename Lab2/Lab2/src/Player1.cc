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

#include "Player1.h"

Define_Module(Player1);

void Player1::initialize()
{
    num = par("number").intValue();
    EV << "Player1 generated the number " << num << endl;

    cMessage *startMsg = new cMessage("Start Guessing");
    send(startMsg, "out");
}

void Player1::handleMessage(cMessage *msg)
{
    int guess = atoi(msg->getName());

        if (guess == num) {
            EV << "Player1 received a correct guess from Player2 " << guess << endl;
            cMessage *response = new cMessage("correct guess");
            send(response, "out");
            delete msg;
        } else {
            EV << "Player1 received a wrong guess from Player2 " << guess << endl;
            cMessage *response = new cMessage("wrong guess");
            send(response, "out");
            delete msg;
        }
}
