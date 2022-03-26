
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main() {
   clock_t start = clock();

   double x, y, z;
   int acertos = 0;

   acertos = 0;
   for (int i=0; i<10000000; i++) {
      x = ((double)rand()/RAND_MAX);
      y = ((double)rand()/RAND_MAX);
      
      z = (x*x) + (y*y);
      if (z <= 1.0)
        acertos++;
    }
      
   printf("%f", (4.0 * acertos/(10000000)));
   
   clock_t end = clock();
   double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
   printf("\n%lf", time_spent);
   
   return 0;
}
