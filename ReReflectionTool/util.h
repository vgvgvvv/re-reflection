#pragma once

#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/AST/RecursiveASTVisitor.h"

#include "llvm/Support/CommandLine.h"

using namespace llvm;
using namespace llvm::cl;
using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;


/* ========================================================================= */
/* STL Utils                                                                 */
/* ========================================================================= */
inline bool ends_with(std::string const &value, std::string const &ending) {
  if (ending.size() > value.size())
    return false;

  return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

/* ========================================================================= */
/* LLVM Utils                                                                */
/* ========================================================================= */
QualType GetDesugaredType(ASTContext *ctx, QualType t);

inline void GetRealTypeName(ASTContext *ctx, QualType t, raw_ostream &os) {
  QualType retType = GetDesugaredType(ctx, t);
  retType.print(os, ctx->getPrintingPolicy());
}

SmallString<32> GenerateQualifier(ASTContext *ctx, QualType type);

SmallString<8> PrintfFormatForType(ASTContext *ctx, QualType t);