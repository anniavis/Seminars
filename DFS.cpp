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
		return edge_count_;
	}

	bool getDirection() const
	{
		return is_directed_;
	}

	virtual void addEdge(const Vertex& start, const Vertex& finish) = 0;

	virtual size_t getVertexDeg(const Vertex& vertex) const = 0;
};


class GraphAdjList : public Graph
{
private:
	std::vector<std::vector<Vertex>> adj_list_;

	void DFS_visit(const Graph::Vertex& vertex, std::vector<bool>& used) const
	{
		used[vertex] = true;

		for (auto i : adj_list_[vertex])
		{
			if (!used[i])
			{
				DFS_visit(i, used);
			}
		}
	}

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

	size_t countVerticesInComponent(const Vertex& vertex) const
	{
		std::vector<bool> used(vertex_count_ + 1, false);
		size_t vertices_in_component = 0;

		DFS_visit(vertex, used);

		for (Vertex i = 1; i < vertex_count_ + 1; ++i)
		{
			if (used[i])
			{
				vertices_in_component++;
			}
		}

		return vertices_in_component;
	}
};


int main()
{
	size_t n;
	Graph::Vertex s;

	std::cin >> n >> s;

	GraphAdjList graph_adj_list(n, false);
	size_t input;

	for (Graph::Vertex i = 1; i < n + 1; ++i)
	{
		for (Graph::Vertex j = 1; j < n + 1; ++j)
		{
			std::cin >> input;

			if (input == 1)
			{
				graph_adj_list.addEdge(i, j);
			}
		}
	}

	std::cout << graph_adj_list.countVerticesInComponent(s);

	//system("PAUSE");
	return 0;
}
