/* St‚phane Charette, stephane@venus.ubishops.ca
 * IBM Open Class Library Thread & Timer Sample
 * (using Visual Age C++ v3.0 with OS/2 v4.0)
 * 1997June24
 */

/* IBM includes necessary for OCL */
#include <iapp.hpp>        // general applications calls
#include <icmdevt.hpp>     // command events
#include <icmdhdr.hpp>     // command events handler (pushbtn and system menu)
#include <iframe.hpp>      // frame window calls
#include <ilistbox.hpp>    // listbox calls
#include <ipushbut.hpp>    // pushbutton calls
#include <istring.hpp>     // string calls
#include <isysmenu.hpp>    // system menu defines (idClose, idMinimize, etc)
#include <ithread.hpp>     // thread calls
#include <itimer.hpp>      // timer calls

/* local includes */
#include "ocl_thr1.h"

/* function prototypes */
int main( void );

/* class prototypes */
class MyDlgClass;
class MyThreadClass;


/* class definition for the window dialog */
class MyDlgClass :                     // inherit from...
   public IFrameWindow,                // ...IFrameWindow...
   public ICommandHandler              // ...and from ICommandHandler
{
   public:
      // declare class variables
      IPushButton *pbtnCreate;         // dialog pushbutton
      IPushButton *pbtnDelete;         // dialog pushbutton
      IPushButton *pbtnClear;          // dialog pushbutton
      MyThreadClass *myThreadFn;       // used to keep track of 2nd thread
      IListBox *lb;                    // listbox
      // declare class methods
      MyDlgClass();                    // constructor
      ~MyDlgClass();                   // destructor
      // declare class methods overloaded from ICommandHandler
      Boolean command( ICommandEvent &event );
      Boolean systemCommand( ICommandEvent &event );
      // declare class method which will be called using a second thread
      void printSomething();
};


/* class definition for the thread */
class MyThreadClass :                  // inherit from...
   public IThreadFn                    // ...IThreadFn
{
   public:
      // declare class variables
      Boolean done;                    // flag used in run() method
      MyDlgClass &frame;               // points to the frame dialog window
      ITimer *timer;                   // timer to call foo() every N millisecs
      // declare class methods
      MyThreadClass(MyDlgClass &dlg);  // constructor
      ~MyThreadClass();                // destructor
      void run();                      // method called when thread is started
};


// constructor for class
MyThreadClass::MyThreadClass( MyDlgClass &dlg ) :
   frame( dlg )
{
   // set the flag used in MyThreadClass::run() to
   // false so that run() will keep looping forever
   done = false;

   // start timer and call MyDlgClass::printSomething every 250 milliseconds
      // Note: I chose 250 milliseconds since it is exactly twice
      //       as fast as the pause time in MyThreadClass::run().
      //       Thus, the timer messages should appear generally
      //       twice as often as the run() messages.
   timer = new ITimer(
      new ITimerMemberFn0<MyDlgClass>(frame, MyDlgClass::printSomething), 250);

   return;
}


// destructor for class
MyThreadClass::~MyThreadClass()
{
   // stop the timer so it can be de-allocated
   timer->stop();

   // free the resources used by the timer
   delete( timer );

   return;
};


void MyThreadClass::run()
{
   // Note: the "done" flag is initially set to false in the
   //       class constructor so that the run() method keeps
   //       looping potentially forever.  This is necessary
   //       since the thread will cease to exist as soon as
   //       run() has finished.  We use this to our advantage
   //       since when it comes time to kill the thread, we
   //       can set this flag to "true" from our main thread,
   //       thus killing the thread.
   while( ! done )
   {
      // sleep for 500 milliseconds (1/2 second)
      IThread::current().sleep( 500 );

      // display a message in the listbox
      frame.lb->addAsFirst( "print from thread..." );
   }
   // display a few messages as we're leaving the thread
   // Note: by the time the destructor for this class has been called,
   //       the ICurrentThread::terminateGUI() method seems to have
   //       already been called, so you cannot send messages from
   //       the destructor.
   frame.lb->addAsFirst( "done flag detected..." );
   frame.lb->addAsFirst( "killing timer & thread..." );

   return;
}


// constructor for class
MyDlgClass::MyDlgClass() :    // we inherited from other classes so...
   IFrameWindow( DLG_RCID ),  // ...call constructor for IFrameWindow
   ICommandHandler()          // ...and for ICommandHandler
{
   // mark the thread class as being not created
   myThreadFn = 0;
      // when we exit the application, we will compare "myThreadFn"
      // to null -- if it is equal to any other value, then we
      // will assume that the second thread is running, and we'll
      // kill it off before exiting

   // create the listbox
   lb = new IListBox( LB_RCID, this );

   // create the pushbuttons
   pbtnCreate = new IPushButton( PBTN_CREATE_RCID, this );
   pbtnDelete = new IPushButton( PBTN_DELETE_RCID, this );
   pbtnClear  = new IPushButton( PBTN_CLEAR_RCID,  this );

   // tell ourselves we can handle our own command events
   ICommandHandler::handleEventsFor( this );
      // There are two protected methods from ICommandHandler
      // that we've overloaded: command() and systemCommand().
      // These functions will now be called when a command or
      // a system command occurs, because we've set ourselves
      // up to handle our own events.  The reason we're doing
      // this is because pushbuttons generate command events,
      // and choosing "close" from the system menu generates
      // a system event:  we want to act upon these events

   return;
}


// destructor for class
MyDlgClass::~MyDlgClass()
{
   // stop handling command and systemCommand events
   ICommandHandler::stopHandlingEventsFor( this );

   // free resources
   delete( pbtnCreate );
   delete( pbtnDelete );
   delete( pbtnClear );
   delete( lb );

   return;
}


// command event method overloaded from ICommandHandler
Boolean MyDlgClass::command( ICommandEvent &event )
{
   switch( event.commandId() )
   {
      case PBTN_CREATE_RCID:
      {  // the CREATE pushbutton was pressed...so start by disabling it...
         pbtnCreate->disable();
         // ...and create class that will run on a thread...
         myThreadFn = new MyThreadClass( *this );
         // ...and create the thread for the class...
            // Note: using the IThread() constructor with an
            //       IThreadFn-derived parameter will not only
            //       create the thread, but also automatically
            //       start it as if IThread::start() had been
            //       called.  The TRUE parameter specified that
            //       this thread needs access to PM resources
            //       and should be initialized accordingly.
         IThread *myThread = new IThread( myThreadFn, true );
         // ...and delete the thread resource...
            // Note: deleting the IThread does NOT stop the thread!
            //       It will keep on running it's run() method to the
            //       end, which in our case, is determined by the
            //       MyThreadClass::done variable.
         delete( myThread );
         // ...and enable the DELETE pushbutton...
         pbtnDelete->enable();
         // ...and return indicating that the event has been handled
         return true;
         break;
      }
      case PBTN_DELETE_RCID:
      {  // the DELETE pushbutton was pressed...so start by disabling it...
         pbtnDelete->disable();
         // ...and then set the flag which will allow the thread to end...
            // Note: do *NOT* try and suspend the thread since it was
            //       created with GUI initialization enabled.  This is
            //       not documented in IThread::suspend(), but it is
            //       mentionned in ICurrentThread::suspend().
         myThreadFn->done = true;
         // ...and keep track of the fact that we've deleted it...
         myThreadFn = 0;
         // ...and enable the CREATE pushbutton...
         pbtnCreate->enable();
         // ...and return indicating that the event has been handled
         return true;
         break;
      }
      case PBTN_CLEAR_RCID:
      {  // the CLEAR pushbutton was pressed...so start by disabling it...
         pbtnClear->disable();
         // ...and then remove all entries in the listbox...
         lb->removeAll();
         // ...and return indicating that the event has been handled
         return true;
         break;
      }
   }
   // return and indicate the event has not been handled
   return false;
}


// system command event method overloaded from ICommandHandler
Boolean MyDlgClass::systemCommand( ICommandEvent &event )
{
   // Note: there are three types of events we are interested in:
   //       1) the minimize event
   //       2) the restore event
   //       3) the close event
   if( event.commandId() == ISystemMenu::idClose )
   {
      // the user has selected to close the window, so make certain
      // that the secondary thread is not running; kill it if it is
      if( myThreadFn )
      {
         // the secondary thread exists...so we have to kill it...
         myThreadFn->done = true;
         myThreadFn = 0;
         // and give up the rest of our time slice
         // to allow the kill to take effect
         IThread::current().sleep( 1 );
      }
   }
   else if( event.commandId() == ISystemMenu::idMinimize )
   {
      // hide the listbox to prevent it from hiding the minized icon
         // Note: because we're not using a ICanvas (or a derivitive)then
         //       when we minimize the window, some of the controls may
         //       overwrite the icon.  What we have to do is detect when
         //       a window is minized, and hide the offending controls.
         //       When using an ICanvas, this functionality is taken care
         //       of for us, so we don't have to worry about it.  Also note
         //       that when a window is restored, we have to remember to
         //       show whatever controls have been hidden.
      lb->hide();
   }
   else if( event.commandId() == ISystemMenu::idRestore )
   {
      // restore the listbox since we had to hide it...
      lb->show();
   }

   // return and indicate the event has not been handled
   return false;
}


// print a message in the listbox
void MyDlgClass::printSomething()
{
   static unsigned long counter = 0;   // variable used to print number

   // print the message
   lb->addAsFirst( IString("print from timer: ") + IString( counter ) );

   // is the "clear" button enabled?
   if( ! pbtnClear->isEnabled() )
   {  // ...no, so enable it now
      pbtnClear->enable();
   }

   // increment the counter for next time
   counter ++;

   return;
}


int main()
{
   // create the dialog window
   MyDlgClass *frameDlg = new MyDlgClass();

   // set the icon for the window
   frameDlg->setIcon( DLG_RCID );

   // add the window to the CTRL-ESC window list
   frameDlg->addToWindowList();

   // enable the "create" pushbutton
   frameDlg->pbtnCreate->enable();

   // run the application until it is closed
   IApplication::current().run();

   // remove the window from the window list and hide it
   frameDlg->removeFromWindowList().hide();

   // free up resources
   delete( frameDlg );

   return 0;
}
