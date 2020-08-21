#include "include.h"
#include "template.h"

template<>
int Compare(CPCHAR src, CPCHAR dest) {
	return strcmp(src, dest);
}
