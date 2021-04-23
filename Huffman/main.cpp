#include "Huffman.h"
#include <iostream>
#include <string>

class Stream: public IInputStream, public IOutputStream{
public:
  explicit Stream(std::string str): str(str), iter(0){};
  bool Read(byte &value) {
    if (iter < str.size()) {
      value = str[iter];
      iter++;
      return true;
    }
    return false;
  }
  void Write(byte value) {
    str += value;
  }
  std::string Full() {
    return str;
  }
private:
  std::string str;
  int iter;
};

int main() {
  Stream str("ABACA");
  Stream str2("");
  Stream str3("");
  Encode((IInputStream &)str, (IOutputStream &)str2);
  std::cout << str2.Full() << std::endl;
  Decode( (IInputStream &)str2, (IOutputStream &)str3);
  std::cout << str3.Full();
  return 0;
}