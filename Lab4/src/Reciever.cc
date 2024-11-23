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

#include "Reciever.h"

Define_Module(Reciever);

void Reciever::initialize()
{
    // TODO - Generated method body
}

void Reciever::handleMessage(cMessage *msg)
{
    std::vector<std::bitset<8>> v;
    std::string msgString = msg->getName();

    for (int i = 0; i < msgString.size(); i += 8) {
        std::string bitString = msgString.substr(i, 8);

        std::bitset<8> bitset(bitString);

        v.push_back(bitset);
    }
    std::cout << "received:" << std::endl;

    for (int i=0 ; i < v.size() ; i++) {
        std::cout << v[i] << std::endl;
    }


    std::bitset<8> parityBitset;
    for (int i = 0; i < v.size()-1; i++) {
        parityBitset ^= v[i];
    }

    std::bitset<8> receivedParity = v.back();

    cMessage *reply;
    if (parityBitset == receivedParity) {

        int charCount = static_cast<int>(v[0].to_ulong());

       std::string message;

       for (size_t i = 1; i < v.size() - 1; i++) {
       message += static_cast<char>(v[i].to_ulong());
       }

        std::cout << "Parity check passed, original messsage: " <<message<< std::endl;
//        reply = new cMessage("correct");
    } else {
        std::cout << "Parity check failed" << std::endl;
//        reply = new cMessage("inorrect");

    }
//    send(reply, "port$o");

    delete msg;
}
