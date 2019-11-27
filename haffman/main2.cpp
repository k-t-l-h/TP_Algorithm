#include "Huffman.h"
#include <algorithm>
#include <functional>
#include <vector>
#include <array>
#include <map>

#define BSIZE 8
#define ALPHABET_SIZE 256

using namespace std;

//класс работы с потоком
class StreamCopy{
public:
  StreamCopy(IInputStream& stream);
  bool ReadBit();
  byte ReadByte();

  long GetCount();
  void restart();
  bool isEmpty();
private:
  vector<byte>* _stream;
  long _position;

};

StreamCopy::StreamCopy(IInputStream& stream){
  _position = 0;
  _stream = new vector<byte>;
  byte value = 0;

  while(stream.Read(value))
  {
    _stream->push_back(value);
  }
};

byte StreamCopy::ReadByte(){
  long index = _position / BSIZE; //получаем байт
  byte value = _stream->at(index);
  _position += BSIZE;
  return value;
};

bool StreamCopy::ReadBit(){
  long index = _position / BSIZE; //получаем байт
  long inbyteindex = _position % BSIZE; //ищем бит
  bool _bit = ((_stream->at(index)) >> inbyteindex) & 1; //проверка бита
	_position++;
	return _bit;
};

bool StreamCopy::isEmpty(){
  return _stream->size()*BSIZE == _position;
};

long StreamCopy::GetCount(){
  return _stream->size() * BSIZE - _position;
};

void StreamCopy::restart(){
  _position = 0;
};




class CompressedStream{
public:
  CompressedStream(IOutputStream& stream);
  void WriteBit(bool value);
  void WriteByte(byte value);
  void Compress();
private:
  IOutputStream& _original;
  byte _stream;
  long _size;
};

CompressedStream::CompressedStream(IOutputStream& stream):
_original(stream),
_size(0),
_stream(0){
};

void CompressedStream::WriteBit(bool value){
  //установили бит
  _stream |=  (value << (BSIZE - _size - 1));
  //увеличили счетчик
  _size++;
  //если байт полон, записали в поток
  if (_size == BSIZE)
  {
    Compress();
  }
};

void CompressedStream::WriteByte(byte value){
  //если мы на 0 отметке, записали в поток сразу
  if (_size == 0)
  {
    _stream = value;
    Compress();
    return;
  }
  //сдвинули вправо до заполнения
  byte first = value >> _size;
  byte second = value << (BSIZE - _size);
  int tmp = BSIZE - _size;
  _stream |= first;
  Compress();
  _stream |= second;
  _size = tmp;
};

void CompressedStream::Compress(){
  _original.Write(_stream);
  _stream = 0;
  _size = 0;
};

void Encode(IInputStream& original, IOutputStream& compressed)
{
  StreamCopy* inputcopy = new StreamCopy(original);
  CompressedStream* outputcopy = new CompressedStream(compressed);

  while (!inputcopy->isEmpty()) {
    outputcopy->WriteByte(inputcopy->ReadByte());
  }
}

void Decode(IInputStream& compressed, IOutputStream& original)
{
  StreamCopy* inputcopy = new StreamCopy(compressed);
  CompressedStream* outputcopy = new CompressedStream(original);

  while (!inputcopy->isEmpty()) {
    outputcopy->WriteByte(inputcopy->ReadByte());
  }
}
