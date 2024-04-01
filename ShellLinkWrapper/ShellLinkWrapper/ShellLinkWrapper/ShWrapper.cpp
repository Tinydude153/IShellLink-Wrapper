#include "ShWrapper.h"

namespace ShWrapper {
	
	// Constructor.
	Shortcut::Shortcut() : ManagedObject(new WindowsShortcut::Shortcut()) {}

	bool Shortcut::CreateShortcut(
		System::String^ LnkPath,
		System::String^ TargetPath,
		System::String^ Desc,
		System::String^ Arguments,
		System::String^ WorkingDir,
		System::String^ RelativePath
	) {
	
		return m_Instance->CreateShortcut(
			string_to_wchar(LnkPath),
			string_to_wchar(TargetPath),
			string_to_wchar(Desc),
			string_to_wchar(Arguments),
			string_to_wchar(WorkingDir),
			string_to_wchar(RelativePath)
		);
		
	}

	bool Shortcut::ResolveShortcut(System::String^ LnkPath) {
	
		return m_Instance->ResolveShortcut(string_to_wchar(LnkPath));

	}

	bool Shortcut::Load(System::String^ LnkPath) {
	
		return m_Instance->LoadShortcut(string_to_wchar(LnkPath));
	
	}

	bool Shortcut::Unload() {
	
		return m_Instance->ReleaseShortcut();

	}

}

