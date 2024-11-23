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

#include "Receiver.h"
#include "MyMessage_m.h"

Define_Module(Receiver);

void Receiver::initialize()
{
    // TODO - Generated method body
}

void Receiver::handleMessage(cMessage *msg)
{
    MyMessage_Base *mymsg = check_and_cast<MyMessage_Base *>(msg);


    char charCount= mymsg->getM_Header();
    char receivedParity = mymsg->getM_Trailer();
    std::string payload = mymsg->getM_Payload();

    std::bitset<8> receivedParityBitset(receivedParity);
    std::bitset<8> charCountBitset(charCount);

    std::cout<<"received header: "<<(int)charCount<<endl;
    std::cout<<"received payload: "<<payload<<endl;
    std::cout<<"received trailer: "<<receivedParityBitset<<endl;
    std::cout<<"received type: "<<mymsg->getM_Type()<<endl;


    std::vector<std::bitset<8>> v;

    v.push_back(charCountBitset);

    for (int i = 0; i < payload.size(); i += 8) {
        std::string bitString = payload.substr(i, 8);

        std::bitset<8> bitset(bitString);

        v.push_back(bitset);
    }

    v.push_back(receivedParityBitset);

    std::bitset<8> parityBitset;
    for (int i = 0; i < v.size()-1; i++) {
        parityBitset ^= v[i];
    }


    MyMessage_Base *reply = new MyMessage_Base("reply");
    if (parityBitset == receivedParityBitset) {
       std::string message;

       for (size_t i = 1; i < v.size() - 1; i++) {
       message += static_cast<char>(v[i].to_ulong());
       }

        std::cout << "Parity check passed, original messsage: " <<message<< std::endl;
        reply->setM_Type(1);
    } else {
        std::cout << "Parity check failed" << std::endl;
        reply->setM_Type(2);
    }
    send(reply, "port$o");

    delete msg;
}
