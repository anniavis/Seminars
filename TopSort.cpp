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

	bool dfsVisitIsCycleGraph(const Graph& graph, const Graph::Vertex& vertex, std::vector<VertexMark>& vertex_marks)
	{
		vertex_marks[vertex] = GREY;
		for (Graph::Vertex u : graph.getNeighbors(vertex))
		{
			if (vertex_marks[u] == WHITE)
			{
				if (dfsVisitIsCycleGraph(graph, u, vertex_marks))
				{
					return true;
				}
			} else 
			if (vertex_marks[u] == GREY)
			{
				return true;
			}
		}
		vertex_marks[vertex] = BLACK;
		return false;
	}

	bool isCycleGraph(const Graph& graph)
	{
		std::vector<VertexMark> vertex_marks(graph.getVertexCount() + 1, WHITE);
		for (Graph::Vertex u = 1; u < graph.getVertexCount() + 1; ++u)
		{
			if (vertex_marks[u] == WHITE)
			{
				if (dfsVisitIsCycleGraph(graph, u, vertex_marks))
				{
					return true;
				}
			}
		}
		return false;
	}

	void dfsVisitTopSort(const Graph& graph, const Graph::Vertex& vertex, std::vector<bool>& used, std::vector<Graph::Vertex>& top_sort_result)
	{
		used[vertex] = true;
		for (Graph::Vertex u : graph.getNeighbors(vertex))
		{
			if (!used[u])
			{
				dfsVisitTopSort(graph, u, used, top_sort_result);
			}
		}
		top_sort_result.push_back(vertex);
	}

	std::vector<Graph::Vertex> TopSort(const Graph& graph)
	{
		if (!graph.isDirected() || isCycleGraph(graph))
		{
			return {};
		}
		std::vector<bool> used(graph.getVertexCount() + 1, false);
		std::vector<Graph::Vertex> top_sort_result;
		for (Graph::Vertex u = 1; u < graph.getVertexCount() + 1; ++u)
		{
			if (!used[u])
			{
				dfsVisitTopSort(graph, u, used, top_sort_result);
			}
		}
		std::reverse(top_sort_result.begin(), top_sort_result.end());
		return top_sort_result;
	}
}


int main()
{
	size_t number_of_soldiers, number_of_relations;
	std::cin >> number_of_soldiers >> number_of_relations;
	GraphAdjList graph_adj_list(number_of_soldiers, true);
	typedef size_t Soldier;
	for (size_t i = 0; i < number_of_relations; ++i)
	{
		Soldier higher_soldier, lower_soldier;
		std::cin >> higher_soldier >> lower_soldier;
		graph_adj_list.addEdge(higher_soldier, lower_soldier);
	}
	std::vector<Graph::Vertex> top_sort_result = GraphProcessing::TopSort(graph_adj_list);
	if (top_sort_result.empty())
	{
		std::cout << "No";
	}
	else
	{
		std::cout << "Yes" << std::endl;
		for (Graph::Vertex i : top_sort_result)
		{
			std::cout << i << ' ';
		}
	}
	//system("PAUSE");
	return 0;
}
