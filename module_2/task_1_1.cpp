#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#define A 7
#define NO -1
#define START 8

using namespace std;

template<class T> struct MyHash;

template<> struct MyHash<string>
{
    size_t operator()(const string str, int m)
    {
        size_t hash = 0;
        for( int i = 0; i < str.size(); i++)
        {
            hash = (hash * A + str[i]);
        }
        return hash % m;
    }
};

template<class Hash = MyHash<string>>
class HashT {
public:

    HashT(int size, Hash hashfunc = MyHash<string>()):
    max_size(size), real_size(0) {
        for( int i = 0; i < max_size; ++i)
            table.push_back(empty);
    };

    HashT& operator = (HashT& Ref)
    {
      if (this == &Ref)
        {
          return *this;
        }

      table = Ref.table;
      max_size = Ref.max_size;
      return *this;

    };

    bool add(string str)  {
      if( find( str ) != NO)
  			return false;
      int h = hash(str, max_size);
      int j = h;
      int step = 0;
  		while( table[j] != empty && table[j] != deleted ) {
  			j = next(h, ++step);
  		}
  		table[j] = str;
      real_size++;

  		if( real_size*4 == max_size*3 ) {
  			grow();
  		}
  		return true;
    };

    bool remove(string str){
        int state = find(str);

        //нет в таблице
        if(state == NO)
            return false;

        //есть в таблице
        table[state] = deleted;
        --real_size;
        return true;

    };

    int find(string str){

      int h = (int)hash(str, max_size);
      int j = h;
      int step = 0;

      if (table[h] == str)
        return h;
      if (table[h] == empty)
        return NO;

		  j = next(h, ++step);

  		while( table[j] != empty ) {

    			if( table[j] == str) {
    				return j;
    			}
    			if( j == h ){
    				return NO;
          }
    			j = next(h, ++step);
    		}
      return NO;
    };

private:
    Hash hash;
    vector<string> table;
    int max_size;
    int real_size;

    string deleted = "DELETE";
    string empty = "EMPTY";

    //функция получает уже хеш строки, чтобы не пересчитывать его
    int next(int hash, int i)  {
        return (hash +  3*i + 8*i*i) % max_size;
    };

    void grow()  {
        HashT<> new_table(max_size*2);

        for (size_t i = 0; i < max_size; i++) {

          if (table[i] != empty && table[i] != deleted)
          {
            new_table.add(table[i]);
          }
        }

        *this = new_table;
    };
};



int main(void) {

    HashT<> mytable(START);
    string state;

    while( getline(cin, state)) {
        if (state.empty())
            continue;

        char command_type;
        string data;
        istringstream stream(state);
        stream >> command_type >> data;

        if( command_type == '+' ) {
            if( mytable.add(data))
                cout << "OK" << endl;
            else
                cout << "FAIL" << endl;
        }
        else if( command_type == '?' ) {
            if( mytable.find(data) != NO  )
                cout << "OK" << endl;
            else
                cout << "FAIL" << endl;
        }
        else if( command_type == '-' ) {
            if( mytable.remove(data))
                cout << "OK" << endl;
            else
                cout << "FAIL" << endl;
        }
    }
    return 0;
}
