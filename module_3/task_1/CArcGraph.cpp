#include <iostream>
#include <vector>
#include <memory>

using namespace std;


struct IGraph {
virtual ~IGraph() {}

	// Добавление ребра от from к to.
  virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const  = 0;

virtual std::vector<int> GetNextVertices(int vertex) const = 0;
virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};


class CArcGraph : public IGraph {
public:
    CArcGraph(int num);
    CArcGraph(const std::shared_ptr<IGraph>& igraph);

    bool validate(int ver);

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    vector<int> GetNextVertices(int vertex) const override;
    vector<int> GetPrevVertices(int vertex) const override;
private:
    vector<pair<int, int>> _graph;
    int _size;
};

CArcGraph::CArcGraph(int num): _size(num) {};

CArcGraph::CArcGraph(const std::shared_ptr<IGraph>& igraph) {

    _size = igraph->VerticesCount();

    for (int i = 0; i < _size; i++){
      auto vertices = igraph->GetNextVertices(i);

      for(const auto& n : vertices)
      {
          _graph.emplace_back(i, n);
      }
    }
};


bool CArcGraph::validate(int ver){
  return (ver >= 0) && (ver < _size);
};

void CArcGraph::AddEdge(int from, int to) {
    if (validate(from) && validate(to)){
      _graph.emplace_back(from, to);
    }
};


int CArcGraph::VerticesCount() const {
    return _size;
}

std::vector<int> CArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> next;

    for (const auto& n : _graph){
      if(n.first == vertex){
        next.push_back(n.second);
      }
    }
    return next;
}

std::vector<int> CArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prev;

    for (const auto& n : _graph){
      if(n.second == vertex){
        prev.push_back(n.first);
      }
    }
    return prev;
}
