from dimacs import loadDirectedWeightedGraph
import math
from queue import Queue

class Graph:
    def __init__(self, graph, capacity,flow, source, outlet,vertices, edges):
        self.graph = graph
        self.capacity = capacity
        self.flow = flow     
        self.source = source
        self.outlet = outlet  
        self.vertices = vertices
        self.edges = edges

def read_input(path):
    input_ = loadDirectedWeightedGraph(path)
    capacity = dict()
    flow = dict()
    graph = [set() for _ in range(input_[0])]
    edges = set()
    for (x,y,f) in input_[1]:
        x-=1
        y-=1
        edges.add((x,y))
        graph[x].add(y)

        capacity[(x,y)] = f
        flow[(x,y)] = 0
        flow[(y,x)] = 0

    return Graph(graph,capacity,flow, 0,input_[0]-1,input_[0], edges)

def bfs(graph, residual):
    process = Queue()
    process.put(graph.source)
    ancestor = [None for _ in range(graph.vertices)]
    residual[graph.source] = math.inf

    while not process.empty():
        node = process.get()        

        for i in graph.graph[node]:
            rescap = graph.capacity[(node, i)] - graph.flow[(node, i)] if (node, i) in graph.edges else graph.flow[(i,node)]
            if rescap <= 0 or ancestor[i] is not None:
                continue

            ancestor[i] = node
            residual[i] = min(residual[node], rescap)
            if i==graph.outlet:
                return (True, ancestor)

            process.put(i)
    
    if ancestor[graph.outlet] is not None:
        return (True, ancestor)

    return (False, [])

def EdmondsKarp(graph):
    residual = [math.inf for _ in range(graph.vertices)]

    b,ancestor = bfs(graph, residual)

    while b:
        i = graph.outlet
        while i != graph.source:
            x = ancestor[i]
            graph.flow[(x,i)] += residual[graph.outlet]
            if x not in graph.graph[i]:
                graph.graph[i].add(x)
            
            graph.flow[(i,x)] -= residual[graph.outlet]
            i = x
        b, ancestor = bfs(graph, residual)


    maximal_flow = 0
    for i in graph.graph[graph.source]:
        maximal_flow += graph.flow[(graph.source, i)]
    return maximal_flow 

def solve(path):
    return EdmondsKarp(read_input(path))

if __name__=='__main__':
    print(solve('flow/simple2'))
