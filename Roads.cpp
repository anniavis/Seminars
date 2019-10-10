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

	virtual void addEdge(const Vertex& start, const Vertex& finish) = 0;
};


class GraphAdjMatrix : public Graph
{
private:
	std::vector<std::vector<size_t>> adj_matrix_;

public:
	GraphAdjMatrix(size_t vertex_count, bool is_directed) : Graph(vertex_count, is_directed), adj_matrix_(vertex_count + 1, std::vector<size_t>(vertex_count + 1, 0)) {}

	void addEdge(const Vertex& start, const Vertex& finish) override
	{
		adj_matrix_[start].push_back(finish);
		if (!is_directed_)
		{
			adj_matrix_[finish].push_back(start);
		}
		edge_count_++;
	}
};


int main()
{
	int n;
	std::cin >> n;
	GraphAdjMatrix graph_adj_matrix(n, false);
	for (Graph::Vertex i = 1; i < n + 1; ++i)
	{
		for (Graph::Vertex j = 1; j < n + 1; ++j)
		{
			size_t input;
			std::cin >> input;
			if (input == 1)
			{
				graph_adj_matrix.addEdge(i, j);
			}
		}
	}
	std::cout << graph_adj_matrix.getEdgeCount();
	//system("PAUSE");
	return 0;
}