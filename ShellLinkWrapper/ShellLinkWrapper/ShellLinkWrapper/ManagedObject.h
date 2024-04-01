#pragma once
#include <vcclr.h>

namespace ShWrapper {

	template<class T> 
	public ref class ManagedObject {

	protected:
		T* m_Instance;
	public:
		ManagedObject(T* instance) : m_Instance(instance) {}

		virtual ~ManagedObject() {
		
			if (m_Instance != nullptr) delete m_Instance;

		}

		!ManagedObject() {
		
			if (m_Instance != nullptr) delete m_Instance;

		}

		T* GetInstance() {
		
			return m_Instance;

		}

	};

}

// To pass a unicode string from managed code to unmanaged.
static const wchar_t* string_to_wchar(System::String^ str) {
	pin_ptr<const wchar_t> w_str = PtrToStringChars(str);
	return w_str;
}

// Returns a managed String^ for managed access/consumption from native/unmanaged code.
static System::String^ wchar_to_string(wchar_t* w_str) {
	System::String^ str = System::Runtime::InteropServices::Marshal::PtrToStringUni((System::IntPtr)w_str);
	return str;
}