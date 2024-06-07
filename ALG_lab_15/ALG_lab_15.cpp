/*Лаборатрная 15.	
Решить задачу о раскраске графа.*/

#include <iostream>
#include <vector>
#include <set>
//Перечисление наших цветов
enum color {
	RED,
	GREEN,
	BLUE,
	WHITE,
	NONE
};
//Это структура вершины графа, тут её назначение и цвет
struct Vertex {
	int dest; 
	color clr;
	Vertex(int _dest) : dest(_dest), clr(color::NONE) {}
};

template <size_t Rows_Colm>
class Graph //Класс графа
{
	int q_Vert;
	std::vector <std::vector<Vertex>> adjList;
	std::vector<bool> visited;
	//можем добавить аершину
	void addVertex(int src, int dest) {
		adjList[src].emplace_back(Vertex(dest));
	}
public:

	Graph() : q_Vert(Rows_Colm) {
		adjList.resize(q_Vert);
		visited.resize(q_Vert);
	}
	//Создание графа из инициализированного списка
	static Graph<Rows_Colm> create(std::initializer_list<std::initializer_list<int>> data) {
		Graph <Rows_Colm> graph;
		int rowIndx = 0;
		for (auto row : data) {
			int colmIndx = 0;
			for (auto val : row) {
				if (val != 0)
					graph.addVertex(rowIndx, colmIndx);
				++colmIndx;
			}
			++rowIndx;
		}
		return graph;
	}
	//Сам метод расскраски графа
	void decorateGraph() {
		std::vector<color> colors(q_Vert, color::WHITE); //Изначально все вершинки задаём белыми

		for (int i = 0; i < q_Vert; ++i) {
			std::set<color> neighborColors;//Цвета соседей
			//Если соседняя вершина имеет цвет, то он добавляется в множество
			for (auto v : adjList[i]) {
				if (colors[v.dest] != color::NONE) {
					neighborColors.insert(colors[v.dest]);
				}
			}
			//Для каждой рассматриваемой вершины мы выбираем первый доступный цвет, которого нет у соседних вершин
			for (int c = 0; c <= 3; ++c) {
				if (!neighborColors.count(static_cast<color>(c))) {
					colors[i] = static_cast<color>(c);
					break;
				}
			}
		}

		for (int i = 0; i < q_Vert; ++i) {
			for (auto& v : adjList[i]) {
				v.clr = colors[v.dest];
			}
		}
	}
	//Вывод гарфа
	void printGraph() {
		std::vector<std::string> colorNames = { "RED", "GREEN", "BLUE", "WHITE", "NONE" };

		for (int i = 0; i < q_Vert; ++i) {
			std::cout << char('A' + i) << ':' << std::endl;
			for (auto v : adjList[i])
				std::cout << char('A' + v.dest) << " - " << colorNames[static_cast<int>(v.clr)] << std::endl;
		}
	}
};

int main() {
	setlocale(LC_ALL, "ru");

	auto graph = Graph<6>::create({
		//   A  B  C  D  E  F
			{0, 1, 1, 1, 0, 0},//A
			{1, 0, 0, 1, 1, 0},//B
			{1, 0, 0, 1, 0, 1},//C
			{1, 1, 1, 0, 0, 0},//D
			{0, 1, 0, 0, 0, 1},//E
			{0, 0, 1, 0, 1, 0},//F
		});
	graph.decorateGraph();
	graph.printGraph();

	return 0;
}