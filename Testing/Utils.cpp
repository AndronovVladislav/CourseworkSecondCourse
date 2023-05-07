#include "Utils.h"

std::string Utils::join(const std::vector<std::string> &sequence, const std::string separator) {
    std::string result;
    for (int i = 0; i < sequence.size(); ++i) {
        result += sequence[i] + ((i != sequence.size() - 1 && !sequence[i].empty()) ? separator : "");
    }
    return result + "\n";
}

std::vector<std::string> Utils::split(std::string s, std::string delimiter) {
    size_t posStart = 0, posEnd, delimLen = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((posEnd = s.find(delimiter, posStart)) != std::string::npos) {
        token = s.substr(posStart, posEnd - posStart);
        posStart = posEnd + delimLen;
        res.push_back(token);
    }

    res.push_back(s.substr(posStart));
    return res;
}