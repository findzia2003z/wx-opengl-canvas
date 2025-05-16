#include "MainFrame.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_SIZE(MainFrame::OnSize)
wxEND_EVENT_TABLE()

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "GL Canvas App", wxDefaultPosition, wxSize(800, 600))
    , m_isPanelVisible(false)
{
    // Create a sizer for the main frame
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    // Create the GL canvas
    m_glCanvas = new GLCanvas(this);
    mainSizer->Add(m_glCanvas, 1, wxEXPAND);

    // Create the control panel (initially hidden)
    m_controlPanel = new ControlPanel(this, m_glCanvas);
    mainSizer->Add(m_controlPanel, 0, wxEXPAND);
    m_controlPanel->Hide();

    SetSizer(mainSizer);

    // Center the frame
    Centre();
}

void MainFrame::OnSize(wxSizeEvent& event)
{
    event.Skip();
    if (GetSizer())
    {
        GetSizer()->Layout();
    }
}

void MainFrame::ToggleControlPanel()
{
    m_isPanelVisible = !m_isPanelVisible;
    m_controlPanel->Show(m_isPanelVisible);
    GetSizer()->Layout();
} 