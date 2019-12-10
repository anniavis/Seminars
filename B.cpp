#include <iostream>
#include <vector>
#include <queue>
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

	bool getDirection() const
	{
		return is_directed_;
	}

	virtual void addEdge(const Vertex& start, const Vertex& finish) = 0;
	virtual size_t getVertexDeg(const Vertex& vertex) const = 0;
	virtual std::vector<Vertex> getNeighbors(const Vertex& vertex) const = 0;
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
	enum VertexGroup { FIRST, SECOND, NOT_SET };

	bool dfsVisit(const Graph& graph, const Graph::Vertex& vertex, std::vector<VertexGroup>& vertex_groups)
	{
		VertexGroup neighbor_group = (vertex_groups[vertex] == FIRST ? SECOND : FIRST);
		for (Graph::Vertex i : graph.getNeighbors(vertex))
		{
			if (vertex_groups[i] == NOT_SET)
			{
				vertex_groups[i] = neighbor_group;
				if (!dfsVisit(graph, i, vertex_groups))
				{
					return false;
				}
			}
			else
			{
				if (vertex_groups[i] != neighbor_group)
				{
					return false;
				}
			}
		}
		return true;
	}

	bool isBipartiteGraph(const Graph& graph)
	{
		std::vector<VertexGroup> vertex_groups(graph.getVertexCount() + 1, NOT_SET);
		for (Graph::Vertex i = 1; i < graph.getVertexCount() + 1; ++i)
		{
			if (vertex_groups[i] == NOT_SET)
			{
				vertex_groups[i] = FIRST;
				if (!dfsVisit(graph, i, vertex_groups))
				{
					return false;
				}
			}
		}
		return true;
	}
}


int main()
{
	size_t n, m;
	std::cin >> n >> m;
	GraphAdjList graph_adj_list(n, false);
	for (size_t i = 0; i < m; ++i)
	{
		Graph::Vertex start, finish;
		std::cin >> start >> finish;
		graph_adj_list.addEdge(start, finish);
	}
	if (GraphProcessing::isBipartiteGraph(graph_adj_list))
	{
		std::cout << "YES";
	}
	else
	{
		std::cout << "NO";
	}
	//system("PAUSE");
	return 0;
}