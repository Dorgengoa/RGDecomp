/* rgp:protos */
#include "port/game_protos.h"
#line 1
/* rg:datareloc */
/* Generated: do not edit. */
#include "types.h"
extern void func_00120748(void);
extern void kFindAddress_120780(void);
u32 D_00446920[4] __attribute__((section(".data$rg00446920"), aligned(16))) = {
    @X@00446920@, (u32)&kFindAddress_120780, @X@00446928@, (u32)&func_00120748
};
typedef char data2c_sizecheck_00446920[(sizeof(D_00446920) == 16) ? 1 : -1];
