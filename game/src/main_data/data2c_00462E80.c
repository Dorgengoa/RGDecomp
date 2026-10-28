/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
extern unsigned char data2c_main_bss[];
/* Generated: do not edit. */
#include "types.h"

u32 D_00462E80[4] __attribute__((section(".data$rg00462E80"), aligned(16))) = {
    @X@00462E80@, @X@00462E84@, @X@00462E88@, (u32)(data2c_main_bss + 0x24B01)
};
typedef char data2c_sizecheck_00462E80[(sizeof(D_00462E80) == 16) ? 1 : -1];
