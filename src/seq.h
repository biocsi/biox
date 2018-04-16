#ifndef BIOX_SEQ_H
#define BIOX_SEQ_H

#include <Rcpp.h>
using namespace Rcpp;

inline String revcomp0(const char * p) {
  // const char * p = s.get_cstring();
  int l = strlen(p);
  char * p2_begin =  new char[l+1];
  char * p2 = p2_begin + l;
  *(p2) = '\0';
  p2--;

  for(; *p != '\0'; p++) {
    switch(*p){
    case 'A':
      *p2 = 'T'; break;
    case 'T':
      *p2 = 'A'; break;
    case 'G':
      *p2 = 'C'; break;
    case 'C':
      *p2 = 'G'; break;
    }
    p2--;
  }

  String s2(p2_begin);
  delete [] p2_begin;
  return s2;
}

inline String substr(const char * p0, int offset, int len) {
  char * p = new char[len+1];
  p[len] = '\0';
  const char * p0_ = p0 + offset;
  for(int i = 0; i < len; i++){
    *(p+i) = *(p0_+i);
  }
  
  String s(p);
  delete[] p;
  return s;
}

#endif
