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


class CMatrixGraph : public IGraph {
public:
    CMatrixGraph(int num);
    CMatrixGraph(const std::shared_ptr<IGraph>& igraph);

    bool validate(int ver);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;

    vector<int> GetNextVertices(int vertex) const override;
    vector<int> GetPrevVertices(int vertex) const override;
private:
    //матрица смежности
      vector<vector<int>> _matrix;
    int _size;
};


CMatrixGraph::CMatrixGraph(int num): _matrix(num, vector<int>(num, 0) ){
  _size = num;
};

CMatrixGraph::CMatrixGraph(const std::shared_ptr<IGraph>& igraph){

  _size = igraph->VerticesCount();

  vector<vector<int>> tmp(_size, vector<int>(_size));

  for (int i = 0; i < _size; i++){
    auto vertices = igraph->GetNextVertices(i);
    for (const auto& v : vertices){
      tmp[i][v] = 1;
    }
  }
};

bool CMatrixGraph::validate(int ver){
  return (ver >= 0) && (ver < _size);
};

int CMatrixGraph::VerticesCount() const{
  return _size;
};


vector<int> CMatrixGraph::GetNextVertices(int vertex) const{
  vector<int> next;

  for (int i = 0; i < _size; i++) {

    if(_matrix[vertex][i] == 1){
      next.push_back(i);
    }
  }

  return next;
};

vector<int> CMatrixGraph::GetPrevVertices(int vertex) const{

  vector<int> prev;

  for (int i = 0; i < _size; i++) {

    if(_matrix[i][vertex] == 1){
      prev.push_back(i);
    }
  }
  return prev;
};
