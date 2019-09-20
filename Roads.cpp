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
};


class GraphAdjMatrix : public Graph
{
private:
	std::vector<std::vector<Vertex>> adj_matrix_;

public:
	GraphAdjMatrix(const std::vector<std::vector<Graph::Vertex>>& adj_matrix) : Graph(adj_matrix.size()), adj_matrix_(adj_matrix)
	{
		for (size_t i = 0; i < vertex_count_; ++i)
		{
			for (size_t j = 0; j < vertex_count_; ++j)
			{
				edge_count_ += adj_matrix_[i][j];
			}
		}
	}
};


int main()
{
	int n;
	std::cin >> n;

	std::vector<std::vector<Graph::Vertex>> matrix(n, std::vector<Graph::Vertex>(n));
	Graph::Vertex input_vertex;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			std::cin >> input_vertex;
			matrix[i][j] = input_vertex;
		}
	}

	GraphAdjMatrix graph_adj_matrix(matrix);
	std::cout << graph_adj_matrix.getEdgeCount() / 2;

	//system("PAUSE");
	return 0;
}