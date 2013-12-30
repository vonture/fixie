#ifndef _FIXIE_H_
#define _FIXIE_H_

#include "fixie/fixie_platform.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef void* fixie_context;

#define FIXIE_ERROR 0

FIXIE_API fixie_context FIXIE_APIENTRY fixie_create_context();
FIXIE_API fixie_context FIXIE_APIENTRY fixie_create_context_shared(fixie_context share_ctx);
FIXIE_API void FIXIE_APIENTRY fixie_destroy_context(fixie_context ctx);

FIXIE_API void FIXIE_APIENTRY fixie_set_context(fixie_context ctx);
FIXIE_API fixie_context FIXIE_APIENTRY fixie_get_context();

FIXIE_API void FIXIE_APIENTRY fixie_terminate();

#ifdef __cplusplus
}
#endif

#endif // _FIXIE_H_
