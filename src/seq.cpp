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
  
//  #pragma omp parallel for
  for(int i = 0; i < l; ++i) {
    ss2[i] = revcomp_(ss[i]);
  }
  return ss2;
}

String transcribe_(String s) {
  const char * p = s.get_cstring();
  return transcribe0(p);
}

//' transcription, from DNA to RNA
//' @examples
//' transcribe("AGCT") # "AGCU"
//' 
//' @export
// [[Rcpp::export]]
StringVector transcribe(StringVector ss) {
  int l = ss.length();
  StringVector ss2(l);
  
//  #pragma omp parallel for
  for(int i = 0; i < l; ++i) {
    ss2[i] = transcribe_(ss[i]);
  }
  return ss2;
}


String translate_(String s, int offset) {
  const char * p = s.get_cstring();
  return translate0(p, offset);
}

//' translation, from RNA to AA
//' @examples
//' transcribe("AGCU") # "AGCU"
//' 
//' @export
// [[Rcpp::export]]
StringVector translate(StringVector ss, int offset = 0) {
  int l = ss.length();
  StringVector ss2(l);
  
//#pragma omp parallel for
  for(int i = 0; i < l; ++i) {
    ss2[i] = translate_(ss[i], offset);
  }
  return ss2;
}

