/*--------------------------------------------------------------------------*/
/* XAW  toolkit                                                             */
/*--------------------------------------------------------------------------*/

#include <config.h>

#include <xaw-toolkit-priv.h>
#include <toolkit.h>
#include <stdlib.h>

/*--------------------------------------------------------------------------*/
/* functions                                                                */
/*--------------------------------------------------------------------------*/

static void xaw_toolkit_close(void *_priv);
static int xaw_toolkit_is_toolkit_active(void *_priv);
static Display *xaw_toolkit_get_xdisplay(void *_priv);
static Window xaw_toolkit_get_xwindow(void *_priv);
void xaw_toolkit_message_box(void *_priv, char *msg);
static void xaw_toolkit_set_progressbar(void *_priv,
                                        char *msg, float progress);
static void xaw_toolkit_set_sensitive_options(void *_priv, int game_active);
static void xaw_toolkit_set_toolkit_active(void *_priv, int active);
static void xaw_toolkit_set_visible_gui(void *_priv, int visible);
static void xaw_toolkit_xflush(void *_priv);
static void xaw_toolkit_create_main_window(void *_priv);

/*--------------------------------------------------------------------------*/
/* xaw_toolkit_init                                                         */
/*--------------------------------------------------------------------------*/

void *xaw_toolkit_init(TOOLKIT *toolkit, int *argc, char **argv)
{
   PRIV *priv;

   toolkit->close = xaw_toolkit_close;
   toolkit->create_main_window    = xaw_toolkit_create_main_window;
   toolkit->get_xdisplay          = xaw_toolkit_get_xdisplay;
   toolkit->get_xwindow           = xaw_toolkit_get_xwindow;
   toolkit->is_toolkit_active     = xaw_toolkit_is_toolkit_active;
   toolkit->message_box           = xaw_toolkit_message_box;
   toolkit->set_progressbar       = xaw_toolkit_set_progressbar;
   toolkit->set_sensitive_options = xaw_toolkit_set_sensitive_options;
   toolkit->set_toolkit_active    = xaw_toolkit_set_toolkit_active;
   toolkit->set_visible_gui       = xaw_toolkit_set_visible_gui;
   toolkit->xflush                = xaw_toolkit_xflush;

   priv = malloc(sizeof(PRIV));
   return priv;
}


static void xaw_toolkit_create_main_window(void *_priv) {}

/*--------------------------------------------------------------------------*/
/* xaw_toolkit_close                                                        */
/*--------------------------------------------------------------------------*/

static void xaw_toolkit_close(void *_priv)
{
   free(_priv);
}

/*--------------------------------------------------------------------------*/
/* xaw_toolkit_is_toolkit_active                                            */
/*--------------------------------------------------------------------------*/

static int xaw_toolkit_is_toolkit_active(void *_priv)
{
  return 1;
}

/*--------------------------------------------------------------------------*/
/* xaw_toolkit_get_xdisplay                                                 */
/*--------------------------------------------------------------------------*/

static Display *xaw_toolkit_get_xdisplay(void *_priv)
{
  return (Display*) NULL;
}

/*--------------------------------------------------------------------------*/
/* xaw_toolkit_get_xwindow                                                  */
/*--------------------------------------------------------------------------*/

static Window xaw_toolkit_get_xwindow(void *_priv)
{
   PRIV *priv;

   priv = (PRIV *)_priv;
   return 0;
}

/*--------------------------------------------------------------------------*/
/* xaw_toolkit_message_box                                                  */
/*--------------------------------------------------------------------------*/

void xaw_toolkit_message_box(void *_priv, char *msg)
{
}

/*--------------------------------------------------------------------------*/
/* xaw_toolkit_set_progressbar                                              */
/*--------------------------------------------------------------------------*/

static void xaw_toolkit_set_progressbar(void *_priv,
                                        char *msg, float progress)
{
   PRIV *priv = (PRIV *)_priv;

   if (progress == 0.0) ; /* disable */
   if (progress == 1.0) ; /* enable */

   /* update slider pos and mesage */

   toolkit_xflush();
}

/*--------------------------------------------------------------------------*/
/* xaw_toolkit_set_sensitive_options                                        */
/*--------------------------------------------------------------------------*/

static void xaw_toolkit_set_sensitive_options(void *_priv, int game_active)
{
   PRIV *priv;

   priv = (PRIV *)_priv;

}

/*--------------------------------------------------------------------------*/
/* xaw_toolkit_set_toolkit_active                                           */
/*--------------------------------------------------------------------------*/

static void xaw_toolkit_set_toolkit_active(void *_priv, int active)
{
   if (active)
     {}     /* set active */
   else
     {}
     /* quit gui */
}

/*--------------------------------------------------------------------------*/
/* xaw_toolkit_set_visible_gui                                              */
/*--------------------------------------------------------------------------*/

static void xaw_toolkit_set_visible_gui(void *_priv, int visible)
{
   PRIV *priv;

   priv = (PRIV *)_priv;

   if (visible) {
     /* show gui */
   } else {
     /* hide gui */
   }
}

/*--------------------------------------------------------------------------*/
/* xaw_toolkit_xflush                                                       */
/*--------------------------------------------------------------------------*/

static void xaw_toolkit_xflush(void *_priv)
{
  /* sync ?? */
}
