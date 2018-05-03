#include <Rcpp.h>
#include <stdio.h>
#include <string>

using namespace Rcpp;

// [[Rcpp::export]]
DataFrame read_fa(String file) {
  StringVector names;
  StringVector seqs;
  StringVector comments;
  
  std::string name;
  std::string seq;
  std::string comment;
  
  FILE * fp = fopen(file.get_cstring(), "r");
  int c = '\0';
  int c0 = '\n';
  int state = 2; // 0 for name, 1 for comment , 2 for seq
  int count = 0;
  while( (c= std::fgetc(fp)) != EOF) {
    // Rprintf("c=%c, count=%d, state=%d\n", c, count, state);
    if (c == '>') {
      // name begin
      state = 0;
      if(count == 0) {
        c0 = c;
        count++;
        continue;
      } else if ((count & 0xfff) == 0) {
        Rprintf("count = %d", count);
      }
      if(count > 0) {
        names.push_back(String(name));
        seqs.push_back(String(seq));
        comments.push_back(String(comment));
        
        name.clear();
        seq.clear();
        comment.clear();
      }
      count++;
    } else if (state == 0 && c != '\n' && c != ' ' && c != '\t') {
      name.push_back(c);
      // name continue
    } else if (state == 0 && (c == '\n')) {
      state = 2;
    } else if (state == 0 && (c == ' ' || c == '\t')) {
      // comment begin
      state = 1;
    } else if (state == 1 && c != '\n') {
      comment.push_back(c);
    } else if (state == 1 && c == '\n') {
      // comment end
      state = 2;
    } else if (state == 2 && c != '\n') {
      // seq continue
      seq.push_back(c);
    } else if (state == 2 && c == '\n') {
      // seq break
    } else {
      c0 = c;
      continue;
    }
    
    c0 = c;
  }
  
  names.push_back(String(name));
  seqs.push_back(String(seq));
  comments.push_back(String(comment));
    
  fclose(fp);
  
  DataFrame df = DataFrame::create(
    Named("name") = names,
    Named("seq") = seqs,
    Named("comment") = comments
    );
  
  return df;
}

// [[Rcpp::export]]
DataFrame read_fq(String file) {
  StringVector names;
  StringVector seqs;
  StringVector comments;
  StringVector quals;
  
  std::string name;
  std::string seq;
  std::string comment;
  std::string qual;
  
  FILE * fp = fopen(file.get_cstring(), "r");
  int c = '\0';
  int c0 = '\n';
  int state = 1; // 1 for name, 2 for seq , 3 for comment, 4 for qual
  int count = 0;
  while( (c= std::fgetc(fp)) != EOF) {
    // Rprintf("c=%c, count=%d, state=%d\n", c, count, state);
    if (state == 1 && c == '@' && c0 == '\n') {
      // name begin
      if(count == 0) {
        count++;
        c0 = c;
        continue;
      } else if ((count & 0xfff) == 0) {
        Rprintf("count = %d", count);
      }
      if(count > 0) {
        names.push_back(String(name));
        seqs.push_back(String(seq));
        comments.push_back(String(comment));
        quals.push_back(String(qual));
        
        name.clear();
        seq.clear();
        comment.clear();
        qual.clear();
      }
      count++;
    } else if (state == 1 && c != '\n') {
      if(!(c == '@' && c0 == '\n')) name.push_back(c);
    } else if (state == 1 && c == '\n') {
      state = 2;
    } else if (state == 2 && c != '\n') {
      seq.push_back(c);
    } else if (state == 2 && c == '\n') {
      state = 3;
    } else if (state == 3 && c != '\n') {
      if(!( c == '+' && c0 == '\n')) comment.push_back(c);
    } else if (state == 3 && c == '\n') {
      state = 4;
    } else if (state == 4 && c != '\n') {
      qual.push_back(c);
    } else if (state == 4 && c == '\n') {
      state = 1;
    } else {
      continue;
    }
    
    c0 = c;
  }
  
  names.push_back(String(name));
  seqs.push_back(String(seq));
  comments.push_back(String(comment));
  quals.push_back(String(qual));
  
  fclose(fp);
  
  DataFrame df = DataFrame::create(
    Named("name") = names,
    Named("seq") = seqs,
    Named("qual") = quals,
    Named("comment") = comments
  );
  
  return df;
}