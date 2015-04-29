#include "column.h"

using namespace Simplex;

Column::Column() {
	_name = "INVALID";
}

Column::Column(std::string const& name) {
	_name = name;
}

Column::Column(char const* name, size_t len) {
	_name = std::string(name, len);
}

Column::~Column() {
}
