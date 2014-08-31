/* St‚phane Charette, stephane@venus.ubishops.ca
 * IBM Open Class Library Animation Sample #2
 * (using Visual Age C++ v3.0 with OS/2 v4.0)
 * 1997July06
 */

/* includes */
#include "ocl_ani2.hpp"    // class definitions


// constructor for the application
Application::Application() :           // construct inherited class...
   IFrameWindow( DLG_RCID ),           // ...IFrameWindow...
   IFrameHandler(),                    // ...IFrameHandler...
   ICommandHandler(),                  // ...ICommandHandler...
   IMouseHandler(),                    // ...IMouseHandler...
   IGList(),                           // ...and IGList
   canvas( CANVAS_RCID, this, this ),
   mouseClickPosition( 0, 0 ),
   mouseMoveInProgress( false ),
   mouseMovePtrHandle( IResourceLibrary().loadPointer( PTR_MOVE_RCID ) )
{
   // set the "animated" frame dialog style
   setStyle( style() | animated.asUnsignedLong() );

   // set the icon for the frame window
   setIcon( DLG_RCID );

   // set the canvas to be the correct size
   canvas.moveSizeTo( clientRectFor( rect() ) );

   // set the canvas background colour
   canvas.setBackgroundColor( IColor( 0, 64, 0 ) );

   // associate the graphic list with the canvas
   canvas.setGraphicList( this );

   // set the drawing canvas as the client for the frame
   setClient( &canvas );

   // set ourselves up to handle events for the canvas
   IMouseHandler::handleEventsFor( &canvas );
   ICommandHandler::handleEventsFor( &canvas );
   IFrameHandler::handleEventsFor( this );

   // add window to the CTRL-ESC window list
   addToWindowList();

   // show the dialog and set the focus
   show().setFocus();

   return;
}


// destructor for application dialog class
Application::~Application()
{
   // stop handling events
   IMouseHandler::stopHandlingEventsFor( &canvas );
   ICommandHandler::stopHandlingEventsFor( &canvas );
   IFrameHandler::stopHandlingEventsFor( this );

   // delete all of the draw items
   while( ! isEmpty() )
   {
      // get the graphic at the current position
      Person *person = (Person*)&(graphicAtPosition( 1 ));
      // remove the graphic
      removeAtPosition( 1 );
      // free up resources
      delete( person );
   }
   return;
}


Boolean Application::mouseClicked( IMouseClickEvent &event )
{
   // save the mouse position for when we handle the menu
   mouseClickPosition = IPoint( event.mousePosition() );

   // is this a popupmenu request?
   if( event.mouseButton() == IMouseClickEvent::button2 )
   {
      // reset necessary states
      resetAttributes();

      if( event.mouseAction() == IMouseClickEvent::click )
      {
         // create a popup menu
         IPopUpMenu *pmenu = new IPopUpMenu( this, MNU_RCID );
         pmenu->setAutoDeleteObject( true );

         // add common menu items
         pmenu->addText( MNU_CREATE_PERSON,  "Create" );
         pmenu->addSubmenu( MNU_CREATE_PERSON );   // convert it to submenu
         // add submenu items
         pmenu->addText( MNU_CREATE_ORANGE,  "Orange",   MNU_CREATE_PERSON );
         pmenu->addText( MNU_CREATE_BLUE,    "Blue",     MNU_CREATE_PERSON );
         pmenu->addText( MNU_CREATE_GREEN,   "Green",    MNU_CREATE_PERSON );
         pmenu->addText( MNU_CREATE_RED,     "Red",      MNU_CREATE_PERSON );
         pmenu->addText( MNU_CREATE_GRAY,    "Gray",     MNU_CREATE_PERSON );

         // where was the button clicked?
         IGraphicContext graphicContext( canvas.handle() );
         IGraphic *graphic = topGraphicUnderPoint( mouseClickPosition,
                                                         graphicContext );
         if( graphic )
         {
            // button 2 was clicked on a graphic in glist

            // figure out which object was clicked for when we handle the menu
            for(  mouseClickBitmapOffset = 1;
                  &( graphicAtPosition( mouseClickBitmapOffset ) ) != graphic;
                  mouseClickBitmapOffset ++ );

            // get the person
            Person *person = (Person *)&graphicAtPosition(mouseClickBitmapOffset);

            // create the menu items specific to the item
            pmenu->addText( MNU_CLONE_PERSON,   "Clone"  );
            pmenu->addText( MNU_DELETE_PERSON,  "Delete" );
            pmenu->addText( MNU_MOVE_PERSON,    "Move"   );
            pmenu->addSubmenu( MNU_MOVE_PERSON );
            pmenu->addText( MNU_MOVE_SET,       "Set",   MNU_MOVE_PERSON );
            pmenu->addText( MNU_MOVE_STOP,      "Stop",  MNU_MOVE_PERSON );
            // if the person is not moving...
            if( ! person->moveTimer )
            {
               // ...disable the "stop" item...
               pmenu->disableItem( MNU_MOVE_STOP );
               // ...set the "set" item as default
               pmenu->setConditionalCascade( MNU_MOVE_PERSON, MNU_MOVE_SET );
            }
            else  // ...else...
            {
               // ...set the "stop" item as default
               pmenu->setConditionalCascade( MNU_MOVE_PERSON, MNU_MOVE_STOP );
            }
         }
         else
         {
            // button 2 was clicked somewhere on the canvas
            mouseClickBitmapOffset = 0;
         }

         // show the menu
         pmenu->show( mouseClickPosition );

         // return the event as having been handled
         return true;
      }
   }
   else
   {
      // if this is mousebutton1click and we are currenting setting a move...
      if(   (event.mouseButton() == IMouseClickEvent::button1) &&
            (event.mouseAction() == IMouseClickEvent::click)   &&
            (mouseMoveInProgress) )
      {
         // we want the object to move to this location
         mouseMoveInProgress = false;
         // get the object that has to be moved
         Person *person = (Person *)&graphicAtPosition(mouseClickBitmapOffset);
         // is this object already moving?
         if( person->moveTimer )
         {
            // yes it is...kill the timer
            person->moveTimer->stop();
            delete( person->moveTimer );
         }
         // setup the necessary move information
         person->moveX = (double)person->position().x();
         person->moveY = (double)person->position().y();
         person->moveDestination = event.mousePosition();
         // what is the length of the move line?
         person->moveCount = (int)
            sqrt( pow( person->moveDestination.x() - person->moveX, 2 ) +
                  pow( person->moveDestination.y() - person->moveY, 2 ) ) /
                  5.0;
         // detemine what DX and DY will be
         person->moveDX =
            ((double)person->moveDestination.x() - person->moveX ) /
             (double)person->moveCount;
         person->moveDY =
            ((double)person->moveDestination.y() - person->moveY ) /
             (double)person->moveCount;
         // start the timer to move the object
         person->moveTimer = new ITimer(
            new ITimerMemberFn0<Person>(*person, Person::animateMove), 100);
         // return message as having been handled
         return true;
      }
   }
   // continue processing this event
   return false;
}


Boolean Application::mousePointerChange( IMousePointerEvent &event )
{
   // are we moving an object?
   if( mouseMoveInProgress )
   {
      // move is in progress...use our built-in mouse pointer
      event.setMousePointer( mouseMovePtrHandle );
      // return message as having been handled
      return true;
   }

   // return the event as not having been handled
   return false;
}


// focus lost event overriden from IFrameHandler
Boolean Application::deactivated( IFrameEvent &event )
{
   resetAttributes();
   return false;
}


// command event overridden from ICommandHandler
Boolean Application::command( ICommandEvent &event )
{
   switch( event.commandId() )
   {
      case MNU_CREATE_ORANGE:
      case MNU_CREATE_BLUE:
      case MNU_CREATE_GREEN:
      case MNU_CREATE_RED:
      case MNU_CREATE_GRAY:
      {
         // create a new person object
         Person *person = new Person( event.commandId(), canvas.handle() );
         // move the bitmap to the position where the mouse was clicked
         person->moveTo( mouseClickPosition );
         // add the person to the glist
         addAsFirst( *(IGBitmap*)person );
         // invalidate rect
         RECTL rectl =
            IRectangle( person->position(), person->size() ).asRECTL();
         WinInvalidateRect( canvas.handle(), &rectl, FALSE );
         // return message as having been handled
         return true;
         break;
      }
      case MNU_DELETE_PERSON:
      {
         // delete the requested item
         // keep track of graphic being deleted
         Person *person=(Person*)&(graphicAtPosition(mouseClickBitmapOffset) );
         // remove the person from the glist
         removeAtPosition( mouseClickBitmapOffset );
         // invalidate rect
         RECTL rectl =
            IRectangle( person->position(), person->size() ).asRECTL();
         WinInvalidateRect( canvas.handle(), &rectl, FALSE );
         // free up resources
         delete( person );
         // return message as having been handled
         return true;
         break;
      }
      case MNU_CLONE_PERSON:
      {
         // create a new person from the bitmap id of the clone parent
         Person *person = new Person(
            ((Person*)&(graphicAtPosition(mouseClickBitmapOffset)))->bitmapId,
            canvas.handle() );
         // move the bitmap to the position where the mouse was clicked
         person->moveTo( mouseClickPosition );
         // add the person to the glist
         addAsFirst( *(IGBitmap*)person );
         // invalidate rect
         RECTL rectl =
            IRectangle(  person->position(), person->size() ).asRECTL();
         WinInvalidateRect( canvas.handle(), &rectl, FALSE );
         // return message as having been handled
         return true;
         break;
      }
      case MNU_MOVE_SET:
      {
         // start tracking for movement
         mouseMoveInProgress = true;
         // return message as having been handled
         return true;
         break;
      }
      case MNU_MOVE_STOP:
      {
         Person *person = (Person *)&graphicAtPosition(mouseClickBitmapOffset);
         // kill the timer
         person->moveTimer->stop();
         delete( person->moveTimer );
         person->moveTimer = '\0';
         // invalidate rect
         RECTL rectl =
            IRectangle(  person->position(), person->size() ).asRECTL();
         WinInvalidateRect( canvas.handle(), &rectl, FALSE );
         return true;
         break;
      }
   }
   // continue processing this event
   return false;
}


// used to reset local class variables after context switches, etc
void Application::resetAttributes()
{
   mouseMoveInProgress = false;
   return;
}
