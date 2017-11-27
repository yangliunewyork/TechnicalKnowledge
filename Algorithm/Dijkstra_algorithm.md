__Dijkstra's algorithm__ is an algorithm for finding the __shortest paths__ between nodes in a graph, which may represent, for example, road networks. It was conceived by computer scientist Edsger W. Dijkstra in 1956 and published three years later.

The algorithm exists in many variants; Dijkstra's original variant found the shortest path between two nodes, but a more common variant fixes a single node as the "source" node and finds shortest paths from the source to all other nodes in the graph, producing a __shortest-path tree__.

The implementation based on a min-priority queue implemented by a Fibonacci heap and running in  __O( (|E|+|V|) * log |V|)__  (where  |E| is the number of edges) is due to Fredman & Tarjan 1984. This is asymptotically the fastest known single-source shortest-path algorithm for arbitrary directed graphs with unbounded non-negative weights.

# Algorithm

Let the node at which we are starting be called the initial node. Let the distance of node Y be the distance from the initial node to Y. Dijkstra's algorithm will assign some initial distance values and will try to improve them step by step.

1. Assign to every node a tentative distance value: set it to zero for our initial node and to infinity for all other nodes.

2. Set the initial node as current. Mark all other nodes unvisited. Create a set of all the unvisited nodes called the unvisited set.

3. For the current node, consider all of its neighbors and calculate their tentative distances. Compare the newly calculated tentative distance to the current assigned value and assign the smaller one. For example, if the current node A is marked with a distance of 6, and the edge connecting it with a neighbor B has length 2, then the distance to B (through A) will be 6 + 2 = 8. If B was previously marked with a distance greater than 8 then change it to 8. Otherwise, keep the current value.

4. When we are done considering all of the neighbors of the current node, mark the current node as visited and remove it from the unvisited set. A visited node will never be checked again.

5. If the destination node has been marked visited (when planning a route between two specific nodes) or if the smallest tentative distance among the nodes in the unvisited set is infinity (when planning a complete traversal; occurs when there is no connection between the initial node and remaining unvisited nodes), then stop. The algorithm has finished.

6. Otherwise, select the unvisited node that is marked with the smallest tentative distance, set it as the new "current node", and go back to step 3.


### Pseudocode

```
function Dijkstra(Graph, source):
 2
 3      create vertex set Q
 4
 5      for each vertex v in Graph:             // Initialization
 6          dist[v] ← INFINITY                  // Unknown distance from source to v
 7          prev[v] ← UNDEFINED                 // Previous node in optimal path from source
 8          add v to Q                          // All nodes initially in Q (unvisited nodes)
 9
10      dist[source] ← 0                        // Distance from source to source
11      
12      while Q is not empty:
13          u ← vertex in Q with min dist[u]    // Node with the least distance
14                                                      // will be selected first
15          remove u from Q 
16          
17          for each neighbor v of u:           // where v is still in Q.
18              alt ← dist[u] + length(u, v)
19              if alt < dist[v]:               // A shorter path to v has been found
20                  dist[v] ← alt 
21                  prev[v] ← u 
22
23      return dist[], prev[]
```

If we are only interested in a shortest path between vertices source and target, we can terminate the search after line 15 if u = target. Now we can read the shortest path from source to target by reverse iteration:

```
1  S ← empty sequence
2  u ← target
3  while prev[u] is defined:                  // Construct the shortest path with a stack S
4      insert u at the beginning of S         // Push the vertex onto the stack
5      u ← prev[u]                            // Traverse from target to source
6  insert u at the beginning of S             // Push the source onto the stack
```

Now sequence S is the list of vertices constituting one of the shortest paths from source to target, or the empty sequence if no path exists.

A more general problem would be to find all the shortest paths between source and target (there might be several different ones of the same length). Then instead of storing only a single node in each entry of prev[] we would store all nodes satisfying the relaxation condition. For example, if both r and source connect to target and both of them lie on different shortest paths through target (because the edge cost is the same in both cases), then we would add both r and source to prev[target]. When the algorithm completes, prev[] data structure will actually describe a graph that is a subset of the original graph with some edges removed. Its key property will be that if the algorithm was run with some starting node, then every path from that node to any other node in the new graph will be the shortest path between those nodes in the original graph, and all paths of that length from the original graph will be present in the new graph. Then to actually find all these shortest paths between two given nodes we would use a path finding algorithm on the new graph, such as depth-first search.

#### Using a priority queue

```
1  function Dijkstra(Graph, source):
2      dist[source] ← 0                                    // Initialization
3
4      create vertex set Q
5
6      for each vertex v in Graph:           
7          if v ≠ source
8              dist[v] ← INFINITY                          // Unknown distance from source to v
9              prev[v] ← UNDEFINED                         // Predecessor of v
10
11         Q.add_with_priority(v, dist[v])
12
13
14     while Q is not empty:                              // The main loop
15         u ← Q.extract_min()                            // Remove and return best vertex
16         for each neighbor v of u:                      // only v that is still in Q
17             alt ← dist[u] + length(u, v) 
18             if alt < dist[v]
19                 dist[v] ← alt
20                 prev[v] ← u
21                 Q.decrease_priority(v, alt)
22
23     return dist[], prev[]
```

# Running time

With a self-balancing binary search tree or binary heap, the algorithm requires O( (|E|+|V|) * log |V|).

### Sample code

Notice that below code does not use priority queue， that's because C++ doesn't have good built-in priority queue to support update priority.

Another thing I want to point out is that below solution, Edge is unidirectional. Of source, bidirectional works basically the same.


```cpp
struct Vertex;
typedef std::shared_ptr<Vertex> VertexPtr;
struct Edge;
typedef std::shared_ptr<Edge> EdgePtr;

struct Vertex
 {
	 Vertex(std::string name) : m_vertex_name(name){}
	 std::string m_vertex_name;
	 std::unordered_set<EdgePtr> m_to_edges;
};

// Here is an unidirectional edge.
struct Edge {
	Edge(VertexPtr from, VertexPtr to, int weight) : m_from_vertex(from), m_to_vertex(to), m_weight(weight) {}
	VertexPtr m_from_vertex;
	VertexPtr m_to_vertex;
	int m_weight;
};

VertexPtr GetUnvisitedMinDistanceVertex(const std::unordered_set<VertexPtr> &unvisited,
					const std::unordered_map<VertexPtr, long> &distance_from_source) {
	VertexPtr reval = nullptr;
	for (const VertexPtr &vertex : unvisited) {
		if (!reval) {
			reval = vertex;
		} else {
			if (distance_from_source.at(vertex) < distance_from_source.at(reval)) {
				reval = vertex;
			}
		}
	}
	return reval;
}


// Return values:
// distance_from_source : Store the distance from source to here.
// prev : Store previous vertex in shortest path
void Dijkstra(const std::vector<VertexPtr> &graph, 
			  VertexPtr source,
			  std::unordered_map<VertexPtr, long> &distance_from_source,
			  std::unordered_map<VertexPtr, VertexPtr> &prev) {

	std::unordered_set<VertexPtr> unvisited;

	for (const VertexPtr &vertex : graph) {
		if (vertex != source) {
			distance_from_source[vertex] = LONG_MAX;
		}
		prev[vertex] = nullptr;
		unvisited.insert(vertex);
	}

	distance_from_source[source] = 0;

	while (!unvisited.empty()) {
		VertexPtr curr = GetUnvisitedMinDistanceVertex(unvisited, distance_from_source);
		unvisited.erase(curr);
		for (const EdgePtr& edge : curr->m_to_edges) {
			int alternative_distance = distance_from_source[curr] + edge->m_weight;
			if (alternative_distance < distance_from_source[edge->m_to_vertex]) {
				distance_from_source[edge->m_to_vertex] = alternative_distance;
				prev[edge->m_to_vertex] = curr;
			}
		}
	}
}

std::vector<VertexPtr> GetShortestPathTo(const std::unordered_map<VertexPtr, VertexPtr> &prev,
						const VertexPtr &source,
					   const VertexPtr &destination) {
	std::vector<VertexPtr> path;
	VertexPtr curr = destination;
	while (curr) {
		path.emplace_back(curr);
		curr = prev.at(curr);
	}
	std::reverse(path.begin(), path.end());
	return path;
}

void PrintPath(const std::vector<VertexPtr>  &vertices) {
	std::ostringstream oss;
	for (const VertexPtr& vertex : vertices) {
		oss << vertex->m_vertex_name;
		oss << "->";
	}
	std::cout << oss.str() << std::endl;
}

void UnitTest() {
	VertexPtr one = std::make_shared<Vertex>("1");
	VertexPtr two = std::make_shared<Vertex>("2");
	VertexPtr three = std::make_shared<Vertex>("3");
	VertexPtr four = std::make_shared<Vertex>("4");
	VertexPtr five = std::make_shared<Vertex>("5");
	VertexPtr six = std::make_shared<Vertex>("6");

	one->m_to_edges.insert(std::make_shared<Edge>(one, two, 7));
	one->m_to_edges.insert(std::make_shared<Edge>(one, three, 9));
	one->m_to_edges.insert(std::make_shared<Edge>(one, six, 14));

	two->m_to_edges.insert(std::make_shared<Edge>(two, three, 10));
	two->m_to_edges.insert(std::make_shared<Edge>(two, four, 15));

	three->m_to_edges.insert(std::make_shared<Edge>(three, four, 11));
	three->m_to_edges.insert(std::make_shared<Edge>(three, six, 2));

	four->m_to_edges.insert(std::make_shared<Edge>(four, five, 6));

	six->m_to_edges.insert(std::make_shared<Edge>(six, five, 9));

	std::vector<VertexPtr> graph;
	graph.push_back(one);
	graph.push_back(two);
	graph.push_back(three);
	graph.push_back(four);
	graph.push_back(five);
	graph.push_back(six);

	std::unordered_map<VertexPtr, long> distance_from_source;
	std::unordered_map<VertexPtr, VertexPtr> prev;
	Dijkstra(graph, one, distance_from_source, prev);
	
	assert(distance_from_source[one] == 0);
	assert(distance_from_source[two] == 7);
	assert(distance_from_source[three] == 9);
	assert(distance_from_source[four] == 20);
	assert(distance_from_source[five] == 20);
	assert(distance_from_source[six] == 11);

	std::vector<VertexPtr> shortest_path = GetShortestPathTo(prev, one, five);
	PrintPath(shortest_path);
}

int _tmain(int argc, _TCHAR* argv[])
{
	UnitTest();
	return 0;
}

```
