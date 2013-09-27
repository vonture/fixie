#ifndef _DEBUG_HPP_
#define _DEBUG_HPP_

#include <assert.h>

#ifdef BUILD_DEBUG
#define UNIMPLEMENTED() assert(false)
#define UNREACHABLE() assert(false)
#else
#define UNIMPLEMENTED()
#define UNREACHABLE()
#endif

#endif // _DEBUG_H_
