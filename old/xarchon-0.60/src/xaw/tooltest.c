/* most important define,
   check APPNAME.ad !
*/
#define APP_NAME "tooltest"

#include "mls.h"

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <sys/time.h>
#include <sys/resource.h>

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xmu/Editres.h>
#include <X11/Vendor.h>
#include <X11/Xaw/XawInit.h>
#include <X11/IntrinsicP.h>
#include <X11/CreateI.h>
#include <X11/IntrinsicI.h>
#include <X11/ThreadsI.h>
#include <X11/VarargsI.h>
#include <WcCreate.h>
#include <Xp.h>
#include <xutil.h>
#include "wcreg2.h"
#include <xtcw/register_wb.h>
#include "widreg.h"

#include "Wlabel.h"
#include "Wlist4.h"
#include "Wlist-common.h"
#include "Gridbox.h"

#include "m_tool.h"
#include "var5.h"
#include "font.h"


Widget TopLevel;
int trace_main;
#define TRACE_MAIN 2

extern struct RC_DB RC;

char *fallback_resources[] = {
    APP_NAME ".allowShellResize: False",
    "*WclResFiles:" APP_NAME ".ad\n",
    "*traceLevel: 2",
    NULL };

/* All Wcl applications should provide at least these Wcl options:
*/
static XrmOptionDescRec options[] = {
    { "-TraceLevel",	"*traceLevel",	XrmoptionSepArg, NULL },
    { "-Inifile",	"*inifile",	XrmoptionSepArg, NULL },
    WCL_XRM_OPTIONS
};

typedef struct SIGNAGE_CONFIG {
    int traceLevel;
    int socket;
    char *inifile;
    Widget widget_grid;
} SIGNAGE_CONFIG ;

#define FLD(n)  XtOffsetOf(SIGNAGE_CONFIG,n)
static XtResource SIGNAGE_CONFIG_RES [] = {

  { "traceLevel", "TraceLevel", XtRInt, sizeof(int),
   FLD(traceLevel), XtRImmediate, 0
  },

  { "socket", "Socket", XtRInt, sizeof(int),
   FLD(socket), XtRImmediate, 0
  },

  { "inifile", "Inifile", XtRString, sizeof(String),
    FLD(inifile), XtRString, NULL
  },

  /*
    { NULL, NULL, XtRWidget, sizeof(Widget),
    FLD(widget_grid), XtRString, "*gb"
  },

  { NULL, NULL, XtRWidget, sizeof(Widget),
    FLD(widget_grid), XtRString, "*gb"
  },
  */

};
#undef FLD

struct SIGNAGE_CONFIG SIGNAGE = { 0 };



/** set the keyboard focus to a named widget and call the focus_in function
    of that widget
*/
void SetFocus( Widget w, void *u, void *c )
{
    char buffer[MAX_XRMSTRING];
    Widget focus_widget;

    TRACE(8, "Widget called the setfocus callback");
    if(! u ) {
	WARN("Callback SetFocus invoked without argument i.e. without a widget name to set the focus to");
	return;
    }

    /* need my own implementation here i.e. snprintf */
    WcCleanName( u, buffer );
    focus_widget=WcFullNameToWidget( w, buffer );

    /* the warning message should be printed by WcFullNameToWidget */
    if( ! focus_widget ) {
	WARN("the widget %s was not found in this widget tree");
	return;
    }


    if( w != focus_widget ) {
	XtCallActionProc( w, "focus_out", NULL, NULL, 0 );
	XtCallActionProc( focus_widget, "focus_in", NULL, NULL, 0 );
    }

    XtCallActionProc( focus_widget, "SetKeyboardFocus", NULL, NULL, 0 );

}

void CallAction( Widget w, void *u, void *c )
{
    char buffer[MAX_XRMSTRING];
    Widget widget;

    TRACE(8, "Widget called the CallAction callback");
    if(! u ) {
	WARN("Callback CallAction invoked without argument i.e. without a widget name to set the focus to");
	return;
    }

    /* need my own implementation here i.e. snprintf */
    char *args = WcCleanName( u, buffer );
    TRACE(8, "Widget Name: %s", buffer );
    widget=WcFullNameToWidget( w, buffer );
    if(! widget ) return;
    WcCleanName( args, buffer );
    TRACE(8, "Action Name: %s", buffer );
    XtCallActionProc( widget, buffer, NULL, NULL, 0 );
}


void test_cb( Widget w, void *u, void *c )
{
  printf("cb\n");

  if(! XtIsSubclass(w, weditWidgetClass ) ) return;
  char *s;
  XtVaGetValues(w, "label", &s, NULL );
  if( is_empty(s) ) return;
  printf("Label: %s\n", s );

}

void quit_cb( Widget w, void *u, void *c )
{
    TRACE(1,"QUIT");
    XtAppSetExitFlag( XtWidgetToApplicationContext(w) );
}

void vl_dump(int opts); // ini_read2.c

void SetKeyboardFocus(Widget w)
{
    Widget shell, parent;

    shell = parent = w;
    while (parent) {
        if (XtIsShell(shell = parent))
            break;
        parent = XtParent(parent);
    }
    XtSetKeyboardFocus(shell, w);
}


int CUR_PAGE = 0;

int decode_xevent(int m, XEvent* e)
{
  char *s;
  switch (e->type) {
  case ButtonPress: s="ButtonPress"; break;
  case ButtonRelease: s="ButtonRelase"; break;
  case MotionNotify: s="MotionNotify"; break;
  default: s="none";
  }
  return s_printf(m,-1,"{ t=\"%s\", x=%d, y=%d }", s, e->xbutton.x, e->xbutton.y );
}


/* --------------------------------------------------------------------------------------------------------------------

                        IMPLEMENTATION


                        Must Provide
                        - RegisterApplication
                        - InitializeApplication

  -------------------------------------------------------------------------------------------------------------------- */


/** all widgets callbacks and actions must be registered at this point
 */
static void RegisterApplication ( Widget top )
{

    /* -- Register widget classes and constructors */


    /* -- Register application specific actions */
    /* -- Register application specific callbacks */
    RCB( top, quit_cb );
    RCB( top, test_cb );
    RCB( top, SetFocus );
    RCB( top, CallAction );
}

/*  init application functions and structures and widgets
    All widgets are created, but not visible.
    functions can now communicate with widgets
*/
static void InitializeApplication( Widget top )
{
    trace_level = SIGNAGE.traceLevel;
}



static void DestroyApplication(void)
{
    // rc_free();
}

/******************************************************************************
**  Private Functions
******************************************************************************/

static void syntax(void)
{
  puts( syntax_wcl );
  puts( "-TraceLevel <num>\n" );
}

void proc_exit()
{

		int wstat;
		pid_t	pid;

		while (TRUE) {
			pid = wait3 (&wstat, WNOHANG, (struct rusage *)NULL );
			if (pid == 0)
				return;
			else if (pid == -1)
				return;
			else
			    printf ("Return code: %d\n",WEXITSTATUS( wstat ));
		}
}

/******************************************************************************
*   MAIN function
******************************************************************************/
int main ( int argc, char **argv )
{
    signal (SIGCHLD, proc_exit);
    trace_main = TRACE_MAIN;

    XtAppContext app;
    m_init(); trace_level=1;

    /*
    asgn("task1.t1=hello");
    asgn("task1.t2=world");
    const char *s = mvar_str_string( "task1", "form: $t1 und $t2");
    fprintf(stderr,"%s\n", s );
    */

    XtSetLanguageProc (NULL, NULL, NULL);
    XawInitializeWidgetSet();

    /*  --  Intialize Toolkit creating the application shell
     */
    Widget appShell = XtOpenApplication (&app, APP_NAME,
             /* resources: can be set from argv */
             options, XtNumber(options),
	     &argc, argv,
	     fallback_resources,
	     sessionShellWidgetClass,
	     NULL, 0
	   );


    /*  --  Enable Editres support
     */
    XtAddEventHandler(appShell, (EventMask) 0, True, _XEditResCheckMessages, NULL);

    /*  --  not parsed options are removed by XtOpenApplication
            the only entry left should be the program name
    */
    if (argc != 1) { m_destruct(); syntax(); exit(1); }
    TopLevel = appShell;


    /*  --  Register all application specific
            callbacks and widget classes
    */
    RegisterApplication ( appShell );

    /*  --  Register all Athena and Public
            widget classes, CBs, ACTs
    */
    XpRegisterAll ( app );
    widreg(app);

    /*  --  Create widget tree below toplevel shell
            using Xrm database
    */
    WcWidgetCreation ( appShell );

    /*  -- Get application resources and widget ptrs
     */
    XtGetApplicationResources(	appShell, (XtPointer)&SIGNAGE,
				SIGNAGE_CONFIG_RES,
				XtNumber(SIGNAGE_CONFIG_RES),
				(ArgList)0, 0 );

    InitializeApplication(appShell);

    /*  --  Realize the widget tree and enter
            the main application loop  */
    XtRealizeWidget ( appShell );


    grab_window_quit( appShell );
    XtAddCallback( appShell, XtNdieCallback, quit_cb, NULL );


    XtAppMainLoop ( app ); /* use XtAppSetExitFlag */

    XtDestroyWidget(appShell);
    DestroyApplication();
    font_cache_flush();
    m_destruct();

    return EXIT_SUCCESS;
}
