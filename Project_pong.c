#include <ansi_c.h>
#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include "Project_pong.h"
#include "dll.h"

static char *gAngledFont = "MyAngledMetaFont"; 
static int panelHandle, panel2, ctrlarray;
int H,W,flag=0,jump=20,jump2=20,ball_x,ball_y,ball_x2,ball_y2,dx=10,dy=10,xflag,yflag,dx2=10,dy2=10;
int score[2],difflvl,goals2win,pudlesize,winflag=0,nofballs;
void DrawWhiteRect(Rect rect);
void DrawBal();
void DrawLeftUser(int H,int W);
void clearcanvas();
void DrawRightUser (int X, int Y);
static void move_ball();
int check_collision();
char str1[10],str2[10];
// multithreading
int CVICALLBACK threadfunction1 (void *callbackData);
int CVICALLBACK threadfunction2 (void *callbackData);
int CVICALLBACK threadfunction3 (void *callbackData);
int CVICALLBACK threadfunction4 (void *callbackData);
int CVICALLBACK ballthread (void *callbackData);

CmtThreadPoolHandle threadhandle, threadhandle2 ,threadhandle3;
CmtThreadFunctionID val1, val2, val3, val4, val5, val6;
CmtThreadLockHandle key,lockhandle;


int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Project_pong.uir", PANEL)) < 0)
		return -1;
	if ((panel2 = LoadPanel (0, "Project_pong.uir", PANEL_2)) < 0)
		return -1;
	ctrlarray = GetCtrlArrayFromResourceID (panel2, CTRLARRAY);
	DisplayPanel (panelHandle);
		
	RunUserInterface ();
	DiscardPanel (panelHandle);
	DiscardPanel (panel2);
	return 0;
}


int CVICALLBACK QuitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK Pongfunction (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch(event) {
	 		case EVENT_KEYPRESS:
			{
				switch(eventData1)
				{
				
					case VAL_ESC_VKEY:
						{
						HidePanel (panel2); 
						DisplayPanel (panelHandle);
						break;
						}
					case VAL_UP_ARROW_VKEY:
						{
						CmtScheduleThreadPoolFunction (threadhandle, threadfunction3, NULL, &val1);
						switch(eventData1)
						{
							case 0x77: // W:
								{
									CmtScheduleThreadPoolFunction (threadhandle2, threadfunction1, NULL, &val2);
									break; 	
								}
							case 0x73: // S:
								{
									CmtScheduleThreadPoolFunction (threadhandle2, threadfunction2, NULL, &val2);
									break; 	
								}
							case 0x57: // w:
								{
									CmtScheduleThreadPoolFunction (threadhandle2, threadfunction1, NULL, &val2);
									break; 	
								}
							case 0x53: // s:
								{
									CmtScheduleThreadPoolFunction (threadhandle2, threadfunction2, NULL, &val2);
									break; 	
								}	
						}	 
						break; 
						}
						
					case VAL_DOWN_ARROW_VKEY:
						{
						CmtScheduleThreadPoolFunction (threadhandle, threadfunction4, NULL, &val1);
						
						switch(eventData1)
						{
							case 0x77: // W:
								{
									CmtScheduleThreadPoolFunction (threadhandle2, threadfunction1, NULL, &val2);
									break; 	
								}
							case 0x73: // S:
								{
									CmtScheduleThreadPoolFunction (threadhandle2, threadfunction2, NULL, &val2);
									break; 	
								}
							case 0x57: // w:
								{
									CmtScheduleThreadPoolFunction (threadhandle2, threadfunction1, NULL, &val2);
									break; 	
								}
							case 0x53: // s:
								{
									CmtScheduleThreadPoolFunction (threadhandle2, threadfunction2, NULL, &val2);
									break; 	
								}	
						}
						break; 	
						}
					case 0x77: // W:
						{
						CmtScheduleThreadPoolFunction (threadhandle2, threadfunction1, NULL, &val2);
						
						switch(eventData1)
						{
							case VAL_UP_ARROW_VKEY:
							{
								CmtScheduleThreadPoolFunction (threadhandle, threadfunction3, NULL, &val1);
								break;
							}
							case VAL_DOWN_ARROW_VKEY:
							{
								CmtScheduleThreadPoolFunction (threadhandle, threadfunction4, NULL, &val1);
								break;
							}
						} 
						break; 	
						}
					case 0x73: // S:
						{
						CmtScheduleThreadPoolFunction (threadhandle2, threadfunction2, NULL, &val2);
						switch(eventData1)
						{
							case VAL_UP_ARROW_VKEY:
							{
								CmtScheduleThreadPoolFunction (threadhandle, threadfunction3, NULL, &val1);
								break;
							}
							case VAL_DOWN_ARROW_VKEY:
							{
								CmtScheduleThreadPoolFunction (threadhandle, threadfunction4, NULL, &val1);
								break;
							}
						}  
						break; 	
						}
					case 0x57: // w:
						{
						CmtScheduleThreadPoolFunction (threadhandle2, threadfunction1, NULL, &val2);
						switch(eventData1)
						{
							case VAL_UP_ARROW_VKEY:
							{
								CmtScheduleThreadPoolFunction (threadhandle, threadfunction3, NULL, &val1);
								break;
							}
							case VAL_DOWN_ARROW_VKEY:
							{
								CmtScheduleThreadPoolFunction (threadhandle, threadfunction4, NULL, &val1);
								break;
							}  
						} 
						break; 	
						}
					case 0x53: // s:
						{
						CmtScheduleThreadPoolFunction (threadhandle2, threadfunction2, NULL, &val2);
						switch(eventData1)
						{
							case VAL_UP_ARROW_VKEY:
							{
								CmtScheduleThreadPoolFunction (threadhandle, threadfunction3, NULL, &val1);
								break;
							}
							case VAL_DOWN_ARROW_VKEY:
							{
								CmtScheduleThreadPoolFunction (threadhandle, threadfunction4, NULL, &val1);
								break;
							}
						}					
						break; 	
						}							 
				}
			}
	}
	return 0;
}


int CVICALLBACK okfunc (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{	  
	   switch (event) 
	{
		case EVENT_COMMIT:	
			{
				HidePanel (panelHandle);
				DisplayPanel (panel2);
				if(flag==0) {
				GetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_HEIGHT, &H);
				GetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_WIDTH, &W);
				}
				flag=1;
				SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, flag);
				score[0] = 0;
				score[1] = 0;
				clearcanvas();
				DrawLeftUser(W,H);
				DrawRightUser (W,H);
				ball_x = W/2;
				ball_y = H/2;
				ball_x2 = W/2;
				ball_y2 = H/2;
				DrawBal(ball_x,ball_y);
				CmtNewLock(NULL,OPT_TL_SUPPORT_TIMEOUT, &lockhandle);
				CmtNewThreadPool (1, &threadhandle);
				CmtNewThreadPool (1, &threadhandle2);
				CmtNewThreadPool (1, &threadhandle3);
				sprintf(str1, "%d", score[0]);
				sprintf(str2, "%d", score[1]);
				GetCtrlVal(panelHandle,PANEL_NUMERIC, &difflvl);
				GetCtrlVal(panelHandle,PANEL_NUMERIC_2, &goals2win);
				GetCtrlVal(panelHandle,PANEL_NUMERIC_4, &pudlesize);
				GetCtrlVal(panelHandle,PANEL_NUMERIC_5, &nofballs);
				
				dx = 10 * difflvl;	
				dy = 10 * difflvl;
				dx2 = dx/2;
				dy2 = dy/2;
				SetCtrlAttribute (panel2, PANEL_2_STRING, ATTR_VISIBLE, 0);
				SetCtrlAttribute (panel2, PANEL_2_PICTURE, ATTR_VISIBLE, 0);
				SetCtrlAttribute (panel2, PANEL_2_STRING_2, ATTR_VISIBLE, 0);		   
				SetCtrlAttribute (panel2, PANEL_2_TABLE, ATTR_VISIBLE, 0);      
				winflag=0;
				if(nofballs>1)
					DrawBal(ball_x2,ball_y2);
				break;
			}
		
	}
	return 0;
}

int CVICALLBACK startgamefunc2 (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	return 0;
}
void DrawWhiteRect(Rect rect) {
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_COLOR, VAL_WHITE);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);	
	CanvasDrawRect(panel2, PANEL_2_CANVAS, rect, VAL_DRAW_FRAME_AND_INTERIOR);
}
void DrawBal(int X, int Y) {
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_COLOR, VAL_WHITE);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_WIDTH, 15);
	CanvasDrawPoint (panel2, PANEL_2_CANVAS, MakePoint (X, Y));
	CanvasUpdate(panel2,PANEL_2_CANVAS,VAL_ENTIRE_OBJECT);
}
void DrawLeftUser(int X, int Y) {
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_COLOR, VAL_WHITE);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);	
	CanvasDrawRect(panel2, PANEL_2_CANVAS, MakeRect(Y/2-(pudlesize*90/2),8, 90*pudlesize,12), VAL_DRAW_FRAME_AND_INTERIOR);
	CanvasUpdate(panel2,PANEL_2_CANVAS,VAL_ENTIRE_OBJECT);
}
void clearcanvas() {
	
	int j=0,i=1;
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_COLOR, VAL_BLACK);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLACK);	
	CanvasClear(panel2, PANEL_2_CANVAS, VAL_ENTIRE_OBJECT);

	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_COLOR, VAL_WHITE);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);	
	CanvasDrawRect(panel2, PANEL_2_CANVAS, MakeRect(0,0, H,2), VAL_DRAW_INTERIOR);	
	
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_FILL_COLOR, VAL_BLACK);
	CreateMetaFontEx(gAngledFont, VAL_DIALOG_FONT, 50, 0, 0, 0, 0, 0); 
	CanvasDrawTextAtPoint (panel2, PANEL_2_CANVAS, str1, gAngledFont, MakePoint (W/2-200, 50), VAL_CENTER);    
	CanvasDrawTextAtPoint (panel2, PANEL_2_CANVAS, str2, gAngledFont, MakePoint (W/2+200, 50), VAL_CENTER);
	
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_COLOR, VAL_WHITE);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);	
	CanvasDrawRect(panel2, PANEL_2_CANVAS, MakeRect(0,0, 2,W), VAL_DRAW_INTERIOR);	
	
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_COLOR, VAL_WHITE);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);	
	CanvasDrawRect(panel2, PANEL_2_CANVAS, MakeRect(0,W-2, H,2), VAL_DRAW_INTERIOR);
	
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_COLOR, VAL_WHITE);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);	
	CanvasDrawRect(panel2, PANEL_2_CANVAS, MakeRect(H-2,0, 2,W), VAL_DRAW_INTERIOR);
	CanvasUpdate(panel2,PANEL_2_CANVAS,VAL_ENTIRE_OBJECT);
	
}
void DrawRightUser (int X, int Y) {
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_DRAW_POLICY, VAL_MARK_FOR_UPDATE);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_COLOR, VAL_WHITE);
	SetCtrlAttribute (panel2, PANEL_2_CANVAS, ATTR_PEN_FILL_COLOR, VAL_WHITE);	
	CanvasDrawRect(panel2, PANEL_2_CANVAS, MakeRect(Y/2-(pudlesize*90/2),X-20, 90*pudlesize,12), VAL_DRAW_FRAME_AND_INTERIOR);
	CanvasUpdate(panel2,PANEL_2_CANVAS,VAL_ENTIRE_OBJECT); 
}

int check_collision() {

if (ball_x>=W-30)
{
	 	if (ball_y <= (H+jump2)/2+(pudlesize*90/2) && ball_y >= (H+jump2)/2-(pudlesize*90/2))	
	 {
	    return 2;	 
	 }
}
if (ball_x<=30)
{
	 if (ball_y <= (H+jump)/2+(pudlesize*90/2) && ball_y >= (H+jump)/2-(pudlesize*90/2))	
	 {
	    return 1;	 
	 }
}
if (ball_x2>=W-30)
{
	 	if (ball_y2 <= (H+jump2)/2+(pudlesize*90/2) && ball_y2 >= (H+jump2)/2-(pudlesize*90/2))	
	 {
	    return 3;	 
	 }
}
if (ball_x2<=30)
{
	 if (ball_y2 <= (H+jump)/2+(pudlesize*90/2) && ball_y2 >= (H+jump)/2-(pudlesize*90/2))	
	 {
	    return 4;	 
	 }
}
return 0;
}

static void move_ball() {
  int collision;
  int z;
  
  ball_x += dx;
  ball_y += dy;
  if (ball_x <= 0)
  {
	  score[1]+=1; //right
	  sprintf(str2, "%d", score[1]);   
	  ball_x = W/2;
	  ball_y = H/2;
	  dy = 10*difflvl;
	  clearcanvas(); 
	  DrawBal(ball_x, ball_y);
  }
  if (ball_x >= W)
  {
	  score[0]+=1; //left
	  sprintf(str1, "%d", score[0]);
	  ball_x = W/2;
	  ball_y = H/2;
	  clearcanvas();
	  dy = 10*difflvl;
	  DrawBal(ball_x, ball_y);
  }
   if (ball_y <=5 || ball_y >= H-5)
   {
	  dy=-dy;
   }
   collision = check_collision() ;
   
   if(nofballs>1) { //ball2 creation.
	ball_x2 += -dx2;
  	ball_y2 += -dy2;
  if (ball_x2 <= 0)
  {
	  score[1]+=1; //right
	  sprintf(str2, "%d", score[1]);   
	  ball_x2 = W/2;
	  ball_y2 = H/2;
	  dy2 = 10*difflvl;
	  clearcanvas(); 
	  DrawBal(ball_x2, ball_y2);
  }
  if (ball_x2 >= W)
  {
	  score[0]+=1; //left
	  sprintf(str1, "%d", score[0]);
	  ball_x2 = W/2;
	  ball_y2 = H/2;
	  clearcanvas();
	  dy2 = 10*difflvl;
	  DrawBal(ball_x2, ball_y2);
  }
   if (ball_y2 <=5 || ball_y2 >= H-5)
   {
	  dy2=-dy2;
   }
  
   collision = check_collision() ;   
   }
  switch (collision)
  {
 	 case 1:	// left paddle
 	 	 { 
			dx=-dx ;
			int hit_pos = (H+jump)/2+45 - ball_y ;
			dy= dll_getdyposition(hit_pos,difflvl,dy);
			break;
		 }				 
 	 case 2:    // right paddle
		 {
			dx=-dx ;
			int hit_pos = (H+jump2)/2+45 - ball_y ;
			dy= dll_getdyposition2(hit_pos,difflvl,dy); 
			break;	
		 }
 	 case 3:	// left paddle 2nd ball
 	 	 { 
			dx2=-dx2 ;
			int hit_pos = (H+jump)/2+45 - ball_y2 ;
			dy2= dll_getdyposition(hit_pos,difflvl,dy2);
			break;
			
			
		 }				 
 	 case 4:    // right paddle 2nd ball
		 {
			dx2=-dx2 ;
			int hit_pos = (H+jump2)/2+45 - ball_y2 ;
			dy2= dll_getdyposition2(hit_pos,difflvl,dy2);
			break;	
		 }		 
     default: {
		 clearcanvas();
		 DrawBal(ball_x, ball_y);
		 if(nofballs>1)
		 	DrawBal(ball_x2, ball_y2); 
		 DrawLeftUser(W,H+jump);
	     DrawRightUser(W,H+jump2);
		 
	 }
			 
	  }			  
}

int CVICALLBACK balltimerfunction (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{   int numofgames=0;
	int z=0;
	int leftscorearr[300],rightscorearr[300];
	switch (event)
	{
		case EVENT_TIMER_TICK:
		   CmtScheduleThreadPoolFunction (threadhandle3, ballthread, NULL, &val3);
		    if (score[0] == goals2win || score[1] == goals2win )
			{
				winflag=1;
				FILE *f;
				int score_left, score_right,i=1,j=1;
 
				f = fopen ("ScoreBoard.txt","r+");
				
				while (!feof(f))
				{
				fscanf(f,"%d %d\n", &leftscorearr[z], &rightscorearr[z]);
				z++;
				}
				fclose(f);
				f = fopen ("ScoreBoard.txt","r+");
				fprintf (f, "%d %d\n",score[0],score[1]);
				for(numofgames=0;numofgames<z;) {
				numofgames++ ;
				fprintf (f, "%d %d\n",leftscorearr[numofgames-1],rightscorearr[numofgames-1]); 	
				}
 				
				fclose(f);
				f = fopen ("ScoreBoard.txt","r");
				numofgames++;
				if(numofgames>10) {
					numofgames=11;
				}
				while (!feof(f))
				{  
					if(i>10) {
					    i=10;
						break;
				   } else {
				   fscanf(f,"%d %d\n", &score_left, &score_right);
 				   SetTableCellVal (panel2, PANEL_2_TABLE, MakePoint (j, i), score_left);
				   j++;
				   SetTableCellVal (panel2, PANEL_2_TABLE, MakePoint (j, i), score_right);  
				   j--;
				   i++;
				   }
				}
				
				
				fclose(f);
				 if(score[0] == goals2win)
					SetCtrlAttribute (panel2, PANEL_2_STRING, ATTR_CTRL_VAL, "Left Player Won");
				 else
					SetCtrlAttribute (panel2, PANEL_2_STRING, ATTR_CTRL_VAL, "Right Player Won");
				SetCtrlAttribute (panel2, PANEL_2_STRING, ATTR_VISIBLE, 1);
				SetCtrlAttribute (panel2, PANEL_2_TABLE, ATTR_VISIBLE, 1);
				SetCtrlAttribute (panel2, PANEL_2_PICTURE, ATTR_VISIBLE, 1);
				SetCtrlAttribute (panel2, PANEL_2_STRING_2, ATTR_VISIBLE, 1);
				flag=0;
				SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, flag);
			}	
			break;
	}
	return 0;
}
int CVICALLBACK threadfunction1 (void *callbackData) {
	//up left
	if (winflag==0) {
		if(jump<=-H+(pudlesize*90+10))
			jump = -H+(pudlesize*90+10);	
		else
			jump-=40;
		DrawLeftUser(W,H+jump);
		DrawRightUser(W,H+jump2);
	}
	return 0;
}
int CVICALLBACK threadfunction2 (void *callbackData) { 
	//down left
	if (winflag==0) { 
		if(jump>=H-(pudlesize*90+10))
			jump = H-(pudlesize*90+10);	
		else
			jump+=40;
		DrawLeftUser(W,H+jump);
		DrawRightUser(W,H+jump2);
	}
	return 0;
}
	 
int CVICALLBACK threadfunction3 (void *callbackData) {	
	  //up right
	if (winflag==0) {	   
		if(jump2<=-H+(pudlesize*90+10))
			jump2 = -H+(pudlesize*90+10);	
		else
			jump2-=40;
		DrawRightUser(W,H+jump2);
		DrawLeftUser(W,H+jump);
	}
	return 0;
}
int CVICALLBACK threadfunction4 (void *callbackData) { 
	 // down right
	if (winflag==0) { 	 ;
		if(jump2>=H-(pudlesize*90+10))
			jump2 = H-(pudlesize*90+10);	
		else
			jump2+=40;
		DrawRightUser(W,H+jump2);
		DrawLeftUser(W,H+jump);
	}
	return 0;
} 
int CVICALLBACK ballthread (void *callbackData) {
	
	CmtGetLock(lockhandle);
	move_ball();
	CmtReleaseLock(lockhandle);
	return 0;
}
