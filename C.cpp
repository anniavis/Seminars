#include <iostream>
#include <vector>
#include <algorithm>


class Graph
{
protected:
	size_t vertex_count_, edge_count_;
	bool is_directed_;

public:
	typedef size_t Vertex;
	Graph(size_t vertex_count, bool is_directed) : vertex_count_(vertex_count), is_directed_(is_directed), edge_count_(0) {}

	size_t getVertexCount() const
	{
		return vertex_count_;
	}

	size_t getEdgeCount() const
	{
		return is_directed_ == 0 ? edge_count_ / 2 : edge_count_;
	}

	bool isDirected() const
	{
		return is_directed_;
	}

	virtual void addEdge(const Vertex& start, const Vertex& finish) = 0;
	virtual size_t getVertexDeg(const Vertex& vertex) const = 0;
	virtual std::vector<Vertex> getNeighbors(const Vertex& v) const = 0;
};


class GraphAdjList : public Graph
{
private:
	std::vector<std::vector<Vertex>> adj_list_;

public:
	GraphAdjList(size_t vertex_count, bool is_directed) : Graph(vertex_count, is_directed), adj_list_(vertex_count + 1) {}

	void addEdge(const Vertex& start, const Vertex& finish) override
	{
		adj_list_[start].push_back(finish);
		if (!is_directed_)
		{
			adj_list_[finish].push_back(start);
		}
		edge_count_++;
	}

	size_t getVertexDeg(const Vertex& vertex) const override
	{
		return adj_list_[vertex].size();
	}

	std::vector<Vertex> getNeighbors(const Vertex& vertex) const override
	{
		return adj_list_[vertex];
	}
};


namespace GraphProcessing
{
	enum VertexMark { WHITE, GREY, BLACK };

	std::vector<Graph::Vertex> getCycle(const Graph::Vertex& start, const Graph::Vertex& finish, std::vector<Graph::Vertex>& cycle, std::vector<Graph::Vertex>& prev)
	{
		Graph::Vertex current = finish;
		while (current != start)
		{
			cycle.push_back(current);
			current = prev[current];
		}
		cycle.push_back(start);
		std::reverse(cycle.begin(), cycle.end());
		return cycle;
	}

	bool dfsVisit(const Graph& graph, const Graph::Vertex& vertex, std::vector<VertexMark>& vertex_marks, std::vector<Graph::Vertex>& cycle, std::vector<Graph::Vertex>& prev)
	{
		vertex_marks[vertex] = GREY;
		for (Graph::Vertex u : graph.getNeighbors(vertex))
		{
			if (vertex_marks[u] == WHITE)
			{
				prev[u] = vertex;
				if (dfsVisit(graph, u, vertex_marks, cycle, prev))
				{
					return true;
				}
			}
			else
			{
				if (vertex_marks[u] == GREY)
				{
					cycle = getCycle(u, vertex, cycle, prev);
					return true;
				}
			}
		}
		vertex_marks[vertex] = BLACK;
		return false;
	}

	std::vector<Graph::Vertex> findCycle(const Graph& graph)
	{
		std::vector<Graph::Vertex> cycle;
		const int NOT_SET = 0;
		std::vector<Graph::Vertex> prev(graph.getVertexCount() + 1, NOT_SET);
		std::vector<VertexMark> vertex_marks(graph.getVertexCount() + 1, WHITE);
		for (Graph::Vertex u = 1; u < graph.getVertexCount() + 1; ++u)
		{
			if (vertex_marks[u] == WHITE)
			{
				if (dfsVisit(graph, u, vertex_marks, cycle, prev))
				{
					return cycle;
				}
			}
		}
		return {};
	}
}


int main()
{
	size_t n, m;
	std::cin >> n >> m;
	GraphAdjList graph_adj_list(n, true);
	for (Graph::Vertex i = 0; i < m; ++i)
	{
		Graph::Vertex start, finish;
		std::cin >> start >> finish;
		graph_adj_list.addEdge(start, finish);
	}
	std::vector<Graph::Vertex> cycle = GraphProcessing::findCycle(graph_adj_list);
	if (cycle.size() == 0)
	{
		std::cout << "NO";
	}
	else
	{
		std::cout << "YES" << std::endl;
		for (size_t i = 0; i < cycle.size(); ++i)
		{
			std::cout << cycle[i] << ' ';
		}
	}
	//system("PAUSE");
	return 0;
}