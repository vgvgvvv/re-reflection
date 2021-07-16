#pragma once

#include "util.h"
#include "reflected_class.h"

namespace re_reflect {
  class ClassFinderCallback : public MatchFinder::MatchCallback {
  public:
    void run(const MatchFinder::MatchResult &Result) override;
    void onStartOfTranslationUnit() override;
    void onEndOfTranslationUnit() override;

  protected:
    void FoundRecord(CXXRecordDecl const *record);
    void FoundField(FieldDecl const *field);
    void FoundFunction(FunctionDecl const *function);

  protected:
    ASTContext *context;
    SourceManager *sourceManager;
    std::vector<ReflectedClass> classes;
    std::string fileName;
  };

}
