#include <iostream>
#include <vector>


class Graph
{
private:
	size_t size;
	std::vector<std::vector<int>> vec;
	
public:
	Graph(size_t input_size) : size(input_size), vec(input_size, std::vector<int>(input_size, 0)) {}

	void AddEdge()
	{
		int number;

		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				std::cin >> number;

				if (number == 1)
				{
					vec[i][j] = 1;
				}
			}

			
		}
	}

	int Count()
	{
		int roads = 0;

		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				if (vec[i][j] == 1)
				{
					roads++;
				}
			}	
		}

		return roads / 2;
	}
}; 

int main()
{
	int n;

	std::cin >> n;

	Graph graph = Graph(n);
	graph.AddEdge();

	std::cout << graph.Count();

	//system("PAUSE");
	return 0;
}