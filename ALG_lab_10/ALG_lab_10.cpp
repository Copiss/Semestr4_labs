/*Лабораторная 10.	
Реализовать алгоритм нахождения эйлерова цикла в неориентированном графе, заданном матрицей смежности.*/

#include <stack>
#include <iostream>
#include <string>
#include <vector>

class Graph 
{
    int q_Vert;                             // Количество вершин в графе
    std::vector<std::vector<int>> adjList;  // Список смежности
    // Метод для добавления ребра между вершинами
    void addVertex(int src, int dest) 
    {
        adjList[src].push_back(dest); // Добавляем вершинку в список смежности
    }

public:
    Graph(int rows_cols) : q_Vert(rows_cols) 
    {
        adjList.resize(q_Vert);
    }
    //Создаём графа из двумерного инициализационного списка
    static Graph create(std::initializer_list<std::initializer_list<int>> data) 
    {
        int rows_cols = data.size();
        Graph graph(rows_cols);

        int rowIndx = 0;
        for (auto row : data) 
        {
            int colmIndx = 0;
            for (auto val : row) 
            {
                if (val != 0) 
                {
                    graph.addVertex(rowIndx, colmIndx);
                }
                ++colmIndx;
            }
            ++rowIndx;
        }
        return graph;
    }
    //Поиска цикла Эйлера в графе
    std::vector<int> algorithEuler(int startVertex) 
    {
        std::vector<int> eulerVert; //Тут будем хранить вершинки эйлерова списка

        std::vector<int> vertDegree(q_Vert, 0); // Тут их степени
        //Собсна, определяем степени по количеству смежных вершин
        for (int u = 0; u < q_Vert; ++u) 
        {
            vertDegree[u] = adjList[u].size();
        }

        std::stack<int> path;   //Стек для хранения пути цикла Эйлера
        path.push(startVertex); //Добавляем начальную вершинку

        while (!path.empty()) //Пока стек не пуст
        {   //Берем вершинку из вершины стека
            int u = path.top();
            //Если степень нулевая, то добавляем её в цикл и удаляем из стека
            if (vertDegree[u] == 0) 
            {
                eulerVert.push_back(u);
                path.pop();
            }
            else 
            {
                bool found = false;
                //Идём по смежным вершинкам
                for (size_t i = 0; i < adjList[u].size(); ++i) 
                {
                    int v = adjList[u][i];

                    if (v != -1) 
                    {
                        path.push(v);//Добавляем смежную вершинку в стек
                        adjList[u].erase(adjList[u].begin() + i);//Удаляем ребро между u и v из списка смежности u
                        for (size_t j = 0; j < adjList[v].size(); ++j) 
                        {
                            if (adjList[v][j] == u) 
                            {
                                adjList[v].erase(adjList[v].begin() + j); //Удаляем ребро между v и u из списка смежности v
                                break;
                            }
                        }//Уменьшаем степени вершин
                        vertDegree[u]--;
                        vertDegree[v]--;
                        found = true;
                        break;
                    }
                }
                if (!found) 
                {
                    path.pop();
                }
            }
        }

        return eulerVert; //Возвращаем цикл Эйлера
    }
};

int main() 
{
    setlocale(LC_ALL, "ru");

    auto graph = Graph::create({
        //A  B  C  D  E 
         {0, 1, 1, 0, 0},//A
         {1, 0, 1, 0, 0},//B
         {1, 1, 0, 1, 1},//C
         {0, 0, 1, 0, 1},//D
         {0, 0, 1, 1, 0} //E
        });

    std::vector<int> vert = graph.algorithEuler(0);

    for (int c : vert) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    return 0;
}