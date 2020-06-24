//
// Copyright © 2020 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include <ghc/filesystem.hpp>
namespace fs = ghc::filesystem;

namespace armnnUtils
{
namespace Filesystem
{

long long GetFileSize(const char* path);

bool Remove(const char* path);

}
}
