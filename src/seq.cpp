#include <Rcpp.h>
#include <omp.h>
#include "seq.h"
using namespace Rcpp;

// [[Rcpp::plugins(openmp)]]

String revcomp_(String s){
  const char * p = s.get_cstring();
  return revcomp0(p);
}

//' reverse complement seq
//' @param ss seq vectors
//' @examples
//' revcomp(c("AGCT", "AAAA"))
//' 
//' @export
// [[Rcpp::export]]
StringVector revcomp(StringVector ss) {
  int l = ss.length();
  StringVector ss2(l);
  
  #pragma omp parallel for
  for(int i = 0; i < l; ++i) {
    ss2[i] = revcomp_(ss[i]);
  }
  return ss2;
}
