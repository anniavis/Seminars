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

	int BFS(const Vertex& start, const Vertex& finish, std::vector<Vertex>& prev) const
	{
		std::vector<int> dist(vertex_count_ + 1, -1);
		std::queue<Vertex> vertex_queue;
		Vertex current;

		dist[start] = 0;
		vertex_queue.push(start);

		while (!vertex_queue.empty())
		{
			current = vertex_queue.front();
			vertex_queue.pop();

			for (auto i : adj_list_[current])
			{
				if (dist[i] == -1)
				{
					dist[i] = dist[current] + 1;
					vertex_queue.push(i);
					prev[i] = current;
				}
			}
		}

		return dist[finish];
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

	std::vector<Vertex> getMinPath(const Vertex& start, const Vertex& finish) const
	{
		std::vector<Vertex> prev(vertex_count_ + 1, 0);
		std::vector<Vertex> min_path;

		int path = BFS(start, finish, prev);

		if (path != -1)
		{
			Vertex current = finish;
			while (current != start)
			{
				min_path.push_back(current);
				current = prev[current];
			}

			min_path.push_back(start);
		}

		return min_path;
	}
};


int main()
{
	size_t n;

	std::cin >> n;

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

	Graph::Vertex start, finish;

	std::cin >> start >> finish;

	std::vector<Graph::Vertex> min_path = graph_adj_list.getMinPath(start, finish);

	if (min_path.size() == 0)
	{
		std::cout << -1;
	}
	else
	{
		std::cout << min_path.size() - 1 << std::endl;

		if (min_path.size() - 1 != 0)
		{
			std::reverse(min_path.begin(), min_path.end());

			for (auto i : min_path)
			{
				std::cout << i << ' ';
			}
		}
	}


	//system("PAUSE");
	return 0;
}