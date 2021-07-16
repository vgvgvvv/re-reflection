
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

using namespace clang;
using namespace tooling;

struct DumpASTAction : public ASTFrontendAction
{
  std::unique_ptr<clang::ASTConsumer>  CreateASTConsumer(CompilerInstance &CI, StringRef InFile) override {
    return CreateASTDumper(nullptr, "", true, true, false, true, ASTDumpOutputFormat::ADOF_JSON);
  } 
};

static llvm::cl::OptionCategory gToolCategory("reflection option");

int main(int argc, const char **argv) {

  CommonOptionsParser optionsParser(argc, argv, gToolCategory);
  ClangTool tool(optionsParser.getCompilations(),
                 optionsParser.getSourcePathList());
  return tool.run(newFrontendActionFactory<DumpASTAction>().get());

}