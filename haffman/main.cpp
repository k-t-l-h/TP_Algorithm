#include "Huffman.h"
#define BSIZE 8

class StreamCopy{
public:
  StreamCopy(IInputStream& stream);
  //bool ReadBit();
  byte ReadByte();

  //long GetCount();
  //bool isEmpty();
  //void restart();
  bool Empty();
private:
  std::vector<byte>* _stream;
  long _position;

};

StreamCopy::StreamCopy(IInputStream& stream){
  _position = 0;
  _stream = new  std::vector<byte>;
  byte value;

  while(stream.Read(value))
  {
    _stream->push_back(value);
  }
};

byte StreamCopy::ReadByte(){
  byte value;
  value = _stream->back();
  _stream->pop_back();
  return value;
};

bool StreamCopy::Empty(){
  return _stream->size()*BSIZE == _position;
};

void Encode(IInputStream& original, IOutputStream& compressed)
{
	StreamCopy* inputcopy = new StreamCopy(original);
  while(!inputcopy->Empty())
  {
    compressed.Write(inputcopy->ReadByte());
  }
}

void Decode(IInputStream& compressed, IOutputStream& original)
{
	StreamCopy* inputcopy = new StreamCopy(compressed);

  while(!inputcopy->Empty())
  {
    original.Write(inputcopy->ReadByte());
  }
}
