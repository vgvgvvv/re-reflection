#pragma once

#include "util.h"

namespace re_reflect {
  class ReflectedClass {
  public:
    ReflectedClass(CXXRecordDecl const *rec)
      : record(rec)
  {}

   void Generate(ASTContext *ctx, raw_ostream &os);
   void AddField(FieldDecl const *field);
   void AddFunction(FunctionDecl const *function);



  private:
    CXXRecordDecl const *const record;
    std::vector<FieldDecl const *> fields;
    std::vector<FunctionDecl const *> functions;
  };
}
