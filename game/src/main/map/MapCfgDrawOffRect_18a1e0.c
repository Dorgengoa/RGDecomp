/* rgp:protos */
#define RGP_SELF_MapCfgDrawOffRect_18a1e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Buf_FUN_0018a1e0 {
    u8 d[0x10];
} Buf_FUN_0018a1e0;

typedef struct Obj_FUN_0018a1e0 Obj_FUN_0018a1e0;
typedef struct G_FUN_0018a1e0 G_FUN_0018a1e0;

extern G_FUN_0018a1e0 *D_00481250;
extern G_FUN_0018a1e0 *D_0048125C;
/*rgp*/
/*rgp*/


s32 MapCfgDrawOffRect_18a1e0(Obj_FUN_0018a1e0 *o)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x10 + sizeof(Buf_FUN_0018a1e0)]; char m1[0x0 + sizeof(Buf_FUN_0018a1e0)]; char m2[0x1c]; char m3[0xc]; char m4[0x20]; })]; typedef char rgp_blk1_chk0[(0x0) + sizeof(Buf_FUN_0018a1e0) <= (0x10) && (0x0) >= 0 ? 1 : -1];
    
    __attribute__((aligned(16))) unsigned char rgp_blk2[sizeof(union { char m0[0x10 + sizeof(Buf_FUN_0018a1e0)]; char m1[0x0 + sizeof(Buf_FUN_0018a1e0)]; char m2[0x1c]; char m3[0xc]; char m4[0x20]; })]; typedef char rgp_blk2_chk0[(0x0) + sizeof(Buf_FUN_0018a1e0) <= (0x10) && (0x0) >= 0 ? 1 : -1];
    

    VariantReadVec3_15f6c0(&(*(Buf_FUN_0018a1e0 *)(rgp_blk1 + 0x10)), o);
    VariantReadVec3_15f6c0(&(*(Buf_FUN_0018a1e0 *)(rgp_blk1 + 0x0)), (u8 *)o + 0x18);
    VariantReadVec3_15f6c0(&(*(Buf_FUN_0018a1e0 *)(rgp_blk2 + 0x10)), (u8 *)o + 0x30);
    VariantReadVec3_15f6c0(&(*(Buf_FUN_0018a1e0 *)(rgp_blk2 + 0x0)), (u8 *)o + 0x48);
    MapAreaModelAddDrawOffRect_189300(D_00481250, D_0048125C, &(*(Buf_FUN_0018a1e0 *)(rgp_blk1 + 0x0)), &(*(Buf_FUN_0018a1e0 *)(rgp_blk2 + 0x0)), 0);
    return 1;
}
