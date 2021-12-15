// Copyright (c) 2019, The Vulkan Developers.
//
// This file is part of Vulkan.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// You should have received a copy of the MIT License
// along with Vulkan. If not, see <https://opensource.org/licenses/MIT>.

// ignores all imports of vulkan.h after being imported once
#pragma once

// imports functions from the C standard library
// assert.h imports #define
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

// allows the sue of C code to be used in C++
#ifdef __cplusplus
// creates two macros: one that tells the compiler code be written in C and another that tells the compiler there will no longer be code written in C
#define VULKAN_BEGIN_DECL extern "C" {
#define VULKAN_END_DECL	}
#else
#define VULKAN_BEGIN_DECL /* empty */
#define VULKAN_END_DECL	/* empty */
#endif

// creates a macro that exports symbols to DLL and shows compilation when using a GNU/Linux operating system
#ifndef VULKAN_API
#if defined(_WIN32)
#ifdef VULKAN_BUILD
#define VULKAN_API __declspec(dllexport)
#else
#define VULKAN_API
#endif
#elif defined(__GNUC__) && defined(VULKAN_BUILD)
#define VULKAN_API __attribute__((visibility("default")))
#else
#define VULKAN_API
#endif
#endif

// defines maximum values
#ifndef MAX
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif

// defines minimum values
#ifndef MIN
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

// creates a macro that terminates the process if the condition and message are both untrue
#define ASSERT_WITH_MESS(condition, message) { assert(condition && message); }
