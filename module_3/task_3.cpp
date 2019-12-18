#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <queue>

using namespace std;

struct IGraph{
    virtual ~IGraph() {};
    // Добавление ребра от from к to.
    //virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const  = 0;

    virtual vector<int> GetNextVertices(int vertex) const = 0;
    virtual vector<int> GetPrevVertices(int vertex) const = 0;
};

class WeightGraph : public IGraph{
public:
    explicit WeightGraph(int n) : graf(n), gsize(n), maxw(0) {}
    //explicit WeightGraph(const std::shared_ptr<IGraph>& igraph);
    void AddEdge(int from, int to, int weight);
    int EdgeWeight(int from, int to);

    int VerticesCount() const;

    vector<int> GetNextVertices(int vertex) const;
    vector<int> GetPrevVertices(int vertex) const;

    bool validate(int vertex);

    int maxw;

private:
    vector<map <int, int>> graf;
    int gsize;
};

//прошло 8 тест
void WeightGraph::AddEdge(int from, int to, int weight){

    if (validate(from) && validate(to)){
      auto it = graf[from].find(to);

      if (it == graf[from].end()){
        graf[from].insert({to, weight});
      }
      else{
        if (it->second > weight){
            maxw -= it->second;
            it->second = weight;
          }
      }
      maxw += weight;
    }
};

//прошло 8 тест
int WeightGraph::EdgeWeight(int from, int to){

  auto it = graf[from].find(to);
  return it != graf[from].end() ? it->second : -1;
};


int WeightGraph::VerticesCount() const{
	return gsize;
};


vector<int> WeightGraph::GetNextVertices(int vertex) const {
    vector<int> result;

    for (const auto &it : graf[vertex]) {
        result.push_back(it.first);
    }
    return result;
}


vector<int> WeightGraph::GetPrevVertices(int vertex) const {
    vector<int> result;

    for (int i = 0; i < gsize; i++) {
    if (graf[i].find(vertex) != graf[i].end())
      {
        result.push_back(i);
      }
    }

    return result;
}

bool WeightGraph::validate(int vertex) {
    return ((vertex >= 0) && (vertex < gsize));
}

int FindWay(WeightGraph* _graph, const int from, const int to){
  //получили количество городов
  int _size = _graph->VerticesCount();
  //путь в каждую вершину из from считаем максимальным
  vector<int> dist(_size, _graph->maxw);
  //путь в самого себя -- нулевой
  dist[from] = 0;

  //набор пар путь:вершина
  set<pair<int, int>> q;
  q.insert({0, from});

  //пока набор не пустой
  while(!q.empty()){
    //взяли вершину
    int current = q.begin()->second;
    //убрали вершину
    q.erase(q.begin());

    //получили список следующих вершин
    auto nextVertices = _graph->GetNextVertices(current);
    //для каждой
    for(const auto& n : nextVertices){
      //узнали, какой вес из текущий
      int w = _graph->EdgeWeight(current, n);

      if (dist[current] + w < dist[n]){
          q.erase({dist[n], n});
          dist[n] = dist[current] + w;
          q.insert({dist[n], n});
      }
    }

  }

  return dist[to];
}

int main(int argc, char const *argv[]) {
  int N = 0; //число городов
  int M = 0; //число дорог

  std::cin >> N;
  std::cin >> M;

  int from = 0;
  int to = 0;
  int time = 0;

  WeightGraph* _graph = new WeightGraph(N);

  for (int i = 0; i < M; i++) {
    std::cin >> from;
    std::cin >> to;
    std::cin >> time;

    _graph->AddEdge(from, to, time);
    _graph->AddEdge(to, from, time);

  }

  cin >> from;
  cin >> to;

  cout << FindWay(_graph, from, to) << '\n';
  return 0;
}
