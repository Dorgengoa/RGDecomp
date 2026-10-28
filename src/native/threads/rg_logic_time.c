/* SPDX-License-Identifier: CC0-1.0
 * Native logic-time frame clock: the game's timer-0 accesses without the hwbus
 * (docs/NATIVE-CPU.md section 8, docs/NATIVE-THREADS.md "T0..T3 register model").
 *
 * Retail measures its frames with timer 0 counting horizontal lines (T0_MODE = 0x83, set
 * once by GfxSysInit_15dd20): GfxEndFrame_141c20 reads T0_COUNT and resets it to 0,
 * GfxFlipBuffersMaybe_143650 reads it twice, Vif1IntcHandler_15e170 latches it when the
 * frame's GPU work ends.  include/port/hwaccess.h routes exactly these constant-address
 * accesses (T0_COUNT read / write, T0_MODE write) here, so the bus never sees them.
 *
 * Native kernel (RG_THREADS=native; the only kernel of an RG_NATIVE_ONLY build): the
 * native kernel table's timer 0 over LOGIC time (src/native/threads/rg_nk_irq.c): a flow's
 * own work costs nothing, so the game reads the nominal frame profile, independent of host
 * speed and render cost.  No bus, no register router.
 * Oracle kernels (default builds, RG_THREADS=hle|service|frame): through the hwbus exactly
 * as before (its per-read charge is part of those modes' virtual timing), so their run
 * hashes do not move.  RG_THREADS_ORACLE=0 compiles that branch out (no hwbus reference).
 */
#include <stdint.h>

#include "ps2k.h"
#include "rg_threads_oracle.h"

#define T0_COUNT 0x10000000u
#define T0_MODE 0x10000010u

#if RG_THREADS_ORACLE
/* src/ps2/hwbus (declared here: the bus library is not a dependency of this one; rg-game
 * links it in default builds) */
uint32_t hw_r32(uint32_t addr);
void hw_w32(uint32_t addr, uint32_t v);
#define RG_LT_ORACLE() (!ps2k_native())
#endif

unsigned int rg_logic_t0_count(void)
{
#if RG_THREADS_ORACLE
    if (RG_LT_ORACLE())
        return hw_r32(T0_COUNT);
#endif
    return ps2k_hw_read32(T0_COUNT);
}

void rg_logic_t0_set_count(unsigned int v)
{
#if RG_THREADS_ORACLE
    if (RG_LT_ORACLE()) {
        hw_w32(T0_COUNT, v);
        return;
    }
#endif
    ps2k_hw_write32(T0_COUNT, v);
}

void rg_logic_t0_set_mode(unsigned int mode)
{
#if RG_THREADS_ORACLE
    if (RG_LT_ORACLE()) {
        hw_w32(T0_MODE, mode);
        return;
    }
#endif
    ps2k_hw_write32(T0_MODE, mode);
}
