## Test environments

* local Ubuntu 14.04, R-3.5.0
* ubuntu 14.04 (on travis-ci), R 3.5.0

## Not available on Windows

The package is not yet available on Windows.  It has a system dependency on librrd, which I haven't yet built for Windows.  However, I've spoken to Jeroen Ooms and he has offered to help with this in future

## R CMD check results

0 errors | 0 warnings | 1 note

The package contains a sample RRD file of 12.8Mb - this is necessary both for examples and tests.  RRD files are typically fixed in size, and I selected the smallest sample file I have access to.

* This is a new release.
