#ifndef _DEBUG_HPP_
#define _DEBUG_HPP_

#ifdef BUILD_DEBUG
#define UNIMPLEMENTED() ASSERT(FALSE)
#else
#define UNIMPLEMENTED()
#endif

#endif // _DEBUG_H_
