# Interactive GL Canvas with Controls

This is a desktop application built with wxWidgets and OpenGL that demonstrates the integration of GUI components with an OpenGL rendering pipeline.

## Features

- OpenGL rendering of a 2D scene with basic geometric shapes
- Interactive overlay button within the OpenGL context
- Side panel with wxWidgets controls:
  - Rotation slider to adjust the shape's rotation
  - Checkbox to toggle shape visibility
- Proper event handling and resource management
- Responsive UI with proper window resizing support

## Prerequisites

- CMake 3.10 or higher
- C++17 compatible compiler
- wxWidgets development libraries
- OpenGL development libraries

### Windows

1. Install Visual Studio with C++ development tools
2. Install wxWidgets:
   - Download wxWidgets source from https://www.wxwidgets.org/downloads/
   - Download the Windows ZIP file of the latest stable release (e.g., wxMSW-3.2.4_vc14x_x64_Dev.7z)
   - Extract it to a directory (e.g., `C:\wxWidgets`)
   - Set the WXWIN environment variable:
     - Open Windows Settings
     - Search for "Environment Variables"
     - Click "Edit the system environment variables"
     - Click "Environment Variables" button
     - Under "System variables", click "New"
     - Variable name: `WXWIN`
     - Variable value: `C:\wxWidgets` (or your actual wxWidgets directory)
     - Click "OK" on all dialogs
   - Build wxWidgets:
     - Open "x64 Native Tools Command Prompt for VS" from Start menu
     - Navigate to your wxWidgets build directory:
       ```cmd
       cd %WXWIN%\build\msw
       ```
     - Build wxWidgets:
       ```cmd
       nmake -f makefile.vc BUILD=release SHARED=0 TARGET_CPU=X64
       ```
     - Wait for the build to complete (this may take several minutes)

### Linux

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential cmake libwxgtk3.0-gtk3-dev libgl1-mesa-dev

# Fedora
sudo dnf install @development-tools cmake wxGTK3-devel mesa-libGL-devel
```

## Build Instructions

1. Clone this repository and enter the directory:
   ```sh
   git clone https://github.com/yourusername/wx-opengl-canvas.git
   cd wx-opengl-canvas
   ```
2. Create a build directory and run CMake:
   ```sh
   mkdir build
   cd build
   cmake ..
   ```
3. Build the project:
   - On Windows (Visual Studio):
     - Open the generated solution in Visual Studio and build in Release mode
   - On Linux:
     ```sh
     make
     ```
4. Run the application:
   - On Windows: `build/Release/GLCanvasApp.exe`
   - On Linux: `./GLCanvasApp`

## Notes

- The overlay button icon is located in the `resources/` folder as a PNG file.
- If you encounter issues with wxWidgets or OpenGL, ensure the development libraries are installed and environment variables are set correctly.

## License

MIT License 