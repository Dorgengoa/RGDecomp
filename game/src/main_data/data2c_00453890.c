/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
extern unsigned char data2c_main_bss[];
/* Generated: do not edit. */
#include "types.h"
extern u8 D_00480000[];
u32 D_00453890[20] __attribute__((section(".data$rg00453890"), aligned(16))) = {
    @X@00453890@, @X@00453894@, @X@00453898@, @X@0045389C@, @X@004538A0@, (u32)&D_00480000, (u32)(data2c_main_bss + 0x3EF85), @X@004538AC@, @X@004538B0@, (u32)(data2c_main_bss + 0x3EF86), @X@004538B8@, @X@004538BC@, (u32)(data2c_main_bss + 0x3EF88), @X@004538C4@, @X@004538C8@, @X@004538CC@, @X@004538D0@, @X@004538D4@, @X@004538D8@, @X@004538DC@
};
typedef char data2c_sizecheck_00453890[(sizeof(D_00453890) == 80) ? 1 : -1];
