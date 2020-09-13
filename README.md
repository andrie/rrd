
<!-- README.md is generated from README.Rmd. Please edit that file -->

# rrd <img src='man/figures/logo.svg' align="right" height="139" />

<!-- badges: start -->

[![R build
status](https://github.com/andrie/rrd/workflows/R-CMD-check/badge.svg)](https://github.com/andrie/rrd/actions)
[![CRAN
status](https://www.r-pkg.org/badges/version/rrd)](https://cran.r-project.org/package=rrd)
[![lifecycle](https://img.shields.io/badge/lifecycle-maturing-blue.svg)](https://www.tidyverse.org/lifecycle/#maturing)
[![](http://www.r-pkg.org/badges/version/rrd)](http://www.r-pkg.org/pkg/rrd)
[![CRAN RStudio mirror
downloads](http://cranlogs.r-pkg.org/badges/rrd)](http://www.r-pkg.org/pkg/rrd)
[![Codecov test
coverage](https://codecov.io/gh/andrie/rrd/branch/master/graph/badge.svg)](https://codecov.io/gh/andrie/rrd?branch=master)
<!-- badges: end -->

The `rrd` package allows you to read data from an
[RRD](https://oss.oetiker.ch/rrdtool/) Round Robin Database.

## Installation

### System requirements

In order to build the package from source you need
[librrd](https://oss.oetiker.ch/rrdtool/doc/librrd.en.html). Installing
[RRDtool](https://oss.oetiker.ch/rrdtool/) from your package manager
will usually also install the library.

| Platform        | Installation                 | Reference                                               |
| --------------- | ---------------------------- | ------------------------------------------------------- |
| Debian / Ubuntu | `apt-get install librrd-dev` |                                                         |
| RHEL / CentOS   | `yum install rrdtool-devel`  |                                                         |
| Fedora          | `yum install rrdtool-devel`  | <https://apps.fedoraproject.org/packages/rrdtool-devel> |
| Solaris / CSW   | Install `rrdtool`            | <https://www.opencsw.org/packages/rrdtool/>             |
| OSX             | `brew install rrdtool`       |                                                         |
| Windows         | Not available                |                                                         |

Note: on OSX you may have to update `xcode`, using `xcode-select
--install`.

### Package installation

You can install the stable version of the package from CRAN:

``` r
install.packages("rrd")
```

And the development version from [GitHub](https://github.com/):

``` r
# install.packages("remotes")
remotes::install_github("andrie/rrd")
```

## About RRD and RRDtool <img src='man/figures/rrdtool-logo.png' align="right" height="70" />

The `rrd` package is a wrapper around `RRDtool`. Internally it uses
[librrd](https://oss.oetiker.ch/rrdtool/doc/librrd.en.html) to import
the binary data directly into R without exporting it to an intermediate
format first.

For an introduction to RRD database, see
<https://oss.oetiker.ch/rrdtool/tut/rrd-beginners.en.html>

## Example

The package contains some example RRD files that originated in an
instance of RStudio Connect. In this example, you analyse CPU data in
the file `cpu-0.rrd`.

Load the package and assign the location of the `cpu-0.rrd` file to a
variable:

``` r
library(rrd)
rrd_cpu_0 <- system.file("extdata/cpu-0.rrd", package = "rrd")
```

To describe the contents of an RRD file, use `describe_rrd()`:

``` r
describe_rrd(rrd_cpu_0)
#> An RRD file with 10 RRA arrays and step size 60
#> [1] AVERAGE_60 (43200 rows)
#> [2] AVERAGE_300 (25920 rows)
#> [3] MIN_300 (25920 rows)
#> [4] MAX_300 (25920 rows)
#> [5] AVERAGE_3600 (8760 rows)
#> [6] MIN_3600 (8760 rows)
#> [7] MAX_3600 (8760 rows)
#> [8] AVERAGE_86400 (1825 rows)
#> [9] MIN_86400 (1825 rows)
#> [10] MAX_86400 (1825 rows)
```

To read an entire RRD file, i.e. all of the RRA archives, use
`read_rrd()`. This returns a list of `tibble` objects:

``` r
cpu <- read_rrd(rrd_cpu_0)

str(cpu, max.level = 1)
#> List of 10
#>  $ AVERAGE60   : tibble [43,199 × 9] (S3: tbl_df/tbl/data.frame)
#>  $ AVERAGE300  : tibble [25,919 × 9] (S3: tbl_df/tbl/data.frame)
#>  $ MIN300      : tibble [25,919 × 9] (S3: tbl_df/tbl/data.frame)
#>  $ MAX300      : tibble [25,919 × 9] (S3: tbl_df/tbl/data.frame)
#>  $ AVERAGE3600 : tibble [8,759 × 9] (S3: tbl_df/tbl/data.frame)
#>  $ MIN3600     : tibble [8,759 × 9] (S3: tbl_df/tbl/data.frame)
#>  $ MAX3600     : tibble [8,759 × 9] (S3: tbl_df/tbl/data.frame)
#>  $ AVERAGE86400: tibble [1,824 × 9] (S3: tbl_df/tbl/data.frame)
#>  $ MIN86400    : tibble [1,824 × 9] (S3: tbl_df/tbl/data.frame)
#>  $ MAX86400    : tibble [1,824 × 9] (S3: tbl_df/tbl/data.frame)
```

Since the resulting object is a list of `tibble`s, you can easily work
with individual data frames:

``` r
names(cpu)
#>  [1] "AVERAGE60"    "AVERAGE300"   "MIN300"       "MAX300"       "AVERAGE3600" 
#>  [6] "MIN3600"      "MAX3600"      "AVERAGE86400" "MIN86400"     "MAX86400"

cpu[[1]]
#> [90m# A tibble: 43,199 x 9[39m
#>    timestamp              user     sys  nice  idle  wait   irq softirq   stolen
#>    [3m[90m<dttm>[39m[23m                [3m[90m<dbl>[39m[23m   [3m[90m<dbl>[39m[23m [3m[90m<dbl>[39m[23m [3m[90m<dbl>[39m[23m [3m[90m<dbl>[39m[23m [3m[90m<dbl>[39m[23m   [3m[90m<dbl>[39m[23m    [3m[90m<dbl>[39m[23m
#> [90m 1[39m 2018-04-02 [90m12:24:00[39m 0.010[4m4[24m  0.008[4m1[24m[4m1[24m     0 0.981     0     0       0 0.000[4m1[24m[4m3[24m[4m7[24m
#> [90m 2[39m 2018-04-02 [90m12:25:00[39m 0.012[4m6[24m  0.006[4m3[24m[4m0[24m     0 0.979     0     0       0 0.001[4m9[24m[4m2[24m 
#> [90m 3[39m 2018-04-02 [90m12:26:00[39m 0.015[4m9[24m  0.008[4m0[24m[4m8[24m     0 0.976     0     0       0 0       
#> [90m 4[39m 2018-04-02 [90m12:27:00[39m 0.008[4m5[24m[4m3[24m 0.006[4m4[24m[4m7[24m     0 0.985     0     0       0 0       
#> [90m 5[39m 2018-04-02 [90m12:28:00[39m 0.012[4m2[24m  0.009[4m9[24m[4m9[24m     0 0.978     0     0       0 0       
#> [90m 6[39m 2018-04-02 [90m12:29:00[39m 0.010[4m6[24m  0.006[4m0[24m[4m4[24m     0 0.983     0     0       0 0       
#> [90m 7[39m 2018-04-02 [90m12:30:00[39m 0.014[4m7[24m  0.004[4m2[24m[4m7[24m     0 0.981     0     0       0 0.000[4m1[24m[4m3[24m[4m7[24m
#> [90m 8[39m 2018-04-02 [90m12:31:00[39m 0.019[4m3[24m  0.007[4m6[24m[4m7[24m     0 0.971     0     0       0 0.001[4m9[24m[4m1[24m 
#> [90m 9[39m 2018-04-02 [90m12:32:00[39m 0.030[4m0[24m  0.027[4m4[24m      0 0.943     0     0       0 0       
#> [90m10[39m 2018-04-02 [90m12:33:00[39m 0.016[4m2[24m  0.006[4m1[24m[4m7[24m     0 0.978     0     0       0 0.000[4m1[24m[4m3[24m[4m7[24m
#> [90m# … with 43,189 more rows[39m

tail(cpu$AVERAGE60$sys)
#> [1] 0.0014390667 0.0020080000 0.0005689333 0.0000000000 0.0014390667
#> [6] 0.0005689333
```

To read a single RRA archive from an RRD file, use `read_rra()`. To use
this function, you must specify several arguments that define the
specific data to retrieve. This includes the consolidation function
(e.g. “AVERAGE”) and time step (e.g. 60), the `end` time. You must also
specifiy either the `start` time, or the number of steps, `n_steps`.

In this example, you extract the average for 1 minute periods (`step
= 60`), for one entire day (`n_steps = 24 * 60`):

``` r
end_time <- as.POSIXct("2018-05-02") # timestamp with data in example
avg_60 <- read_rra(rrd_cpu_0, cf = "AVERAGE", step = 60, n_steps = 24 * 60,
                     end = end_time)

avg_60
#> [90m# A tibble: 1,440 x 9[39m
#>    timestamp              user     sys  nice  idle    wait   irq softirq  stolen
#>    [3m[90m<dttm>[39m[23m                [3m[90m<dbl>[39m[23m   [3m[90m<dbl>[39m[23m [3m[90m<dbl>[39m[23m [3m[90m<dbl>[39m[23m   [3m[90m<dbl>[39m[23m [3m[90m<dbl>[39m[23m   [3m[90m<dbl>[39m[23m   [3m[90m<dbl>[39m[23m
#> [90m 1[39m 2018-05-01 [90m00:01:00[39m 0.004[4m5[24m[4m8[24m 2.01[90me[39m[31m-3[39m     0 0.992 0.  [90m [39m       0       0 1.44[90me[39m[31m-3[39m
#> [90m 2[39m 2018-05-01 [90m00:02:00[39m 0.002[4m5[24m[4m8[24m 5.70[90me[39m[31m-4[39m     0 0.996 0.  [90m [39m       0       0 5.70[90me[39m[31m-4[39m
#> [90m 3[39m 2018-05-01 [90m00:03:00[39m 0.006[4m3[24m[4m3[24m 1.44[90me[39m[31m-3[39m     0 0.992 0.  [90m [39m       0       0 0.  [90m [39m  
#> [90m 4[39m 2018-05-01 [90m00:04:00[39m 0.005[4m1[24m[4m5[24m 2.01[90me[39m[31m-3[39m     0 0.991 0.  [90m [39m       0       0 1.44[90me[39m[31m-3[39m
#> [90m 5[39m 2018-05-01 [90m00:05:00[39m 0.004[4m0[24m[4m2[24m 5.69[90me[39m[31m-4[39m     0 0.995 0.  [90m [39m       0       0 5.69[90me[39m[31m-4[39m
#> [90m 6[39m 2018-05-01 [90m00:06:00[39m 0.006[4m8[24m[4m9[24m 1.44[90me[39m[31m-3[39m     0 0.992 0.  [90m [39m       0       0 0.  [90m [39m  
#> [90m 7[39m 2018-05-01 [90m00:07:00[39m 0.003[4m7[24m[4m1[24m 2.01[90me[39m[31m-3[39m     0 0.993 1.44[90me[39m[31m-3[39m     0       0 0.  [90m [39m  
#> [90m 8[39m 2018-05-01 [90m00:08:00[39m 0.004[4m8[24m[4m8[24m 2.01[90me[39m[31m-3[39m     0 0.993 5.69[90me[39m[31m-4[39m     0       0 0.  [90m [39m  
#> [90m 9[39m 2018-05-01 [90m00:09:00[39m 0.007[4m4[24m[4m8[24m 5.68[90me[39m[31m-4[39m     0 0.992 0.  [90m [39m       0       0 0.  [90m [39m  
#> [90m10[39m 2018-05-01 [90m00:10:00[39m 0.005[4m1[24m[4m6[24m 0.  [90m [39m       0 0.995 0.  [90m [39m       0       0 0.  [90m [39m  
#> [90m# … with 1,430 more rows[39m
```

And you can easily plot using your favourite packages:

``` r
library(ggplot2)
ggplot(avg_60, aes(x = timestamp, y = user)) + 
  geom_line() +
  stat_smooth(method = "loess", span = 0.125, se = FALSE) +
  ggtitle("CPU0 usage, data read from RRD file")
#> `geom_smooth()` using formula 'y ~ x'
```

<img src="man/figures/README-plot-1.png" width="90%" />

## More information

For more information on `rrdtool` and the `rrd` format please refer to
the official [rrdtool
documentation](https://oss.oetiker.ch/rrdtool/doc/index.en.html) and
[tutorials](https://oss.oetiker.ch/rrdtool/tut/index.en.html).

You can also read a more in-depth description of the package in an [R
Views](https://rviews.rstudio.com/) blog post [Reading and analysing log
files in the RRD database
format](https://rviews.rstudio.com/2018/06/20/reading-rrd-files/).
