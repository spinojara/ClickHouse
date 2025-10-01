#pragma once

#include <Client/LineReader.h>

namespace DB
{

class ReadlineLineReader : public LineReader
{
public:

    explicit ReadlineLineReader(ReplxxLineReader::Options && options);
    ~ReadlineLineReader() override;

    void enableBracketedPaste() override;
    void disableBracketedPaste() override;

    /// Set text to be prepopulated in the next readLine call
    void setInitialText(const String & text) override;
private:
    InputStatus readOneLine(const String & prompt) override;
    void addToHistory(const String & line) override;
};

}
