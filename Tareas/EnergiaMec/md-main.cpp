#include "md-simul.h" // this has all functions declarations
#include <cmath>

int main(int argc, char **argv)
{
  Particle ball;
  double DT = std::atof(argv[1]);
  int NSTEPS = int(TF/DT);

  // start system
  initial_conditions(ball);
  compute_force(ball);
  start_integration(ball, DT);
  print(ball, 0.0);

  // evolve
  double E0 = 0.0;
  for(int istep = 0; istep < NSTEPS; ++istep) {
    time_integration(ball, DT);
    compute_force(ball);
    double E = ball.U+ball.K+ball.R; // E Mecánica
    if(istep == 0){E0 = E;}          // Em inicial
    print(ball, istep*DT);
    std::cout << E << "\t" //11
              << (fabs(E-E0))/E0 << "\n"; // 12
  }

  return 0;
}
