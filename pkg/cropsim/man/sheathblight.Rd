\name{sheathBlight}
\alias{sheathBlight}

%- Also NEED an '\alias' for EACH other topic documented here.
\title{ ~~function to do ... ~~ }
\description{
  ~~ A concise (1-5 lines) description of what the function does. ~~
}
\usage{
sheathBlight(tmp, rh, duration=120, startday=30) 
}
\arguments{
  \item{tmp}{ Describe \code{xy} here }
  \item{rh}{ Describe \code{xy} here }  
  \item{duration}{ Describe \code{x} here }  
  \item{startday}{ Describe \code{x} here }    
}
\details{
  ~~ If necessary, more details than the description above ~~
}
\value{
  ...
}
\references{ ~put references to the literature/web site here ~ }
\author{ ~~who you are~~ }
\note{ ~~further notes~~ 

 ~Make other sections like Warning with \section{Warning }{....} ~
}
\seealso{ ~~objects to See Also as \code{\link{help}}, ~~~ }
\examples{

rhtable <- cbind(0:10*12, c(99.0, 98.5, 97, 96, 98.5, 96, 95.5, 96.5, 96, 95.5, 96))
tmptable <- cbind(0:10*12, c(27.8, 27.8, 28, 27.9, 27.8, 27.8, 27.8, 27.7, 27.7, 27.7, 27.5))
dur <- 120
rh <- vector(length=dur)
tmp  <- vector(length=dur)
for (d in 1:dur) {
	rh[d] <- AFGen(rhtable, d)
	tmp[d] <- AFGen(tmptable, d)
}	
res <- sheathBlight(tmp, rh)
splot(res)


}
\keyword{ spatial }