#' Reverse a Vector of Strings
#' 
#' Reverses a vector of 'strings' (a character vector). Not safe for
#' unicode (UTF-8) characters.
#' 
#' 
#' @export
#' @param x a character vector.
#' @examples
#' x <- c("ABC", "DEF", "GHIJ")
#' rev(x)
rev <- function(x) {
  tmp <- .Call("str_rev", as.character(x))
  tmp[ is.na(x) ] <- NA
  return(tmp)
}