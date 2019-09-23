#include <iostream>
#include <vector>


class Graph
{
protected:
	size_t vertex_count_, edge_count_;

public:
	typedef size_t Vertex;
	Graph(size_t vertex_count) : vertex_count_(vertex_count), edge_count_(0) {}

	size_t getVertexCount() const
	{
		return vertex_count_;
	}

	size_t getEdgeCount() const
	{
		return edge_count_;
	}

	virtual void addEdge(const Vertex& start, const Vertex& finish) = 0;

	virtual size_t getVertexDeg(const Vertex& vertex) const = 0;
};


class GraphAdjList : public Graph
{
private:
	std::vector<std::vector<Vertex>> adj_list_;

public:
	GraphAdjList(size_t vertex_count) : Graph(vertex_count), adj_list_(vertex_count + 1) {}
	
	void addEdge(const Vertex& start, const Vertex& finish) override
	{
		adj_list_[start].push_back(finish);
		adj_list_[finish].push_back(start);
		edge_count_++;
	}

	size_t getVertexDeg(const Vertex& vertex) const override
	{
		return adj_list_[vertex].size();
	}
};


int main()
{
	int n, m;
	std::cin >> n >> m;

	Graph::Vertex start, finish;
	GraphAdjList graph_adj_list(n);

	for (int i = 0; i < m; ++i)
	{
		std::cin >> start >> finish;
		graph_adj_list.addEdge(start, finish);
	}

	for (Graph::Vertex i = 1; i < n + 1; ++i)
	{
		std::cout << graph_adj_list.getVertexDeg(i) << ' ';
	}

	//system("PAUSE");
	return 0;
}