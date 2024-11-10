#pragma once
#include "TextGo.h"
class UiScore :
    public TextGo
{
protected:
    std::string strFormat = "SCORE : ";
    int dScore = 0;

    UiScore(const UiScore&) = delete;
    UiScore& operator=(const UiScore&) = delete;
public:
    UiScore(const std::string& iFontId, const std::string& iName = "");
    virtual ~UiScore() = default;

    void reset() override;
    void setScore(int iScore);

};

