I'm resubmitting after fixing CRAN's request to change backticks to straight single quotes in the description.

This is an update of the rrd package with an updated configuration script that attempts to fix the note (on Linux) and error (on Mac OS) on the CRAN build machines.

This update makes no functional changes.

## R CMD check results

0 errors | 0 warnings | 1 note

The package contains a sample RRD file of 12.8Mb - this is necessary both for examples and tests.  RRD files are typically fixed in size, and I selected the smallest sample file I have access to.

