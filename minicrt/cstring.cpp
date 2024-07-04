#include "cstring.h"
#include "minicrt.h"

namespace std {
  string::string(const char *str) : len(0), buf(0) {
    *this = str;
  }

  string::string(const string &s) : len(0), buf(0) {
    *this = s;
  }

  string::~string() {
    if (buf != 0) {
      delete [] buf;
      buf = 0;
    }
  }

  string &string::operator=(const string &s) {
    if (&s == this) {
      return *this;
    }

    this->~string();
    len = s.len;
    
    buf = new char[len + 1];
    strcpy(buf, s.buf);
    return *this;
  }

  string &string::operator=(const char *s) {
    this->~string();
    len = strlen(s);
    buf = new char[len + 1];
    strcpy(buf, s);
    return *this;
  }

  const char &string::operator[](unsigned int index) const {
    return buf[index];
  }

  char &string::operator[](unsigned int index) {
    return buf[index];
  }

  const char *string::c_str() const {
    return buf;
  }

  unsigned int string::length() const {
    return len;
  }

  unsigned string::size() const {
    return len;
  }

  ofstream &operator<<(ofstream &o, const string &s) {
    return o << s.c_str();
  }

}