/* rgp:protos */
#define RGP_SELF_DynBindSpringStartCmd_167c30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 padD4[0xD4];
    s32 unkD4;
    void *unkD8;
    s32 unkDC;
    void *unkE0;
} S00481154;

/*rgp*/
/*rgp*/
extern void *memset(void *, s32, u32);
extern S00481154 *D_00481154;
extern s32 D_00481158;
extern s32 D_0048116C;
extern s32 D_00481178;

s32 DynBindSpringStartCmd_167c30(void *rgp_a0) {
    s32 count;
    s32 g;
    u32 bytes;
    u32 blocks;
    S00481154 *ctx;
    s32 i;

    count = VariantGetInt_15f780((void *)rgp_a0);
    g = D_00481158;
    ctx = D_00481154;
    if (g != 0) {
        ctx->unkE0 = MemStackNew_14e1b0(count * 0x20,g);
        if (ctx->unkE0 != NULL) {
            ctx->unkDC=count;
        }
            for(i=0;i<ctx->unkD4;i++) memset((u8 *)ctx->unkE0+i*0x20,0,0x20);
    }
    D_00481178 = 0;
    D_0048116C = 0;
    return 1;
}
