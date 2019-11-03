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
		return is_directed_ == 0 ? edge_count_ / 2 : edge_count_;
	}

	bool getDirection() const
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
	void dfsVisit(const Graph& graph, const Graph::Vertex& vertex, std::vector<bool>& used, std::vector<std::vector<Graph::Vertex>>& components)
	{
		used[vertex] = true;
		components.back().push_back(vertex);
		for (Graph::Vertex i : graph.getNeighbors(vertex))
		{
			if (!used[i])
			{
				dfsVisit(graph, i, used, components);
			}
		}
	}

	std::vector<std::vector<Graph::Vertex>> getComponents(const Graph& graph)
	{
		std::vector<std::vector<Graph::Vertex>> components;
		std::vector<bool> used(graph.getVertexCount() + 1, false);
		for (Graph::Vertex i = 1; i < graph.getVertexCount() + 1; ++i)
		{
			if (!used[i])
			{
				components.push_back({});
				dfsVisit(graph, i, used, components);
			}
		}
		return components;
	}
}


int main()
{
	size_t n, m;
	std::cin >> n >> m;
	GraphAdjList graph_adj_list(n, false);
	for (Graph::Vertex i = 0; i < m; ++i)
	{
		Graph::Vertex start, finish;
		std::cin >> start >> finish;
		graph_adj_list.addEdge(start, finish);
	}
	std::vector<std::vector<Graph::Vertex>> components = GraphProcessing::getComponents(graph_adj_list);
	std::cout << components.size() << std::endl;
	for (size_t i = 0; i < components.size(); ++i)
	{
		std::cout << components[i].size() << std::endl;
		for (Graph::Vertex vertex : components[i])
		{
			std::cout << vertex << ' ';
		}
		std::cout << std::endl;
	}
	//system("PAUSE");
	return 0;
}
