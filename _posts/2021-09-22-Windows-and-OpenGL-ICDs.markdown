---
layout: post
title:  "Windows and OpenGL ICDs"
excerpt: "Notes on opengl.32.dll and how ICDs are loaded"
date:   2021-09-21 01:00:00
---

Most of the content here is taken from a 2 year old Reddit comment of mine back when I was deep into the jungle of OpenGL on Win32.

The TL;DR:

``wglProcAddress`` can be used to query the function pointers of OpenGL APIs that are not present in OpenGL 1.1.
For APIs already present in OpenGL 1.1 or older, the ICD loads the function pointers to these APIs once ``wglMakeCurrent`` is invoked.

The long story:

On Windows, Microsoft ships a ``opengl32.dll`` as part of the Windows UM(Usermode) SDKs. This dll contains the OpenGL function signatures for only the APIs present in OpenGL 1.1.
This dll hasn't been updated in decades and any API newer than OpenGL 1.1 is not present in this dll. No AMD/Intel/Nvidia specific code is present in this dll. So how does the ICD OpenGL driver
get used by an OpenGL application on Windows?

Enter Wiggle (WGL). Wiggle is an API that can be thought of as a binding layer between OpenGL and the underlying operating system (More accurately the windowing system which in Windows Vista/7/8/10's case is dwm).
WGL provides APIs for managing the lifecycle of GL contexts on Windows and for loading function addresses.

The WGL API ``wglCreateContext`` and its siblings are the only way to create a valid GL context on Windows. This call is usually followed with a call to ``wglMakeCurrent`` and this is where the magic happens.

The call to ``wglMakeCurrent`` will result in a special API ``DrvSetContext`` being called by the Microsoft DLL. The OpenGL ICD implements this function all the return value of this API is a struct containing all the function pointers to the
IHV's implementation of the OpenGL 1.1 APIs present in ``opengl32.dll``.
For any newer OpenGL APIs, calling ``wglGetProcAddress`` will return the address to the implementation inside the IHV's ICD.

For even more context with a few more interesting comments, here's the [link](https://old.reddit.com/r/opengl/comments/ai9k2u/manually_load_opengl_constants_and_functions/eem45r6/?context=3) to the Reddit thread where this discussion originated.
