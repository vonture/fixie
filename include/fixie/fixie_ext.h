#ifndef _FIXIE_EXT_H_
#define _FIXIE_EXT_H_

#include "fixie/fixie_platform.h"
#include "fixie/fixie_gl_types.h"

#ifndef GL_KHR_debug
typedef void (FIXIE_APIENTRYP GLDEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, GLvoid *userParam);
#define GL_DEBUG_OUTPUT_SYNCHRONOUS                             0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH                     0x8243
#define GL_DEBUG_CALLBACK_FUNCTION                              0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM                            0x8245
#define GL_DEBUG_SOURCE_API                                     0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM                           0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER                         0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY                             0x8249
#define GL_DEBUG_SOURCE_APPLICATION                             0x824A
#define GL_DEBUG_SOURCE_OTHER                                   0x824B
#define GL_DEBUG_TYPE_ERROR                                     0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR                       0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR                        0x824E
#define GL_DEBUG_TYPE_PORTABILITY                               0x824F
#define GL_DEBUG_TYPE_PERFORMANCE                               0x8250
#define GL_DEBUG_TYPE_OTHER                                     0x8251
#define GL_DEBUG_TYPE_MARKER                                    0x8268
#define GL_DEBUG_TYPE_PUSH_GROUP                                0x8269
#define GL_DEBUG_TYPE_POP_GROUP                                 0x826A
#define GL_DEBUG_SEVERITY_NOTIFICATION                          0x826B
#define GL_MAX_DEBUG_GROUP_STACK_DEPTH                          0x826C
#define GL_DEBUG_GROUP_STACK_DEPTH                              0x826D
#define GL_BUFFER                                               0x82E0
#define GL_SHADER                                               0x82E1
#define GL_PROGRAM                                              0x82E2
#define GL_QUERY                                                0x82E3
/* PROGRAM_PIPELINE only in GL */                               
#define GL_SAMPLER                                              0x82E6
/* DISPLAY_LIST only in GL */                                   
#define GL_MAX_LABEL_LENGTH                                     0x82E8
#define GL_MAX_DEBUG_MESSAGE_LENGTH                             0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES                            0x9144
#define GL_DEBUG_LOGGED_MESSAGES                                0x9145
#define GL_DEBUG_SEVERITY_HIGH                                  0x9146
#define GL_DEBUG_SEVERITY_MEDIUM                                0x9147
#define GL_DEBUG_SEVERITY_LOW                                   0x9148
#define GL_DEBUG_OUTPUT                                         0x92E0
#define GL_CONTEXT_FLAG_DEBUG_BIT                               0x00000002
#define GL_STACK_OVERFLOW                                       0x0503
#define GL_STACK_UNDERFLOW                                      0x0504
#endif

#ifndef GL_KHR_debug
#define GL_KHR_debug 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glDebugMessageControl (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
FIXIE_API void FIXIE_APIENTRY glDebugMessageInsert (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
FIXIE_API void FIXIE_APIENTRY glDebugMessageCallback (GLDEBUGPROC callback, const void *userParam);
FIXIE_API GLuint FIXIE_APIENTRY glGetDebugMessageLog (GLuint count, GLsizei bufsize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
FIXIE_API void FIXIE_APIENTRY glPushDebugGroup (GLenum source, GLuint id, GLsizei length, const GLchar *message);
FIXIE_API void FIXIE_APIENTRY glPopDebugGroup (void);
FIXIE_API void FIXIE_APIENTRY glObjectLabel (GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
FIXIE_API void FIXIE_APIENTRY glGetObjectLabel (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
FIXIE_API void FIXIE_APIENTRY glObjectPtrLabel (const void *ptr, GLsizei length, const GLchar *label);
FIXIE_API void FIXIE_APIENTRY glGetObjectPtrLabel (const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
FIXIE_API void FIXIE_APIENTRY glGetPointerv (GLenum pname, void **params);
#endif
typedef void (FIXIE_APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC) (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void (FIXIE_APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
typedef void (FIXIE_APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC callback, const void *userParam);
typedef GLuint (FIXIE_APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC) (GLuint count, GLsizei bufsize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
typedef void (FIXIE_APIENTRYP PFNGLPUSHDEBUGGROUPPROC) (GLenum source, GLuint id, GLsizei length, const GLchar *message);
typedef void (FIXIE_APIENTRYP PFNGLPOPDEBUGGROUPPROC) (void);
typedef void (FIXIE_APIENTRYP PFNGLOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
typedef void (FIXIE_APIENTRYP PFNGLGETOBJECTLABELPROC) (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
typedef void (FIXIE_APIENTRYP PFNGLOBJECTPTRLABELPROC) (const void *ptr, GLsizei length, const GLchar *label);
typedef void (FIXIE_APIENTRYP PFNGLGETOBJECTPTRLABELPROC) (const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
typedef void (FIXIE_APIENTRYP PFNGLGETPOINTERVPROC) (GLenum pname, void **params);
#endif

#endif // _FIXIE_EXT_H_
