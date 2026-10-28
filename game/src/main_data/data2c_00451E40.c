/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
extern unsigned char data2c_gap_00461E58[];
/* Generated: do not edit. */
#include "types.h"

u32 D_00451E40[8] __attribute__((section(".data$rg00451E40"), aligned(16))) = {
    (u32)((u8 *)&data2c_gap_00461E58 + 0x50), @X@00451E44@, (u32)((u8 *)&data2c_gap_00461E58 + 0x58), @X@00451E4C@, (u32)((u8 *)&data2c_gap_00461E58 + 0x60), @X@00451E54@, @X@00451E58@, @X@00451E5C@
};
typedef char data2c_sizecheck_00451E40[(sizeof(D_00451E40) == 32) ? 1 : -1];
