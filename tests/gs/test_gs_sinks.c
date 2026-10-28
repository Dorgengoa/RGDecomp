/* SPDX-License-Identifier: CC0-1.0 */
/* The GS adapters must match the VU/VIF models' sink types exactly.  This
 * file includes their headers only (no link dependency): a signature change
 * on either side breaks the build here. */
#include "gs_test_util.h"
#include "vu.h"
#include "vif.h"

static const vu_gif_sink_fn k_vu_sink = gs_vu1_gif_sink;
static const vif_gif_sink_fn k_vif_sink = gs_vif1_gif_sink;

int test_sinks(const char *name)
{
    if (strcmp(name, "gif_sinks")) return 0;
    gs_state *gs = gs_create();
    uint64_t pkt[4] = { 1 | (1ull << 15) | (1ull << 60), 0xE, 0x123, GS_FOGCOL };
    k_vif_sink(gs, (const uint8_t *)pkt, 32);
    CHECK_EQ(gs->reg[GS_FOGCOL], 0x123);
    CHECK_EQ(gs->path[GS_PATH2].packets, 1);
    pkt[2] = 0x456;
    k_vu_sink(gs, (const uint8_t *)pkt, 32, 0x3F0);
    CHECK_EQ(gs->reg[GS_FOGCOL], 0x456);
    CHECK_EQ(gs->path[GS_PATH1].packets, 1);
    gs_destroy(gs);
    return 1;
}
