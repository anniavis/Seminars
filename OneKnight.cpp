#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>


class Graph
{
protected:
	size_t vertex_count_, edge_count_;
bool is_directed_;

public:
	typedef std::pair<size_t, size_t> Vertex;
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

	bool checker(const Vertex& vertex)
	{
		if (vertex.first <= 0 || vertex.first > sqrt(vertex_count_) || vertex.second <= 0 || vertex.second > sqrt(vertex_count_))
		{
			return false;
		}
		return true;
	}

	std::vector<Vertex> getNeighbors(const Vertex& vertex)
	{
		std::vector<Vertex> neighbors;
		std::vector<int> delta_x = { 2, -2, 1, -1 };
		std::vector<int> delta_y = { 2, -2, 1, -1 };
		Vertex neighbor;
		for (int dx : delta_x)
		{
			for (int dy : delta_y)
			{
				if ((dx + dy) % 2 == 0)
				{
					continue;
				}
				neighbor = std::make_pair(vertex.first + dx, vertex.second + dy);
				if (checker(neighbor))
				{
					neighbors.push_back(neighbor);
				}
			}
		}
		return neighbors;
	}
};


namespace GraphProcessing
{
	int BFS(Graph& graph, const Graph::Vertex& start, const Graph::Vertex& finish, std::map<Graph::Vertex, Graph::Vertex>& prev)
	{
		const int NOT_SET = -1;
		std::map<Graph::Vertex, int> dist;
		size_t vertex_count = graph.getVertexCount();
		for (size_t i = 1; i <= sqrt(vertex_count); ++i)
		{
			for (size_t j = 1; j <= sqrt(vertex_count); ++j)
			{
				dist[std::make_pair(i, j)] = NOT_SET;
			}
		}
		std::queue<Graph::Vertex> vertex_queue;
		dist[start] = 0;
		vertex_queue.push(start);
		while (!vertex_queue.empty())
		{
			Graph::Vertex current;
			current = vertex_queue.front();
			vertex_queue.pop();
			std::vector<Graph::Vertex> neighbors = graph.getNeighbors(current);
			for (Graph::Vertex i : neighbors)
			{
				if (dist[i] == NOT_SET)
				{
					dist[i] = dist[current] + 1;
					vertex_queue.push(i);
					prev[i] = current;
				}
			}
		}
		return dist[finish];
	}

	std::vector<Graph::Vertex> getMinPath(Graph& graph, const Graph::Vertex& start, const Graph::Vertex& finish)
	{
		const std::pair<int, int> NOT_SET = std::make_pair(0, 0);
		std::map<Graph::Vertex, Graph::Vertex> prev;
		size_t vertex_count = graph.getVertexCount();
		for (size_t i = 1; i <= sqrt(vertex_count); ++i)
		{
			for (size_t j = 1; j <= sqrt(vertex_count); ++j)
			{
				prev[std::make_pair(i, j)] = NOT_SET;
			}
		}
		std::vector<Graph::Vertex> min_path;
		int path = GraphProcessing::BFS(graph, start, finish, prev);
		if (path != -1)
		{
			Graph::Vertex current = finish;
			while (current != start)
			{
				min_path.push_back(current);
				current = prev[current];
			}
			min_path.push_back(start);
		}
		std::reverse(min_path.begin(), min_path.end());
		return min_path;
	}
}


int main()
{
	size_t n;
	std::cin >> n;
	size_t x1, y1, x2, y2;
	std::cin >> x1 >> y1 >> x2 >> y2;
	Graph::Vertex start(x1, y1);
	Graph::Vertex finish(x2, y2);
	Graph graph(n*n, false);
	std::vector<Graph::Vertex> min_path = GraphProcessing::getMinPath(graph, start, finish);
	if (min_path.size() == 0)
	{
		std::cout << -1;
	}
	else
	{
		std::cout << min_path.size() - 1 << std::endl;

		if (min_path.size() - 1 != 0)
		{
			for (Graph::Vertex i : min_path)
			{
				std::cout << i.first << ' ' << i.second << std::endl;
			}
		}
	}
	//system("PAUSE");
	return 0;
}