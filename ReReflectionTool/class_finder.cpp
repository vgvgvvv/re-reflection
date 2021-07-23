#include "class_finder.h"

namespace re_reflect {

void ClassFinderCallback::run(const MatchFinder::MatchResult &Result) {
  context = Result.Context;
  sourceManager = Result.SourceManager;

  const auto record = Result.Nodes.getNodeAs<CXXRecordDecl>("id");
  if (record) {
    return FoundRecord(record);
  }

  const auto field = Result.Nodes.getNodeAs<FieldDecl>("id");
  if (record) {
    return FoundField(field);
  }

  const auto function = Result.Nodes.getNodeAs<FunctionDecl>("id");
  if (function) {
    return FoundFunction(function);
  }

}

void ClassFinderCallback::onStartOfTranslationUnit() {
  
}

void ClassFinderCallback::onEndOfTranslationUnit() {

  std::error_code ec;
  llvm::raw_fd_ostream os(fileName, ec);
  assert(!ec && "error opening file");

  for (auto &ref : classes) {
    ref.Generate(context, os);
  }
}

void ClassFinderCallback::FoundRecord(CXXRecordDecl const *record) {
  fileName = std::string(sourceManager->getFilename(record->getLocation()));
  fileName.erase(std::find(fileName.begin(), fileName.end(), '.'),
                 fileName.end());
  fileName.append(".reflected.h");
  classes.emplace_back(ReflectedClass(record));
}

void ClassFinderCallback::FoundField(FieldDecl const *field) {
  classes.back().AddField(field);
}

void ClassFinderCallback::FoundFunction(FunctionDecl const *function) {
  classes.back().AddFunction(function);
}
 
}
