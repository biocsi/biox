#ifndef BIOX_SEQ_H
#define BIOX_SEQ_H

#include <Rcpp.h>
using namespace Rcpp;

inline int base_code(char c) {
  int i = 0;
  switch(c) {
  case 'U':
    i = 0; break;
  case 'C':
    i = 1; break;
  case 'A':
    i = 2; break;
  case 'G':
    i = 3; break;
  default:
    i = 64; break;
  }
  return i;
}

inline int base3_code(char b1, char b2, char b3) {
  int code = base_code(b1) * 16 + base_code(b2) * 4 + base_code(b3);
  if (code >= 64) { code = 64; }
  return code;
}

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

inline String transcribe0(const char * p) {
  // const char * p = s.get_cstring();
  int l = strlen(p);
  char * p2_begin =  new char[l+1];
  char * p2 = p2_begin;
  
  char c = '\0';
  for (int i =0; i <= l; ++i) {
    c = *(p+i);
    switch (c) {
    case 'T':
      *(p2+i) = 'U'; break;
    default:
      *(p2+i) = c;
    }
  }
  String s2(p2_begin);
  delete [] p2_begin;
  return s2;
}

inline String translate1(const char * p, int offset) {
  // const char * p = s.get_cstring();
  const char * pi = p + offset;
  int l = strlen(pi);
  int l2 = l/3 + 1;
  char * p2_begin =  new char[l2];
  char * p2 = p2_begin;
  
  char b1, b2, b3;
  
  for (int i =0; i < l2 - 1; ++i) {
    b1 = *(pi + (3*i));
    b2 = *(pi + (3*i) + 1);
    b3 = *(pi + (3*i) + 2);
    if      (b1 == 'U' && b2 == 'U' && b3 == 'U') { *(p2+i) = 'F'; } 
    else if (b1 == 'U' && b2 == 'U' && b3 == 'C') { *(p2+i) = 'F'; }
    else if (b1 == 'U' && b2 == 'U' && b3 == 'A') { *(p2+i) = 'L'; }
    else if (b1 == 'U' && b2 == 'U' && b3 == 'G') { *(p2+i) = 'L'; }
    
    else if (b1 == 'U' && b2 == 'C' && b3 == 'U') { *(p2+i) = 'S'; } 
    else if (b1 == 'U' && b2 == 'C' && b3 == 'C') { *(p2+i) = 'S'; }
    else if (b1 == 'U' && b2 == 'C' && b3 == 'A') { *(p2+i) = 'S'; }
    else if (b1 == 'U' && b2 == 'C' && b3 == 'G') { *(p2+i) = 'S'; }
    
    else if (b1 == 'U' && b2 == 'A' && b3 == 'U') { *(p2+i) = 'Y'; } 
    else if (b1 == 'U' && b2 == 'A' && b3 == 'C') { *(p2+i) = 'Y'; }
    else if (b1 == 'U' && b2 == 'A' && b3 == 'A') { *(p2+i) = '.'; }
    else if (b1 == 'U' && b2 == 'A' && b3 == 'G') { *(p2+i) = '.'; }
    
    else if (b1 == 'U' && b2 == 'G' && b3 == 'U') { *(p2+i) = 'C'; } 
    else if (b1 == 'U' && b2 == 'G' && b3 == 'C') { *(p2+i) = 'C'; }
    else if (b1 == 'U' && b2 == 'G' && b3 == 'A') { *(p2+i) = '.'; }
    else if (b1 == 'U' && b2 == 'G' && b3 == 'G') { *(p2+i) = 'W'; }
    
    else if (b1 == 'C' && b2 == 'U' && b3 == 'U') { *(p2+i) = 'L'; } 
    else if (b1 == 'C' && b2 == 'U' && b3 == 'C') { *(p2+i) = 'L'; }
    else if (b1 == 'C' && b2 == 'U' && b3 == 'A') { *(p2+i) = 'L'; }
    else if (b1 == 'C' && b2 == 'U' && b3 == 'G') { *(p2+i) = 'L'; }
    
    else if (b1 == 'C' && b2 == 'C' && b3 == 'U') { *(p2+i) = 'P'; } 
    else if (b1 == 'C' && b2 == 'C' && b3 == 'C') { *(p2+i) = 'P'; }
    else if (b1 == 'C' && b2 == 'C' && b3 == 'A') { *(p2+i) = 'P'; }
    else if (b1 == 'C' && b2 == 'C' && b3 == 'G') { *(p2+i) = 'P'; }
    
    else if (b1 == 'C' && b2 == 'A' && b3 == 'U') { *(p2+i) = 'H'; } 
    else if (b1 == 'C' && b2 == 'A' && b3 == 'C') { *(p2+i) = 'H'; }
    else if (b1 == 'C' && b2 == 'A' && b3 == 'A') { *(p2+i) = 'Q'; }
    else if (b1 == 'C' && b2 == 'A' && b3 == 'G') { *(p2+i) = 'Q'; }
    
    else if (b1 == 'C' && b2 == 'G' && b3 == 'U') { *(p2+i) = 'R'; } 
    else if (b1 == 'C' && b2 == 'G' && b3 == 'C') { *(p2+i) = 'R'; }
    else if (b1 == 'C' && b2 == 'G' && b3 == 'A') { *(p2+i) = 'R'; }
    else if (b1 == 'C' && b2 == 'G' && b3 == 'G') { *(p2+i) = 'R'; }
    
    else if (b1 == 'A' && b2 == 'U' && b3 == 'U') { *(p2+i) = 'I'; } 
    else if (b1 == 'A' && b2 == 'U' && b3 == 'C') { *(p2+i) = 'I'; }
    else if (b1 == 'A' && b2 == 'U' && b3 == 'A') { *(p2+i) = 'M'; }
    else if (b1 == 'A' && b2 == 'U' && b3 == 'G') { *(p2+i) = 'M'; }
    
    else if (b1 == 'A' && b2 == 'C' && b3 == 'U') { *(p2+i) = 'T'; } 
    else if (b1 == 'A' && b2 == 'C' && b3 == 'C') { *(p2+i) = 'T'; }
    else if (b1 == 'A' && b2 == 'C' && b3 == 'A') { *(p2+i) = 'T'; }
    else if (b1 == 'A' && b2 == 'C' && b3 == 'G') { *(p2+i) = 'T'; }
    
    else if (b1 == 'A' && b2 == 'A' && b3 == 'U') { *(p2+i) = 'N'; } 
    else if (b1 == 'A' && b2 == 'A' && b3 == 'C') { *(p2+i) = 'N'; }
    else if (b1 == 'A' && b2 == 'A' && b3 == 'A') { *(p2+i) = 'K'; }
    else if (b1 == 'A' && b2 == 'A' && b3 == 'G') { *(p2+i) = 'K'; }
    
    else if (b1 == 'A' && b2 == 'G' && b3 == 'U') { *(p2+i) = 'S'; } 
    else if (b1 == 'A' && b2 == 'G' && b3 == 'C') { *(p2+i) = 'S'; }
    else if (b1 == 'A' && b2 == 'G' && b3 == 'A') { *(p2+i) = 'R'; }
    else if (b1 == 'A' && b2 == 'G' && b3 == 'G') { *(p2+i) = 'R'; }
    
    else if (b1 == 'G' && b2 == 'U' && b3 == 'U') { *(p2+i) = 'V'; } 
    else if (b1 == 'G' && b2 == 'U' && b3 == 'C') { *(p2+i) = 'V'; }
    else if (b1 == 'G' && b2 == 'U' && b3 == 'A') { *(p2+i) = 'V'; }
    else if (b1 == 'G' && b2 == 'U' && b3 == 'G') { *(p2+i) = 'V'; }
    
    else if (b1 == 'G' && b2 == 'C' && b3 == 'U') { *(p2+i) = 'A'; } 
    else if (b1 == 'G' && b2 == 'C' && b3 == 'C') { *(p2+i) = 'A'; }
    else if (b1 == 'G' && b2 == 'C' && b3 == 'A') { *(p2+i) = 'A'; }
    else if (b1 == 'G' && b2 == 'C' && b3 == 'G') { *(p2+i) = 'A'; }
    
    else if (b1 == 'G' && b2 == 'A' && b3 == 'U') { *(p2+i) = 'D'; } 
    else if (b1 == 'G' && b2 == 'A' && b3 == 'C') { *(p2+i) = 'D'; }
    else if (b1 == 'G' && b2 == 'A' && b3 == 'A') { *(p2+i) = 'E'; }
    else if (b1 == 'G' && b2 == 'A' && b3 == 'G') { *(p2+i) = 'E'; }
    
    else if (b1 == 'G' && b2 == 'G' && b3 == 'U') { *(p2+i) = 'G'; } 
    else if (b1 == 'G' && b2 == 'G' && b3 == 'C') { *(p2+i) = 'G'; }
    else if (b1 == 'G' && b2 == 'G' && b3 == 'A') { *(p2+i) = 'G'; }
    else if (b1 == 'G' && b2 == 'G' && b3 == 'G') { *(p2+i) = 'G'; }
    
    else                                          { *(p2+i) = '*'; }
  }
  String s2(p2_begin);
  delete [] p2_begin;
  return s2;
}

inline String translate0(const char * p, int offset) {
  // const char * p = s.get_cstring();
  const char * pi = p + offset;
  int l = strlen(pi);
  int l2 = l/3 + 1;
  char * p2_begin =  new char[l2];
  char * p2 = p2_begin;
  
  char b1, b2, b3;
  
  char genetic_codes[65] = { 
    'F', 'F', 'L', 'L',
    'S', 'S', 'S', 'S',
    'Y', 'Y', '.', '.',
    'C', 'C', '.', 'W',
    
    'L', 'L', 'L', 'L',
    'P', 'P', 'P', 'P',
    'H', 'H', 'Q', 'Q',
    'R', 'R', 'R', 'R',
    
    'I', 'I', 'M', 'M',
    'T', 'T', 'T', 'T',
    'N', 'N', 'K', 'K',
    'S', 'S', 'R', 'R',
    
    'V', 'V', 'V', 'V',
    'A', 'A', 'A', 'A',
    'D', 'D', 'E', 'E',
    'G', 'G', 'G', 'G',
    '*'
  };
  
  for (int i =0; i < l2 - 1; ++i) {
    b1 = *(pi + (3*i));
    b2 = *(pi + (3*i) + 1);
    b3 = *(pi + (3*i) + 2);
    *(p2+i) = genetic_codes[base3_code(b1, b2, b3)];
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
