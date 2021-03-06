#include <R.h>
#include <Rmath.h>
//#include <assert.h>

// ======================================================================
// norm_rs(a, b)
// generates a sample from a N(0,1) RV restricted to be in the interval
// (a,b) via rejection sampling.
// This function should be called by rnorm_truncated (where Get/PutRNGstate
// are invoked)
// ======================================================================
double
norm_rs(double a, double b)
{
   double	x;
   x = norm_rand();
   while( (x < a) || (x > b) ) x = norm_rand();
   return x;
}

// ======================================================================
// half_norm_rs(a, b)
// generates a sample from a N(0,1) RV restricted to the interval
// (a,b) (with a > 0) using half normal rejection sampling.
// This function should be called by rnorm_truncated (where Get/PutRNGstate
// are invoked)
// ======================================================================
double
half_norm_rs(double a, double b)
{
   double 	x;

   //assert(a >= 0); // check it

   x = fabs(norm_rand());
   while( (x<a) || (x>b) ) x = fabs(norm_rand());
   return x;
}

// ======================================================================
// unif_rs(a, b)
// generates a sample from a N(0,1) RV restricted to the interval
// (a,b) using uniform rejection sampling. 
// This function should be called by rnorm_truncated (where Get/PutRNGstate
// are invoked)
// ======================================================================
double
unif_rs(double a, double b)
{
   double xstar, logphixstar, x, logu;

   // Find the argmax (b is always >= 0)
   // This works because we want to sample from N(0,1)
   if(a <= 0.0) xstar = 0.0;
   else xstar = a;
   logphixstar = dnorm(xstar, 0.0, 1.0, 1);

   x = runif(a, b);
   logu = log(runif(0.0, 1.0));
   while( logu > (dnorm(x, 0.0, 1.0, 1) - logphixstar))
   {
      x = runif(a, b);
      logu = log(runif(0.0, 1.0));
   }
   return x;
}

// ======================================================================
// exp_rs(a, b)
// generates a sample from a N(0,1) RV restricted to the interval
// (a,b) using exponential rejection sampling.
// This function should be called by rnorm_truncated (where Get/PutRNGstate
// are invoked)
// ======================================================================
double
exp_rs(double a, double b)
{
  double	z, u, scale;

  scale = 1.0/a;

   // Generate a proposal on (0, b-a)
   z = rexp(scale);
   while(z > (b-a)) z = rexp(scale);
   u = runif(0.0, 1.0);

   while( log(u) > (-0.5*z*z))
   {
      z = rexp(scale);
      while(z > (b-a)) z = rexp(scale);
      u = runif(0.0,1.0);
   }

   return(z+a);
}


//======================================================================
// rnorm_trunc(sample, n, mu, sigma, lower, upper)
//
// generates 'n' random normal RVs with mean 'mu' and standard
// deviation 'sigma', truncated to the interval (lower,upper), where
// lower can be -Inf and upper can be Inf.
// Stores the result in 'sample'
// mu, sigma, lower and upper must be of length n.
// (one value for each value to sample)
//======================================================================

void
rnorm_truncated (double *sample,  int *n, double *mu,
		 double *sigma, double *lower, double *upper)
{
 int		k;
 int		change;
 double	a, b;
 double	logt1 = log(0.150), logt2 = log(2.18);
 double	z, tmp, lograt;

 GetRNGstate();

 for (k=0; k<(*n); k++)
 {
   change = 0;
   a = (lower[k] - mu[k])/sigma[k];
   b = (upper[k] - mu[k])/sigma[k];

    // First scenario
    if( (a == R_NegInf) || (b == R_PosInf))
    {
       if(a == R_NegInf)
	{
          change = 1;
	   a = -b;
	   b = R_PosInf;
	}

	// The two possibilities for this scenario
       if(a <= 0.45) z = norm_rs(a, b);
	else z = exp_rs(a, b);
	if(change) z = -z;
    }
    // Second scenario
    else if((a * b) <= 0.0)
    {
       // The two possibilities for this scenario
       if((dnorm(a, 0.0, 1.0, 1) <= logt1) || (dnorm(b, 0.0, 1.0, 1) <= logt1))
	{
          z = norm_rs(a, b);
	}
	else z = unif_rs(a,b);
    }
    // Third scenario
    else
    {
       if(b < 0)
	{
	   tmp = b; b = -a; a = -tmp; change = 1;
	}

	lograt = dnorm(a, 0.0, 1.0, 1) - dnorm(b, 0.0, 1.0, 1);
	if(lograt <= logt2) z = unif_rs(a,b);
	else if((lograt > logt1) && (a < 0.725)) z = half_norm_rs(a,b);
	else z = exp_rs(a,b);
	if(change) z = -z;
    }

    sample[k] = sigma[k]*z + mu[k];
 }

 PutRNGstate();
}



//======================================================================
// rnorm_trunc( mu, sigma, lower, upper)
//
// generates one random normal RVs with mean 'mu' and standard
// deviation 'sigma', truncated to the interval (lower,upper), where
// lower can be -Inf and upper can be Inf.
//======================================================================
double 
rnorm_trunc (double mu, double sigma, double lower, double upper)
{
 int	change;
 double	a, b;
 double	logt1 = log(0.150), logt2 = log(2.18);
 double	z, tmp, lograt;

 change = 0;
 a = (lower - mu)/sigma;
 b = (upper - mu)/sigma;
 
 // First scenario
 if( (a == R_NegInf) || (b == R_PosInf))
   {
     if(a == R_NegInf)
       {
	 change = 1;
	 a = -b;
	 b = R_PosInf;
       }
     
     // The two possibilities for this scenario
     if(a <= 0.45) z = norm_rs(a, b);
     else z = exp_rs(a, b);
     if(change) z = -z;
   }
 // Second scenario
 else if((a * b) <= 0.0)
   {
     // The two possibilities for this scenario
     if((dnorm(a, 0.0, 1.0, 1) <= logt1) || (dnorm(b, 0.0, 1.0, 1) <= logt1))
       {
	 z = norm_rs(a, b);
       }
     else z = unif_rs(a,b);
   }
 // Third scenario
 else
   {
     if(b < 0)
       {
	 tmp = b; b = -a; a = -tmp; change = 1;
       }
     
     lograt = dnorm(a, 0.0, 1.0, 1) - dnorm(b, 0.0, 1.0, 1);
     if(lograt <= logt2) z = unif_rs(a,b);
     else if((lograt > logt1) && (a < 0.725)) z = half_norm_rs(a,b);
     else z = exp_rs(a,b);
     if(change) z = -z;
   }
 
 return (sigma*z + mu);
}

