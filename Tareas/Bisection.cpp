#include <iostream>
#include <cmath>
#include <cstdlib>

double f(double x);
template <class fptr>
double bisection(double xl, double xu, fptr fun, double eps, int & niter);
template <class fptr>
double bisection_rec(double xl, double xu, fptr fun, double eps, int & niter);

int main(int argc, char **argv) {
  std::cout.precision(16); std::cout.setf(std::ios::scientific);

  const double XL = std::atof(argv[1]);
  const double XU = std::atof(argv[2]);
  const double EPS = std::atof(argv[3]);
  int counter = 0;
  std::cout << "\nClase: " << bisection(XL, XU, f, EPS, counter) << ", " << counter << std::endl;
  counter = 1;
  std::cout << "Recursiva: " << bisection_rec(XL, XU, f, EPS, counter) << ", " << counter << "\n\n";

  return 0;
}

double f(double x)  {
  return 9.81*(68.1)*(1 - std::exp(-x*10/68.1))/x - 40;
}

template <class fptr>
double bisection(double xl, double xu, fptr fun, double eps, int & niter)
{
  double xr = 0;
  int iter = 1;
  for( ;  ; ) { // while(true)
    xr = (xl + xu)/2; // bisection
    // encontre la raiz?
    if (std::fabs(fun(xr)) <= eps) break;
    // actualizar los limites
    iter++;
    if (fun(xr)*fun(xl) < 0) {
      xu = xr;
    } else {
      xl = xr;
    }
  }
  niter = iter;
  return xr;
}

template <class fptr>
double bisection_rec(double xl, double xu, fptr fun, double eps, int & niter) {
  double xr = 0;
  int iter = niter;

  xr = (xl + xu)/2;
  if (std::fabs(fun(xr)) <= eps) return xr;
  else {
    iter++;
    if (fun(xr)*fun(xl) < 0) {
      xu = xr;
    }
    else {
      xl = xr;
    }
  }

  niter = iter;
  return bisection_rec(xl, xu, fun, eps, niter);
}
