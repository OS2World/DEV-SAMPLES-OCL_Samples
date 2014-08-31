/* St‚phane Charette, scharett@vansel.alcatel.com
 * IBM Open Class Library Container Sample
 * (using Visual Age C++ v3.0 with OS/2 v4.0)
 * 1997June21
 */

/* IBM Open Class Library includes */
#include <iapp.hpp>     // general application function calls
#include <icnrcol.hpp>  // container column function calls
#include <icnrctl.hpp>  // container control function calls
#include <icnrobj.hpp>  // container object function calls
#include <iframe.hpp>   // framewindow function calls
#include <istring.hpp>  // used in container object

/* local includes */
#include "ocl_con1.h"

/* function prototype */
int main( void );

/* class prototype */
class item;

/* global variables */
IFrameWindow *frameDlg;
IContainerControl *container;
IContainerColumn *col1; // this column will display IString c1
IContainerColumn *col2; // this column will display IString c2
IContainerColumn *col3; // this column will display IString c3
IContainerColumn *col4; // this column will display the icon
IContainerColumn *col5; // this column will display the icon view text
item *item1;
item *item2;
item *item3;


/* container object class */
class item : public IContainerObject
{
   public:
      item( char *col1, char *col2, char *col3, unsigned long col4, char *col5 ) :
         IContainerObject( col5, col4 ),  // ...IContainerObject constructor,
         c1( col1 ),                      // ...initializes c1,
         c2( col2 ),                      // ...c2,
         c3( col3 )                       // ...and c3
         { ; };
      IString c1;  // text to display in column 1
      IString c2;  // text to display in column 2
      IString c3;  // text to display in column 3
};


int main()
{
   // create the frame window
   frameDlg = new IFrameWindow( DLG_FRAME_RCID );

   // set the icon
   frameDlg->setIcon( DLG_FRAME_RCID );

   // create the container
   container = new IContainerControl( CONTAINER_RCID, frameDlg );

   // hide/show the title and the title separator
   //container->hideTitle().hideTitleSeparator();
   container->showTitle().showTitleSeparator().setTitle( "Container Title" );

   // set "details view" and show column titles (when columns are inserted)
   container->showDetailsView().showDetailsViewTitles();

   // automatically delete all columns and objects when done
   container->setDeleteColumnsOnClose().setDeleteObjectsOnClose();

   // create the columns
      // the first three columns will display the text defined
      // at the offset "c1", "c2" or "c3" into the object "item"
   col1 = new IContainerColumn( offsetof( item, c1 ) );
   col2 = new IContainerColumn( offsetof( item, c2 ) );
   col3 = new IContainerColumn( offsetof( item, c3 ) );
      // the fourth column will display the default icon which
      // is associated with an item when that item is created
   col4 = new IContainerColumn( IContainerColumn::isIcon );
      // the fifth column will display the default icon text which
      // is associated with an item when that item is created
   col5 = new IContainerColumn( IContainerColumn::isIconViewText );

   // set the heading title of the columns
   col1->setHeadingText( "First" );          // set the column text
   col2->setHeadingText( "Second" );         // set the column text
   col3->setHeadingText( "Third" );          // set the column text
   col4->setHeadingIcon( PEOPLE_RCID );      // set the column icon
   col5->setHeadingIcon( DLG_FRAME_RCID );   // set the column icon

   // set width in pixels to force it to be longer that what is has to be
   col3->setDisplayWidth( 150 );

   // set the separators between the columns
      // when specified without parameters, showSeparators() will
      // include both the horizontal and vertical separators...
   col1->showSeparators();
      // ...or they can be specified individually...
   col2->showSeparators( IContainerColumn::verticalSeparator );
   col3->showSeparators( IContainerColumn::verticalSeparator | IContainerColumn::horizontalSeparator );
   col4->showSeparators();
      // the last column looks nicer if it doesn't have a vertical separator
   col5->showSeparators( IContainerColumn::horizontalSeparator );

   // hide/show the details view splitbar
   container->showSplitBar().setDetailsViewSplit( col1, 80 );
   //container->hideSplitBar();
   // if the splitbar is being shown, then we should hide the separator for col1
   col1->hideSeparators( IContainerColumn::verticalSeparator );

   // add the columns to the container
   container->addColumn( col1 ).addColumn( col2 ).addColumn( col3 );
   container->addColumn( col4 ).addColumn( col5 );

   // create items to put into the container
   item1 = new item( "Aaa",   "Bbb",   "Ccc",   PERSON1_RCID, "Item 1" );
   item2 = new item( "111",   "222",   "333",   PERSON2_RCID, "Item 2" );
   item3 = new item( "Alpha", "Beta",  "Gamma", PERSON3_RCID, "Item 3" );

   // add objects to the container
   container->addObject( item1 ).addObject( item2 ).addObject( item3 );

   // show how we can add another object to the container without declaring it
   container->addObject( new item( "Do", "Re", "Mi", PERSON4_RCID, "Item 4" ) );

   // automatically refresh when needed, and refresh right now!
   container->setRefreshOn().refresh();

   // add the window to the task list, show it, and set the focus
   frameDlg->addToWindowList().show().setFocus();

   // wait until the window has finished running...
   IApplication::current().run();

   // remove the window from the window list and hide it
   frameDlg->removeFromWindowList().hide();

   // free up resources
   delete( container );
   delete( frameDlg );

   return 0;
}

