#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Функция для выполнения BFS и нахождения кратчайших путей
void BFS(int start, const vector<vector<int>>& graph, vector<int>& distance) {
    int n = graph.size();  // количество вершин в графе
    queue<int> q;          // очередь для BFS

    // Инициализация всех расстояний как бесконечность
    fill(distance.begin(), distance.end(), INT_MAX);
    distance[start] = 0;  // расстояние до начальной вершины равно 0

    q.push(start);  // добавляем начальную вершину в очередь

    while (!q.empty()) {
        int current = q.front();  // извлекаем текущую вершину
        q.pop();                  // удаляем её из очереди

        // Обрабатываем все соседние вершины
        for (int neighbor : graph[current]) {
            if (distance[neighbor] == INT_MAX) {  // если вершина ещё не посещена
                distance[neighbor] = distance[current] + 1;  // обновляем расстояние
                q.push(neighbor);  // добавляем соседнюю вершину в очередь
            }
        }
    }
}

// Функция для вывода кратчайших расстояний
void printDistances(const vector<int>& distance) {
    for (int i = 0; i < distance.size(); ++i) {
        if (distance[i] == INT_MAX)
            cout << "Вершина " << i + 1 << ": недостижима" << endl;
        else
            cout << "Вершина " << i + 1 << ": " << distance[i] << endl;
    }
}

int main() {
    // Пример графа (неориентированный граф с единичными длинами рёбер)
    int n = 6;  // количество вершин
    vector<vector<int>> graph(n);

    // Добавляем рёбра (граф представлен списком смежности)
    graph[0] = {1, 3};  // вершина 1 соединена с вершинами 2 и 4
    graph[1] = {0, 2};  // вершина 2 соединена с вершинами 1 и 3
    graph[2] = {1, 3, 4};  // вершина 3 соединена с вершинами 2, 4 и 5
    graph[3] = {0, 2, 5};  // вершина 4 соединена с вершинами 1, 3 и 6
    graph[4] = {2};  // вершина 5 соединена с вершиной 3
    graph[5] = {3};  // вершина 6 соединена с вершиной 4

    // Вектор для хранения расстояний
    vector<int> distance(n);

    // Запуск BFS от вершины 0 (1-я вершина, индекс 0)
    BFS(0, graph, distance);

    // Вывод результатов
    printDistances(distance);

    return 0;
}
