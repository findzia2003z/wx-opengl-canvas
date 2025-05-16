#include "ControlPanel.h"
#include "GLCanvas.h"

wxBEGIN_EVENT_TABLE(ControlPanel, wxPanel)
    EVT_SLIDER(wxID_ANY, ControlPanel::OnRotationChanged)
    EVT_CHECKBOX(wxID_ANY, ControlPanel::OnShapeToggled)
wxEND_EVENT_TABLE()

ControlPanel::ControlPanel(wxWindow* parent, GLCanvas* canvas)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(200, -1))
    , m_glCanvas(canvas)
{
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Add some padding and a title
    sizer->AddSpacer(10);
    wxStaticText* title = new wxStaticText(this, wxID_ANY, "Controls");
    wxFont titleFont = title->GetFont();
    titleFont.SetPointSize(titleFont.GetPointSize() + 2);
    titleFont.SetWeight(wxFONTWEIGHT_BOLD);
    title->SetFont(titleFont);
    sizer->Add(title, 0, wxALIGN_CENTER | wxALL, 5);
    sizer->AddSpacer(10);

    // Add rotation slider
    wxStaticText* rotationLabel = new wxStaticText(this, wxID_ANY, "Rotation:");
    sizer->Add(rotationLabel, 0, wxALL, 5);

    m_rotationSlider = new wxSlider(this, wxID_ANY, 0, 0, 360,
                                   wxDefaultPosition, wxDefaultSize,
                                   wxSL_HORIZONTAL | wxSL_LABELS);
    sizer->Add(m_rotationSlider, 0, wxEXPAND | wxALL, 5);

    sizer->AddSpacer(10);

    // Add shape toggle
    m_shapeToggle = new wxCheckBox(this, wxID_ANY, "Show Shape");
    m_shapeToggle->SetValue(true);
    sizer->Add(m_shapeToggle, 0, wxALL, 5);

    SetSizer(sizer);
    SetBackgroundColour(wxColour(240, 240, 240));
}

void ControlPanel::OnRotationChanged(wxCommandEvent& event)
{
    m_glCanvas->SetRotation(static_cast<float>(m_rotationSlider->GetValue()));
}

void ControlPanel::OnShapeToggled(wxCommandEvent& event)
{
    m_glCanvas->SetShowShape(m_shapeToggle->GetValue());
} 