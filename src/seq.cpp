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
//' revcom(c("AGCT", "AAAA"))
//' 
//' @export
// [[Rcpp::export]]
StringVector revcomp(StringVector ss) {
  int l = ss.length();
  StringVector ss2(l);
  
  #pragma omp parallel for
  for(int i = 0; i < l; i++) {
    ss2[i] = revcomp_(ss[i]);
  }
  return ss2;
}


//' kmers
//' @param s seq
//' @param k kmer size
//' @examples
//' kmers("AGCTTTTTTTTT")
//' kmers("AGCTTTTTTTTT", 4)
//' 
//' @export
//' 
// [[Rcpp::export]]
StringVector kmers(String s, int k = 3) {
  const char * p = s.get_cstring();
  int len = strlen(p);
  if(len < k ) { stop("error, string' len must longer than k"); }
  
  StringVector kms(len-k+1);
  
  #pragma omp parallel for
  for(int offset = 0; offset <= len - k ; offset++){
    char *p2_begin, *p2;
    p2 = p2_begin = new char[len+1];
    strcpy(p2, p);
    // Rprintf("offset: %d\n", offset);
    p2 = p2_begin + offset;
    p2[k] = '\0';
    String si(p2);
    kms[offset] = si;
    p2[k] = p[k];
    delete[] p2_begin;
  }
  
  return kms;
}
