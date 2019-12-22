#include <vector>
#include <memory>
#include <unordered_set>
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


class CSetGraph : public IGraph {
public:
    CSetGraph(int num): _size(num) {};
    CSetGraph(const std::shared_ptr<IGraph> &igraph);

    bool validate(int ver);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    vector<int> GetNextVertices(int vertex) const override;
    vector<int> GetPrevVertices(int vertex) const override;
private:
    vector<unordered_set<int>> setVector;
    int _size;
};


int CSetGraph::VerticesCount() const{
  return _size;
};

bool CSetGraph::validate(int ver){
  return ((ver >= 0) && (ver < _size));
};


void CSetGraph::AddEdge(int from, int to){
  if (validate(from) && validate(to)){
    setVector[from].insert(to);
  }
};

vector<int> CSetGraph::GetNextVertices(int vertex) const {

    vector<int> next(setVector[vertex].begin(), setVector[vertex].end());

    return next;
};

vector<int> CSetGraph::GetPrevVertices(int vertex) const {
    vector<int> prev;
    for (int i = 0; i < _size; i++){

        if ( setVector[i].find(vertex) != setVector[i].end())
            prev.push_back(i);
    }
    return prev;
};


CSetGraph::CSetGraph(const std::shared_ptr<IGraph> &igraph) {
    _size = igraph->VerticesCount();
    setVector.reserve(_size);

    for (int i = 0; i < _size; i++) {
        auto vecVert = igraph->GetNextVertices(i);
        setVector.emplace_back(vecVert.begin(), vecVert.end());
    }
};
