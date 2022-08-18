#' @section Details:
#' 
#' Exposes the following functions:
#' 
#' * [describe_rrd()] to enumerate the archives included in a RRD file.
#' * [read_rrd()] to read an entire RRD file, including all the archives
#' * [read_rra()] to extract a single RRA (round robin archive) from an RRD file
#' 
#' For more information on `RRdtool` and the `RRD` format please refer to the official RRDtool [documentation](https://oss.oetiker.ch/rrdtool/doc/index.en.html) and [tutorials](https://oss.oetiker.ch/rrdtool/tut/index.en.html).
#' 
#' You can also read a more in-depth description of the package in an [R Views](https://rviews.rstudio.com/) blog post [Reading and analyzing log files in the RRD database format](https://rviews.rstudio.com/2018/06/20/reading-rrd-files/).
#' 
#' @section Package history:
#' 
#' Plamen Dimitrov wrote the original proof of concept of the package during a Google [Summer of Code 2014](https://www.google-melange.com/archive/gsoc/2014) project and wrote an accompanying blog post "[R Package for Working With RRD Files](http://plamendimitrov.net/blog/2014/08/09/r-package-for-working-with-rrd-files/)".
#' 
#' Andrie de Vries became maintainer of the package early in 2018, and prepared the package for release to CRAN by adding documentation, examples and unit tests. At this time the API changed so resulting objects are `tibble` objects, making it easier to analyze data using `tidyverse` concepts.  At this time he also published the "R Views" [blog post](https://rviews.rstudio.com/2018/06/20/reading-rrd-files/).
#' 
#' 
#' @name rrd-package
#' @aliases rrd
#' @docType package
#' 
#' @useDynLib rrd, .registration = TRUE
#'  
# @seealso
#' @references <https://oss.oetiker.ch/rrdtool/doc/index.en.html>
#' 
#' @keywords package rrd rrdtool librrd
#' 
#' 
#' @importFrom assertthat assert_that
#' 
"_PACKAGE"



