/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
extern unsigned char data2c_main_bss[];
/* Generated: do not edit. */
#include "types.h"
extern u8 D_00470000[];
u32 D_004544F0[20] __attribute__((section(".data$rg004544F0"), aligned(16))) = {
    @X@004544F0@, @X@004544F4@, @X@004544F8@, @X@004544FC@, (u32)&D_00470000, @X@00454504@, @X@00454508@, (u32)(data2c_main_bss + 0x2EF80), @X@00454510@, @X@00454514@, @X@00454518@, @X@0045451C@, @X@00454520@, @X@00454524@, @X@00454528@, @X@0045452C@, @X@00454530@, @X@00454534@, @X@00454538@, @X@0045453C@
};
typedef char data2c_sizecheck_004544F0[(sizeof(D_004544F0) == 80) ? 1 : -1];
