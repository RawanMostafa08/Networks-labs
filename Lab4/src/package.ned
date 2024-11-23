package lab4;

import ned.IdealChannel;


@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=346,212");
    submodules:
        sender: Sender {
            @display("p=61,72");
        }
        reciever: Reciever {
            @display("p=263,72");
        }
    connections:
        sender.port <--> IdealChannel <--> reciever.port;
}

