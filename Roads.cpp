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
};


class GraphAdjMatrix : public Graph
{
private:
	std::vector<std::vector<size_t>> adj_matrix_;

public:
	GraphAdjMatrix(size_t vertex_count) : Graph(vertex_count), adj_matrix_(vertex_count + 1, std::vector<size_t>(vertex_count + 1, 0)) {}
	
	void addEdge(const Vertex& start, const Vertex& finish) override
	{
		adj_matrix_[start][finish] = 1;
		adj_matrix_[finish][start] = 1;
		edge_count_++;
	}
};


int main()
{
	int n;
	std::cin >> n;

	size_t input;
	GraphAdjMatrix graph_adj_matrix(n);

	for (Graph::Vertex i = 1; i < n + 1; ++i)
	{
		for (Graph::Vertex j = 1; j < n + 1; ++j)
		{
			std::cin >> input;
			
			if (input == 1)
			{
				graph_adj_matrix.addEdge(i, j);
			}
		}
	}

	
	std::cout << graph_adj_matrix.getEdgeCount() / 2;

	//system("PAUSE");
	return 0;
}