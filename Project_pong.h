/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_QUITBUTTON                 2       /* control type: command, callback function: QuitCallback */
#define  PANEL_COMMANDBUTTON              3       /* control type: command, callback function: okfunc */
#define  PANEL_PICTURE                    4       /* control type: picture, callback function: startgamefunc2 */
#define  PANEL_NUMERIC                    5       /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_5                  6       /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_4                  7       /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_2                  8       /* control type: numeric, callback function: (none) */
#define  PANEL_TIMER                      9       /* control type: timer, callback function: balltimerfunction */

#define  PANEL_2                          2
#define  PANEL_2_CANVAS                   2       /* control type: canvas, callback function: Pongfunction */
#define  PANEL_2_PICTURE                  3       /* control type: picture, callback function: (none) */
#define  PANEL_2_STRING                   4       /* control type: textMsg, callback function: (none) */
#define  PANEL_2_TABLE                    5       /* control type: table, callback function: (none) */
#define  PANEL_2_STRING_2                 6       /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

#define  CTRLARRAY                        1
#define  CTRLARRAY_2                      2

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK balltimerfunction(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK okfunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pongfunction(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK startgamefunc2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
