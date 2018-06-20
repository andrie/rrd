#' Import data from a RRD database into R
#' 
#' The package uses `librrd` to import the numerical data in a rrd database
#' directly into R data structures without using intermediate formats.
#' 
#' Exposes the following functions:
#' 
#' * [describe_rrd()] to enumerate the archives included in a RRD file.
#' * [read_rrd()] to read an entire RRD file, including all the archives
#' * [read_rra()] to extract a single RRA (round robin archive) from an RRD file
#' 
#' For more information on `RRdtool` and the `RRD` format please refer to the official RRDtool [documentation](http://oss.oetiker.ch/rrdtool/doc/index.en.html) and [tutorials](http://oss.oetiker.ch/rrdtool/tut/index.en.html).
#' 
#' You can also read a more in-depth description of the package in a [blog post](http://plamendimitrov.net/blog/2014/08/09/r-package-for-working-with-rrd-files/).
#' 
#' 
#' @name rrd-package
#' @docType package
#' 
#' @useDynLib rrd, .registration = TRUE
#'  
# @seealso
#' @references <http://oss.oetiker.ch/rrdtool/doc/index.en.html>
#' @references <https://github.com/pldimitrov/rrd>
#' 
#' @keywords package rrd rrdtool librrd
#' 
#' 
#' @importFrom assertthat assert_that
#' 
NULL



