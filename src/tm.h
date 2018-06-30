#ifndef BIOX_TM_H
#define BIOX_TM_H

inline float tm0(const char * p) {
  // const char * p = s.get_cstring();
  // t = (len < 14) * (len*2 + nGC*2) +  (len >=14) * (64.9 + 41*(nGC-16.4)/len)
  float t = 0;
  int len = 0;
  int nGC = 0;
  
  for(const char *pi = p; *pi != '\0'; pi++) {
    len ++;
    if(*pi == 'G' || *pi == 'C') nGC++;
  }
  
  if(len == 0) {
    t  = 0;
  } else if (len < 14) {
    t = len * 2 + nGC *2;
  } else if (len >= 14){
    t = 64.9 + 41*(nGC-16.4)/len;
  }
  
  return t;
}

// t = 64.9 + 41*(len-16.4)/len;
// t = 64.9 + 41 - 41*16.4/len;
inline int tm2minL(float t) {
  int l1 = (int)(t / 3);
  int l2 = (int)((-41*16.4) / (t - 64.9-41));
  return std::min(l1, l2);
}

// t = 64.9 + 41*(nGC-16.4)/len;
// t = 64.9 + 41*(0-16.4)/len;
inline int tm2maxL(float t) {
  int l1 = (int) (t / 2);
  int l2 = (int) ((41*16.4) / (64.9+41));
  return std::max(l1, l2);
}

#endif