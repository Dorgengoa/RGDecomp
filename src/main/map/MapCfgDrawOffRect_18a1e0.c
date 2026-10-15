#include "types.h"

typedef struct Buf_FUN_0018a1e0 {
    u8 d[0x10];
} Buf_FUN_0018a1e0;

typedef struct Obj_FUN_0018a1e0 Obj_FUN_0018a1e0;
typedef struct G_FUN_0018a1e0 G_FUN_0018a1e0;

extern G_FUN_0018a1e0 *D_00481250;
extern G_FUN_0018a1e0 *D_0048125C;
extern void VariantReadVec3_15f6c0(Buf_FUN_0018a1e0 *b, void *p);
extern void MapAreaModelAddDrawOffRect_189300(G_FUN_0018a1e0 *a, G_FUN_0018a1e0 *b, Buf_FUN_0018a1e0 *c,
                         Buf_FUN_0018a1e0 *d, s32 e);

s32 MapCfgDrawOffRect_18a1e0(Obj_FUN_0018a1e0 *o)
{
    Buf_FUN_0018a1e0 a;
    Buf_FUN_0018a1e0 b;
    Buf_FUN_0018a1e0 c;
    Buf_FUN_0018a1e0 d;

    VariantReadVec3_15f6c0(&a, o);
    VariantReadVec3_15f6c0(&b, (u8 *)o + 0x18);
    VariantReadVec3_15f6c0(&c, (u8 *)o + 0x30);
    VariantReadVec3_15f6c0(&d, (u8 *)o + 0x48);
    MapAreaModelAddDrawOffRect_189300(D_00481250, D_0048125C, &b, &d, 0);
    return 1;
}
