#ifndef _DEBUG_HPP_
#define _DEBUG_HPP_

#include <assert.h>

#ifdef BUILD_DEBUG
#define UNIMPLEMENTED() assert(false)
#else
#define UNIMPLEMENTED()
#endif

#endif // _DEBUG_H_
