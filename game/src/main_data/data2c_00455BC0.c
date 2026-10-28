/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
extern unsigned char D_00455B20[];
/* Generated: do not edit. */
#include "types.h"

u32 func_00455BC0[3] __attribute__((section(".data$rg00455BC0"), aligned(16))) = {
    @X@00455BC0@, @X@00455BC4@, (u32)((u8 *)&D_00455B20 + 0x40)
};
typedef char data2c_sizecheck_00455BC0[(sizeof(func_00455BC0) == 12) ? 1 : -1];
