#include <string>

#include "include/CommandArgs.hh"

namespace Nikola::Init
{
    CompilerOps processCommandArgs(int argc, const char** argv)
    {
        for(int i = 1 ; i < argc; ++i)
        {
            std::string arg = argv[i];
        }
    }
} // namespace Nikola::Init
