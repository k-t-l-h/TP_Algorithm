#include <iostream>
#include <cassert>
#include <vector>
#include <memory>
#include <list>
#include <algorithm>
#include <queue>

using namespace std;

struct IGraph {
virtual ~IGraph() {}

	// Добавление ребра от from к to.
  virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const  = 0;

virtual std::vector<int> GetNextVertices(int vertex) const = 0;
virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
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
