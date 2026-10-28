/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
extern unsigned char data2c_main_bss[];
/* Generated: do not edit. */
#include "types.h"

u32 D_00462378[8] __attribute__((section(".data$rg00462378"), aligned(8))) = {
    @X@00462378@, @X@0046237C@, (u32)(data2c_main_bss + 0x44D13), @X@00462384@, @X@00462388@, @X@0046238C@, @X@00462390@, @X@00462394@
};
typedef char data2c_sizecheck_00462378[(sizeof(D_00462378) == 32) ? 1 : -1];
