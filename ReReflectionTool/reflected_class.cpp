#include "reflected_class.h"

namespace re_reflect {
void ReflectedClass::Generate(ASTContext *ctx, raw_ostream &os) {
  
}

void ReflectedClass::AddField(FieldDecl const *field) {
  fields.push_back(field);
}

void ReflectedClass::AddFunction(FunctionDecl const *function) {
  functions.push_back(function);
}

}
