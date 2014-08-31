// St‚phane Charette, charette@writeme.com
// IBM Open Class Library Custom Drawing Container Sample
// (using Visual Age C++ v3.0 with OS/2 v4.0)
// 1997Nov02

// includes
#include "ocl_con2.hpp"

// defines and includes needed to "paint" text at a specified location
#define INCL_WIN
#define INCL_PM
#include <os2.h>


// class constructor
MyApplicationClass::MyApplicationClass() :
   IFrameWindow(  IResourceId(0x1000),
                  IFrameWindow::classDefaultStyle  |
                  IFrameWindow::animated           |
                  IFrameWindow::dialogBackground   ),
   container(     0x1002, this, this               ),
   col1(          offsetof( MyCnrObject, first_name) ),
   col2(          offsetof( MyCnrObject, last_name ) )
{
   // setup some basic container attributes
   container.  setMultipleSelection().
               setExtendedSelection().
               showDetailsViewTitles().
               setDeleteColumnsOnClose( false ).   // <-- cols are in the class
               setDeleteObjectsOnClose().
               showDetailsView().
               enableDrawItem();    // <-- required for custom-draw containers

   // set the headings for the container columns
   col1. setHeadingText( "First Name" ).
         showSeparators();
   col2. setHeadingText( "Last Name" ).
         showSeparators( IContainerColumn::horizontalSeparator );

   // add the columns to the container
   container.addColumn( &col1 ).addColumn( &col2 );

   // put some fake data in the container
   // note that the colour values I used are some of the built-in
   // definitions that are available when using #include <os2.h>:
   //    CLR_DEFAULT    CLR_BLACK      CLR_BLUE       CLR_RED
   //    CLR_PINK       CLR_GREEN      CLR_CYAN       CLR_YELLOW
   //    CLR_BROWN      CLR_DARKGRAY   CLR_DARKBLUE   CLR_DARKRED
   //    CLR_DARKPINK   CLR_DARKGREEN  CLR_DARKCYAN   CLR_PALEGRAY
   container.addObject( new MyCnrObject( "Luc",    "Fontaine", CLR_WHITE   ) );
   container.addObject( new MyCnrObject( "David",  "LeBlanc",  CLR_PINK    ) );
   container.addObject( new MyCnrObject( "Steph",  "Charette", CLR_RED     ) );
   container.addObject( new MyCnrObject( "Suzie",  "Falkner",  CLR_WHITE   ) );
   container.addObject( new MyCnrObject( "Lucy",   "Beattle",  CLR_DARKRED ) );
   container.addObject( new MyCnrObject( "Amy",    "Thurston", CLR_BLUE    ) );
   container.addObject( new MyCnrObject( "Frank",  "Jones",    CLR_WHITE   ) );
   container.addObject( new MyCnrObject( "Kevin",  "Woods",    CLR_GREEN   ) );
   container.addObject( new MyCnrObject( "Jenny",  "Marks",    CLR_DEFAULT ) );
   container.addObject( new MyCnrObject( "Gene",   "Moody",    CLR_WHITE   ) );
   container.refresh();

   // tell the frame window that the container will be the main client
   setClient( &container ).show().setFocus();

   // setup container draw handler
   ICnrDrawHandler::handleEventsFor( &container );
   return;
}


MyApplicationClass::drawDetailsItem( ICnrDrawItemEvent &event )
{
   // get the object being drawn
   MyCnrObject *myObj = (MyCnrObject*)event.object();

   if( myObj == 0 )
   {
      // titles are being drawn -- let OS/2 take care of that,
      // even though we could do it ourselves if we wanted to
      // -- do nothing --
   }
   else
   {
      // get the rectangle that is to be repainted
      RECTL rect = event.itemRect().asRECTL();

      // lets pretend this is a special case -- is this the object "Frank?"
      if( myObj->first_name == "Frank" )
      {
         // are we drawing the first column?
         if( event.column() == &col1 )
         {
            // draw the first name in cyan
            WinFillRect( event.itemPresSpaceHandle(), &rect, CLR_CYAN );
         }
         else
         {
            // draw the last name in yellow
            WinFillRect( event.itemPresSpaceHandle(), &rect, CLR_YELLOW );
         }
      }
      else
      {
         // what colour should we use to draw the background?

         // get the colour from the object -- we specified it when the object
         // was created during the class constructor

         // instead, we could be checking the state of some boolean flag
         // (or whatever) and then selecting the colour to use; for example,
         // if an object is marked as OVERDUE_FEES_DUE instead of NO_FEES_DUE
         // then the colour might be red instead of green, etc...

         // paint the rectangle!
         WinFillRect( event.itemPresSpaceHandle(), &rect, myObj->colour );
      }
   }

   // return the event as having been unhandled -- this will ensure
   // that OS/2 will now draw the text.  If we set/return TRUE instead,
   // then we also have to draw the text ourselves
   event.setResult( false );
   return false;
}


MyApplicationClass::~MyApplicationClass()
{
   // stop handling events
   ICnrDrawHandler::stopHandlingEventsFor( &container );
   return;
}


int main()
{
   // create an instance of the test dialog...
   MyApplicationClass *application = new MyApplicationClass();
   // run it...
   IApplication::current().run();
   // delete it...
   delete( application );
   return 0;
}

