# 3D Viewer

Qt/C++ application for visualizing wireframe models.

## 1. Description

A desktop application for visualizing 3D wireframe models using Qt and OpenGL.  
The viewer supports customizable rendering options such as vertex appearance, line style, and projection mode.

The project focuses on clean architecture, separation of concerns, and maintainable C++ code.

---

## 2. About

**Main features:**
- Wireframe rendering of 3D models
- Configurable vertex color and line color
- Vertex shape: sphere / square / disabled
- Line style: solid / dashed
- Projection: orthographic / perspective
- Real-time settings updates

**Tech stack:**
- C++
- Qt 
- OpenGL (QOpenGLWidget)
- CMake
- Makefile

**Goals:**
- Practice modern C++ and graphics programming
- Explore clean architecture and modular design
- Keep the codebase readable and extensible
- Learn design patterns and when to use them

**Patterns used:**
- Facade - in model
- Strategy - in model and view
- Factory - in view

---

## 3. Installation

### Requirements
- C++ compiler with C++20 support
- Qt >= 6
- CMake >= 3.16

### Build

```bash
git clone <repo-url>
cd <project-folder>
make
```

### Run

```bash
./build/3d_viewer
```

## 4. Controls / Usage

- Press `Open File` button and choose any `.obj` file to open the model, or use one from `./objects` folder
- After loading the model, you can manipulate the camera using sliders on the right side of the window
- All view settings for colors, thickness and projection type are located at the bottom of the window


## 5. Additional Targets

### Tests
**Requires:** GoogleTest
```bash
make tests
./s21_test
```

### Test coverage report
**Requires:** gcovr 8.4
```bash
make gcov_report
open report/index.html
```

### Documentation
**Notes:** documentation only covers model, controller and common files
**Requires:** doxygen 1.15.0
```bash
make dvi
open docs/html/index.html 
```
