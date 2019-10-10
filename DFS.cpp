#include <iostream>
#include <vector>


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
		if (is_directed_ == 0)
		{
			return edge_count_ / 2;
		}
		return edge_count_;
	}

	bool getDirection() const
	{
		return is_directed_;
	}

	virtual void addEdge(const Vertex& start, const Vertex& finish) = 0;
	virtual size_t getVertexDeg(const Vertex& vertex) const = 0;
	virtual std::vector<std::vector<Vertex>> getAdjList() const = 0;
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

	std::vector<std::vector<Vertex>> getAdjList() const override
	{
		return adj_list_;
	}

	std::vector<Vertex> getNeighbors(const Vertex& vertex) const override
	{
		return adj_list_[vertex];
	}
};


namespace GraphProcessing
{
	void DFS_visit(Graph& graph, const Graph::Vertex& vertex, std::vector<bool>& used)
	{
		used[vertex] = true;
		std::vector<Graph::Vertex> neighbors = graph.getNeighbors(vertex);
		for (Graph::Vertex i : neighbors)
		{
			if (!used[i])
			{
				DFS_visit(graph, i, used);
			}
		}
	}

	std::vector<Graph::Vertex> VerticesInComponentContaining(Graph& graph, const Graph::Vertex& vertex) 
	{
		size_t vertex_count = graph.getVertexCount();
		std::vector<bool> used(vertex_count + 1, false);
		std::vector<Graph::Vertex> vertices_in_component;
		DFS_visit(graph, vertex, used);
		for (Graph::Vertex i = 1; i < vertex_count + 1; ++i)
		{
			if (used[i])
			{
				vertices_in_component.push_back(i);
			}
		}
		return vertices_in_component;
	}
}


int main()
{
	size_t n;
	Graph::Vertex s;
	std::cin >> n >> s;
	GraphAdjList graph_adj_list(n, false);
	for (Graph::Vertex i = 1; i < n + 1; ++i)
	{
		for (Graph::Vertex j = 1; j < n + 1; ++j)
		{
			size_t input;
			std::cin >> input;
			if (input == 1)
			{
				graph_adj_list.addEdge(i, j);
			}
		}
	}
	std::cout << GraphProcessing::VerticesInComponentContaining(graph_adj_list, s).size();
	//system("PAUSE");
	return 0;
}
