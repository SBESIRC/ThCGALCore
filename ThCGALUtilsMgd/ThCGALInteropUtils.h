#pragma once
#include <string>
#include <vector>
#include "ManagedObject.h"
using namespace System;

// https://docs.microsoft.com/en-us/cpp/dotnet/how-to-convert-system-string-to-standard-string?view=msvc-160
String^ MarshalNativeString(std::string& os);
void MarshalString(String^ s, std::string& os);
void MarshalString(String^ s, std::wstring& os);

// https://www.chriswirz.com/software/managed-to-un-managed-byte-arrays-in-c-sharp
// https://docs.microsoft.com/en-us/cpp/dotnet/how-to-marshal-arrays-using-cpp-interop?view=msvc-160
cli::array<Byte>^ MarshalNativeBindaryBuffer(std::vector<unsigned char>& vector);
void MarshalBindaryBuffer(cli::array<Byte>^ buffer, std::vector<unsigned char>& vector);