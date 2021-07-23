

#include "util.h"
#include "class_finder.h"

static OptionCategory ToolCategory("re-reflection tool");


int main(int argc, const char** argv)
{
  CommonOptionsParser optionsParser(argc, argv, ToolCategory);
  ClangTool tool(optionsParser.getCompilations(),
                                 optionsParser.getSourcePathList());

  auto &db = optionsParser.getCompilations();
  for (auto &cmd : db.getAllCompileCommands()) {
    printf("CommandLine:");
    for (auto &opt : cmd.CommandLine)
      printf(" %s", opt.c_str());
    printf("\n");
    printf("File: %s\n", cmd.Filename.c_str());
    printf("Directory: %s\n", cmd.Directory.c_str());
    printf("Output: %s\n", cmd.Output.c_str());
  }

  re_reflect::ClassFinderCallback classFinderCallback;
  MatchFinder matchFinder;

  static DeclarationMatcher const classMatcher =
      cxxRecordDecl(decl().bind("id"), hasAttr(attr::Annotate));
  matchFinder.addMatcher(classMatcher, &classFinderCallback);

  static DeclarationMatcher const fieldMatcher =
      fieldDecl(decl().bind("id"), hasAttr(attr::Annotate));
  matchFinder.addMatcher(fieldMatcher, &classFinderCallback);

  static DeclarationMatcher const functionMatcher =
      functionDecl(decl().bind("id"), hasAttr(attr::Annotate));
  matchFinder.addMatcher(functionMatcher, &classFinderCallback);

  return tool.run(newFrontendActionFactory(&matchFinder).get());
}
