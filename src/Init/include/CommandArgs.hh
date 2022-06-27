#ifndef COMMAND_ARGS_HH
#define COMMAND_ARGS_HH

#include <string>
#include <vector>

namespace Nikola::Init
{
    struct CompilerOps
    {
        bool displayHelp;
        bool displayVersion;
        bool outputTokens;
        bool outputParseTree;
        bool outputEquivalentCode;
        bool outputIR;
        bool outputAssembly;
        bool outputExecutable;
        bool outputDebugSymbols;
        std::string outputFile;
        std::vector<std::string> inputFiles;
    };

    CompilerOps processCommandArgs(int argc, const char** argv);
} // namespace Nikola::Init


#endif