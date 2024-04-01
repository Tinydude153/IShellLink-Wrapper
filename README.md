# IShellLink Wrapper
IShellLink Wrapper is a .NET framework wrapper for the Win32 IShellLink interface. The primary purpose for writing this wrapper was (1) to learn about native C++ and .NET interoperability utilizing C++/CLI and CLR (Common Language Runtime) and (2) for a smoother experience manipulating Windows' shell links in PowerShell scripts and modules (e.g., shortcuts, .lnk files). 

## Motivation
While writing PowerShell scripts at work for easing the process of deploying a desktop shortcut to a network location for a pharmacy application (PioneerRx) and location-specific configurations for multiple computers, I ran into an issue when programmatically creating Windows shortcuts using Windows Script Host in PowerShell. The WSH-created shortcut did not work properly and, often times, attempting to interface with the shortcut created by WSH would cause Windows to slow down to an almost unusable degree. This was my main motivation for developing my own wrapper library for the IShellLink interface; as a second motivation, I am also fairly interested in native C++ and .NET interop.

## Setup
### Dependencies
If you are loading this DLL into PowerShell, a PowerShell version with at least CLR version 4 (4.0.30319.42000) is required, as the IShellLink Wrapper DLL was compiled targeting .NET Framework 4.7.2 (supported by CLR version 4). By default, all Windows 10 versions have, at minimum, this CLR version installed. This version of the .NET Framework can be installed on Windows versions down to Windows 7. See these MSDN articles for more information: [Determine .NET Framework Version](https://learn.microsoft.com/en-us/dotnet/framework/migration-guide/how-to-determine-which-versions-are-installed), [.NET Framework Versions and Dependencies](https://learn.microsoft.com/en-us/dotnet/framework/migration-guide/versions-and-dependencies).
I am not an expert on C# by any means, but I assume that the above roughly applies to C# development, as well.
## Usage 
### Design
The design of this interface was intended to take on an object-oriented approach: a `Shortcut` object represents a shell links properties. In native C++, this is a member struct defined as such:
```cpp
struct ShortcutProperties {
    ~ShortcutProperties();
    wchar_t* TargetPath = {};
    wchar_t* Description = {};
    wchar_t* Arguments = {};
    wchar_t* WorkingDirectory = {};
    wchar_t* RelativePath = {};
    wchar_t* IconLocation = {};
    int* IconIndex = {};
    
    void SetTargetPath(const wchar_t* target_path);
    wchar_t* GetTargetPath();
    void SetDescription(const wchar_t* description);
    wchar_t* GetDescription();
    void SetArguments(const wchar_t* arguments);
    wchar_t* GetArguments();
    void SetWorkingDirectory(const wchar_t* working_directory);
    wchar_t* GetWorkingDirectory();
    void SetRelativePath(const wchar_t* relative_path);
    wchar_t* GetRelativePath();
    void SetIconLocation(const wchar_t* icon_location);
    wchar_t* GetIconLocation();
    int* GetIconIndex();
};
```
In managed C++, this struct is represented by .NET properties with getter and setter functions.
### Creating a shortcut
Creating a shortcut is straightforward and ***does not*** associate the `Shortcut` object with the created shortcut:
```cpp
bool CreateShortcut(
    System::String^ LnkPath,     // Literal .lnk path.
    System::String^ TargetPath,  // Target .exe path.
    System::String^ Desc,        // Shortcut description. 
    System::String^ Arguments,   // Arguments to be applied when the shortcut is used to run the target.
    System::String^ WorkingDir,  // Working directory of the target; usually the same directory as the target.
    System::String^ RelativePath // Useless.
);
```
The created shortcut will be created at the location specified in the first argument, `System::String^ LnkPath`.
Returns true if a shortcut is successfully created, else it returns false.
*Note: the working directory seems to be automatically filled with the directory of the TargetPath.*

### Associating a shortcut with a Shortcut object
To associate a `Shortcut` object with a shortcut, the `Load(String)` function is used:
```cpp
bool Load(System::String^ LnkPath);
```
All of a `Shortcut` object's properties will be set to the corresponding target .lnk file's properties when this function is used, and the properties can be interactively set.
Returns true if the shortcut was loaded successfully, else it returns false.
### Changing a property's value
Changing a property's value is not complicated and needs little explanation:
```cpp
shortcut.TargetPath = "C:/path";
```
Properties of the `Shortcut` object are tied to the actual shortcut and are applied accordingly as they are changed.
### Deleting an object's shortcut association
To disassociate a shortcut from a `Shortcut` object, the `Unload()` function is used:
```cpp
bool Unload();
```
The `Unload()` function calls the `ReleaseShortcut()` function from the native, unmanaged C++ code; if a shortcut has been loaded, `ReleaseShortcut()` saves the shortcut currently associated with the object, releases the IPersistFile and IShellLink pointers, and deletes then re-allocates `ShortcutProperties` to clear the properties and initialize the struct for its next usage. 
Returns true if a shortcut was loaded, else it returns false.
### Resolving a shortcut's target
To resolve a shortcut's target, the `ResolveShortcut(String)` is used:
```cpp
bool ResolveShortcut(System::String^ LnkPath);
```
This function attempts to find the target of a shell link.
Returns true if the target was found, else it returns false.
## PowerShell Example
Loading the DLL in PowerShell is quite simple. Here is a small usage example:
```powershell
# Load DLL into PowerShell session.
[System.Reflection.Assembly]::LoadFile("C:/path/to/dll/ShellLinkWrapper.dll")

# Construct a new Shortcut object.
$shelllink = [ShWrapper.Shortcut]::new()

# Create a shortcut at the path contained in $path.
[string]$path = "C:\Users\%USERNAME%\Desktop\example.lnk"
$shelllink.CreateShortcut($path, "C:\Program Files\BraveSoftware\Brave-Browser\Application\brave.exe", "description...", [NullString]::Value, "C:\Program Files\BraveSoftware\Brave-Browser\Application", "C:\Program Files\BraveSoftware\Brave-Browser\Application")

# Load the created shortcut and change properties.
$shelllink.Load($path)
$shelllink.TargetPath = "C:\Windows\System32\Magnify.exe"
$shelllink.WorkingDirectory = "C:\Windows\System32"
$shelllink.Unload()
```
