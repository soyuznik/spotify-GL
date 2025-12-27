

## Spotify-GL
![Example](https://github.com/Vasika-uso/spotify-GL/blob/main/.github/screenshots/exampleIMAGE4.png)

Most modern desktop applications rely on heavy, high-level abstractions like Electron or Qt. This one relies on just the OpenGL graphics library.

1. Zero-Abstraction UI Core

Instead of utilizing a pre-existing GUI toolkit, I implemented a custom event-driven UI framework directly on top of OpenGL, using my own custom math.
Custom Vertex Buffers: Manual management of VAOs and VBOs for interface elements.         
Shader-Based Logic: UI styling and effects handled via GLSL programs to keep the CPU cycle count minimal.          
Non-Blocking Architecture: A thread-safe bridge ensuring that network-heavy Python tasks never interrupt the 60fps rendering loop.          
     

2. High-Performance Language Bridging

The project features a deep integration of the Python C-API. Rather than executing external scripts, Python is embedded directly into the C++ memory space.


## Class Diagram

<img src="Resources/class_diag.png" width="85%" alt="Class Diagram" />

Core Capabilities

<table width="100%">
<tr>
<td width="50%">
<h4>Custom Rendering Pipeline</h4>
<ul>
<li>Manual Shader Linkage & Management.</li>
<li>Sub-millisecond UI response times.</li>
<li>Dynamic texture loading and buffer updates.</li>
</ul>
</td>
<td width="50%">
<h4>Integrated Python Logic</h4>
<ul>
<li>Embedded <code>Python.h</code> C-API usage.</li>
<li>Automatic environment localization.</li>
</ul>
</td>
</tr>
</table>


## Getting Started

Prerequisites

C++ Compiler: GCC 11+ or Clang 13+.

Graphics: OpenGL 4.6 compatible drivers.

## Build Instructions

Configure Include Paths:
Ensure your compiler is pointed to the embedded Python headers located in src/VideoDownloader/python.

Link Libraries:
Link against opengl32, glew32, and the python3 dynamic libraries.

## Compile:

`g++ -I./src/VideoDownloader/python MAIN.cpp -lGL -lpython3.10 -o spotify-GL`
or compile using Visual Studio 2022




