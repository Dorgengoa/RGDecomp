/* SPDX-License-Identifier: CC0-1.0 */
/* Named VU0 register contexts for the cross-file register protocols
 * (port/vu0_ctx.h, docs/NATIVE-CPU.md "Cross-file protocols").  With
 * RG_VU0_LOCAL each game file has a private register file; the functions of
 * one protocol below share one of these instead:
 *   xfbox    AabbLoadToVu_13bfc0 / BoxToCenterExtentsVu0Maybe_14ff40 load a
 *            box and a matrix into vf7, vf10-vf12 for AabbPlaneDistances_13bf50
 *            / BoxTransformExtentsVu0Maybe_14fed0 (called right after, from
 *            AabbInFrustum_13be60 / ModelPrepareDrawMaybe_14f760);
 *   colltri  CollFrameTreeCollectTris_16bfb0 loads a matrix into vf10-vf13
 *            for CollTriTransform_16c1a0 (called in its loop).
 * vf0 is the constant (0, 0, 0, 1) as in every register file. */
#include "port/vu0.h"

#define RG_VU0_CTX_DEF(name) \
    rg_vu0_state rg_vu0_ctx_##name = { .vf = { [0] = { .f = { 0.0f, 0.0f, 0.0f, 1.0f } } } }

RG_VU0_CTX_DEF(xfbox);
RG_VU0_CTX_DEF(colltri);
