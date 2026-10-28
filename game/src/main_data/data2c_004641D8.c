/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
extern unsigned char data2c_main_bss[];
/* Generated: do not edit. */
#include "types.h"

u32 D_004641D8[12] __attribute__((section(".data$rg004641D8"), aligned(8))) = {
    @X@004641D8@, @X@004641DC@, @X@004641E0@, @X@004641E4@, (u32)(data2c_main_bss + 0x233C1), @X@004641EC@, @X@004641F0@, @X@004641F4@, @X@004641F8@, @X@004641FC@, (u32)(data2c_main_bss + 0x43EC3), @X@00464204@
};
typedef char data2c_sizecheck_004641D8[(sizeof(D_004641D8) == 48) ? 1 : -1];
