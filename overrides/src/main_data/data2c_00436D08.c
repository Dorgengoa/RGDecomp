/* rg-override: replaces game/src/main_data/data2c_00436D08.c sha256 80ff8d70bac2ce1fb4132b88af64fbe5c8e89a6f4d1203cd9732a1be06d506bb
 * why: VU1 microcode words at 0x436D10 (lower 0x09044801, upper NOP) were emitted as a zero gap-pad */
/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

u32 func_00436D08[2] __attribute__((section(".data$rg00436D08"), aligned(8))) = {
    @X@00436D08@, @X@00436D0C@
};
typedef char data2c_sizecheck_00436D08[(sizeof(func_00436D08) == 8) ? 1 : -1];
/* gap 0x00436D10..0x00436D18 (datareloc: retail offsets) */
static unsigned char rg_pad_00436D10[0x8] __attribute__((section(".data$rg00436D10"), used)) = {
    0x01, 0x48, 0x04, 0x09, 0xFF, 0x02, 0x00, 0x00 /* retail: 0x09044801, 0x000002FF */
};
