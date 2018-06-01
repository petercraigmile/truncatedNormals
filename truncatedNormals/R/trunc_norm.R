
## ======================================================================
## File     : trunc_norm.R
## Purpose  : Simulates normal RV's truncated to (lower , upper)
## Requires : trunc_norm.c to be compiled and dynamically loaded.
##
## e.g., in PC windows: dyn.load("windows/trunc_norm.dll")
##       in PC linux:   dyn.load("linux/trunc_norm.so")
##
## Reference : Section 2 of Geweke, J. (1991). "Efficient simulation
## from the multivariate normal and student-t distributions subject to
## linear constraints". In Keramidas, E. M., editor, Computing Science
## and Statistics: Proceedings of the Twenty-Third Symposium on the
## Interface, pages 571-578. Interface Foundation of North America,
## Fairfax, VA.
##
## Updated 27 May 2007 by Chris Hans (hans@stat.osu.edu)
## Updated 04 Sep 2008 by Peter Craigmile (pfc@stat.osu.edu)
## ======================================================================


pnorm.truncated <- function (q, mu, sd, lower, upper, log.p=FALSE) {
 ## ======================================================================
 ## Purpose  : calculate distribution function at quantile 'q' for
 ##            normal('mu', 'sd'^2) random variables, truncated
 ##            to the region (lower , upper)
 ## Created  : 04 Sep 08, pfc@stat.osu.edu
 ## Warning  : Bad error checking!
 ## Note     : behavior now mimics rnorm (parameters can be of length 1 or n)
 ##  ======================================================================

  denom <- (pnorm(upper, mu, sd) - pnorm(lower, mu, sd))
  numer <- (pnorm(q, mu, sd) - pnorm(lower, mu, sd))

  if (log.p)
    log(denom) - log(numer)
  else
    numer/denom
}




dnorm.truncated <- function (x, mu, sd, lower, upper, log=FALSE) {
 ## ======================================================================
 ## Purpose  : calculate density function at value 'x' for
 ##            normal('mu', 'sd'^2) random variables, truncated
 ##            to the region (lower , upper)
 ## Created  : 04 Sep 08, pfc@stat.osu.edu
 ## Warning  : Bad error checking!
 ## Note     : behavior now mimics rnorm (parameters can be of length 1 or n)
 ##  ======================================================================

  denom <- (pnorm(upper, mu, sd) - pnorm(lower, mu, sd))

  if (log)
    dnorm(x, mu, sd, log=TRUE) - log(denom)
  else
    dnorm(x, mu, sd) / denom  
}






rnorm.truncated <- function (n, mu, sd, lower, upper)
 ## ======================================================================
 ## Purpose : sample 'n' normal('mu', 'sd'^2) random variables, truncated
 ##           to the region (lower , upper)
 ## Based on : April 07, pfc@stat.osu.edu (left truncation)
 ## Updated  : 27 May 2007 (hans@stat.osu.edu)
 ## Warning  : Bad error checking!
 ## Note     : behavior now mimics rnorm (parameters can be of length 1 or n)
 ##  ======================================================================
{
 if (length(mu)==1)
   mu <- rep(mu,n)
 else if (length(mu)!=n)
   stop("mu must be of length 1 or n")

 if (length(sd)==1)
   sd <- rep(sd,n)
 else if (length(sd)!=n)
   stop("sd must be of length 1 or n")

 if (length(lower)==1)
   lower <- rep(lower,n)
 else if (length(lower)!=n)
   stop("lower must be of length 1 or n")

 if (length(upper)==1)
   upper <- rep(upper,n)
 else if (length(upper)!=n)
   stop("upper must be of length 1 or n")

 .C("rnorm_truncated", results=double(n),
    as.integer(n), as.double(mu), as.double(sd),
    as.double(lower), as.double(upper), NAOK=TRUE,
    PACKAGE="truncatedNormals")$results
}
