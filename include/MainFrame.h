#pragma once

#include <wx/wx.h>
#include "GLCanvas.h"
#include "ControlPanel.h"

class MainFrame : public wxFrame
{
public:
    MainFrame();
    void ToggleControlPanel();

private:
    GLCanvas* m_glCanvas;
    ControlPanel* m_controlPanel;
    bool m_isPanelVisible;

    void OnSize(wxSizeEvent& event);

    wxDECLARE_EVENT_TABLE();
}; 