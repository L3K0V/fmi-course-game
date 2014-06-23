#include "utilities.hh"

#include <stdlib.h>
#include <ctime>

int random(int min, int max) {
   static bool first = true;
   if ( first )  {  
      srand(time(NULL)); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (max - min);
}
