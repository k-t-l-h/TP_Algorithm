#include "Huffman.h"
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
private:
  std::string str;
  int iter;
};

int main() {
  Stream str("feecccbbbbdddddaaaaaa");
  Stream str2("");
  Encode((IInputStream &)str, (IOutputStream &)str2);

  return 0;
}