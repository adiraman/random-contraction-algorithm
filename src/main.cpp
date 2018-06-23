#include "../include/undirected_graph.h"
#include "../include/kargerCut.h"

int main()
{
	undirected_graph g;
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(0, 3);
	g.addEdge(4, 1);
	g.addEdge(1, 5);
	g.addEdge(2, 6);
	g.addEdge(7, 3);
	g.addEdge(4, 7);
	g.addEdge(7, 5);
	g.addEdge(6, 7);
	std::cout << g << std::endl;
	g.writeDot("graph.dot");

    kargerCut kc(g);
    kc.writeDot("partition.dot");
    std::cout << "applied karger partition " << std::endl;
    std::cout << kc.getMinCut() << std::endl;
    for(auto i : kc.getPartition())
    {
        std::cout << i << ", ";
    }
    std::cout << std::endl;

	return 0;
}

