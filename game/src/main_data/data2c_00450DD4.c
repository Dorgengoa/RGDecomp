/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
extern unsigned char data2c_main_bss[];
/* Generated: do not edit. */
#include "types.h"

u32 data2c_gap_00450DD4[7] __attribute__((section(".data$rg00450DD4"))) = {
    (u32)(data2c_main_bss + 0x1EF85), @X@00450DD8@, (u32)(data2c_main_bss + 0x5EF84), @X@00450DE0@, @X@00450DE4@, @X@00450DE8@, @X@00450DEC@
};
typedef char data2c_sizecheck_00450DD4[(sizeof(data2c_gap_00450DD4) == 28) ? 1 : -1];
