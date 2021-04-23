#include "Huffman.h"
#include <bitset>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

class HNode{
public:
  HNode(int frequency, byte ch ):
                                  frequency(frequency), symb(ch),
                                  isLeaf(true), left(nullptr),
                                  right(nullptr){};
  explicit HNode(int frequency):frequency(frequency),
                                     symb(0), isLeaf(false),
                                     left(nullptr), right(nullptr){};
  byte symb;
  int frequency;
  bool isLeaf;
  HNode* left;
  HNode* right;
};

struct HNodeCmp {
  bool operator() (HNode* const& left, HNode* const& right) {
    return left->frequency > right->frequency;
  }
};

class Huffman {
  public:
    explicit Huffman(IInputStream& ref):original(ref){};
    ~Huffman()= default;;

    void Encode(IOutputStream& compressed);
    void Decode(IOutputStream& original);

  private:
    vector<byte> words; //копия потока
    map<byte, int> freq; //частота символов
    IInputStream& original; //??
    HNode *root{}; //корень дерева //построение дерева
    map<byte, vector<bool>> Table; //таблица соотношения
    void MakeTable(HNode *current, vector<bool>);
    static vector<byte >BoolToByte(vector<bool> bl);
    static vector<byte >IntToByte(int);
};


vector<byte> Huffman::BoolToByte(vector<bool> bl) {
  vector<byte> result;
  byte value = 0;
  bitset<8> bits{};

  for (int i = 0; i < bl.size(); i=i+8) {
    for (int j = 0; j < 8; ++j) {
      bits.set(j, bl.at(j+i));
    }
    auto vl = bits.to_ulong();
    value = static_cast<byte>(vl);
    result.push_back(value);
  }
  return result;
}
vector<byte> Huffman::IntToByte(int value) {
  vector<byte> result;

  while (value > 0) {
    byte vl = value % 255;
    result.push_back(vl);
    value /= 256;
  }
  while (result.size() != 4) {
    result.insert(result.begin(), 0);
  }
  return result;
}

void Huffman::Encode(IOutputStream &compressed) {
  //копия нашего потока
  auto _stream = new  std::vector<byte>;
  //переменная для записи
  byte value;

  //просто копируем поток
  while(original.Read(value))
  {
    //заодно считаем частоту
    freq[value]++;
    _stream->push_back(value);
  }

  //теперь у нас есть список символов
  //и их частоты
  //всё для очереди с приоритетом
  vector<HNode> nodes;
  map<byte, int>::iterator i;
  for( i = freq.begin(); i != freq.end(); i++ ){
   HNode node(i->second, i->first);
   nodes.push_back(node);
  }

  //теперь делаем дерево
  priority_queue<HNode*, vector<HNode*>, HNodeCmp> queue;
  for (auto & node : nodes) {
    queue.push(&node);
  }

  while (queue.size() > 1) {
    HNode* left = queue.top();
    queue.pop();
    HNode* right = queue.top();
    queue.pop();
    HNode* node = new HNode(left->frequency+right->frequency);
    node->left = left;
    node->right = right;
    queue.push(node);
  }

  HNode* rt = queue.top();
  queue.pop();
  root = rt;

  //а потом делаем таблицу символов
  auto symbols = vector<bool>();
  MakeTable(root, symbols);
  //к этому моменту у нас даже есть символы и их коды
  //сколько байтов нам надо записать?
  int fullByte = 0;

  for (int j = 0; j < _stream->size(); ++j) {
    fullByte += Table[_stream->at(j)].size();
  }
  //сколько вышло всего
  double full = ceil(double(fullByte) / 8);
  //возможно у нас будет не весь байт заполнен, проверяем
  int tail = full*8 - fullByte;

  //записываем сколько букв, сколько хвост у текста
  auto sz = IntToByte(Table.size());
  compressed.Write(sz.at(3));

  auto it = freq.begin();
  for (int j = 0; j < freq.size(); ++j) {
    compressed.Write(it->first);
    auto sz = IntToByte(it->second);
    for (int k = 0; k < sz.size(); ++k) {
      compressed.Write(sz.at(j));
    }
    it++;
  }

  vector<bool> buffer;
  //получаем вектор из битов
  for (int i = 0; i < _stream->size(); ++i) {
    //compressed.Write(_stream->at(i));
    auto  vec = Table[_stream->at(i)];
    for (int j = 0; j < vec.size(); ++j) {
      buffer.push_back(vec.at(j));
    }
  }

  //дополняем до кратного размеру числа
  for (int j = 0; j < tail; ++j) {
    buffer.push_back(false);
  }

  auto cmp = BoolToByte(buffer);
  for (int j = 0; j < cmp.size(); ++j) {
    compressed.Write(cmp.at(j));
  }
}
void Huffman::Decode(IOutputStream& origin) {
  auto _stream = new  std::vector<byte>;
  byte value;
  while (this->original.Read(value)){
    _stream->push_back(value);
  }
  int iter = 0;
  //читаю количество знаков
  int vl = (int)_stream->at(iter);
  iter++;

  cout << vl;
  for (int i = 0; i < vl; ++i) {
    byte ch = _stream->at(iter);
    cout << ch;
    iter++;
    for (int j = 0; j < 4; ++j) {
      ch = _stream->at(iter);
      iter++;
    }
    cout << ch;
  }
}

void Huffman::MakeTable(HNode *current, vector<bool> syms) {

  if (current->isLeaf) {
    this->Table[current->symb] = syms;
    return;
  }

  if (current->left != nullptr) {
    auto symsl = vector<bool>(syms);
    symsl.push_back(false);
    MakeTable(current->left, symsl);
  }

  if (current->right != nullptr) {
    auto symsr = vector<bool>(syms);
    symsr.push_back(true);
    MakeTable(current->right, symsr);
  }

}

void Encode(IInputStream& original, IOutputStream& compressed)
{
  Huffman hf(original);
  hf.Encode(compressed);

}

void Decode(IInputStream& compressed, IOutputStream& original)
{
  Huffman hf(compressed);
  hf.Decode(original);
}
