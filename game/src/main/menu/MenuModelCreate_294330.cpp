/* rgp:protos */
#line 1
#include "types.h"
#include "vec.h"

class G294 {
public:
    u8 d[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v50() { VCM0(void, 0x50); }
    
    
    void v5C() { VCM0(void, 0x5C); }
};

struct Desc {
    s32 x0;
    void *x4;
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 x18;
    u8 pad1C[0x2C - 0x1C];
    void *x2C;
    s32 x30;
    u8 pad34[4];
    void *x38;
    s32 x3C;
    u8 a[0x20];
    u8 b[0x28];
};

struct Q16 {
    s32 a;
    f32 b;
    s32 c;
    s32 d;
};

struct V16 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

extern "C" {
extern void MemStackAlign64_14d8e0(s32);
extern G294 *MemStackNew_14e230(s32, s32);
extern void ModelSetScale_150ff0(G294 *, V16 *);
extern void ModelSetRot_151080(G294 *, Q16 *);
extern void ModelSetPos_151110(G294 *, V16 *);
extern void NameTableFreeGroup_158ac0(s32, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void InfoCfgParseAll_1afd00(G294 *, Desc *);
extern s32 SoundBankLoad_1b9f00(s32, s32, s32);
extern s32 ArchiveGetFileByPath_1c2800(s32, void *, s32 *);
extern void ModelObjExCtor_1c4920(G294 *, int, int, int);
extern void *memset(void *, s32, u32);
extern u8 D_00461178[];
extern u8 D_00461188[];
extern u8 D_00470F50[];
extern f32 D_0047D5B0;
extern f32 D_0047EB80;
extern f32 D_0047EB84;
extern f32 D_0047EB88;
extern f32 D_0047EB8C;
extern s32 D_00482338;
extern u8 D_00482398;
extern G294 *D_004823D0;
extern s32 D_004823E4;
}

extern "C" void MenuModelCreate_294330(s32 arg0)
{
    struct { u8 pad[0xC]; s32 v; } idv;
    G294 *p;
    G294 *g;
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(Desc)) + (0x88) + (0x90)];
    volatile V16 c __attribute__((aligned(16)));
    Q16 q __attribute__((aligned(16)));
    V16 one __attribute__((aligned(16)));
    u8 *z;
    u32 k;
    s32 r;

    MemStackAlign64_14d8e0(D_00482338);
    p = MemStackNew_14e230(0x790, D_00482338);
    if (p != NULL) {
        ModelObjExCtor_1c4920(p, 0, 0, 0);
        *(u8 **)((u8 *)p + 0x1B0) = D_00470F50;
    }
    D_004823D0 = p;
    if (p == NULL) {
        return;
    }
    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x288);
    memset(&(*(Desc *)(rgp_blk1 + 0x0)), 0, 0x88);
    (*(Desc *)(rgp_blk1 + 0x0)).x30 = 8;
    (*(Desc *)(rgp_blk1 + 0x0)).x2C = (*(Desc *)(rgp_blk1 + 0x0)).a;
    (*(Desc *)(rgp_blk1 + 0x0)).x3C = 8;
    (*(Desc *)(rgp_blk1 + 0x0)).x0 = arg0;
    (*(Desc *)(rgp_blk1 + 0x0)).x38 = (*(Desc *)(rgp_blk1 + 0x0)).b;
    (*(Desc *)(rgp_blk1 + 0x0)).x4 = D_00461178;
    (*(Desc *)(rgp_blk1 + 0x0)).x8 = D_00482338;
    (*(Desc *)(rgp_blk1 + 0x0)).xC = D_00482338;
    (*(Desc *)(rgp_blk1 + 0x0)).x10 = D_00482338;
    (*(Desc *)(rgp_blk1 + 0x0)).x14 = 0x288;
    (*(Desc *)(rgp_blk1 + 0x0)).x18 = 1;
    D_004823D0->v5C();
    D_004823D0->v50();
    InfoCfgParseAll_1afd00(D_004823D0, &(*(Desc *)(rgp_blk1 + 0x0)));
    c.x = D_0047EB80;
    c.y = D_0047EB84;
    c.z = D_0047EB88;
    c.w = D_0047EB8C;
    c.x = 0.0f;
    c.y = 0.0f;
    c.z = 0.0f;
    ModelSetPos_151110(D_004823D0, (V16 *)&c);
    g = D_004823D0;
    z = (u8 *)&q;
    k = 0x10;
    if (z != NULL) {
        do {
            *z = 0;
            k--;
            z++;
        } while (k != 0);
    }
    q.a = 0;
    q.c = 0;
    q.b = D_0047D5B0;
    ModelSetRot_151080(g, &q);
    g = D_004823D0;
    z = (u8 *)&one;
    k = 0x10;
    if (z != NULL) {
        do {
            *z = 0;
            k--;
            z++;
        } while (k != 0);
    }
    one.x = 1.0f;
    one.y = 1.0f;
    one.z = 1.0f;
    ModelSetScale_150ff0(g, &one);
    r = ArchiveGetFileByPath_1c2800(arg0, D_00461188, &idv.v);
    if (r != 0) {
        D_004823E4 = SoundBankLoad_1b9f00(5, r, D_00482338);
    }
    D_00482398 = 1;
}
