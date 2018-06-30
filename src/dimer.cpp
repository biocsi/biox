#include <Rcpp.h>
#include <omp.h>
#include "tm.h"
#include "seq.h"

using namespace Rcpp;
NumericVector tm(StringVector ss);

//' dimer
//' @export
//' @examples
//' dimer("AG", "CT")
//' dimer("AG", "CCCT")
//' dimer("AG", "CTCC")
//' dimer("CCCT", "AG")
// [[Rcpp::export]]

String dimer(String s1, String s2) {
  const char * p1 = s1.get_cstring();
  const char * p2 = s2.get_cstring();
  int l1 = strlen(p1); int l2 = strlen(p2);
  int lmin = std::min(l1, l2);
  String s2v = revcomp0(p2);
  const char * p2v = s2v.get_cstring();
  
  int overlap = lmin;
  for ( ; overlap >=0; overlap--){
    //Rcout << "overlap:" << overlap << std::endl;
    int i = 0;
    for (; i < overlap; i++) {
      //Rcout << i << std::endl;
      if (*(p1+l1-overlap+i) != *(p2v+i)) break;
    }
    if (i == overlap) break;
  }
  
  return String(p1+l1-overlap);
}

//' @export
// [[Rcpp::export]]
StringVector dimer_v(StringVector ss1, StringVector ss2) {
  int l1 = ss1.length();
  int l2 = ss2.length();
  if(l1 != l2) stop("ss1 length must equal ss2 length.");
  
  StringVector ss(l1);
  
  for(int i = 0; i < l1 ; i++){
    ss[i] = dimer(ss1[i], ss2[i]);
  }
  
  return ss;
}

//' @export
// [[Rcpp::export]]
NumericVector dimer_test(StringVector ss, float cutoff=18.0) {
  int l = ss.length();
  NumericVector nn(l);
  
  for(int i = 0; i < l; i++){
    if(i % 1000 == 0)
      Rcout << i << '\n';
    nn[i] = 0;
    for(int j = 0; j < l; j++){
      if(dimer(ss[i], ss[j]) > cutoff) {
        nn[i]++;
      }
    }
  }
  
  return nn;
}

//' @export
// [[Rcpp::export]]
NumericVector dimer_tm_v(StringVector ss1, StringVector ss2) {
  int l1 = ss1.length();
  int l2 = ss2.length();
  if(l1 != l2) stop("ss1 length must equal ss2 length.");
  
  NumericVector tt = tm(dimer_v(ss1, ss2));
  return tt;
}
