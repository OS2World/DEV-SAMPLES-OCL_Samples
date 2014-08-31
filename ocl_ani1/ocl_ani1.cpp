/* St‚phane Charette, scharett@vansel.alcatel.com
 * IBM Open Class Library Animation Sample
 * (using Visual Age C++ v3.0 with OS/2 v4.0)
 * 1997June19
 */

/* local include */
#include "ocl_ani1.hpp"

/* function prototypes */
int main( void );

/* global variables */
IDrawingCanvas *canvas;
IFrameWindow *frameDlg;
Ball *bitmap;
IGList *glist;
ITimer *timer;

/*
 * main
 */
int main()
{
   // create the frame window
   frameDlg = new IFrameWindow( DIALOG_RCID );

   // set the icon for the window
   frameDlg->setIcon( DIALOG_RCID );

   // create the drawing canvas
   canvas = new IDrawingCanvas(  CANVAS_RCID,         // id
                                 frameDlg,            // parent
                                 frameDlg,            // owner
                                 frameDlg->clientRectFor( frameDlg->rect() ) );

   // set the background color
   canvas->setBackgroundColor( IColor::white );

   // add the drawing canvas to the frame
   frameDlg->setClient( canvas );

   // show the window
   frameDlg->show();

   // add the title to the window list
   frameDlg->addToWindowList();

   // create the bitmap object
   bitmap = new Ball( BMP_BALL_RCID );

   // position the object at the lower-left corner of canvas
   bitmap->moveTo( canvas->rect().bottomLeft() );
   bitmap->x = bitmap->position().x();
   bitmap->y = bitmap->position().y();

   // create the graphic list with the object
   glist = new IGList( *bitmap );

   // associate the list to the drawing canvas
   canvas->setGraphicList( glist );

   // start the timer
   timer = new ITimer( new ITimerMemberFn0<Ball>(*bitmap,Ball::calcNextMove), 50 );

   // run the application
   IApplication::current().run();

   // window has exited
   frameDlg->removeFromWindowList();
   frameDlg->hide();
   delete( timer );
   delete( canvas );
   delete( glist );
   delete( bitmap );
   delete( frameDlg );

   // return to the O/S
   return 0;
}



Ball::Ball( USHORT rcid ) : IGBitmap( rcid )
{
      /* At the moment, the speed, angle, deltaX and deltaY are all
       * set once at the beginning of the application.  My goal was
       * to make it as easy as possible to add some window controls
       * (spinbuttons, etc) to change these values dynamically while
       * the application is running.
       */
   speed = 15.0;
   angle = 30.0;
   x = 0.0;
   y = 0.0;
   dx = 0.0;
   dy = 0.0;

   // calculate the deltas
   dx = cos( convertDegToRad(angle) ) * speed;
   dy = sin( convertDegToRad(angle) ) * speed;

   return;
}



void Ball::calcNextMove()
{
   IRectangle originalRect, newRect;   // bounding rectangles used to refresh
   IPoint newPos;                      // new bitmap position

   // get the graphic context
   IGraphicContext *graphicContext = new IGraphicContext(canvas->handle());

   // find the original bounding rectangle (needed when it comes time to refresh)
   originalRect = bitmap->boundingRect(*graphicContext);

   // find the new location
   x += dx;
   y += dy;
   newPos.setX( (long)x ).setY( (long)y );

   // move the bitmap
   bitmap->moveTo( newPos );

   // calculate the new bounding rectangle
   newRect = bitmap->boundingRect(*graphicContext);

   // is the new location valid?
   if( ! canvas->rect().contains( newRect ) )
   {
      // we've gone beyond the bounds...calculate a new position and angle!
      IPoint position = bitmap->position();

      // is the left side off the canvas?
      if( position.x() < canvas->rect().left() )
      {
         position.setX( canvas->rect().left() );
         dx = - dx;
      }
      // is the bottom off the canvas?
      if( position.y() < canvas->rect().bottom() )
      {
         position.setY( canvas->rect().bottom() );
         dy = - dy;
      }
      // is the right side off the canvas?
      if( position.x() + newRect.width() > canvas->rect().right() )
      {
         position.setX( canvas->rect().right() - newRect.width() );
         dx = - dx;
      }
      // is the top off the canvas?
      if( position.y() + newRect.height() > canvas->rect().top() )
      {
         position.setY( canvas->rect().top() - newRect.height() );
         dy = - dy;
      }

      // move the bitmap
      bitmap->moveTo( position );

      // make sure we know where our bitmap is located
      bitmap->x = bitmap->position().x();
      bitmap->y = bitmap->position().y();

      // calculate the new bounding rectangle
      newRect = bitmap->boundingRect(*graphicContext);
   }

   // delete the graphic context used to get the rectangles
   delete( graphicContext );

   // figure out the maximum rectangle of the screen that needs updating
   _RECTL rectl = ( originalRect | newRect ).expandBy(1).asRECTL();
      /* I'm not certain why I have to do ".expandBy(1)" for
       * this to work correctly...if it isn't there, then the
       * ball will leave "tracks" every once in a while when
       * it moves around the window.  I thought that finding
       * the old and new bounding rectangles would be enough,
       * but somehow it isn't...
       */

   // tell PM what part of the screen needs to be refreshed
   WinInvalidateRect( canvas->handle(), &rectl, FALSE );

   return;
}

