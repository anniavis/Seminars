#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <map>


struct KnightMove
{
	int dx, dy;

	static std::vector<KnightMove> knightMoves()
	{
		return { {2, 1}, {2, -1}, {-2, 1}, {-2 ,-1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };
	}
};


class Graph
{
protected:
	size_t vertex_count_, edge_count_;
	bool is_directed_;

public:
	struct Vertex
	{
		size_t column_, row_;

		Vertex() = default;

		Vertex(size_t column, size_t row) : column_(column), row_(row) {}

		Vertex(const Vertex& vertex) : column_(vertex.column_), row_(vertex.row_) {}

		bool operator<(const Vertex& vertex) const
		{
			if (column_ != vertex.column_)
			{
				return column_ < vertex.column_;
			}
			return row_ < vertex.row_;
		}

		bool operator!=(const Vertex& vertex) const
		{
			return column_ != vertex.column_ || row_ != vertex.row_;
		}
	};

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
	virtual std::vector<Vertex> getNeighbors(const Vertex& vertex) const = 0;
};


class GraphAdjList : public Graph
{
private:
	std::map<Vertex, std::vector<Vertex>> adj_list_;

public:
	GraphAdjList(size_t vertex_count, bool is_directed) : Graph(vertex_count, is_directed) {}

	void addEdge(const Vertex& start, const Vertex& finish) override
	{
		adj_list_[start].push_back(finish);
		if (!is_directed_)
		{
			adj_list_[finish].push_back(start);
		}
		edge_count_++;
	}

	std::vector<Vertex> getNeighbors(const Vertex& vertex) const override
	{
		return adj_list_.at(vertex);
	}
};


namespace GraphProcessing
{
	template <typename T>
	void initializeMap(size_t vertex_count, std::map<Graph::Vertex, T>& map, const T& value)
	{
		for (size_t i = 1; i < vertex_count + 1; ++i)
		{
			for (size_t j = 1; j < vertex_count + 1; ++j)
			{
				Graph::Vertex vertex(i, j);
				map[vertex] = value;
			}
		}
	}

	int BFS(const Graph& graph, const Graph::Vertex& start, const Graph::Vertex& finish, std::map<Graph::Vertex, Graph::Vertex>& prev)
	{
		const int NOT_SET = -1;
		std::map<Graph::Vertex, int> dist;
		initializeMap(graph.getVertexCount(), dist, NOT_SET);
		std::queue<Graph::Vertex> vertex_queue;
		dist[start] = 0;
		vertex_queue.push(start);
		while (!vertex_queue.empty())
		{
			Graph::Vertex current = vertex_queue.front();
			vertex_queue.pop();
			for (Graph::Vertex i : graph.getNeighbors(current))
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

	std::vector<Graph::Vertex> getMinPath(const Graph& graph, const Graph::Vertex& start, const Graph::Vertex& finish)
	{
		const Graph::Vertex NOT_SET(0, 0);
		std::map<Graph::Vertex, Graph::Vertex> prev;
		initializeMap(graph.getVertexCount(), prev, NOT_SET);
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

	bool checker(const Graph::Vertex& vertex, size_t table_size)
	{
		return 1 <= vertex.column_ && vertex.column_ <= table_size && 1 <= vertex.row_ && vertex.row_ <= table_size;
	}

	GraphAdjList makeAdjList(size_t vertex_count)
	{
		GraphAdjList graph_adj_list(vertex_count, true);
		static std::vector<KnightMove> knight_moves = KnightMove::knightMoves();
		for (size_t i = 1; i < vertex_count + 1; ++i) 
		{
			for (size_t j = 1; j < vertex_count + 1; ++j) 
			{
				Graph::Vertex vertex(i, j);
				for (KnightMove knight_move : knight_moves) 
				{
					Graph::Vertex neighbor(i + knight_move.dx, j + knight_move.dy);
					if (checker(neighbor, vertex_count))
					{
						graph_adj_list.addEdge(vertex, neighbor);
					}
				}
			}
		}
		return graph_adj_list;
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
	GraphAdjList graph_adj_list = GraphProcessing::makeAdjList(n);
	std::vector<Graph::Vertex> min_path = GraphProcessing::getMinPath(graph_adj_list, start, finish);
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
				std::cout << i.column_ << ' ' << i.row_ << std::endl;
			}
		}
	}
	//system("PAUSE");
	return 0;
}