#include "Helper.h"

#include <vector>

std::string convertToNonAccentVN(std::string str) {
    std::vector<std::pair<std::string, std::vector<std::string>>> mapping;

    mapping.emplace_back(
        "A", std::vector<std::string>({"A", "Á", "À", "Ã", "Ạ", "Â", "Ấ", "Ầ",
                                       "Ẫ", "Ậ", "Ă", "Ắ", "Ằ", "Ẵ", "Ặ"}));
    mapping.emplace_back("a", std::vector<std::string>(
                                  {"à", "á", "ạ", "ả", "ã", "â", "ầ", "ấ", "ậ",
                                   "ẩ", "ẫ", "ă", "ằ", "ắ", "ặ", "ẳ", "ẵ"}));
    mapping.emplace_back(
        "E", std::vector<std::string>(
                 {"E", "É", "È", "Ẽ", "Ẹ", "Ê", "Ế", "Ề", "Ễ", "Ệ"}));
    mapping.emplace_back(
        "e", std::vector<std::string>(
                 {"è", "é", "ẹ", "ẻ", "ẽ", "ê", "ề", "ế", "ệ", "ể", "ễ"}));
    mapping.emplace_back("I",
                         std::vector<std::string>({"I", "Í", "Ì", "Ĩ", "Ị"}));
    mapping.emplace_back("i",
                         std::vector<std::string>({"ì", "í", "ị", "ỉ", "ĩ"}));
    mapping.emplace_back(
        "O", std::vector<std::string>({"O", "Ó", "Ò", "Õ", "Ọ", "Ô", "Ố", "Ồ",
                                       "Ỗ", "Ộ", "Ơ", "Ớ", "Ờ", "Ỡ", "Ợ"}));
    mapping.emplace_back("o", std::vector<std::string>(
                                  {"ò", "ó", "ọ", "ỏ", "õ", "ô", "ồ", "ố", "ộ",
                                   "ổ", "ỗ", "ơ", "ờ", "ớ", "ợ", "ở", "ỡ"}));
    mapping.emplace_back(
        "U", std::vector<std::string>(
                 {"U", "Ú", "Ù", "Ũ", "Ụ", "Ư", "Ứ", "Ừ", "Ữ", "Ự"}));
    mapping.emplace_back(
        "u", std::vector<std::string>(
                 {"ù", "ú", "ụ", "ủ", "ũ", "ư", "ừ", "ứ", "ự", "ử", "ữ"}));
    mapping.emplace_back("Y",
                         std::vector<std::string>({"Y", "Ý", "Ỳ", "Ỹ", "Ỵ"}));
    mapping.emplace_back("y",
                         std::vector<std::string>({"ỳ", "ý", "ỵ", "ỷ", "ỹ"}));
    mapping.emplace_back("D", std::vector<std::string>({"Đ"}));
    mapping.emplace_back("d", std::vector<std::string>({"đ"}));
    // Some system encode vietnamese combining accent as individual utf-8
    // characters
    mapping.emplace_back(
        "", std::vector<std::string>({"\u0300", "\u0301", "\u0303", "\u0309",
                                      "\u0323"})); // Huyền, sắc, hỏi, ngã, nặng
    mapping.emplace_back("",
                         std::vector<std::string>(
                             {"\u02C6", "\u0306", "\u031B"})); // Â, Ê, Ă, Ơ, Ư

    for (auto &charConverter : mapping) {
        const std::string &replaceStr = charConverter.first;
        for (auto &toSearch : charConverter.second) {
            size_t pos = str.find(toSearch);
            while (pos != std::string::npos) {
                str.replace(pos, toSearch.size(), replaceStr);
                pos = str.find(toSearch, pos + replaceStr.size());
            }
        }
    }

    return str;
}
std::string normalize(std::string str)
{
    for( int i=0;i<str.length();i++)
    {
        if(str[i]<='Z'&&str[i]>='A')
        {
            str[i]+=32;
        }
        
    }
    return str;
}