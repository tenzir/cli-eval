#pragma once

#include <iosfwd>

struct custom_t {
    int i;
};

namespace CLI {

std::istringstream& operator>>(std::istringstream& in, custom_t& val);

std::ostream& operator>>(std::ostream& out, custom_t& val);

}
