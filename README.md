<div align="center">
A High-Performance C++ Multimedia Core with Embedded Python Integration

<p align="center">
<b>Beyond the Wrapper:</b> A ground-up implementation of a custom rendering pipeline and cross-language system architecture.
</p>

View Architecture • Key Features • Technical Stack • Build Guide

</div>

Architecture Philosophy

Most modern desktop applications rely on heavy, high-level abstractions like Electron or Qt. The Bare Media Engine was built to demonstrate how lean and responsive a system can be when you bridge the gap between high-level versatility and low-level control.

This project serves as a proof-of-concept for Scientific Computing environments (like those at CERN), where real-time data visualization must coexist with complex backend processing without sacrificing performance.

1. Zero-Abstraction UI Core

Instead of utilizing a pre-existing GUI toolkit, I implemented a custom event-driven UI framework directly on top of OpenGL.

Custom Vertex Buffers: Manual management of VAOs and VBOs for interface elements.

Shader-Based Logic: UI styling and effects handled via GLSL programs to keep the CPU cycle count minimal.

Non-Blocking Architecture: A thread-safe bridge ensuring that network-heavy Python tasks never interrupt the 60fps rendering loop.

2. High-Performance Language Bridging

The project features a deep integration of the Python C-API. Rather than executing external scripts, Python is embedded directly into the C++ memory space, allowing for:

Direct Memory Sharing: Passing metadata between the C++ rendering objects and the Python backend.

Modular Extensibility: The ability to swap acquisition logic without touching the compiled C++ core.

Class Diagram

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
<li>Asynchronous metadata scraping via <code>pytube</code>.</li>
<li>Automatic environment localization.</li>
</ul>
</td>
</tr>
</table>

System Visualization

<div align="center">
<img src="image_676719.png" width="85%" alt="UI Preview" />

<sub><i>The final UI state: A custom-rendered dashboard managing live media streams.</i></sub>

<img src="Untitled diagram-2025-12-27-181500.jpg" width="85%" alt="Architecture Diagram" />

<sub><i>Technical Flow: Illustrating the separation between GPU-bound rendering and the Python data acquisition thread.</i></sub>
</div>

This project highlights:

Low-Level Competency: Direct GPU programming and raw memory management in C++.

Systems Integration: Seamlessly merging two disparate execution environments (C++ and Python).

Hardware-First Mentality: Choosing efficiency and custom control over heavy third-party dependencies.

Getting Started

Prerequisites

C++ Compiler: GCC 11+ or Clang 13+.

Graphics: OpenGL 4.6 compatible drivers.

Python: 3.10+ Development Headers installed.

Build Instructions

Configure Include Paths:
Ensure your compiler is pointed to the embedded Python headers located in src/VideoDownloader/python.

Link Libraries:
Link against opengl32, glew32, and the python3 dynamic libraries.

Compile:

g++ -I./src/VideoDownloader/python main.cpp -lGL -lpython3.10 -o BareMediaEngine



