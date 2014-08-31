// St‚phane Charette, charette@writeme.com
// IBM Open Class Library Custom Drawing Container Sample
// (using Visual Age C++ v3.0 with OS/2 v4.0)
// 1997Nov02

// OCL includes
#include <icnrcol.hpp>  // IContainerColumn
#include <icnrdihd.hpp> // ICnrDrawHandler
#include <icnrctl.hpp>  // IContainerControl
#include <icnrobj.hpp>  // IContainerObject
#include <iframe.hpp>   // IFrameWindow

// class definition
class MyApplicationClass :    // inherits from...
   public IFrameWindow,       // ...basic frame window...
   protected ICnrDrawHandler  // ...and container draw handler
{
   public:
      // instance variables
      IContainerControl container;
      IContainerColumn  col1;
      IContainerColumn  col2;
      // class constructor/destructor
      MyApplicationClass( void );
      virtual ~MyApplicationClass( void );
      // inherited method from ICnrDrawHandler
      drawDetailsItem( ICnrDrawItemEvent &event );

   // imbeded class used as objects for the container
   class MyCnrObject :  // inherits from...
      public IContainerObject // ...container object
   {
      public:
         IString first_name;
         IString last_name;
         long colour;
         // constructor
         MyCnrObject( char *first, char *last, long clr ) :
            first_name( first ),
            last_name(  last  ),
            colour(     clr   )
            {return;}
   };
};

