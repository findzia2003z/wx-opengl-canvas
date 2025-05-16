#pragma once

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <GL/gl.h>

class GLCanvas : public wxGLCanvas
{
public:
    GLCanvas(wxWindow* parent);
    ~GLCanvas();

    void SetRotation(float rotation) { m_rotation = rotation; Refresh(); }
    void SetShowShape(bool show) { m_showShape = show; Refresh(); }
    bool IsOverlayButtonClicked(const wxPoint& pos) const;

private:
    wxGLContext* m_glContext;
    float m_rotation;
    bool m_showShape;
    unsigned int m_overlayTexture;
    wxRect m_buttonRect;

    void OnPaint(wxPaintEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnMouseDown(wxMouseEvent& event);
    
    void InitGL();
    void RenderScene();
    void RenderOverlayButton();
    void LoadOverlayTexture();

    wxDECLARE_EVENT_TABLE();
}; 