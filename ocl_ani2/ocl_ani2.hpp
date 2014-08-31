/* St‚phane Charette, stephane@venus.ubishops.ca
 * IBM Open Class Library Animation Sample #2
 * (using Visual Age C++ v3.0 with OS/2 v4.0)
 * 1997July06
 */

/* IBM OCL includes */
#include <iapp.hpp>        // IApplication
#include <icmdevt.hpp>     // ICommandEvent
#include <icmdhdr.hpp>     // ICommandHandler
#include <icolor.hpp>      // IColor
#include <ictlevt.hpp>     // IControlEvent
#include <idrawcv.hpp>     // IDrawingCanvas
#include <iframe.hpp>      // IFrameWindow
#include <iframevt.hpp>    // IFrameEvent
#include <iframhdr.hpp>    // IFrameHandler
#include <igbitmap.hpp>    // IGBitmap
#include <iglist.hpp>      // IGList
#include <igrafctx.hpp>    // IGraphicContext
#include <imousevt.hpp>    // IMouseClickEvent
#include <imoushdr.hpp>    // IMouseHandler
#include <ipopmenu.hpp>    // IPopUpMenu
#include <itimer.hpp>      // ITimerMemberFn0

/* local includes */
#define INCL_WINWINDOWMGR  // WinInvalidateRect()
#include <os2.h>           // standard OS/2 include
#include <math.h>          // sqrt()
#include "ocl_ani2.h"      // #defines

/* class prototypes */
class Application;
class Person;


// class used to encapsulate the frame, client canvas, etc...
class Application :                    // inherit from...
   public IFrameWindow,                // ...IFrameWindow...
   public ICommandHandler,             // ...ICommandHandler...
   public IFrameHandler,               // ...IFrameHandler...
   public IMouseHandler,               // ...IMouseHandler...
   public IGList                       // ...and IGList
{
   public:
      // declare constructor and destructor for class
      Application( void );
      ~Application( void );
      void resetAttributes( void );    // used to reset local vars
   protected:
      // declare protected class variables
      IDrawingCanvas canvas;                    // drawing canvas
      IPointerHandle mouseMovePtrHandle;        // pointer to use when moving
      IPoint         mouseClickPosition;        // location of last mouseclick
      Boolean        mouseMoveInProgress;       // move operation in progress?
      unsigned long  mouseClickBitmapOffset;    // IGBitmap offset into IGList

      // declare overloaded functions that were inherited from...
      Boolean command( ICommandEvent &event );           // ...ICommandHandler
      Boolean deactivated( IFrameEvent &event );         // ...IFrameHandler
      Boolean mouseClicked( IMouseClickEvent &event );   // ...IMouseHandler
      Boolean mousePointerChange( IMousePointerEvent &event ); // ...IMouse...
};


// class used to encapsulate the "people" objects
class Person :                         // inherit from...
   public IGBitmap                     // ...IGBitmap
{
   public:
      // declare public class variables
      unsigned long bitmapId;          // bitmap id (needed when cloning)
      double moveX;                    // x location used when moving
      double moveY;                    // y location used when moving
      double moveDX;                   // delta used when moving
      double moveDY;                   // delta used when moving
      int    moveCount;                // how many steps left to move
      IPoint moveDestination;          // final destination used when moving
      ITimer *moveTimer;               // timer used when moving
      IWindowHandle canvasHandle;      // needed when we invalidate canvas
      // declare constructor and destructor for class
      Person( int rcId, IWindowHandle handle );
      ~Person( void );
      void animateMove( void );        // called by timer to redraw person
};
