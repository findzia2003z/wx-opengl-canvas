#pragma once

#include <wx/wx.h>
#include <wx/slider.h>

class GLCanvas;

class ControlPanel : public wxPanel
{
public:
    ControlPanel(wxWindow* parent, GLCanvas* canvas);

private:
    GLCanvas* m_glCanvas;
    wxSlider* m_rotationSlider;
    wxCheckBox* m_shapeToggle;

    void OnRotationChanged(wxCommandEvent& event);
    void OnShapeToggled(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
}; 