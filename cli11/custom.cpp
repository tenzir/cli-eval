#include "custom.hpp"

#include <sstream>

namespace CLI {

std::istringstream& operator>>(std::istringstream& in, custom_t& val) {
    in >> val.i;
    return in;
}

std::ostream& operator>>(std::ostream& out, custom_t& val) {
    out << val.i;
    return out;
}

}
