#include <wx/wx.h>
#include "MainFrame.h"
#include <wx/log.h>

class GLCanvasApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        wxInitAllImageHandlers();
        wxLog::EnableLogging(true);
        wxLog::SetLogLevel(wxLOG_Message);
        
        MainFrame* frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(GLCanvasApp);

int main(int argc, char** argv)
{
    return wxEntry(argc, argv);
} 