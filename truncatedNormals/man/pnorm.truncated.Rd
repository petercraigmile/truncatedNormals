
\name{pnorm.truncated}
\alias{pnorm.truncated}
\title{Calculate distribution function for truncated normal random variables}
\description{Calculate distribution function for truncated normal random variables}
\usage{ pnorm.truncated(q, mu, sd, lower, upper, log.p)}
\arguments{
  \item{q}{quantile to calculate}
  \item{mu}{mean}
  \item{sd}{standard deviation}
  \item{lower}{lower truncation point}
  \item{upper}{upper truncation point}
  \item{log.p}{if TRUE, probabilities are given as log(p)}
  }
\value{A vector of probabilities}
\author{Peter F. Craigmile}

