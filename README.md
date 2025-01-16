# SM-KeyAPI

This mod extends the [SM](https://scrapmechanic.com/) Lua API to allow you to query any key on the keyboard as long as the window is focussed!

## Installation

> [!TIP]
> The recommended method of installing this is [Carbon Launcher](https://github.com/ScrappySM/CarbonLauncher) which is maintained by me and will let you simply press download and launch the game!

However, there are many other ways. Here's a launcher agnostic way of installing this mod:
- Go to releases and download the latest `.dll` file.
- Open a tool like Process Hacker/System Informer and find the process of Scrap Mechanic.
- Inject the `.dll` file as a module into the process.

You can also use a tool like [SM-DLL-Injector](https://github.com/QuestionableM/SM-DLL-Injector) maintained by [QuestionableM](https://github.com/QuestionableM) and will let you simply inject any DLL files in a folder called `DllModules`, you could use this project and put the `.dll` file in the folder and it will automatically inject it for you.

## Explanation/Updating guide

> [!WARNING]
> This section is for developers and modders who want to understand how the mod works and how to update it.

An explanation of how the mod works and how to update is available in [dllmain](SM-KeyAPI/src/dllmain.cpp).
