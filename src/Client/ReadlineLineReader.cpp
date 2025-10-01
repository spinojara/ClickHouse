#include <Client/ClientBaseHelpers.h>
#include <Client/ReadlineLineReader.h>
#include <base/errnoToString.h>

#include <Common/memory.h>

#include <readline/readline.h>

namespace
{

void rightTrim(String & s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}

}

namespace DB
{

ReadlineLineReader::ReadlineLineReader(ReplxxLineReader::Options && options)
    : LineReader
    (
        options.history_file_path,
        options.multiline,
        std::move(options.extenders),
        std::move(options.delimiters),
        options.input_stream,
        options.output_stream,
        options.in_fd
    )
{
}

ReadlineLineReader::~ReadlineLineReader()
{
#if 0
    if (history_file_fd >= 0 && close(history_file_fd))
        rx.print("Close of history file failed: %s\n", errnoToString().c_str());

    /// Reset cursor blinking
    if (overwrite_mode)
        rx.print("%s", "\033[0 q");
#endif
}

LineReader::InputStatus ReadlineLineReader::readOneLine(const String &prompt)
{
    input.clear();

    const char *cinput = readline(prompt.c_str());
    if (cinput == nullptr)
        return ABORT;
    input = cinput;
    free((void *)cinput);

    rightTrim(input);
    return INPUT_LINE;
}

void ReadlineLineReader::enableBracketedPaste()
{
}
void ReadlineLineReader::disableBracketedPaste()
{
}

void ReadlineLineReader::setInitialText(const String & text)
{
}

void ReadlineLineReader::addToHistory(const String &line)
{
}

}
