#ifndef COURSEWORKSECONDCOURSE_UTILS_H
#define COURSEWORKSECONDCOURSE_UTILS_H

#include "../common.h"

namespace Utils {
    std::string join(const std::vector<std::string> &sequence, const std::string separator);

    std::vector<std::string> split(std::string s, std::string delimiter);
}

#endif //COURSEWORKSECONDCOURSE_UTILS_H
