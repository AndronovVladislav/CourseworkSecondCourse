#include "Utils.h"

std::string Utils::join(const std::vector<std::string> &sequence, const std::string separator) {
    std::string result;
    for (int i = 0; i < sequence.size(); ++i) {
        result += sequence[i] + ((i != sequence.size() - 1 && !sequence[i].empty()) ? separator : "");
    }
    return result + "\n";
}

static std::vector<std::string> Utils::split(std::string s, std::string delimiter);