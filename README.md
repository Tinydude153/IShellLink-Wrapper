# IShellLink Wrapper
IShellLink Wrapper is a .NET framework wrapper for the Win32 IShellLink interface. The primary purpose for writing this wrapper was (1) to learn about native C++ and .NET interoperability utilizing C++/CLI and CLR (Common Language Runtime) and (2) for a smoother experience manipulating Windows' shell links in PowerShell scripts and modules (e.g., shortcuts, .lnk files). 

## Motivation
While writing PowerShell scripts at work for easing the process of deploying a desktop shortcut to a network location for a pharmacy application (PioneerRx) and location-specific configurations for multiple computers, I ran into an issue when programmatically creating Windows shortcuts using Windows Script Host in PowerShell. The WSH-created shortcut did not work properly and, often times, attempting to interface with the shortcut created by WSH would cause Windows to slow down to an almost unusable degree. This was my main motivation for developing my own wrapper library for the IShellLink interface; as a second motivation, I am also fairly interested in native C++ and .NET interop.

## Setup
### Dependencies
If you are loading this DLL into PowerShell, a PowerShell version with at least CLR version 4 (4.0.30319.42000) is requried, as the IShellLink Wrapper DLL was compiled targeting .NET Framework 4.7.2 (supported by CLR version 4). By default, all Windows 10 versions have, at minimum, this CLR version installed. This version of the .NET Framework can be installed on Windows versions down to Windows 7. See these MSDN articles for more information: [Determine .NET Framework Version](https://learn.microsoft.com/en-us/dotnet/framework/migration-guide/how-to-determine-which-versions-are-installed), [.NET Framework Versions and Dependencies](https://learn.microsoft.com/en-us/dotnet/framework/migration-guide/versions-and-dependencies).

I am not an expert on C# by any means, but I assume that the above roughly applies to C# development, as well.
### Loading the DLL in PowerShell
Loading the DLL in PowerShell is quite simple. Here is a small usage example:
```powershell
[System.Reflection.Assembly]::LoadFile("C:/path/to/dll/ShellLinkWrapper.dll")
$shelllink = [ShWrapper.Shortcut]::new()
$shelllink.CreateShortcut("C:\Users\%USERNAME%\Desktop\example.lnk", "C:\Program Files\BraveSoftware\Brave-Browser\Application\brave.exe", "description...", [NullString]::Value, "C:\Program Files\BraveSoftware\Brave-Browser\Application", "C:\Program Files\BraveSoftware\Brave-Browser\Application")
```
## Usage 
This sections will be filled soon.
