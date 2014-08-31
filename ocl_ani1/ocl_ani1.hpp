/* St‚phane Charette, scharett@vansel.alcatel.com
 * IBM Open Class Library Animation Sample
 * (using Visual Age C++ v3.0 with OS/2 v4.0)
 * 1997June19
 */

#ifndef OCL_ANIM_HPP
#define OCL_ANIM_HPP

/* IBM Open Class Library include */
#include <iapp.hpp>
#include <icolor.hpp>
#include <idrawcv.hpp>
#include <ievent.hpp>
#include <ievtdata.hpp>
#include <iframe.hpp>
#include <igbitmap.hpp>
#include <iglist.hpp>
#include <igrafctx.hpp>
#include <ipoint.hpp>
#include <irect.hpp>
#include <itimer.hpp>

/* general OS/2 include */
#define INCL_WINWINDOWMGR
#include <os2.h>
#include <math.h>                      // needed for cos(), sin()

/* local include */
#include "ocl_ani1.h"

/* macros */
#define convertDegToRad( degree ) (degree * 180.0 / 3.141592654)

/* forward decleration of classes */
class Ball;



class Ball : public IGBitmap
{
   public:
      double speed;                    // speed of the object
      double angle;                    // angle of the object (in degrees)
      double x;                        // X coordinate of object
      double y;                        // Y coordinate of object
      double dx;                       // delta X to add every timer count
      double dy;                       // delta Y to add every timer count
      Ball( USHORT rcid );             // constructor derived from IGBitmap
      void calcNextMove( void );       // function to call every timer count
};

#endif

