package lab3_2;

@license(LGPL);

network Ring
{
    parameters:
        int N = default(4);
    submodules:
        nodes[N]: Node;
    connections:
		for i = 0..N-2 {
            nodes[i].out --> nodes[i+1].in;
        }
        nodes[N-1].out --> nodes[0].in;
}