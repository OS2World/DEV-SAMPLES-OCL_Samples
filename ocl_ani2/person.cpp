/* St‚phane Charette, stephane@venus.ubishops.ca
 * IBM Open Class Library Animation Sample #2
 * (using Visual Age C++ v3.0 with OS/2 v4.0)
 * 1997July06
 */

/* includes */
#include "ocl_ani2.hpp"    // class definitions

// constructor for "people" objects
Person::Person( int rcId, IWindowHandle handle ) :
   IGBitmap( rcId ),
   moveDestination( 0, 0 ),
   canvasHandle( handle )
{
   // save the bitmap id...used when cloning
   bitmapId = rcId;

   // variables used when moving the object...for now just reset them
   moveX = 0.0;
   moveY = 0.0;
   moveDX = 0.0;
   moveDY = 0.0;
   moveCount = 0;
   moveTimer = '\0';

   // set the transparent background colour
      // Note: since I created the bitmaps (more like modified
      //       existing bitmaps) that are displayed, I know
      //       that the color I intended to make see-through
      //       is pure blue...( 0, 0, 255 ).
   setTransparentColor( IColor( 0, 0, 255 ) );

   return;
}


// destructor for "people" objects
Person::~Person()
{
   // is there an active timer?
   if( moveTimer )
   {
      moveTimer->stop();               // ...stop the timer...
      delete( moveTimer );             // ...delete the timer...
      moveTimer = '\0';                // ...set timer as non-existant
   }
   return;
}


void Person::animateMove()
{
   if( moveCount == 1 )
   {
      // this is the last call...delete the timer
      moveTimer->stop();
      delete( moveTimer );
      moveTimer = '\0';
   }

   // find the current position
   IRectangle rect1 = IRectangle( position(), size() );

   moveCount --;                    // decrease count...
   moveX += moveDX;                 // ...find new X...
   moveY += moveDY;                 // ...finx new Y...
   moveTo( IPoint( (int)moveX, (int)moveY ) ); // ...draw

   // find the new position
   IRectangle rect2 = IRectangle( position(), size() );

   // invalidate rect to force the canvas to redraw
   RECTL rectl = ( rect1 | rect2 ).asRECTL();
   WinInvalidateRect( canvasHandle, &rectl, FALSE );

   return;
}
