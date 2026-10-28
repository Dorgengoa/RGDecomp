/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
extern unsigned char data2c_main_bss[];
/* Generated: do not edit. */
#include "types.h"
extern u8 D_00480000[];
u32 D_00453CD0[20] __attribute__((section(".data$rg00453CD0"), aligned(16))) = {
    @X@00453CD0@, @X@00453CD4@, @X@00453CD8@, @X@00453CDC@, @X@00453CE0@, (u32)&D_00480000, (u32)(data2c_main_bss + 0x3EF85), @X@00453CEC@, @X@00453CF0@, (u32)(data2c_main_bss + 0x3EF86), @X@00453CF8@, @X@00453CFC@, (u32)(data2c_main_bss + 0x3EF88), @X@00453D04@, @X@00453D08@, @X@00453D0C@, @X@00453D10@, @X@00453D14@, @X@00453D18@, @X@00453D1C@
};
typedef char data2c_sizecheck_00453CD0[(sizeof(D_00453CD0) == 80) ? 1 : -1];
