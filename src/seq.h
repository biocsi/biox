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
    case 'a':
      *p2 = 't'; break;
    case 't':
      *p2 = 'a'; break;
    case 'g':
      *p2 = 'c'; break;
    case 'c':
      *p2 = 'g'; break;
      
    case 'N':
      *p2 = 'N'; break;
    case 'n':
      *p2 = 'n'; break;
      
    case 'R':
      *p2 = 'Y'; break;
    case 'Y':
      *p2 = 'R'; break;
    case 'M':
      *p2 = 'K'; break;
    case 'K':
      *p2 = 'M'; break;
    case 'S':
      *p2 = 'W'; break;
    case 'W':
      *p2 = 'S'; break;
    case 'H':
      *p2 = 'D'; break;
    case 'B':
      *p2 = 'V'; break;
    case 'V':
      *p2 = 'B'; break;
    case 'D':
      *p2 = 'H'; break;
      
    case 'r':
      *p2 = 'y'; break;
    case 'y':
      *p2 = 'r'; break;
    case 'm':
      *p2 = 'k'; break;
    case 'k':
      *p2 = 'm'; break;
    case 's':
      *p2 = 'w'; break;
    case 'w':
      *p2 = 's'; break;
    case 'h':
      *p2 = 'd'; break;
    case 'b':
      *p2 = 'v'; break;
    case 'v':
      *p2 = 'b'; break;
    case 'd':
      *p2 = 'h'; break;
      
    default:
      *p2 = 'X'; break;
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
