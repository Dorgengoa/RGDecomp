/* SPDX-License-Identifier: CC0-1.0 */
/* Native renderer: the dominant VU1 program's constant block filled on the EE
 * side from the game's packet builders (docs/NATIVE-RENDER.md "Constants
 * from the game", slice 1).
 *
 * The VU1 data memory the model program reads (qwords 0..111 and the bone
 * rows 768..899) is written by a handful of game builders, each producing one
 * small fixed-layout packet (STCYCL 1,1 + UNPACK V4-32 + data):
 *
 *   CameraWriteViewPacket_148740   qw 0-19   (projection, screen, tag templates)
 *   DrawPktBuildCameraMatrix_1486c0 qw 24-28 (view matrix)
 *   LightStateWritePacket_1484a0   qw 30-51  (lights, fog, material colours)
 *   VifPktUploadMatrix_148440      qw 60-63 + MSCAL 0 (object matrix; the VU
 *                                  program at 0 derives 64-75, 100-102, 111.z)
 *   model v14 (ModelMeshWriteVuHeaderMaybe_15b1d0 ...) qw 76-79, 81, 42
 *   ModelBuildSkinMtxPacketMaybe_150390               bone rows 768+
 *   MeshMaterialBuildPkt_14ac90 / TexEnvBuildDmaChainMaybe_14abb0 qw 82-88
 *
 * nr_const_* reads those builders' outputs at record time (the same moment
 * the draw list is built), so a native mesh needs neither the VIF nor VU1:
 * nothing is taken from VU memory.  The MSCAL 0 program is nr_const_prog0
 * (transcribed from the runtime-uploaded VU1 program at address 0; listing in
 * the doc).  Anything outside the builders' layout (other VIF commands, masks,
 * cycle modes, double-buffered addresses) makes the scan fail and the mesh
 * stays on the emulated path. */
#ifndef RG_NR_CONST_H
#define RG_NR_CONST_H

#include <stdint.h>

#include "nr_vu1.h"

#ifdef __cplusplus
extern "C" {
#endif

enum { NR_BONE_ROW0 = 768, NR_BONE_ROWS = 256 };   /* rows 768..1023 (skin indices wrap at 1024) */

typedef struct nr_cblock {
    nr_qw c[NRQ_CONST_N];          /* VU qwords 0..111 */
    nr_qw bones[NR_BONE_ROWS];     /* VU qwords 768..899 */
    uint8_t wr[NRQ_CONST_N];       /* qwords some scanned packet wrote */
    uint32_t bones_hi;             /* bone rows written: 768 .. 768 + bones_hi - 1 */
} nr_cblock;

/* Apply the packet at host address pkt (a DMA chain: CNT/REF/CALL/RET/END
 * tags whose two VIF words and payload are interpreted) to b.  MSCAL 0 runs
 * nr_const_prog0.  Returns 0, or a negative code when the packet holds
 * something outside the builders' layout (b is then partially updated). */
int nr_const_apply(nr_cblock *b, uint32_t pkt);
/* Packets the renderer keeps across frames (the camera / light / plane packet a draw context
 * built last, every light packet by address) are copied when they are built, never re-read
 * from game memory later: the game reuses that memory, and a re-read walked garbage tags into
 * unmapped memory (1025b shop-close crash; nr_scene.c "Packets the renderer remembers",
 * docs/NATIVE-RENDER.md "Constants from the game").  nr_const_inline_bytes: the size of the packet at pkt when it is one RET / END tag
 * with its payload inline (what the builders write) and fits max_bytes, else 0.
 * nr_const_apply_inline: nr_const_apply on such a copy. */
uint32_t nr_const_inline_bytes(uint32_t pkt, uint32_t max_bytes);
int nr_const_apply_inline(nr_cblock *b, const void *copy, uint32_t bytes);
/* the VU1 program at address 0 (MSCAL 0 after the object matrix upload):
 * normalised rotation 64-66, screen matrix 68-71, clip matrix 72-75, light
 * directions in object space 100-102, handedness 111.z */
void nr_const_prog0(nr_cblock *b);
/* text for a nr_const_apply error code */
const char *nr_const_err(int code);

#ifdef __cplusplus
}
#endif
#endif
