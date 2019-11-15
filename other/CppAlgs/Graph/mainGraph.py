
#read graph from txt
graphlist = []
f = open("D:\PC\GitFiles\Cpp-STL-test\other\CppAlgs\Graph\inputGraph.txt", "r");
for line in f.readlines():
    linesp = line.split(',')
    linesp[1] = linesp[1][:-1] #remove \n
    assert(len(linesp) == 2)
    graphlist.append(linesp)

#generate nx.Graph
#networkx有四种图 Graph 、DiGraph、MultiGraph、MultiDiGraph，分别为无多重边无向图、无多重边有向图、有多重边无向图、有多重边有向图。
import networkx as nx
G = nx.Graph()
#G.add_edges_from([(1,2),(1,3)])
G.add_edges_from(graphlist)

#draw graph
import matplotlib.pyplot as plt
nx.draw(G, pos = nx.random_layout(G), node_color = 'b',
    edge_color = 'r', with_labels = True, font_size = 18, node_size = 20)
#plt.show()
plt.savefig('D:\PC\GitFiles\Cpp-STL-test\other\CppAlgs\Graph\inputGraph.jpg')
