package lab2;

import ned.IdealChannel;


@license(LGPL);
//
// TODO documentation
//
network Network
{
    @display("bgb=617,318");
    submodules:
        player1: Player1 {
            @display("p=126,105");
        }
        player2: Player2 {
            @display("p=437,105");
        }
    connections:
        player2.out --> IdealChannel --> player1.in;
        player1.out --> IdealChannel --> player2.in;
}

