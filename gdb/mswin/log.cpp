// log.cpp : implementation file

/* We save the logview as a standard editview, and we buffer
   up text from gdb until we get to an idle.  If we see a return
   from the user, then we suck up that line and treat it as input */

// OnEditChange is called when text is added to the log window.
// This happens when doidle calls GetEditCtrl().ReplaceSel
// to print text strored up in the CString class "pending".
// "pending" is appended by gdb output via gdbwin_fputs, 
// User input is echoed via the base class CEdit.
// When the user presses return, OnKeyDown gets control.
// this routine copies the command and sends it off to gdb.
// At this point, gdb is blocked until gdb returns and 
// execution resumes inside OnKeyDown.

#include "stdafx.h"
#include "log.h"

extern CGuiApp theApp;

static char linebuf[100];
static int cmd_entered = 0;
static char prompt[32] = "(gdb) ";
/* index within line where command begins */
static int cmd_start = strlen(prompt);	

/* class CHistory - used to save user's commands */
#define MAX_CMDHIST 25	/* max number of commands to remeber */
#define MAX_CMDLEN 256	/* max number of chars in a command */
class CHistory 
{
public:
  CHistory(void);
  char *next(void);
  char *prev(void);
  void add(char *cmd);
//  void reset(void);

private:
  int cmd_index;
  int cmd_select;
  int max_cmds;
  char cmd_history[MAX_CMDHIST][MAX_CMDLEN];
};

static CHistory cmdhist;

CHistory::CHistory(void) 
{ 
      cmd_index = 0; 	/* index of next slot to fill in circular buffer */
      cmd_select = 0;	/* index of current selection */ 
      max_cmds = 0;
      //cmd_history = new char[MAX_CMDHIST][MAX_CMDLEN];
      //if (!cmd_history)
      //  max_cmds = 0;
      //else
      //  {
          memset(cmd_history,0,MAX_CMDHIST*MAX_CMDLEN);
          max_cmds = MAX_CMDHIST;
      //  }
}
char *CHistory::next(void) 
{
      cmd_select++;
      if (cmd_select >= max_cmds)
        cmd_select = 0;	/* wrap around to beginning */
      return cmd_history[cmd_select];
}
char *CHistory::prev(void)
{
      cmd_select--;
      if (cmd_select < 0)
        cmd_select = max_cmds-1;	/* wrap around to end */
      return cmd_history[cmd_select];
}
void CHistory::add(char *cmd) 
{
      strcpy(cmd_history[cmd_index], cmd);
      cmd_index++;
      if (cmd_index >= max_cmds)
        cmd_index = 0; 		/* wrap around to beginning */
      cmd_select = cmd_index;
}
//void CHistory::reset(void) 
//{
//      cmd_select = cmd_index;
//}


static void redraw_allcmdlogwins()
{ 
  redraw_allwins(theApp.m_CmdLogTemplate);
}
static void redraw_alliologwins()
{ 
  redraw_allwins(theApp.m_IOLogTemplate);
}

CFontInfo cmdlogview_fontinfo ("Command", redraw_allcmdlogwins);
CFontInfo iologview_fontinfo  ("IO", redraw_alliologwins);

IMPLEMENT_DYNCREATE(CGenericLogView, CEditView)



CIOLogView *iowinptr;
CCmdLogView *cmdwinptr;


CGenericLogView::CGenericLogView()
{
  // How's getptr getting initialized??
  ASSERT(getptr);
  *(getptr) = this;
  shown = 0;
  ASSERT(getfontinfo);
  getfontinfo->MakeFont();
}

CGenericLogView::~CGenericLogView()
{
  *(getptr) = 0;
}


BEGIN_MESSAGE_MAP(CGenericLogView, CEditView)
	//{{AFX_MSG_MAP(CGenericLogView)
	ON_COMMAND(ID_REAL_CMD_BUTTON_SET_FONT, OnSetFont)
	ON_EN_CHANGE(AFX_IDW_PANE_FIRST, OnEditChange)
	ON_WM_SHOWWINDOW()
	ON_WM_KEYDOWN()
	ON_WM_DESTROY()
     ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//May want to add later
//	ON_WM_PROMPT()


void CGenericLogView::add(const char *s)
{
    pending += s;
}

// Problems...
// we want to flush when gdb sends us something 
// (when gdbwin_fputs is called in iface)
// But, we want to print status back from gdb for the user,
// so we don't want to wait until the user presses return.
// We'll buffer until we receive a newline and hope that that's
// good enough.
void CGenericLogView::flush()
{
    doidle();
}

void CGenericLogView::OnDraw(CDC* pDC)
{
    CDocument* pDoc = GetDocument();
}


void CGenericLogView::OnSetFont() 
{
  getfontinfo ->OnChooseFont();	
  SetFont(&(getfontinfo ->m_font));
}

BOOL CGenericLogView::PreCreateWindow(CREATESTRUCT& cs) 
{
  return CEditView::PreCreateWindow(cs);
}

void CGenericLogView::OnInitialUpdate() 
{
  SetFont(&(getfontinfo ->m_font));
  CEditView::OnInitialUpdate();
  load_where(GetParentFrame(), getfontinfo->windowname);
  // Want to post a VK_RETURN here so we'll get a prompt
  // and wait for a command.
  // Note: This version of PostMessage is an inherited MFC member function
  // BOOL PostMessageA(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);
  PostMessage(WM_KEYDOWN,VK_RETURN);
}


void CGenericLogView::OnDestroy() 
{
    save_where(GetParentFrame(), getfontinfo->windowname);
    CEditView::OnDestroy();
}

void CGenericLogView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
  CEditView::OnShowWindow(bShow, nStatus);
}

void CGenericLogView::OnEditChange()
{
  CEditView::OnEditChange();
  // FIXME!  do a post msg, then pick up the msg and get the cmd
  if (cmd_entered) {
    char buf[200];
    static int j;
    cmd_entered = 0;
    cmdhist.add(linebuf+cmd_start); //add to cmd history 
    togdb_command_from_tty(linebuf+cmd_start); //get command response from gdb

    sprintf(buf, prompt, j++);
    add (buf);	// get ready for next input
  	//togdb_force_update ();
  }
}

#if 0
void CGenericLogView::OnPrompt(void)
{
    togdb_command_from_tty(linebuf+cmd_start);
}
#endif

void CGenericLogView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  doidle();
  int line = GetEditCtrl().GetLineCount();
  int col = GetEditCtrl().GetLine(line-1, linebuf, sizeof(linebuf));
  int idx = GetEditCtrl().LineIndex(line-1);
  
  // Check these filters before calling parent
  
  switch (nChar)
    {
        case VK_BACK:
	    // make sure we don't go past the command prompt
	    if (col <= cmd_start)
	      {
		// insert a space, then backspace over that space
		GetEditCtrl().ReplaceSel(" ");
		return;         
    }
	    break;
        case VK_LEFT:
	    // make sure we don't go past the command prompt
	    if (col <= cmd_start)
		return; 	// ignore
	    break;
        case VK_UP:
	    // replace with previous command from history 
	    strcpy(linebuf, cmdhist.prev());
	    GetEditCtrl().SetSel (idx + cmd_start, idx + col+1, TRUE);
	    GetEditCtrl().ReplaceSel(linebuf);
	    return;         
        case VK_DOWN:
	    // replace with next command in history 
	    strcpy(linebuf, cmdhist.next());
	    GetEditCtrl().SetSel (idx + cmd_start, idx + col+1, TRUE);
	    GetEditCtrl().ReplaceSel(linebuf);
            return;         
	case VK_RETURN:
  // We wait for return from user, then get control here.
  // cmd_entered is set so that OnEditChange will process the command 
    {
      // null-terminate the last line (the user's command)
	      // col points to the the end of the user's command.
	      linebuf[col] = 0;
      cmd_entered = 1;
	      // read command line
	      col = GetEditCtrl().GetLine(line-1, linebuf, sizeof(linebuf));
	      // place cursor at end of command
      	      GetEditCtrl().SetSel (idx + col, idx + col, TRUE);
	    }
	    break;
    }

  CEditView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGenericLogView::OnIdle() 
{
  //if (*getptr())
  //  getptr()->doidle();
}

void CGenericLogView::doidle()
{
  if (pending.GetLength()) 
    { 
      WINDOWPLACEMENT wnp;
      GetWindowPlacement (&wnp); 
      if (wnp.showCmd != SW_SHOWMINIMIZED) 
	{ 
	  int i;
	  while (pending.GetLength()) 
	  {
	    i = pending.Find('\n');
	    if (i >= 0)
	      {
		CString l = pending.Left(i);

		// SetSel(startchar, endchar, noscroll_flag)
		//   scrollflag-   FLASE - scroll into view. If 
		//   startchar-   starting position. If startchar is 0 and 
		//      endchar is -1, all the text in the edit control is 
		//      selected. If startchar is -1, any current selection 
		//      is removed.
		//   nedchar-   ending position.

		GetEditCtrl().SetSel(-1,-1,FALSE); 
		// this command causes call to OnEditChange
		GetEditCtrl().ReplaceSel(l);	
		GetEditCtrl().ReplaceSel("\r"); 
		GetEditCtrl().ReplaceSel("\n"); 
		pending = pending.Mid(i+1);
	      }
	    else 
	      {
	        GetEditCtrl().ReplaceSel(pending); 
	        pending ="";
	        return ;
	      }
	  }
	} 
    }
}


IMPLEMENT_DYNCREATE(CIOLogView, CGenericLogView)
IMPLEMENT_DYNCREATE(CCmdLogView, CGenericLogView)


void CCmdLogView::Initialize()
{
  cmdlogview_fontinfo.Initialize();
}
void CCmdLogView::Terminate() 
{
  cmdlogview_fontinfo.Terminate();
}

void CIOLogView::Initialize()
{
  iologview_fontinfo.Initialize();
}
void CIOLogView::Terminate() 
{
  iologview_fontinfo.Terminate();
}



CGenericLogView::CGenericLogView(CGenericLogView **p, CFontInfo *f) 

{ 
    shown = 0;
    *p = this; 
    getptr = p; 
    getfontinfo = f;
}

CIOLogView::CIOLogView() 
    : CGenericLogView ((CGenericLogView **)&iowinptr,   &iologview_fontinfo) 
{
}

CCmdLogView::CCmdLogView() 
    : CGenericLogView ((CGenericLogView **)&cmdwinptr, &cmdlogview_fontinfo)  
{
}


void CIOLogView_output (const char *s)
{
  if (!iowinptr)
    {
        /* Window doesn't exist!! make one */
	theApp.OnNewIOLogWin(); 
    }

  if (iowinptr)
    {
      iowinptr->add (s);
      iowinptr->doidle ();
    }
}

void CGenericLogView::OnSize(UINT nType, int cx, int cy) 
{
  //  ::OnSize(nType, cx, cy);
  // TODO: Add your message handler code here
  GetWindowRect (&getfontinfo->where);
  SetFont(&(getfontinfo ->m_font));
}

