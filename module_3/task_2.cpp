#include <iostream>
#include <cassert>
#include <vector>
#include <memory>
#include <list>
#include <algorithm>
#include <queue>

using namespace std;

struct IGraph{
    virtual ~IGraph() {};
    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const  = 0;

    virtual vector<int> GetNextVertices(int vertex) const = 0;
    virtual vector<int> GetPrevVertices(int vertex) const = 0;
};

class CListGraph : public IGraph{
public:
    explicit CListGraph(int n) : graf(n), gsize(n) {}
    explicit CListGraph(const std::shared_ptr<IGraph>& igraph);
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    vector<int> GetNextVertices(int vertex) const override;
    vector<int> GetPrevVertices(int vertex) const override;

    bool validate(int vertex);

private:
    vector<list<int>> graf;
    int gsize;
};


void CListGraph::AddEdge(int from, int to) {

    if (validate(from) && validate(to)){
      graf[from].push_back(to);
    }
}

int CListGraph::VerticesCount() const {
    return gsize;
}

vector<int> CListGraph::GetNextVertices(int vertex) const {
    vector<int> result(graf[vertex].begin(), graf[vertex].end());
    return result;
}


vector<int> CListGraph::GetPrevVertices(int vertex) const {
    vector<int> result;
    for (int i = 0; i < gsize; i++){
        if (find(graf[i].begin(), graf[i].end(), vertex) != graf[i].end()){
            result.push_back(i);
        }
    }
    return result;
}

bool CListGraph::validate(int vertex) {
    return ((vertex >= 0) && (vertex < gsize));
}

CListGraph::CListGraph(const std::shared_ptr<IGraph>& igraph) {
    graf.resize(igraph->VerticesCount());
    gsize = igraph->VerticesCount();
    for (int i = 0; i < gsize; i++){
      auto vertices = igraph->GetNextVertices(i);
      std::copy(vertices.begin(), vertices.end(), std::back_inserter(graf[i]));
    }
}


//BFS -- O(V + E)
size_t FindWay(CListGraph* _graph, const size_t from, const size_t to){
  int _size = _graph->VerticesCount();
  std::vector<int> dis(_size);
  std::vector<int> ways(_size);
  std::vector<bool> visited(_size);


  //инициализация
  visited[from] = true;
  dis[from] = 0; //уже в этой точке
  ways[from] = 1;

  //очередь на рассмотрение
  std::queue<int> que;
  que.push(from);

  while(que.size()){
    int current = que.front();
    que.pop();
    //получаем список вершин
    auto nextVertices = _graph->GetNextVertices(current);
    for(const auto& n : nextVertices){
      if(!visited[n]){
        dis[n] = dis[current] + 1;
        visited[n] = true;
        que.push(n);
      }
      if (dis[current] + 1 == dis[n]) {
        ways[n] += ways[current];
      }
    }
  }

  return ways[to];
}



int main(int argc, char const *argv[]) {
  unsigned int V = 0;
  unsigned int N = 0;

  std::cin >> V;
  std::cin >> N;

  unsigned int from = 0;
  unsigned int to = 0;

  CListGraph* _graph = new CListGraph(V);

  for (size_t i = 0; i < N; i++) {
    std::cin >> from;
    std::cin >> to;

    _graph->AddEdge(from, to);
    _graph->AddEdge(to, from);

  }

  cin >> from;
  cin >> to;

  cout << FindWay(_graph, from, to) << '\n';
  return 0;
}
