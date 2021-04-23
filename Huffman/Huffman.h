#ifndef TP_ALGO_HUFFMAN_H
#define TP_ALGO_HUFFMAN_H

#define interface struct
typedef unsigned char byte;

interface IInputStream {
  virtual bool Read(byte& value) = 0;
};

interface IOutputStream {
  virtual void Write(byte value) = 0;
};

void Encode(IInputStream& original, IOutputStream& compressed);

void Decode(IInputStream& compressed, IOutputStream& original);

#endif // TP_ALGO_HUFFMAN_H
