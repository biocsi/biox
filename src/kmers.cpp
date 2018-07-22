#include <Rcpp.h>
#include <omp.h>
#include "tm.h"

using namespace Rcpp;

//' kmers
//' @param s seq
//' @param bin kmer count size
//' @param step kmer count step
//' @examples
//' kmers("AGCTTTTTTTTT")
//' kmers("AGCTTTTTTTTT", 4)
//' 
//' @export
// [[Rcpp::export]]
StringVector kmers(String s, int bin=3, int step=1) {
  const char * p0 = s.get_cstring();
  int len = strlen(p0);
  
  if(len < bin ) { stop("error, string' len must longer than k"); }
  
  StringVector kms((len-bin)/step+1);
  
  char * p2 = new char[len+1];
  strcpy(p2, p0);
  
  char c;
  int i = 0;
  for(int offset = 0; offset <= len - bin; offset += step){
    c = p2[offset+bin];
    p2[offset+bin] = '\0';
    String si(p2+offset);
    kms[i++] = si;
    p2[offset+bin] = c;
  }
  
  delete[] p2;
  return kms;
}


//' get kmers by tm range
//' @export
//' @param s seq
//' @param t0 kmer tm
//' @param dt kmer tm range
//' @examples
//' kmers_tm("AGCTTTTTTTTT", 8)
// [[Rcpp::export]]
StringVector kmers_tm(String s, float t0, float dt=1) {
  const char * p = s.get_cstring();
  int len = strlen(p);
  char * p2 = new char[len+1];
  strcpy(p2, p);
  
  StringVector ss(0);
  
  
  char * p2_begin = p2;
  char * p2_end = p2;
  char p_name[20];
  
  char c;
  int offset = 0;
  for(; *p2_begin != '\0';) {
    p2_begin++; offset++;
    
    int size = 0;
    for(p2_end = p2_begin; *p2_end != '\0'; ++size) {
      p2_end++;
      c = *p2_end;
      *p2_end = '\0';
      if(std::abs(tm0(p2_begin) - t0) < dt) {
        String s_tmp(p2_begin);
        sprintf(p_name, "%d", offset);
        String name(p_name);
        ss.push_back(s_tmp, name);
      }
      *p2_end = c;
    }
  }
  
  return ss;
}