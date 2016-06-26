//===--- J2.cpp - Implement J2 target feature support ---------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements J2 TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#include "J2.h"
#include "Targets.h"
#include "clang/Basic/MacroBuilder.h"

using namespace clang;
using namespace clang::targets;

void J2TargetInfo::getTargetDefines(const LangOptions &Opts,
                                    MacroBuilder &Builder) const {
  DefineStd(Builder, "J2", Opts);
  Builder.defineMacro("__J2__");
}
