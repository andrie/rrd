# Build against mingw-w64 build of rrdtool
VERSION <- commandArgs(TRUE)
if(!file.exists(sprintf("../windows/rrdtool-%s/include/openssl/rrd.h", VERSION))){
  download.file(sprintf("https://github.com/rwinlib/rrdtool/archive/%s.zip", VERSION),
                "lib.zip", quiet = TRUE)
  dir.create("../windows", showWarnings = FALSE)
  unzip("lib.zip", exdir = "../windows")
  unlink("lib.zip")
}
