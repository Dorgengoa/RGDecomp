/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
extern unsigned char data2c_main_bss[];
/* Generated: do not edit. */
#include "types.h"
extern u8 D_00480000[];
u32 D_00450D80[20] __attribute__((section(".data$rg00450D80"), aligned(16))) = {
    @X@00450D80@, @X@00450D84@, @X@00450D88@, @X@00450D8C@, @X@00450D90@, (u32)&D_00480000, (u32)(data2c_main_bss + 0x3EF85), @X@00450D9C@, @X@00450DA0@, (u32)(data2c_main_bss + 0x3EF86), @X@00450DA8@, @X@00450DAC@, (u32)(data2c_main_bss + 0x3EF88), @X@00450DB4@, @X@00450DB8@, @X@00450DBC@, @X@00450DC0@, @X@00450DC4@, @X@00450DC8@, @X@00450DCC@
};
typedef char data2c_sizecheck_00450D80[(sizeof(D_00450D80) == 80) ? 1 : -1];
