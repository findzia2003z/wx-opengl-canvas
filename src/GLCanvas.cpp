#include "GLCanvas.h"
#include "MainFrame.h"
#include <wx/image.h>
#include <wx/mstream.h>
#define _USE_MATH_DEFINES
#include <cmath>

wxBEGIN_EVENT_TABLE(GLCanvas, wxGLCanvas)
    EVT_PAINT(GLCanvas::OnPaint)
    EVT_SIZE(GLCanvas::OnSize)
    EVT_LEFT_DOWN(GLCanvas::OnMouseDown)
wxEND_EVENT_TABLE()

GLCanvas::GLCanvas(wxWindow* parent)
    : wxGLCanvas(parent, wxID_ANY, nullptr, wxDefaultPosition, wxDefaultSize,
                wxFULL_REPAINT_ON_RESIZE)
    , m_glContext(nullptr)
    , m_rotation(0.0f)
    , m_showShape(true)
    , m_overlayTexture(0)
{
    m_glContext = new wxGLContext(this);
    m_buttonRect = wxRect(10, 10, 32, 32); // Position and size of overlay button
    
    // Initialize OpenGL and load texture
    SetCurrent(*m_glContext);
    InitGL();
}

GLCanvas::~GLCanvas()
{
    if (m_glContext)
    {
        SetCurrent(*m_glContext);
        if (m_overlayTexture)
            glDeleteTextures(1, &m_overlayTexture);
        delete m_glContext;
    }
}

void GLCanvas::InitGL()
{
    if (!m_glContext)
        return;

    SetCurrent(*m_glContext);

    // Basic OpenGL setup
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Load the overlay button texture
    LoadOverlayTexture();
}

void GLCanvas::LoadOverlayTexture()
{
    // Log current working directory
    wxLogMessage("Current working directory: %s", wxGetCwd());
    // Use absolute path for debugging
    wxString imagePath = "D:/Projects/C++/build/Release/resources/button_icon.png";
    wxLogMessage("Attempting to load image from: %s", imagePath);
    
    wxImage image;
    if (!image.LoadFile(imagePath, wxBITMAP_TYPE_PNG))
    {
        wxLogError("Failed to load image: %s", imagePath);
        // Fallback to a simple white texture if image loading fails
        unsigned char texData[4 * 32 * 32];
        for (int i = 0; i < 32 * 32; ++i)
        {
            texData[i * 4 + 0] = 255; // R
            texData[i * 4 + 1] = 255; // G
            texData[i * 4 + 2] = 255; // B
            texData[i * 4 + 3] = 255; // A
        }

        glGenTextures(1, &m_overlayTexture);
        glBindTexture(GL_TEXTURE_2D, m_overlayTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    }
    else
    {
        wxLogMessage("Successfully loaded image. Size: %dx%d", image.GetWidth(), image.GetHeight());
        // Ensure image has alpha channel
        if (!image.HasAlpha())
        {
            wxLogMessage("Image has no alpha channel, initializing one");
            image.InitAlpha();
        }
        
        // Generate and bind texture
        glGenTextures(1, &m_overlayTexture);
        glBindTexture(GL_TEXTURE_2D, m_overlayTexture);
        
        // Upload image data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.GetWidth(), image.GetHeight(), 
                    0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetData());
    }

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void GLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
    wxPaintDC dc(this);
    SetCurrent(*m_glContext);

    glClear(GL_COLOR_BUFFER_BIT);
    
    // Set up viewport
    int w, h;
    GetSize(&w, &h);
    glViewport(0, 0, w, h);
    
    // Set up orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0 * h/w, 1.0 * h/w, -1.0, 1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (m_showShape)
    {
        RenderScene();
    }

    RenderOverlayButton();
    
    SwapBuffers();
}

void GLCanvas::RenderScene()
{
    glPushMatrix();
    glRotatef(m_rotation, 0.0f, 0.0f, 1.0f);

    // Render a simple triangle
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.5f, -0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.0f, 0.5f);
    glEnd();

    glPopMatrix();
}

void GLCanvas::RenderOverlayButton()
{
    // Switch to screen coordinates for 2D overlay
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    int w, h;
    GetSize(&w, &h);
    glOrtho(0, w, h, 0, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Enable texturing for the button
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_overlayTexture);

    // Draw the textured quad for the button
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(m_buttonRect.GetLeft(), m_buttonRect.GetTop());
    glTexCoord2f(1.0f, 0.0f); glVertex2i(m_buttonRect.GetRight(), m_buttonRect.GetTop());
    glTexCoord2f(1.0f, 1.0f); glVertex2i(m_buttonRect.GetRight(), m_buttonRect.GetBottom());
    glTexCoord2f(0.0f, 1.0f); glVertex2i(m_buttonRect.GetLeft(), m_buttonRect.GetBottom());
    glEnd();

    glDisable(GL_TEXTURE_2D);

    // Restore matrices
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void GLCanvas::OnSize(wxSizeEvent& event)
{
    event.Skip();
}

void GLCanvas::OnMouseDown(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();
    if (IsOverlayButtonClicked(pos))
    {
        MainFrame* frame = static_cast<MainFrame*>(GetParent());
        frame->ToggleControlPanel();
    }
}

bool GLCanvas::IsOverlayButtonClicked(const wxPoint& pos) const
{
    return m_buttonRect.Contains(pos);
} 