# vtkDearImGUIInjector
[![Deploy WebAssembly binary](https://github.com/jspanchu/vtkDearImGUIInjector/actions/workflows/build-wasm.yml/badge.svg)](https://github.com/jspanchu/vtkDearImGUIInjector/actions/workflows/build-wasm.yml)

Inject DearImGUI into an existing VTK application.

A very closely related project is phcerdan's https://github.com/phcerdan/vtkImGuiAdapter.
The two are slightly different in that:
1. With vtkDearImGUIInjector, 
    
    a. you do not have to take care of ImGUI contexts yourself.
    
    b. no need to write an event loop.
2. With vtkImGUIAdapter,
    
    a. you are responsible for ensuring the sdl2 window is setup and the ImGUI context is initialized.
    
    b. you must write an event loop in your application, ensure events are processed and ensure NewFrame/EndFrame are called.

# what's modified?
The VTK framework is essentially different from other graphic applications like games that they typically do not require real-time rendering all the time. Rendering only happens when necessary, e.g. interaction events happened including mouse movement! This behavior is desirable since such applications generally display static graphics and there is literally no GPU load when no interaction/animation happens. 

With little modification, the lazy render feature of VTK is maintained **without** sacrificing responsive ImGui elements! This is done by adding few additional render calls trigger by timer to complete ImGui elements' changes.