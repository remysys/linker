#include "iostream.h"

namespace std {
  class string {
    private:
      unsigned int len;
      char *buf;
      
    public:
      explicit string(const char *str);
      string(const string &);
      ~string();

      string &operator=(const char *);
      string &operator=(const string &);
      const char &operator[](unsigned int index) const;
      char &operator[](unsigned int index);

      const char *c_str() const;
      unsigned int length() const;
      unsigned int size() const;
  };

  ofstream &operator<<(ofstream &o, const string &s);
}