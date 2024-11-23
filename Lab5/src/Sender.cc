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

#include "Sender.h"
#include "MyMessage_m.h"
Define_Module(Sender);

void Sender::initialize()
{
    scheduleAt(simTime(), new cMessage("self message"));
}

void Sender::handleMessage(cMessage *msg)
{
       MyMessage_Base *mymsg = new MyMessage_Base("data");

       std::string input;
       std::cout<<"enter message";
       std::cin>>input;


       std::vector<std::bitset<8>> v;

       std::bitset<8> charCountBitset(input.size()+2);
       v.push_back(charCountBitset);

       std::bitset<8> parityBitset;
       parityBitset^=charCountBitset;

       for (int i=0;i<input.size();i++)
       {
           std::bitset<8> inputBitset(input[i]);
           v.push_back(inputBitset);

           parityBitset^=inputBitset;
       }

       v.push_back(parityBitset);

       std::cout << "before error: message: "<<input<<":\n";

       for (int i=0 ; i < v.size() ; i++) {
           std::cout << v[i] << std::endl;
       }


       std::random_device rd;
       std::mt19937 rng(rd());
       std::uniform_int_distribution<int> bitDist(0, v.size() * 8 - 1);
       int randomBit = bitDist(rng);

       std::uniform_int_distribution<int> flipDist(0, 1);
       int FlipOrNot = flipDist(rng); // if 1 flip, if 0 don't

       if (FlipOrNot == 1) {

           int bitsetIndex = randomBit / 8;
           int bitIndex = randomBit % 8;

           v[bitsetIndex].flip(bitIndex);
           EV<<"adding error to bit number "<<bitIndex<<" in character number "<<bitsetIndex<<"\n";
       }

       std::string msgString="";
       std::cout << "after error: message: "<<":\n";
       for (int i=0 ; i < v.size() ; i++) {
           std::cout << v[i] << std::endl;

           msgString += v[i].to_string();

       }

       mymsg->setM_Header((char)v[0].to_ulong());

       mymsg->setM_Payload(msgString.substr(8, msgString.size() - 16).c_str());

       mymsg->setM_Trailer((char)v[v.size()-1].to_ulong());

       mymsg->setM_Type(0);


       EV<<"header: "<<(int)mymsg->getM_Header()<<"\n";
       EV<<"pay-load: "<<mymsg->getM_Payload()<<"\n";
       EV<<"trailer in bits: "<<v[v.size()-1]<<"\n";
       EV<<"type: "<<mymsg->getM_Type()<<"\n";


       send(mymsg, "port$o");

}
