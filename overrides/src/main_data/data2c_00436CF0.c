/* rg-override: replaces game/src/main_data/data2c_00436CF0.c sha256 5145460a36c4e40632eb27fef3fe63cbf7e3b24ed44e25bd2078568fcaaa5a01
 * why: VU1 microcode words at 0x436D00 (lower 0x09070057, upper NOP) were emitted as a zero gap-pad;
 * the 0x320 model program then ran without them (garbage vi04, stray stores, broken GIF tags) */
/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"

u32 func_00436CF0[4] __attribute__((section(".data$rg00436CF0"), aligned(16))) = {
    @X@00436CF0@, @X@00436CF4@, @X@00436CF8@, @X@00436CFC@
};
typedef char data2c_sizecheck_00436CF0[(sizeof(func_00436CF0) == 16) ? 1 : -1];
/* gap 0x00436D00..0x00436D08 (datareloc: retail offsets) */
static unsigned char rg_pad_00436D00[0x8] __attribute__((section(".data$rg00436D00"), used)) = {
    0x57, 0x00, 0x07, 0x09, 0xFF, 0x02, 0x00, 0x00 /* retail: 0x09070057, 0x000002FF */
};
