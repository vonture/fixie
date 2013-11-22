#ifndef _FIXIE_GL_ES_EXT_H_
#define _FIXIE_GL_ES_EXT_H_

#ifndef __glext_h_
#define __glext_h_

/* $Revision: 20798 $ on $Date:: 2013-03-07 01:19:34 -0800 #$ */

#include "fixie/fixie_platform.h"
#include "fixie/fixie_gl_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This document is licensed under the SGI Free Software B License Version
 * 2.0. For details, see http://oss.sgi.com/projects/FreeB/ .
 */

/*------------------------------------------------------------------------*
 * OES extension tokens
 *------------------------------------------------------------------------*/

/* GL_OES_blend_equation_separate */
#ifndef GL_OES_blend_equation_separate
/* BLEND_EQUATION_RGB_OES same as BLEND_EQUATION_OES */
#define GL_BLEND_EQUATION_RGB_OES                               0x8009
#define GL_BLEND_EQUATION_ALPHA_OES                             0x883D
#endif

/* GL_OES_blend_func_separate */
#ifndef GL_OES_blend_func_separate
#define GL_BLEND_DST_RGB_OES                                    0x80C8
#define GL_BLEND_SRC_RGB_OES                                    0x80C9
#define GL_BLEND_DST_ALPHA_OES                                  0x80CA
#define GL_BLEND_SRC_ALPHA_OES                                  0x80CB
#endif

/* GL_OES_blend_subtract */
#ifndef GL_OES_blend_subtract
#define GL_BLEND_EQUATION_OES                                   0x8009
#define GL_FUNC_ADD_OES                                         0x8006
#define GL_FUNC_SUBTRACT_OES                                    0x800A
#define GL_FUNC_REVERSE_SUBTRACT_OES                            0x800B
#endif

/* GL_OES_compressed_ETC1_RGB8_texture */
#ifndef GL_OES_compressed_ETC1_RGB8_texture
#define GL_ETC1_RGB8_OES                                        0x8D64
#endif

/* GL_OES_depth24 */
#ifndef GL_OES_depth24
#define GL_DEPTH_COMPONENT24_OES                                0x81A6
#endif

/* GL_OES_depth32 */
#ifndef GL_OES_depth32
#define GL_DEPTH_COMPONENT32_OES                                0x81A7
#endif

/* GL_OES_draw_texture */
#ifndef GL_OES_draw_texture
#define GL_TEXTURE_CROP_RECT_OES                                0x8B9D
#endif

/* GL_OES_EGL_image */
#ifndef GL_OES_EGL_image
typedef void* GLeglImageOES;
#endif

/* GL_OES_EGL_image_external */
#ifndef GL_OES_EGL_image_external
/* GLeglImageOES defined in GL_OES_EGL_image already. */
#define GL_TEXTURE_EXTERNAL_OES                                 0x8D65
#define GL_TEXTURE_BINDING_EXTERNAL_OES                         0x8D67
#define GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES                     0x8D68
#endif

/* GL_OES_element_index_uint */
#ifndef GL_OES_element_index_uint
#define GL_UNSIGNED_INT                                         0x1405
#endif

/* GL_OES_fixed_point */
#ifndef GL_OES_fixed_point
#define GL_FIXED_OES                                            0x140C
#endif

/* GL_OES_framebuffer_object */
#ifndef GL_OES_framebuffer_object
#define GL_NONE_OES                                             0
#define GL_FRAMEBUFFER_OES                                      0x8D40
#define GL_RENDERBUFFER_OES                                     0x8D41
#define GL_RGBA4_OES                                            0x8056
#define GL_RGB5_A1_OES                                          0x8057
#define GL_RGB565_OES                                           0x8D62
#define GL_DEPTH_COMPONENT16_OES                                0x81A5
#define GL_RENDERBUFFER_WIDTH_OES                               0x8D42
#define GL_RENDERBUFFER_HEIGHT_OES                              0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT_OES                     0x8D44
#define GL_RENDERBUFFER_RED_SIZE_OES                            0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE_OES                          0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE_OES                           0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE_OES                          0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE_OES                          0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE_OES                        0x8D55
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES               0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES               0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES             0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES     0x8CD3
#define GL_COLOR_ATTACHMENT0_OES                                0x8CE0
#define GL_DEPTH_ATTACHMENT_OES                                 0x8D00
#define GL_STENCIL_ATTACHMENT_OES                               0x8D20
#define GL_FRAMEBUFFER_COMPLETE_OES                             0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES                0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES        0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES                0x8CD9
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES                   0x8CDA
#define GL_FRAMEBUFFER_UNSUPPORTED_OES                          0x8CDD
#define GL_FRAMEBUFFER_BINDING_OES                              0x8CA6
#define GL_RENDERBUFFER_BINDING_OES                             0x8CA7
#define GL_MAX_RENDERBUFFER_SIZE_OES                            0x84E8
#define GL_INVALID_FRAMEBUFFER_OPERATION_OES                    0x0506
#endif

/* GL_OES_mapbuffer */
#ifndef GL_OES_mapbuffer
#define GL_WRITE_ONLY_OES                                       0x88B9
#define GL_BUFFER_ACCESS_OES                                    0x88BB
#define GL_BUFFER_MAPPED_OES                                    0x88BC
#define GL_BUFFER_MAP_POINTER_OES                               0x88BD
#endif

/* GL_OES_matrix_get */
#ifndef GL_OES_matrix_get
#define GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES               0x898D
#define GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES              0x898E
#define GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES                 0x898F
#endif

/* GL_OES_matrix_palette */
#ifndef GL_OES_matrix_palette
#define GL_MAX_VERTEX_UNITS_OES                                 0x86A4
#define GL_MAX_PALETTE_MATRICES_OES                             0x8842
#define GL_MATRIX_PALETTE_OES                                   0x8840
#define GL_MATRIX_INDEX_ARRAY_OES                               0x8844
#define GL_WEIGHT_ARRAY_OES                                     0x86AD
#define GL_CURRENT_PALETTE_MATRIX_OES                           0x8843
#define GL_MATRIX_INDEX_ARRAY_SIZE_OES                          0x8846
#define GL_MATRIX_INDEX_ARRAY_TYPE_OES                          0x8847
#define GL_MATRIX_INDEX_ARRAY_STRIDE_OES                        0x8848
#define GL_MATRIX_INDEX_ARRAY_POINTER_OES                       0x8849
#define GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES                0x8B9E
#define GL_WEIGHT_ARRAY_SIZE_OES                                0x86AB
#define GL_WEIGHT_ARRAY_TYPE_OES                                0x86A9
#define GL_WEIGHT_ARRAY_STRIDE_OES                              0x86AA
#define GL_WEIGHT_ARRAY_POINTER_OES                             0x86AC
#define GL_WEIGHT_ARRAY_BUFFER_BINDING_OES                      0x889E
#endif

/* GL_OES_packed_depth_stencil */
#ifndef GL_OES_packed_depth_stencil
#define GL_DEPTH_STENCIL_OES                                    0x84F9
#define GL_UNSIGNED_INT_24_8_OES                                0x84FA
#define GL_DEPTH24_STENCIL8_OES                                 0x88F0
#endif

/* GL_OES_required_internalformat */
/* No new tokens introduced by this extension. */

/* GL_OES_rgb8_rgba8 */
#ifndef GL_OES_rgb8_rgba8
#define GL_RGB8_OES                                             0x8051
#define GL_RGBA8_OES                                            0x8058
#endif

/* GL_OES_stencil1 */
#ifndef GL_OES_stencil1
#define GL_STENCIL_INDEX1_OES                                   0x8D46
#endif

/* GL_OES_stencil4 */
#ifndef GL_OES_stencil4
#define GL_STENCIL_INDEX4_OES                                   0x8D47
#endif

/* GL_OES_stencil8 */
#ifndef GL_OES_stencil8
#define GL_STENCIL_INDEX8_OES                                   0x8D48
#endif

/* GL_OES_stencil_wrap */
#ifndef GL_OES_stencil_wrap
#define GL_INCR_WRAP_OES                                        0x8507
#define GL_DECR_WRAP_OES                                        0x8508
#endif

/* GL_OES_texture_cube_map */
#ifndef GL_OES_texture_cube_map
#define GL_NORMAL_MAP_OES                                       0x8511
#define GL_REFLECTION_MAP_OES                                   0x8512
#define GL_TEXTURE_CUBE_MAP_OES                                 0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP_OES                         0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X_OES                      0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X_OES                      0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y_OES                      0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_OES                      0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z_OES                      0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_OES                      0x851A
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE_OES                        0x851C
#define GL_TEXTURE_GEN_MODE_OES                                 0x2500
#define GL_TEXTURE_GEN_STR_OES                                  0x8D60
#endif

/* GL_OES_texture_mirrored_repeat */
#ifndef GL_OES_texture_mirrored_repeat
#define GL_MIRRORED_REPEAT_OES                                  0x8370
#endif

/* GL_OES_vertex_array_object */
#ifndef GL_OES_vertex_array_object
#define GL_VERTEX_ARRAY_BINDING_OES                             0x85B5
#endif

/*------------------------------------------------------------------------*
 * AMD extension tokens
 *------------------------------------------------------------------------*/

/* GL_AMD_compressed_3DC_texture */
#ifndef GL_AMD_compressed_3DC_texture
#define GL_3DC_X_AMD                                            0x87F9
#define GL_3DC_XY_AMD                                           0x87FA
#endif

/* GL_AMD_compressed_ATC_texture */
#ifndef GL_AMD_compressed_ATC_texture
#define GL_ATC_RGB_AMD                                          0x8C92
#define GL_ATC_RGBA_EXPLICIT_ALPHA_AMD                          0x8C93
#define GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD                      0x87EE
#endif

/*------------------------------------------------------------------------*
 * APPLE extension tokens
 *------------------------------------------------------------------------*/

/* GL_APPLE_copy_texture_levels */
/* No new tokens introduced by this extension. */

/* GL_APPLE_framebuffer_multisample */
#ifndef GL_APPLE_framebuffer_multisample
#define GL_RENDERBUFFER_SAMPLES_APPLE                           0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_APPLE             0x8D56
#define GL_MAX_SAMPLES_APPLE                                    0x8D57
#define GL_READ_FRAMEBUFFER_APPLE                               0x8CA8
#define GL_DRAW_FRAMEBUFFER_APPLE                               0x8CA9
#define GL_DRAW_FRAMEBUFFER_BINDING_APPLE                       0x8CA6
#define GL_READ_FRAMEBUFFER_BINDING_APPLE                       0x8CAA
#endif

/* GL_APPLE_sync */
#ifndef GL_APPLE_sync

/* These types are defined with reference to <inttypes.h>
 * in the Apple extension spec, but here we use the Khronos
 * portable types in khrplatform.h, and assume those types
 * are always defined.
 * If any other extensions using these types are defined,
 * the typedefs must move out of this block and be shared.
 */
typedef int64_t GLint64;
typedef uint64_t GLuint64;
typedef struct __GLsync *GLsync;

#define GL_SYNC_OBJECT_APPLE                                    0x8A53
#define GL_MAX_SERVER_WAIT_TIMEOUT_APPLE                        0x9111
#define GL_OBJECT_TYPE_APPLE                                    0x9112
#define GL_SYNC_CONDITION_APPLE                                 0x9113
#define GL_SYNC_STATUS_APPLE                                    0x9114
#define GL_SYNC_FLAGS_APPLE                                     0x9115
#define GL_SYNC_FENCE_APPLE                                     0x9116
#define GL_SYNC_GPU_COMMANDS_COMPLETE_APPLE                     0x9117
#define GL_UNSIGNALED_APPLE                                     0x9118
#define GL_SIGNALED_APPLE                                       0x9119
#define GL_ALREADY_SIGNALED_APPLE                               0x911A
#define GL_TIMEOUT_EXPIRED_APPLE                                0x911B
#define GL_CONDITION_SATISFIED_APPLE                            0x911C
#define GL_WAIT_FAILED_APPLE                                    0x911D
#define GL_SYNC_FLUSH_COMMANDS_BIT_APPLE                        0x00000001
#define GL_TIMEOUT_IGNORED_APPLE                                0xFFFFFFFFFFFFFFFFull
#endif

/* GL_APPLE_texture_2D_limited_npot */
/* No new tokens introduced by this extension. */

/* GL_APPLE_texture_format_BGRA8888 */
#ifndef GL_APPLE_texture_format_BGRA8888
#define GL_BGRA_EXT                                             0x80E1
#endif

/* GL_APPLE_texture_max_level */
#ifndef GL_APPLE_texture_max_level
#define GL_TEXTURE_MAX_LEVEL_APPLE                              0x813D
#endif

/*------------------------------------------------------------------------*
 * ARM extension tokens
 *------------------------------------------------------------------------*/

/* GL_ARM_rgba8 */
/* No new tokens introduced by this extension. */

/*------------------------------------------------------------------------*
 * EXT extension tokens
 *------------------------------------------------------------------------*/

/* GL_EXT_blend_minmax */
#ifndef GL_EXT_blend_minmax
#define GL_MIN_EXT                                              0x8007
#define GL_MAX_EXT                                              0x8008
#endif

/* GL_EXT_discard_framebuffer */
#ifndef GL_EXT_discard_framebuffer
#define GL_COLOR_EXT                                            0x1800
#define GL_DEPTH_EXT                                            0x1801
#define GL_STENCIL_EXT                                          0x1802
#endif

/* GL_EXT_map_buffer_range */
#ifndef GL_EXT_map_buffer_range
#define GL_MAP_READ_BIT_EXT                                     0x0001
#define GL_MAP_WRITE_BIT_EXT                                    0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT_EXT                         0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT_EXT                        0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT_EXT                           0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT_EXT                           0x0020
#endif

/* GL_EXT_multisampled_render_to_texture */
#ifndef GL_EXT_multisampled_render_to_texture
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_SAMPLES_EXT           0x8D6C
/* reuse values from GL_EXT_framebuffer_multisample (desktop extension) */
#define GL_RENDERBUFFER_SAMPLES_EXT                             0x8CAB
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT               0x8D56
#define GL_MAX_SAMPLES_EXT                                      0x8D57
#endif

/* GL_EXT_multi_draw_arrays */
/* No new tokens introduced by this extension. */

/* GL_EXT_read_format_bgra */
#ifndef GL_EXT_read_format_bgra
#define GL_BGRA_EXT                                             0x80E1
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_EXT                       0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV_EXT                       0x8366
#endif

/* GL_EXT_robustness */
#ifndef GL_EXT_robustness
/* reuse GL_NO_ERROR */
#define GL_GUILTY_CONTEXT_RESET_EXT                             0x8253
#define GL_INNOCENT_CONTEXT_RESET_EXT                           0x8254
#define GL_UNKNOWN_CONTEXT_RESET_EXT                            0x8255
#define GL_CONTEXT_ROBUST_ACCESS_EXT                            0x90F3
#define GL_RESET_NOTIFICATION_STRATEGY_EXT                      0x8256
#define GL_LOSE_CONTEXT_ON_RESET_EXT                            0x8252
#define GL_NO_RESET_NOTIFICATION_EXT                            0x8261
#endif

/* GL_EXT_sRGB */
#ifndef GL_EXT_sRGB
#define GL_SRGB_EXT                                             0x8C40
#define GL_SRGB_ALPHA_EXT                                       0x8C42
#define GL_SRGB8_ALPHA8_EXT                                     0x8C43
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT            0x8210
#endif

/* GL_EXT_texture_compression_dxt1 */
#ifndef GL_EXT_texture_compression_dxt1
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT                         0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT                        0x83F1
#endif

/* GL_EXT_texture_filter_anisotropic */
#ifndef GL_EXT_texture_filter_anisotropic
#define GL_TEXTURE_MAX_ANISOTROPY_EXT                           0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT                       0x84FF
#endif

/* GL_EXT_texture_format_BGRA8888 */
#ifndef GL_EXT_texture_format_BGRA8888
#define GL_BGRA_EXT                                             0x80E1
#endif

/* GL_EXT_texture_lod_bias */
#ifndef GL_EXT_texture_lod_bias
#define GL_MAX_TEXTURE_LOD_BIAS_EXT                             0x84FD
#define GL_TEXTURE_FILTER_CONTROL_EXT                           0x8500
#define GL_TEXTURE_LOD_BIAS_EXT                                 0x8501
#endif

/* GL_EXT_texture_storage */
#ifndef GL_EXT_texture_storage
#define GL_TEXTURE_IMMUTABLE_FORMAT_EXT                         0x912F
#define GL_ALPHA8_EXT                                           0x803C
#define GL_LUMINANCE8_EXT                                       0x8040
#define GL_LUMINANCE8_ALPHA8_EXT                                0x8045
#define GL_RGBA32F_EXT                                          0x8814
#define GL_RGB32F_EXT                                           0x8815
#define GL_ALPHA32F_EXT                                         0x8816
#define GL_LUMINANCE32F_EXT                                     0x8818
#define GL_LUMINANCE_ALPHA32F_EXT                               0x8819
/* reuse GL_RGBA16F_EXT */
#define GL_RGB16F_EXT                                           0x881B
#define GL_ALPHA16F_EXT                                         0x881C
#define GL_LUMINANCE16F_EXT                                     0x881E
#define GL_LUMINANCE_ALPHA16F_EXT                               0x881F
#define GL_RGB10_A2_EXT                                         0x8059
#define GL_RGB10_EXT                                            0x8052
#define GL_BGRA8_EXT                                            0x93A1
#endif

/*------------------------------------------------------------------------*
 * IMG extension tokens
 *------------------------------------------------------------------------*/

/* GL_IMG_read_format */
#ifndef GL_IMG_read_format
#define GL_BGRA_IMG                                             0x80E1
#define GL_UNSIGNED_SHORT_4_4_4_4_REV_IMG                       0x8365
#endif

/* GL_IMG_texture_compression_pvrtc */
#ifndef GL_IMG_texture_compression_pvrtc
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG                      0x8C00
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG                      0x8C01
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG                     0x8C02
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG                     0x8C03
#endif

/* GL_IMG_texture_env_enhanced_fixed_function */
#ifndef GL_IMG_texture_env_enhanced_fixed_function
#define GL_MODULATE_COLOR_IMG                                   0x8C04
#define GL_RECIP_ADD_SIGNED_ALPHA_IMG                           0x8C05
#define GL_TEXTURE_ALPHA_MODULATE_IMG                           0x8C06
#define GL_FACTOR_ALPHA_MODULATE_IMG                            0x8C07
#define GL_FRAGMENT_ALPHA_MODULATE_IMG                          0x8C08
#define GL_ADD_BLEND_IMG                                        0x8C09
#define GL_DOT3_RGBA_IMG                                        0x86AF
#endif

/* GL_IMG_user_clip_plane */
#ifndef GL_IMG_user_clip_plane
#define GL_CLIP_PLANE0_IMG                                      0x3000
#define GL_CLIP_PLANE1_IMG                                      0x3001
#define GL_CLIP_PLANE2_IMG                                      0x3002
#define GL_CLIP_PLANE3_IMG                                      0x3003
#define GL_CLIP_PLANE4_IMG                                      0x3004
#define GL_CLIP_PLANE5_IMG                                      0x3005
#define GL_MAX_CLIP_PLANES_IMG                                  0x0D32
#endif

/* GL_IMG_multisampled_render_to_texture */
#ifndef GL_IMG_multisampled_render_to_texture
#define GL_RENDERBUFFER_SAMPLES_IMG                             0x9133
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_IMG               0x9134
#define GL_MAX_SAMPLES_IMG                                      0x9135
#define GL_TEXTURE_SAMPLES_IMG                                  0x9136
#endif

/*------------------------------------------------------------------------*
 * NV extension tokens
 *------------------------------------------------------------------------*/

/* GL_NV_fence */
#ifndef GL_NV_fence
#define GL_ALL_COMPLETED_NV                                     0x84F2
#define GL_FENCE_STATUS_NV                                      0x84F3
#define GL_FENCE_CONDITION_NV                                   0x84F4
#endif

/*------------------------------------------------------------------------*
 * QCOM extension tokens
 *------------------------------------------------------------------------*/

/* GL_QCOM_driver_control */
/* No new tokens introduced by this extension. */

/* GL_QCOM_extended_get */
#ifndef GL_QCOM_extended_get
#define GL_TEXTURE_WIDTH_QCOM                                   0x8BD2
#define GL_TEXTURE_HEIGHT_QCOM                                  0x8BD3
#define GL_TEXTURE_DEPTH_QCOM                                   0x8BD4
#define GL_TEXTURE_INTERNAL_FORMAT_QCOM                         0x8BD5
#define GL_TEXTURE_FORMAT_QCOM                                  0x8BD6
#define GL_TEXTURE_TYPE_QCOM                                    0x8BD7
#define GL_TEXTURE_IMAGE_VALID_QCOM                             0x8BD8
#define GL_TEXTURE_NUM_LEVELS_QCOM                              0x8BD9
#define GL_TEXTURE_TARGET_QCOM                                  0x8BDA
#define GL_TEXTURE_OBJECT_VALID_QCOM                            0x8BDB
#define GL_STATE_RESTORE                                        0x8BDC
#endif

/* GL_QCOM_extended_get2 */
/* No new tokens introduced by this extension. */

/* GL_QCOM_perfmon_global_mode */
#ifndef GL_QCOM_perfmon_global_mode
#define GL_PERFMON_GLOBAL_MODE_QCOM                             0x8FA0
#endif

/* GL_QCOM_writeonly_rendering */
#ifndef GL_QCOM_writeonly_rendering
#define GL_WRITEONLY_RENDERING_QCOM                             0x8823
#endif

/* GL_QCOM_tiled_rendering */
#ifndef GL_QCOM_tiled_rendering
#define GL_COLOR_BUFFER_BIT0_QCOM                               0x00000001
#define GL_COLOR_BUFFER_BIT1_QCOM                               0x00000002
#define GL_COLOR_BUFFER_BIT2_QCOM                               0x00000004
#define GL_COLOR_BUFFER_BIT3_QCOM                               0x00000008
#define GL_COLOR_BUFFER_BIT4_QCOM                               0x00000010
#define GL_COLOR_BUFFER_BIT5_QCOM                               0x00000020
#define GL_COLOR_BUFFER_BIT6_QCOM                               0x00000040
#define GL_COLOR_BUFFER_BIT7_QCOM                               0x00000080
#define GL_DEPTH_BUFFER_BIT0_QCOM                               0x00000100
#define GL_DEPTH_BUFFER_BIT1_QCOM                               0x00000200
#define GL_DEPTH_BUFFER_BIT2_QCOM                               0x00000400
#define GL_DEPTH_BUFFER_BIT3_QCOM                               0x00000800
#define GL_DEPTH_BUFFER_BIT4_QCOM                               0x00001000
#define GL_DEPTH_BUFFER_BIT5_QCOM                               0x00002000
#define GL_DEPTH_BUFFER_BIT6_QCOM                               0x00004000
#define GL_DEPTH_BUFFER_BIT7_QCOM                               0x00008000
#define GL_STENCIL_BUFFER_BIT0_QCOM                             0x00010000
#define GL_STENCIL_BUFFER_BIT1_QCOM                             0x00020000
#define GL_STENCIL_BUFFER_BIT2_QCOM                             0x00040000
#define GL_STENCIL_BUFFER_BIT3_QCOM                             0x00080000
#define GL_STENCIL_BUFFER_BIT4_QCOM                             0x00100000
#define GL_STENCIL_BUFFER_BIT5_QCOM                             0x00200000
#define GL_STENCIL_BUFFER_BIT6_QCOM                             0x00400000
#define GL_STENCIL_BUFFER_BIT7_QCOM                             0x00800000
#define GL_MULTISAMPLE_BUFFER_BIT0_QCOM                         0x01000000
#define GL_MULTISAMPLE_BUFFER_BIT1_QCOM                         0x02000000
#define GL_MULTISAMPLE_BUFFER_BIT2_QCOM                         0x04000000
#define GL_MULTISAMPLE_BUFFER_BIT3_QCOM                         0x08000000
#define GL_MULTISAMPLE_BUFFER_BIT4_QCOM                         0x10000000
#define GL_MULTISAMPLE_BUFFER_BIT5_QCOM                         0x20000000
#define GL_MULTISAMPLE_BUFFER_BIT6_QCOM                         0x40000000
#define GL_MULTISAMPLE_BUFFER_BIT7_QCOM                         0x80000000
#endif

/*------------------------------------------------------------------------*
 * End of extension tokens, start of corresponding extension functions
 *------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*
 * OES extension functions
 *------------------------------------------------------------------------*/

/* GL_OES_blend_equation_separate */
#ifndef GL_OES_blend_equation_separate
#define GL_OES_blend_equation_separate 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glBlendEquationSeparateOES (GLenum modeRGB, GLenum modeAlpha);
#endif
typedef void (FIXIE_APIENTRYP PFNGLBLENDEQUATIONSEPARATEOESPROC) (GLenum modeRGB, GLenum modeAlpha);
#endif

/* GL_OES_blend_func_separate */
#ifndef GL_OES_blend_func_separate
#define GL_OES_blend_func_separate 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glBlendFuncSeparateOES (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#endif
typedef void (FIXIE_APIENTRYP PFNGLBLENDFUNCSEPARATEOESPROC) (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
#endif

/* GL_OES_blend_subtract */
#ifndef GL_OES_blend_subtract
#define GL_OES_blend_subtract 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glBlendEquationOES (GLenum mode);
#endif
typedef void (FIXIE_APIENTRYP PFNGLBLENDEQUATIONOESPROC) (GLenum mode);
#endif

/* GL_OES_byte_coordinates */
#ifndef GL_OES_byte_coordinates
#define GL_OES_byte_coordinates 1
#endif

/* GL_OES_compressed_ETC1_RGB8_texture */
#ifndef GL_OES_compressed_ETC1_RGB8_texture
#define GL_OES_compressed_ETC1_RGB8_texture 1
#endif

/* GL_OES_depth24 */
#ifndef GL_OES_depth24
#define GL_OES_depth24 1
#endif

/* GL_OES_depth32 */
#ifndef GL_OES_depth32
#define GL_OES_depth32 1
#endif

/* GL_OES_draw_texture */
#ifndef GL_OES_draw_texture
#define GL_OES_draw_texture 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glDrawTexsOES (GLshort x, GLshort y, GLshort z, GLshort width, GLshort height);
FIXIE_API void FIXIE_APIENTRY glDrawTexiOES (GLint x, GLint y, GLint z, GLint width, GLint height);
FIXIE_API void FIXIE_APIENTRY glDrawTexxOES (GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height);
FIXIE_API void FIXIE_APIENTRY glDrawTexsvOES (const GLshort *coords);
FIXIE_API void FIXIE_APIENTRY glDrawTexivOES (const GLint *coords);
FIXIE_API void FIXIE_APIENTRY glDrawTexxvOES (const GLfixed *coords);
FIXIE_API void FIXIE_APIENTRY glDrawTexfOES (GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);
FIXIE_API void FIXIE_APIENTRY glDrawTexfvOES (const GLfloat *coords);
#endif
typedef void (FIXIE_APIENTRYP PFNGLDRAWTEXSOESPROC) (GLshort x, GLshort y, GLshort z, GLshort width, GLshort height);
typedef void (FIXIE_APIENTRYP PFNGLDRAWTEXIOESPROC) (GLint x, GLint y, GLint z, GLint width, GLint height);
typedef void (FIXIE_APIENTRYP PFNGLDRAWTEXXOESPROC) (GLfixed x, GLfixed y, GLfixed z, GLfixed width, GLfixed height);
typedef void (FIXIE_APIENTRYP PFNGLDRAWTEXSVOESPROC) (const GLshort *coords);
typedef void (FIXIE_APIENTRYP PFNGLDRAWTEXIVOESPROC) (const GLint *coords);
typedef void (FIXIE_APIENTRYP PFNGLDRAWTEXXVOESPROC) (const GLfixed *coords);
typedef void (FIXIE_APIENTRYP PFNGLDRAWTEXFOESPROC) (GLfloat x, GLfloat y, GLfloat z, GLfloat width, GLfloat height);
typedef void (FIXIE_APIENTRYP PFNGLDRAWTEXFVOESPROC) (const GLfloat *coords);
#endif

/* GL_OES_EGL_image */
#ifndef GL_OES_EGL_image
#define GL_OES_EGL_image 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glEGLImageTargetTexture2DOES (GLenum target, GLeglImageOES image);
FIXIE_API void FIXIE_APIENTRY glEGLImageTargetRenderbufferStorageOES (GLenum target, GLeglImageOES image);
#endif
typedef void (FIXIE_APIENTRYP PFNGLEGLIMAGETARGETTEXTURE2DOESPROC) (GLenum target, GLeglImageOES image);
typedef void (FIXIE_APIENTRYP PFNGLEGLIMAGETARGETRENDERBUFFERSTORAGEOESPROC) (GLenum target, GLeglImageOES image);
#endif

/* GL_OES_EGL_image_external */
#ifndef GL_OES_EGL_image_external
#define GL_OES_EGL_image_external 1
/* glEGLImageTargetTexture2DOES defined in GL_OES_EGL_image already. */
#endif

/* GL_OES_element_index_uint */
#ifndef GL_OES_element_index_uint
#define GL_OES_element_index_uint 1
#endif

/* GL_OES_extended_matrix_palette */
#ifndef GL_OES_extended_matrix_palette
#define GL_OES_extended_matrix_palette 1
#endif

/* GL_OES_fbo_render_mipmap */
#ifndef GL_OES_fbo_render_mipmap
#define GL_OES_fbo_render_mipmap 1
#endif

/* GL_OES_fixed_point */
#ifndef GL_OES_fixed_point
#define GL_OES_fixed_point 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glAlphaFuncxOES (GLenum func, GLclampx ref);
FIXIE_API void FIXIE_APIENTRY glClearColorxOES (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha);
FIXIE_API void FIXIE_APIENTRY glClearDepthxOES (GLclampx depth);
FIXIE_API void FIXIE_APIENTRY glClipPlanexOES (GLenum plane, const GLfixed *equation);
FIXIE_API void FIXIE_APIENTRY glColor4xOES (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
FIXIE_API void FIXIE_APIENTRY glDepthRangexOES (GLclampx zNear, GLclampx zFar);
FIXIE_API void FIXIE_APIENTRY glFogxOES (GLenum pname, GLfixed param);
FIXIE_API void FIXIE_APIENTRY glFogxvOES (GLenum pname, const GLfixed *params);
FIXIE_API void FIXIE_APIENTRY glFrustumxOES (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
FIXIE_API void FIXIE_APIENTRY glGetClipPlanexOES (GLenum pname, GLfixed eqn[4]);
FIXIE_API void FIXIE_APIENTRY glGetFixedvOES (GLenum pname, GLfixed *params);
FIXIE_API void FIXIE_APIENTRY glGetLightxvOES (GLenum light, GLenum pname, GLfixed *params);
FIXIE_API void FIXIE_APIENTRY glGetMaterialxvOES (GLenum face, GLenum pname, GLfixed *params);
FIXIE_API void FIXIE_APIENTRY glGetTexEnvxvOES (GLenum env, GLenum pname, GLfixed *params);
FIXIE_API void FIXIE_APIENTRY glGetTexParameterxvOES (GLenum target, GLenum pname, GLfixed *params);
FIXIE_API void FIXIE_APIENTRY glLightModelxOES (GLenum pname, GLfixed param);
FIXIE_API void FIXIE_APIENTRY glLightModelxvOES (GLenum pname, const GLfixed *params);
FIXIE_API void FIXIE_APIENTRY glLightxOES (GLenum light, GLenum pname, GLfixed param);
FIXIE_API void FIXIE_APIENTRY glLightxvOES (GLenum light, GLenum pname, const GLfixed *params);
FIXIE_API void FIXIE_APIENTRY glLineWidthxOES (GLfixed width);
FIXIE_API void FIXIE_APIENTRY glLoadMatrixxOES (const GLfixed *m);
FIXIE_API void FIXIE_APIENTRY glMaterialxOES (GLenum face, GLenum pname, GLfixed param);
FIXIE_API void FIXIE_APIENTRY glMaterialxvOES (GLenum face, GLenum pname, const GLfixed *params);
FIXIE_API void FIXIE_APIENTRY glMultMatrixxOES (const GLfixed *m);
FIXIE_API void FIXIE_APIENTRY glMultiTexCoord4xOES (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
FIXIE_API void FIXIE_APIENTRY glNormal3xOES (GLfixed nx, GLfixed ny, GLfixed nz);
FIXIE_API void FIXIE_APIENTRY glOrthoxOES (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
FIXIE_API void FIXIE_APIENTRY glPointParameterxOES (GLenum pname, GLfixed param);
FIXIE_API void FIXIE_APIENTRY glPointParameterxvOES (GLenum pname, const GLfixed *params);
FIXIE_API void FIXIE_APIENTRY glPointSizexOES (GLfixed size);
FIXIE_API void FIXIE_APIENTRY glPolygonOffsetxOES (GLfixed factor, GLfixed units);
FIXIE_API void FIXIE_APIENTRY glRotatexOES (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
FIXIE_API void FIXIE_APIENTRY glSampleCoveragexOES (GLclampx value, GLboolean invert);
FIXIE_API void FIXIE_APIENTRY glScalexOES (GLfixed x, GLfixed y, GLfixed z);
FIXIE_API void FIXIE_APIENTRY glTexEnvxOES (GLenum target, GLenum pname, GLfixed param);
FIXIE_API void FIXIE_APIENTRY glTexEnvxvOES (GLenum target, GLenum pname, const GLfixed *params);
FIXIE_API void FIXIE_APIENTRY glTexParameterxOES (GLenum target, GLenum pname, GLfixed param);
FIXIE_API void FIXIE_APIENTRY glTexParameterxvOES (GLenum target, GLenum pname, const GLfixed *params);
FIXIE_API void FIXIE_APIENTRY glTranslatexOES (GLfixed x, GLfixed y, GLfixed z);
#endif
typedef void (FIXIE_APIENTRYP PFNGLALPHAFUNCXOESPROC) (GLenum func, GLclampx ref);
typedef void (FIXIE_APIENTRYP PFNGLCLEARCOLORXOESPROC) (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha);
typedef void (FIXIE_APIENTRYP PFNGLCLEARDEPTHXOESPROC) (GLclampx depth);
typedef void (FIXIE_APIENTRYP PFNGLCLIPPLANEXOESPROC) (GLenum plane, const GLfixed *equation);
typedef void (FIXIE_APIENTRYP PFNGLCOLOR4XOESPROC) (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
typedef void (FIXIE_APIENTRYP PFNGLDEPTHRANGEXOESPROC) (GLclampx zNear, GLclampx zFar);
typedef void (FIXIE_APIENTRYP PFNGLFOGXOESPROC) (GLenum pname, GLfixed param);
typedef void (FIXIE_APIENTRYP PFNGLFOGXVOESPROC) (GLenum pname, const GLfixed *params);
typedef void (FIXIE_APIENTRYP PFNGLFRUSTUMXOESPROC) (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
typedef void (FIXIE_APIENTRYP PFNGLGETCLIPPLANEXOESPROC) (GLenum pname, GLfixed eqn[4]);
typedef void (FIXIE_APIENTRYP PFNGLGETFIXEDVOESPROC) (GLenum pname, GLfixed *params);
typedef void (FIXIE_APIENTRYP PFNGLGETLIGHTXVOESPROC) (GLenum light, GLenum pname, GLfixed *params);
typedef void (FIXIE_APIENTRYP PFNGLGETMATERIALXVOESPROC) (GLenum face, GLenum pname, GLfixed *params);
typedef void (FIXIE_APIENTRYP PFNGLGETTEXENVXVOESPROC) (GLenum env, GLenum pname, GLfixed *params);
typedef void (FIXIE_APIENTRYP PFNGLGETTEXPARAMETERXVOESPROC) (GLenum target, GLenum pname, GLfixed *params);
typedef void (FIXIE_APIENTRYP PFNGLLIGHTMODELXOESPROC) (GLenum pname, GLfixed param);
typedef void (FIXIE_APIENTRYP PFNGLLIGHTMODELXVOESPROC) (GLenum pname, const GLfixed *params);
typedef void (FIXIE_APIENTRYP PFNGLLIGHTXOESPROC) (GLenum light, GLenum pname, GLfixed param);
typedef void (FIXIE_APIENTRYP PFNGLLIGHTXVOESPROC) (GLenum light, GLenum pname, const GLfixed *params);
typedef void (FIXIE_APIENTRYP PFNGLLINEWIDTHXOESPROC) (GLfixed width);
typedef void (FIXIE_APIENTRYP PFNGLLOADMATRIXXOESPROC) (const GLfixed *m);
typedef void (FIXIE_APIENTRYP PFNGLMATERIALXOESPROC) (GLenum face, GLenum pname, GLfixed param);
typedef void (FIXIE_APIENTRYP PFNGLMATERIALXVOESPROC) (GLenum face, GLenum pname, const GLfixed *params);
typedef void (FIXIE_APIENTRYP PFNGLMULTMATRIXXOESPROC) (const GLfixed *m);
typedef void (FIXIE_APIENTRYP PFNGLMULTITEXCOORD4XOESPROC) (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
typedef void (FIXIE_APIENTRYP PFNGLNORMAL3XOESPROC) (GLfixed nx, GLfixed ny, GLfixed nz);
typedef void (FIXIE_APIENTRYP PFNGLORTHOXOESPROC) (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar);
typedef void (FIXIE_APIENTRYP PFNGLPOINTPARAMETERXOESPROC) (GLenum pname, GLfixed param);
typedef void (FIXIE_APIENTRYP PFNGLPOINTPARAMETERXVOESPROC) (GLenum pname, const GLfixed *params);
typedef void (FIXIE_APIENTRYP PFNGLPOINTSIZEXOESPROC) (GLfixed size);
typedef void (FIXIE_APIENTRYP PFNGLPOLYGONOFFSETXOESPROC) (GLfixed factor, GLfixed units);
typedef void (FIXIE_APIENTRYP PFNGLROTATEXOESPROC) (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
typedef void (FIXIE_APIENTRYP PFNGLSAMPLECOVERAGEXOESPROC) (GLclampx value, GLboolean invert);
typedef void (FIXIE_APIENTRYP PFNGLSCALEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
typedef void (FIXIE_APIENTRYP PFNGLTEXENVXOESPROC) (GLenum target, GLenum pname, GLfixed param);
typedef void (FIXIE_APIENTRYP PFNGLTEXENVXVOESPROC) (GLenum target, GLenum pname, const GLfixed *params);
typedef void (FIXIE_APIENTRYP PFNGLTEXPARAMETERXOESPROC) (GLenum target, GLenum pname, GLfixed param);
typedef void (FIXIE_APIENTRYP PFNGLTEXPARAMETERXVOESPROC) (GLenum target, GLenum pname, const GLfixed *params);
typedef void (FIXIE_APIENTRYP PFNGLTRANSLATEXOESPROC) (GLfixed x, GLfixed y, GLfixed z);
#endif

/* GL_OES_framebuffer_object */
#ifndef GL_OES_framebuffer_object
#define GL_OES_framebuffer_object 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API GLboolean FIXIE_APIENTRY glIsRenderbufferOES (GLuint renderbuffer);
FIXIE_API void FIXIE_APIENTRY glBindRenderbufferOES (GLenum target, GLuint renderbuffer);
FIXIE_API void FIXIE_APIENTRY glDeleteRenderbuffersOES (GLsizei n, const GLuint* renderbuffers);
FIXIE_API void FIXIE_APIENTRY glGenRenderbuffersOES (GLsizei n, GLuint* renderbuffers);
FIXIE_API void FIXIE_APIENTRY glRenderbufferStorageOES (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
FIXIE_API void FIXIE_APIENTRY glGetRenderbufferParameterivOES (GLenum target, GLenum pname, GLint* params);
FIXIE_API GLboolean FIXIE_APIENTRY glIsFramebufferOES (GLuint framebuffer);
FIXIE_API void FIXIE_APIENTRY glBindFramebufferOES (GLenum target, GLuint framebuffer);
FIXIE_API void FIXIE_APIENTRY glDeleteFramebuffersOES (GLsizei n, const GLuint* framebuffers);
FIXIE_API void FIXIE_APIENTRY glGenFramebuffersOES (GLsizei n, GLuint* framebuffers);
FIXIE_API GLenum FIXIE_APIENTRY glCheckFramebufferStatusOES (GLenum target);
FIXIE_API void FIXIE_APIENTRY glFramebufferRenderbufferOES (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
FIXIE_API void FIXIE_APIENTRY glFramebufferTexture2DOES (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
FIXIE_API void FIXIE_APIENTRY glGetFramebufferAttachmentParameterivOES (GLenum target, GLenum attachment, GLenum pname, GLint* params);
FIXIE_API void FIXIE_APIENTRY glGenerateMipmapOES (GLenum target);
#endif
typedef GLboolean (FIXIE_APIENTRYP PFNGLISRENDERBUFFEROESPROC) (GLuint renderbuffer);
typedef void (FIXIE_APIENTRYP PFNGLBINDRENDERBUFFEROESPROC) (GLenum target, GLuint renderbuffer);
typedef void (FIXIE_APIENTRYP PFNGLDELETERENDERBUFFERSOESPROC) (GLsizei n, const GLuint* renderbuffers);
typedef void (FIXIE_APIENTRYP PFNGLGENRENDERBUFFERSOESPROC) (GLsizei n, GLuint* renderbuffers);
typedef void (FIXIE_APIENTRYP PFNGLRENDERBUFFERSTORAGEOESPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (FIXIE_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVOESPROC) (GLenum target, GLenum pname, GLint* params);
typedef GLboolean (FIXIE_APIENTRYP PFNGLISFRAMEBUFFEROESPROC) (GLuint framebuffer);
typedef void (FIXIE_APIENTRYP PFNGLBINDFRAMEBUFFEROESPROC) (GLenum target, GLuint framebuffer);
typedef void (FIXIE_APIENTRYP PFNGLDELETEFRAMEBUFFERSOESPROC) (GLsizei n, const GLuint* framebuffers);
typedef void (FIXIE_APIENTRYP PFNGLGENFRAMEBUFFERSOESPROC) (GLsizei n, GLuint* framebuffers);
typedef GLenum (FIXIE_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSOESPROC) (GLenum target);
typedef void (FIXIE_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFEROESPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
typedef void (FIXIE_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DOESPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
typedef void (FIXIE_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVOESPROC) (GLenum target, GLenum attachment, GLenum pname, GLint* params);
typedef void (FIXIE_APIENTRYP PFNGLGENERATEMIPMAPOESPROC) (GLenum target);
#endif

/* GL_OES_mapbuffer */
#ifndef GL_OES_mapbuffer
#define GL_OES_mapbuffer 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void* FIXIE_APIENTRY glMapBufferOES (GLenum target, GLenum access);
FIXIE_API GLboolean FIXIE_APIENTRY glUnmapBufferOES (GLenum target);
FIXIE_API void FIXIE_APIENTRY glGetBufferPointervOES (GLenum target, GLenum pname, GLvoid ** params);
#endif
typedef void* (FIXIE_APIENTRYP PFNGLMAPBUFFEROESPROC) (GLenum target, GLenum access);
typedef GLboolean (FIXIE_APIENTRYP PFNGLUNMAPBUFFEROESPROC) (GLenum target);
typedef void (FIXIE_APIENTRYP PFNGLGETBUFFERPOINTERVOESPROC) (GLenum target, GLenum pname, GLvoid ** params);
#endif

/* GL_OES_matrix_get */
#ifndef GL_OES_matrix_get
#define GL_OES_matrix_get 1
#endif

/* GL_OES_matrix_palette */
#ifndef GL_OES_matrix_palette
#define GL_OES_matrix_palette 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glCurrentPaletteMatrixOES (GLuint matrixpaletteindex);
FIXIE_API void FIXIE_APIENTRY glLoadPaletteFromModelViewMatrixOES (void);
FIXIE_API void FIXIE_APIENTRY glMatrixIndexPointerOES (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
FIXIE_API void FIXIE_APIENTRY glWeightPointerOES (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
#endif
typedef void (FIXIE_APIENTRYP PFNGLCURRENTPALETTEMATRIXOESPROC) (GLuint matrixpaletteindex);
typedef void (FIXIE_APIENTRYP PFNGLLOADPALETTEFROMMODELVIEWMATRIXOESPROC) (void);
typedef void (FIXIE_APIENTRYP PFNGLMATRIXINDEXPOINTEROESPROC) (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (FIXIE_APIENTRYP PFNGLWEIGHTPOINTEROESPROC) (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
#endif

/* GL_OES_packed_depth_stencil */
#ifndef GL_OES_packed_depth_stencil
#define GL_OES_packed_depth_stencil 1
#endif

/* GL_OES_required_internalformat */
#ifndef GL_OES_required_internalformat
#define GL_OES_required_internalformat 1
#endif

/* GL_OES_query_matrix */
#ifndef GL_OES_query_matrix
#define GL_OES_query_matrix 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API GLbitfield FIXIE_APIENTRY glQueryMatrixxOES (GLfixed mantissa[16], GLint exponent[16]);
#endif
typedef GLbitfield (FIXIE_APIENTRYP PFNGLQUERYMATRIXXOESPROC) (GLfixed mantissa[16], GLint exponent[16]);
#endif

/* GL_OES_rgb8_rgba8 */
#ifndef GL_OES_rgb8_rgba8
#define GL_OES_rgb8_rgba8 1
#endif

/* GL_OES_single_precision */
#ifndef GL_OES_single_precision
#define GL_OES_single_precision 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glDepthRangefOES (GLclampf zNear, GLclampf zFar);
FIXIE_API void FIXIE_APIENTRY glFrustumfOES (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
FIXIE_API void FIXIE_APIENTRY glOrthofOES (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
FIXIE_API void FIXIE_APIENTRY glClipPlanefOES (GLenum plane, const GLfloat *equation);
FIXIE_API void FIXIE_APIENTRY glGetClipPlanefOES (GLenum pname, GLfloat eqn[4]);
FIXIE_API void FIXIE_APIENTRY glClearDepthfOES (GLclampf depth);
#endif
typedef void (FIXIE_APIENTRYP PFNGLDEPTHRANGEFOESPROC) (GLclampf zNear, GLclampf zFar);
typedef void (FIXIE_APIENTRYP PFNGLFRUSTUMFOESPROC) (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
typedef void (FIXIE_APIENTRYP PFNGLORTHOFOESPROC) (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar);
typedef void (FIXIE_APIENTRYP PFNGLCLIPPLANEFOESPROC) (GLenum plane, const GLfloat *equation);
typedef void (FIXIE_APIENTRYP PFNGLGETCLIPPLANEFOESPROC) (GLenum pname, GLfloat eqn[4]);
typedef void (FIXIE_APIENTRYP PFNGLCLEARDEPTHFOESPROC) (GLclampf depth);
#endif

/* GL_OES_stencil1 */
#ifndef GL_OES_stencil1
#define GL_OES_stencil1 1
#endif

/* GL_OES_stencil4 */
#ifndef GL_OES_stencil4
#define GL_OES_stencil4 1
#endif

/* GL_OES_stencil8 */
#ifndef GL_OES_stencil8
#define GL_OES_stencil8 1
#endif

/* GL_OES_stencil_wrap */
#ifndef GL_OES_stencil_wrap
#define GL_OES_stencil_wrap 1
#endif

/* GL_OES_texture_cube_map */
#ifndef GL_OES_texture_cube_map
#define GL_OES_texture_cube_map 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glTexGenfOES (GLenum coord, GLenum pname, GLfloat param);
FIXIE_API void FIXIE_APIENTRY glTexGenfvOES (GLenum coord, GLenum pname, const GLfloat *params);
FIXIE_API void FIXIE_APIENTRY glTexGeniOES (GLenum coord, GLenum pname, GLint param);
FIXIE_API void FIXIE_APIENTRY glTexGenivOES (GLenum coord, GLenum pname, const GLint *params);
FIXIE_API void FIXIE_APIENTRY glTexGenxOES (GLenum coord, GLenum pname, GLfixed param);
FIXIE_API void FIXIE_APIENTRY glTexGenxvOES (GLenum coord, GLenum pname, const GLfixed *params);
FIXIE_API void FIXIE_APIENTRY glGetTexGenfvOES (GLenum coord, GLenum pname, GLfloat *params);
FIXIE_API void FIXIE_APIENTRY glGetTexGenivOES (GLenum coord, GLenum pname, GLint *params);
FIXIE_API void FIXIE_APIENTRY glGetTexGenxvOES (GLenum coord, GLenum pname, GLfixed *params);
#endif
typedef void (FIXIE_APIENTRYP PFNGLTEXGENFOESPROC) (GLenum coord, GLenum pname, GLfloat param);
typedef void (FIXIE_APIENTRYP PFNGLTEXGENFVOESPROC) (GLenum coord, GLenum pname, const GLfloat *params);
typedef void (FIXIE_APIENTRYP PFNGLTEXGENIOESPROC) (GLenum coord, GLenum pname, GLint param);
typedef void (FIXIE_APIENTRYP PFNGLTEXGENIVOESPROC) (GLenum coord, GLenum pname, const GLint *params);
typedef void (FIXIE_APIENTRYP PFNGLTEXGENXOESPROC) (GLenum coord, GLenum pname, GLfixed param);
typedef void (FIXIE_APIENTRYP PFNGLTEXGENXVOESPROC) (GLenum coord, GLenum pname, const GLfixed *params);
typedef void (FIXIE_APIENTRYP PFNGLGETTEXGENFVOESPROC) (GLenum coord, GLenum pname, GLfloat *params);
typedef void (FIXIE_APIENTRYP PFNGLGETTEXGENIVOESPROC) (GLenum coord, GLenum pname, GLint *params);
typedef void (FIXIE_APIENTRYP PFNGLGETTEXGENXVOESPROC) (GLenum coord, GLenum pname, GLfixed *params);
#endif

/* GL_OES_texture_env_crossbar */
#ifndef GL_OES_texture_env_crossbar
#define GL_OES_texture_env_crossbar 1
#endif

/* GL_OES_texture_mirrored_repeat */
#ifndef GL_OES_texture_mirrored_repeat
#define GL_OES_texture_mirrored_repeat 1
#endif

/* GL_OES_vertex_array_object */
#ifndef GL_OES_vertex_array_object
#define GL_OES_vertex_array_object 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glBindVertexArrayOES (GLuint array);
FIXIE_API void FIXIE_APIENTRY glDeleteVertexArraysOES (GLsizei n, const GLuint *arrays);
FIXIE_API void FIXIE_APIENTRY glGenVertexArraysOES (GLsizei n, GLuint *arrays);
FIXIE_API GLboolean FIXIE_APIENTRY glIsVertexArrayOES (GLuint array);
#endif
typedef void (FIXIE_APIENTRYP PFNGLBINDVERTEXARRAYOESPROC) (GLuint array);
typedef void (FIXIE_APIENTRYP PFNGLDELETEVERTEXARRAYSOESPROC) (GLsizei n, const GLuint *arrays);
typedef void (FIXIE_APIENTRYP PFNGLGENVERTEXARRAYSOESPROC) (GLsizei n, GLuint *arrays);
typedef GLboolean (FIXIE_APIENTRYP PFNGLISVERTEXARRAYOESPROC) (GLuint array);
#endif

/*------------------------------------------------------------------------*
 * AMD extension functions
 *------------------------------------------------------------------------*/

/* GL_AMD_compressed_3DC_texture */
#ifndef GL_AMD_compressed_3DC_texture
#define GL_AMD_compressed_3DC_texture 1
#endif

/* GL_AMD_compressed_ATC_texture */
#ifndef GL_AMD_compressed_ATC_texture
#define GL_AMD_compressed_ATC_texture 1
#endif

/*------------------------------------------------------------------------*
 * APPLE extension functions
 *------------------------------------------------------------------------*/

/* GL_APPLE_copy_texture_levels */
#ifndef GL_APPLE_copy_texture_levels
#define GL_APPLE_copy_texture_levels 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glCopyTextureLevelsAPPLE (GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei sourceLevelCount);
#endif
typedef void (FIXIE_APIENTRYP PFNGLCOPYTEXTURELEVELSAPPLEPROC) (GLuint destinationTexture, GLuint sourceTexture, GLint sourceBaseLevel, GLsizei sourceLevelCount);
#endif

/* GL_APPLE_framebuffer_multisample */
#ifndef GL_APPLE_framebuffer_multisample
#define GL_APPLE_framebuffer_multisample 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glRenderbufferStorageMultisampleAPPLE (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
FIXIE_API void FIXIE_APIENTRY glResolveMultisampleFramebufferAPPLE (void);
#endif /* GL_GLEXT_PROTOTYPES */
typedef void (FIXIE_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEAPPLEPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (FIXIE_APIENTRYP PFNGLRESOLVEMULTISAMPLEFRAMEBUFFERAPPLEPROC) (void);
#endif

/* GL_APPLE_sync */
#ifndef GL_APPLE_sync
#define GL_APPLE_sync 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API GLsync FIXIE_APIENTRY glFenceSyncAPPLE (GLenum condition, GLbitfield flags);
FIXIE_API GLboolean FIXIE_APIENTRY glIsSyncAPPLE (GLsync sync);
FIXIE_API void FIXIE_APIENTRY glDeleteSyncAPPLE (GLsync sync);
FIXIE_API GLenum FIXIE_APIENTRY glClientWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
FIXIE_API void FIXIE_APIENTRY glWaitSyncAPPLE (GLsync sync, GLbitfield flags, GLuint64 timeout);
FIXIE_API void FIXIE_APIENTRY glGetInteger64vAPPLE (GLenum pname, GLint64 *params);
FIXIE_API void FIXIE_APIENTRY glGetSyncivAPPLE (GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);
#endif
typedef GLsync (FIXIE_APIENTRYP PFNGLFENCESYNCAPPLEPROC) (GLenum condition, GLbitfield flags);
typedef GLboolean (FIXIE_APIENTRYP PFNGLISSYNCAPPLEPROC) (GLsync sync);
typedef void (FIXIE_APIENTRYP PFNGLDELETESYNCAPPLEPROC) (GLsync sync);
typedef GLenum (FIXIE_APIENTRYP PFNGLCLIENTWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (FIXIE_APIENTRYP PFNGLWAITSYNCAPPLEPROC) (GLsync sync, GLbitfield flags, GLuint64 timeout);
typedef void (FIXIE_APIENTRYP PFNGLGETINTEGER64VAPPLEPROC) (GLenum pname, GLint64 *params);
typedef void (FIXIE_APIENTRYP PFNGLGETSYNCIVAPPLEPROC) (GLsync sync, GLenum pname, GLsizei bufSize, GLsizei *length, GLint *values);
#endif

/* GL_APPLE_texture_2D_limited_npot */
#ifndef GL_APPLE_texture_2D_limited_npot
#define GL_APPLE_texture_2D_limited_npot 1
#endif

/* GL_APPLE_texture_format_BGRA8888 */
#ifndef GL_APPLE_texture_format_BGRA8888
#define GL_APPLE_texture_format_BGRA8888 1
#endif

/* GL_APPLE_texture_max_level */
#ifndef GL_APPLE_texture_max_level
#define GL_APPLE_texture_max_level 1
#endif

/*------------------------------------------------------------------------*
 * ARM extension functions
 *------------------------------------------------------------------------*/

/* GL_ARM_rgba8 */
#ifndef GL_ARM_rgba8
#define GL_ARM_rgba8 1
#endif

/*------------------------------------------------------------------------*
 * EXT extension functions
 *------------------------------------------------------------------------*/

/* GL_EXT_blend_minmax */
#ifndef GL_EXT_blend_minmax
#define GL_EXT_blend_minmax 1
#endif

/* GL_EXT_discard_framebuffer */
#ifndef GL_EXT_discard_framebuffer
#define GL_EXT_discard_framebuffer 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glDiscardFramebufferEXT (GLenum target, GLsizei numAttachments, const GLenum *attachments);
#endif
typedef void (FIXIE_APIENTRYP PFNGLDISCARDFRAMEBUFFEREXTPROC) (GLenum target, GLsizei numAttachments, const GLenum *attachments);
#endif

/* GL_EXT_map_buffer_range */
#ifndef GL_EXT_map_buffer_range
#define GL_EXT_map_buffer_range 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY *glMapBufferRangeEXT (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
FIXIE_API void FIXIE_APIENTRY glFlushMappedBufferRangeEXT (GLenum target, GLintptr offset, GLsizeiptr length);
#endif
typedef void* (FIXIE_APIENTRYP PFNGLMAPBUFFERRANGEEXTPROC) (GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
typedef void (FIXIE_APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEEXTPROC) (GLenum target, GLintptr offset, GLsizeiptr length);
#endif

/* GL_EXT_multisampled_render_to_texture */
#ifndef GL_EXT_multisampled_render_to_texture
#define GL_EXT_multisampled_render_to_texture 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glRenderbufferStorageMultisampleEXT (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
FIXIE_API void FIXIE_APIENTRY glFramebufferTexture2DMultisampleEXT (GLenum, GLenum, GLenum, GLuint, GLint, GLsizei);
#endif
typedef void (FIXIE_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (FIXIE_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#endif

/* GL_EXT_multi_draw_arrays */
#ifndef GL_EXT_multi_draw_arrays
#define GL_EXT_multi_draw_arrays 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glMultiDrawArraysEXT (GLenum, const GLint *, const GLsizei *, GLsizei);
FIXIE_API void FIXIE_APIENTRY glMultiDrawElementsEXT (GLenum, const GLsizei *, GLenum, const GLvoid* *, GLsizei);
#endif /* GL_GLEXT_PROTOTYPES */
typedef void (FIXIE_APIENTRYP PFNGLMULTIDRAWARRAYSEXTPROC) (GLenum mode, const GLint *first, const GLsizei *count, GLsizei primcount);
typedef void (FIXIE_APIENTRYP PFNGLMULTIDRAWELEMENTSEXTPROC) (GLenum mode, const GLsizei *count, GLenum type, const GLvoid* *indices, GLsizei primcount);
#endif

/* GL_EXT_read_format_bgra */
#ifndef GL_EXT_read_format_bgra
#define GL_EXT_read_format_bgra 1
#endif

/* GL_EXT_robustness */
#ifndef GL_EXT_robustness
#define GL_EXT_robustness 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API GLenum FIXIE_APIENTRY glGetGraphicsResetStatusEXT (void);
FIXIE_API void FIXIE_APIENTRY glReadnPixelsEXT (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data);
FIXIE_API void FIXIE_APIENTRY glGetnUniformfvEXT (GLuint program, GLint location, GLsizei bufSize, float *params);
FIXIE_API void FIXIE_APIENTRY glGetnUniformivEXT (GLuint program, GLint location, GLsizei bufSize, GLint *params);
#endif
typedef GLenum (FIXIE_APIENTRYP PFNGLGETGRAPHICSRESETSTATUSEXTPROC) (void);
typedef void (FIXIE_APIENTRYP PFNGLREADNPIXELSEXTPROC) (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data);
typedef void (FIXIE_APIENTRYP PFNGLGETNUNIFORMFVEXTPROC) (GLuint program, GLint location, GLsizei bufSize, float *params);
typedef void (FIXIE_APIENTRYP PFNGLGETNUNIFORMIVEXTPROC) (GLuint program, GLint location, GLsizei bufSize, GLint *params);
#endif

/* GL_EXT_sRGB */
#ifndef GL_EXT_sRGB
#define GL_EXT_sRGB 1
#endif

/* GL_EXT_texture_compression_dxt1 */
#ifndef GL_EXT_texture_compression_dxt1
#define GL_EXT_texture_compression_dxt1 1
#endif

/* GL_EXT_texture_filter_anisotropic */
#ifndef GL_EXT_texture_filter_anisotropic
#define GL_EXT_texture_filter_anisotropic 1
#endif

/* GL_EXT_texture_format_BGRA8888 */
#ifndef GL_EXT_texture_format_BGRA8888
#define GL_EXT_texture_format_BGRA8888 1
#endif

/* GL_EXT_texture_lod_bias */
#ifndef GL_EXT_texture_lod_bias
#define GL_EXT_texture_lod_bias 1
#endif

/* GL_EXT_texture_storage */
#ifndef GL_EXT_texture_storage
#define GL_EXT_texture_storage 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glTexStorage1DEXT (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
FIXIE_API void FIXIE_APIENTRY glTexStorage2DEXT (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
FIXIE_API void FIXIE_APIENTRY glTexStorage3DEXT (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
FIXIE_API void FIXIE_APIENTRY glTextureStorage1DEXT (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
FIXIE_API void FIXIE_APIENTRY glTextureStorage2DEXT (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
FIXIE_API void FIXIE_APIENTRY glTextureStorage3DEXT (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
#endif
typedef void (FIXIE_APIENTRYP PFNGLTEXSTORAGE1DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (FIXIE_APIENTRYP PFNGLTEXSTORAGE2DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (FIXIE_APIENTRYP PFNGLTEXSTORAGE3DEXTPROC) (GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
typedef void (FIXIE_APIENTRYP PFNGLTEXTURESTORAGE1DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
typedef void (FIXIE_APIENTRYP PFNGLTEXTURESTORAGE2DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (FIXIE_APIENTRYP PFNGLTEXTURESTORAGE3DEXTPROC) (GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
#endif

/*------------------------------------------------------------------------*
 * IMG extension functions
 *------------------------------------------------------------------------*/

/* GL_IMG_read_format */
#ifndef GL_IMG_read_format
#define GL_IMG_read_format 1
#endif

/* GL_IMG_texture_compression_pvrtc */
#ifndef GL_IMG_texture_compression_pvrtc
#define GL_IMG_texture_compression_pvrtc 1
#endif

/* GL_IMG_texture_env_enhanced_fixed_function */
#ifndef GL_IMG_texture_env_enhanced_fixed_function
#define GL_IMG_texture_env_enhanced_fixed_function 1
#endif

/* GL_IMG_user_clip_plane */
#ifndef GL_IMG_user_clip_plane
#define GL_IMG_user_clip_plane 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glClipPlanefIMG (GLenum, const GLfloat *);
FIXIE_API void FIXIE_APIENTRY glClipPlanexIMG (GLenum, const GLfixed *);
#endif
typedef void (FIXIE_APIENTRYP PFNGLCLIPPLANEFIMGPROC) (GLenum p, const GLfloat *eqn);
typedef void (FIXIE_APIENTRYP PFNGLCLIPPLANEXIMGPROC) (GLenum p, const GLfixed *eqn);
#endif

/* GL_IMG_multisampled_render_to_texture */
#ifndef GL_IMG_multisampled_render_to_texture
#define GL_IMG_multisampled_render_to_texture 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glRenderbufferStorageMultisampleIMG (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
FIXIE_API void FIXIE_APIENTRY glFramebufferTexture2DMultisampleIMG (GLenum, GLenum, GLenum, GLuint, GLint, GLsizei);
#endif
typedef void (FIXIE_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEIMGPROC) (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (FIXIE_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEIMGPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#endif

/*------------------------------------------------------------------------*
 * NV extension functions
 *------------------------------------------------------------------------*/

/* NV_fence */
#ifndef GL_NV_fence
#define GL_NV_fence 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glDeleteFencesNV (GLsizei, const GLuint *);
FIXIE_API void FIXIE_APIENTRY glGenFencesNV (GLsizei, GLuint *);
FIXIE_API GLboolean FIXIE_APIENTRY glIsFenceNV (GLuint);
FIXIE_API GLboolean FIXIE_APIENTRY glTestFenceNV (GLuint);
FIXIE_API void FIXIE_APIENTRY glGetFenceivNV (GLuint, GLenum, GLint *);
FIXIE_API void FIXIE_APIENTRY glFinishFenceNV (GLuint);
FIXIE_API void FIXIE_APIENTRY glSetFenceNV (GLuint, GLenum);
#endif
typedef void (FIXIE_APIENTRYP PFNGLDELETEFENCESNVPROC) (GLsizei n, const GLuint *fences);
typedef void (FIXIE_APIENTRYP PFNGLGENFENCESNVPROC) (GLsizei n, GLuint *fences);
typedef GLboolean (FIXIE_APIENTRYP PFNGLISFENCENVPROC) (GLuint fence);
typedef GLboolean (FIXIE_APIENTRYP PFNGLTESTFENCENVPROC) (GLuint fence);
typedef void (FIXIE_APIENTRYP PFNGLGETFENCEIVNVPROC) (GLuint fence, GLenum pname, GLint *params);
typedef void (FIXIE_APIENTRYP PFNGLFINISHFENCENVPROC) (GLuint fence);
typedef void (FIXIE_APIENTRYP PFNGLSETFENCENVPROC) (GLuint fence, GLenum condition);
#endif

/*------------------------------------------------------------------------*
 * QCOM extension functions
 *------------------------------------------------------------------------*/

/* GL_QCOM_driver_control */
#ifndef GL_QCOM_driver_control
#define GL_QCOM_driver_control 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glGetDriverControlsQCOM (GLint *num, GLsizei size, GLuint *driverControls);
FIXIE_API void FIXIE_APIENTRY glGetDriverControlStringQCOM (GLuint driverControl, GLsizei bufSize, GLsizei *length, GLchar *driverControlString);
FIXIE_API void FIXIE_APIENTRY glEnableDriverControlQCOM (GLuint driverControl);
FIXIE_API void FIXIE_APIENTRY glDisableDriverControlQCOM (GLuint driverControl);
#endif
typedef void (FIXIE_APIENTRYP PFNGLGETDRIVERCONTROLSQCOMPROC) (GLint *num, GLsizei size, GLuint *driverControls);
typedef void (FIXIE_APIENTRYP PFNGLGETDRIVERCONTROLSTRINGQCOMPROC) (GLuint driverControl, GLsizei bufSize, GLsizei *length, GLchar *driverControlString);
typedef void (FIXIE_APIENTRYP PFNGLENABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
typedef void (FIXIE_APIENTRYP PFNGLDISABLEDRIVERCONTROLQCOMPROC) (GLuint driverControl);
#endif

/* GL_QCOM_extended_get */
#ifndef GL_QCOM_extended_get
#define GL_QCOM_extended_get 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glExtGetTexturesQCOM (GLuint *textures, GLint maxTextures, GLint *numTextures);
FIXIE_API void FIXIE_APIENTRY glExtGetBuffersQCOM (GLuint *buffers, GLint maxBuffers, GLint *numBuffers);
FIXIE_API void FIXIE_APIENTRY glExtGetRenderbuffersQCOM (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *numRenderbuffers);
FIXIE_API void FIXIE_APIENTRY glExtGetFramebuffersQCOM (GLuint *framebuffers, GLint maxFramebuffers, GLint *numFramebuffers);
FIXIE_API void FIXIE_APIENTRY glExtGetTexLevelParameterivQCOM (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
FIXIE_API void FIXIE_APIENTRY glExtTexObjectStateOverrideiQCOM (GLenum target, GLenum pname, GLint param);
FIXIE_API void FIXIE_APIENTRY glExtGetTexSubImageQCOM (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLvoid *texels);
FIXIE_API void FIXIE_APIENTRY glExtGetBufferPointervQCOM (GLenum target, GLvoid **params);
#endif
typedef void (FIXIE_APIENTRYP PFNGLEXTGETTEXTURESQCOMPROC) (GLuint *textures, GLint maxTextures, GLint *numTextures);
typedef void (FIXIE_APIENTRYP PFNGLEXTGETBUFFERSQCOMPROC) (GLuint *buffers, GLint maxBuffers, GLint *numBuffers);
typedef void (FIXIE_APIENTRYP PFNGLEXTGETRENDERBUFFERSQCOMPROC) (GLuint *renderbuffers, GLint maxRenderbuffers, GLint *numRenderbuffers);
typedef void (FIXIE_APIENTRYP PFNGLEXTGETFRAMEBUFFERSQCOMPROC) (GLuint *framebuffers, GLint maxFramebuffers, GLint *numFramebuffers);
typedef void (FIXIE_APIENTRYP PFNGLEXTGETTEXLEVELPARAMETERIVQCOMPROC) (GLuint texture, GLenum face, GLint level, GLenum pname, GLint *params);
typedef void (FIXIE_APIENTRYP PFNGLEXTTEXOBJECTSTATEOVERRIDEIQCOMPROC) (GLenum target, GLenum pname, GLint param);
typedef void (FIXIE_APIENTRYP PFNGLEXTGETTEXSUBIMAGEQCOMPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLvoid *texels);
typedef void (FIXIE_APIENTRYP PFNGLEXTGETBUFFERPOINTERVQCOMPROC) (GLenum target, GLvoid **params);
#endif

/* GL_QCOM_extended_get2 */
#ifndef GL_QCOM_extended_get2
#define GL_QCOM_extended_get2 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glExtGetShadersQCOM (GLuint *shaders, GLint maxShaders, GLint *numShaders);
FIXIE_API void FIXIE_APIENTRY glExtGetProgramsQCOM (GLuint *programs, GLint maxPrograms, GLint *numPrograms);
FIXIE_API GLboolean FIXIE_APIENTRY glExtIsProgramBinaryQCOM (GLuint program);
FIXIE_API void FIXIE_APIENTRY glExtGetProgramBinarySourceQCOM (GLuint program, GLenum shadertype, GLchar *source, GLint *length);
#endif
typedef void (FIXIE_APIENTRYP PFNGLEXTGETSHADERSQCOMPROC) (GLuint *shaders, GLint maxShaders, GLint *numShaders);
typedef void (FIXIE_APIENTRYP PFNGLEXTGETPROGRAMSQCOMPROC) (GLuint *programs, GLint maxPrograms, GLint *numPrograms);
typedef GLboolean (FIXIE_APIENTRYP PFNGLEXTISPROGRAMBINARYQCOMPROC) (GLuint program);
typedef void (FIXIE_APIENTRYP PFNGLEXTGETPROGRAMBINARYSOURCEQCOMPROC) (GLuint program, GLenum shadertype, GLchar *source, GLint *length);
#endif

/* GL_QCOM_perfmon_global_mode */
#ifndef GL_QCOM_perfmon_global_mode
#define GL_QCOM_perfmon_global_mode 1
#endif

/* GL_QCOM_writeonly_rendering */
#ifndef GL_QCOM_writeonly_rendering
#define GL_QCOM_writeonly_rendering 1
#endif

/* GL_QCOM_tiled_rendering */
#ifndef GL_QCOM_tiled_rendering
#define GL_QCOM_tiled_rendering 1
#ifdef GL_GLEXT_PROTOTYPES
FIXIE_API void FIXIE_APIENTRY glStartTilingQCOM (GLuint x, GLuint y, GLuint width, GLuint height, GLbitfield preserveMask);
FIXIE_API void FIXIE_APIENTRY glEndTilingQCOM (GLbitfield preserveMask);
#endif
typedef void (FIXIE_APIENTRYP PFNGLSTARTTILINGQCOMPROC) (GLuint x, GLuint y, GLuint width, GLuint height, GLbitfield preserveMask);
typedef void (FIXIE_APIENTRYP PFNGLENDTILINGQCOMPROC) (GLbitfield preserveMask);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __glext_h_ */

#endif // _FIXIE_GL_ES_EXT_H_
