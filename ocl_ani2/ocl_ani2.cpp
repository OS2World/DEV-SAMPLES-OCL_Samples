/* St‚phane Charette, stephane@venus.ubishops.ca
 * IBM Open Class Library Animation Sample #2
 * (using Visual Age C++ v3.0 with OS/2 v4.0)
 * 1997July06
 */

/* includes */
#include "ocl_ani2.hpp"    // class definitions

/* function prototype */
int main( void );


int main()
{
   // create the frame window
   Application *frame = new Application();

   // run until the window is closed
   IApplication::current().run();

   // free resources
   delete( frame );

   return 0;
}
