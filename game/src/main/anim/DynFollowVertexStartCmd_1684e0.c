/* rgp:protos */
#define RGP_SELF_DynFollowVertexStartCmd_1684e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 padD4[0xBC];
    s32 unkBC;
    void *unkC0;
    s32 unkC4;
    void *unkC8;
} S00481154;

/*rgp*/
/*rgp*/
extern void *memset(void *, s32, u32);
extern S00481154 *D_00481154;
extern s32 D_00481158;
extern s32 D_0048116C;
extern s32 D_00481184;

s32 DynFollowVertexStartCmd_1684e0(void *rgp_a0) {
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
        ctx->unkC8 = MemStackNew_14e1b0(count * 0xC,g);
        if (ctx->unkC8 != NULL) {
            ctx->unkC4=count;
        }
            for(i=0;i<ctx->unkC4;i++) memset((u8 *)ctx->unkC8+i*0xC,0,0xC);
    }
    D_00481184 = 0;
    return 1;
}
