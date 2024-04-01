#ifndef SHWRAPPER_H
#define SHWRAPPER_H
#pragma once
#include "ManagedObject.h"
#include "ShCore.h"

namespace ShWrapper {
	public ref class Shortcut : public ManagedObject<WindowsShortcut::Shortcut> {
		
    public:
		Shortcut();
		bool CreateShortcut(
            System::String^ LnkPath,
            System::String^ TargetPath,
            System::String^ Desc,
            System::String^ Arguments,
            System::String^ WorkingDir,
            System::String^ RelativePath
        );
        bool ResolveShortcut(System::String^ LnkPath);
        bool Load(System::String^ LnkPath);
        bool Unload();

        property System::String^ Arguments {
        public:
            System::String^ get() {
                wchar_t* arg = m_Instance->Properties->GetArguments();
                return wchar_to_string(arg);
            }
        //private:
            void set(System::String^ arguments) {
                m_Instance->Properties->SetArguments(string_to_wchar(arguments));
                m_Instance->SetArguments(string_to_wchar(arguments));
            }
        }

        property System::String^ TargetPath {
        public:
            System::String^ get() {
                return wchar_to_string(m_Instance->Properties->GetTargetPath());
            }
        //private:
            void set(System::String^ target_path) {
                m_Instance->Properties->SetTargetPath(string_to_wchar(target_path));
                m_Instance->SetPath(string_to_wchar(target_path));
            }
        }

        property System::String^ Description {
        public:
            System::String^ get() {
                return wchar_to_string(m_Instance->Properties->GetDescription());
            }
        //private:
            void set(System::String^ description) {
                m_Instance->Properties->SetDescription(string_to_wchar(description));
                m_Instance->SetDescription(string_to_wchar(description));
            }
        }

        property System::String^ WorkingDirectory {
        public:
        System::String^ get() {
            return wchar_to_string(m_Instance->Properties->GetWorkingDirectory());
        }
        //private:
        void set(System::String^ working_directory) {
                m_Instance->Properties->SetWorkingDirectory(string_to_wchar(working_directory));
                m_Instance->SetWorkingDirectory(string_to_wchar(working_directory));
            }
        }

        property System::String^ RelativePath {
        public:
        System::String^ get() {
            return wchar_to_string(m_Instance->Properties->GetRelativePath());
        }
        private:
        void set(System::String^ relative_path) {}
        }

        property System::String^ IconLocation {
        public:
        System::String^ get() {
            return wchar_to_string(m_Instance->Properties->GetIconLocation());
        }
        private:
        void set(System::String^ icon_location) {}
        }


	};
}

#endif