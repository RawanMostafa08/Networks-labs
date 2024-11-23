package lab5;

import ned.IdealChannel;


@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=447,235");
    submodules:
        sender: Sender {
            @display("p=68,82");
        }
        receiver: Receiver {
            @display("p=330,82");
        }
    connections:
        sender.port <--> IdealChannel <--> receiver.port;
}

