This is an update of the rrd package.  In this release I fixed a bug, and added anticonf configuration, so the package gives helpful messages if the system requirements are not installed.

## System requirements

This package requires `librrd-dev` and `rrdtool` as Linux system requirements.

Ubuntu: apt-get install librrd-dev
CentOS: yum install rrdtool-devel
Fedora: dnf install rrdtool-devel

## Test environments

* local Ubuntu 14.04, R-3.6.0
* ubuntu 14.04 (on travis-ci), using R-release, R-devel as well as R-old-release

## Not available on Windows

The package is not yet available on Windows (as indicated with OS_type: unix).

## R CMD check results

0 errors | 0 warnings | 1 note

The package contains a sample RRD file of 12.8Mb - this is necessary both for examples and tests.  RRD files are typically fixed in size, and I selected the smallest sample file I have access to.

