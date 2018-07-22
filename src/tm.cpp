#include <Rcpp.h>
#include <omp.h>
#include "tm.h"

using namespace Rcpp;

// [[Rcpp::plugins(openmp)]]
float tm_(String s) {
  const char * p = s.get_cstring();
  // t = (len < 14) * (len*2 + nGC*2) +  (len >=14) * (64.9 + 41*(nGC-16.4)/len)
  int t = tm0(p);
  return t;
}

//' @export
// [[Rcpp::export]]
NumericVector tm(StringVector ss) {
  int l  = ss.size();
  NumericVector tt(l);
  for(int i = 0; i< l; i++){
    tt[i] = tm_(ss[i]);
  }
  return tt;
}