/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
extern unsigned char data2c_main_bss[];
/* Generated: do not edit. */
#include "types.h"
extern u8 D_00480000[];
u32 D_00450870[20] __attribute__((section(".data$rg00450870"), aligned(16))) = {
    @X@00450870@, @X@00450874@, @X@00450878@, @X@0045087C@, @X@00450880@, (u32)&D_00480000, (u32)(data2c_main_bss + 0x3EF85), @X@0045088C@, @X@00450890@, (u32)(data2c_main_bss + 0x3EF86), @X@00450898@, @X@0045089C@, (u32)(data2c_main_bss + 0x3EF88), @X@004508A4@, @X@004508A8@, @X@004508AC@, @X@004508B0@, @X@004508B4@, @X@004508B8@, @X@004508BC@
};
typedef char data2c_sizecheck_00450870[(sizeof(D_00450870) == 80) ? 1 : -1];
