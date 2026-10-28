/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
extern unsigned char data2c_main_bss[];
/* Generated: do not edit. */
#include "types.h"

u32 D_00450A00[12] __attribute__((section(".data$rg00450A00"), aligned(16))) = {
    @X@00450A00@, @X@00450A04@, @X@00450A08@, @X@00450A0C@, @X@00450A10@, @X@00450A14@, @X@00450A18@, (u32)(data2c_main_bss + 0x2EF90), @X@00450A20@, @X@00450A24@, @X@00450A28@, @X@00450A2C@
};
typedef char data2c_sizecheck_00450A00[(sizeof(D_00450A00) == 48) ? 1 : -1];
