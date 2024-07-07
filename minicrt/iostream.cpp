#include "iostream.h"
#include "minicrt.h"

namespace std {
  stdout_stream::stdout_stream() : ofstream() {
    fp = stdout;
  }

  stdout_stream cout;

  ofstream::ofstream() : fp(0) {

  }

  ofstream::ofstream(const char *filename, ofstream::openmode mode) : fp(0) {
    open(filename, mode);
  }

  ofstream::~ofstream() {
    close();
  }

  ofstream &ofstream::operator<<(char c) {
    fputc(c, fp);
    return *this;
  }

  ofstream &ofstream::operator<<(int n) {
    fprintf(fp, "%d", n);
    return *this;
  }
  
  ofstream &ofstream::operator<<(const char *str) {
    fprintf(fp, "%s", str);
    return *this;
  }

  ofstream &ofstream::operator<<(ofstream &(*manip)(ofstream &)) {
    return manip(*this);
  }

  void ofstream::open(const char *filename, ofstream::openmode mode) {
    char smode[4];
    close();
    switch (mode) {
        strcpy(smode, "w");
        break;
      case out | in | trunc:
        strcpy(smode, "w+");
        break;
      case out | trunc | binary:
        strcpy(smode, "wb");
        break;
      case out | in | trunc | binary:
        strcpy(smode, "wb+");
        break;
    }

    fp = fopen(filename, smode);
  }

  void ofstream::close() {
    if (fp > stderr) { // not close 0 1 2 
      fclose(fp);
      fp = 0;
    }
  }

  ofstream &ofstream::write(const char *buf, unsigned int size) {
    fwrite(buf, 1, size, fp);
    return *this;
  }
}