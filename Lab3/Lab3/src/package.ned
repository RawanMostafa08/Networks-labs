package lab3;

@license(LGPL);

network Star
{
    parameters:
        int N = default(4);
	submodules:
	    hub: Hub;
	    nodes[N]:Node;
	connections:
	    for i=0..N-1 {
	        hub.port++ <--> nodes[i].port;
	    }
	    
}