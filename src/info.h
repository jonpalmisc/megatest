//===-- info.h - Build & version info -------------------------------------===//
//
// Copyright (c) 2021 Jon Palmisciano
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//===----------------------------------------------------------------------===//

#pragma once

#define _STR(x) #x
#define STR(x) _STR(x)

/* Build commit */
#ifndef MT_COMMIT
#define MT_COMMIT "0000000"
#endif

/* Compiler name & version */
#ifdef _MSC_VER
#define MT_COMPILER_NAME "msvc"
#define MT_COMPILER_VERSION STR(_MSC_VER)
#elif defined(__clang__)
#define MT_COMPILER_NAME "clang"
#define MT_COMPILER_VERSION STR(__clang_major__)
#elif defined(__GNUC__)
#define MT_COMPILER_NAME "gcc"
#define MT_COMPILER_VERSION STR(__GNUC__)
#else
#define MT_COMPILER_NAME "other"
#define MT_COMPILER_VERSION ""
#endif

/* Target platform */
#ifdef __linux__
#define MT_SYSTEM_NAME "linux"
#elif defined(__APPLE__)
#define MT_SYSTEM_NAME "mac"
#elif defined(_WIN32)
#define MT_SYSTEM_NAME "win"
#else
#define MT_SYSTEM_NAME "other"
#endif

/* Target architecture */
#ifdef __i386__
#define MT_SYSTEM_ARCH "x86"
#elif defined(__x86_64__)
#define MT_SYSTEM_ARCH "x86_64"
#elif defined(__aarch64__)
#define MT_SYSTEM_ARCH "arm64"
#elif defined(__arm__)
#define MT_SYSTEM_ARCH "arm"
#else
#define MT_SYSTEM_ARCH "other"
#endif
