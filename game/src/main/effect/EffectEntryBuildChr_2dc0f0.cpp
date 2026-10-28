/* rgp:protos */
#line 1
#include "types.h"
#undef NULL

class VObj {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f() { VCM0(void, 0x50); }
};

struct Heap {
    u8 pad0[0x28];
    s32 unk28;
    s32 unk2C;
    u8 pad30[0x4];
    s32 unk34;
};

struct Desc {
    s32 unk0;
    void *unk4;
    Heap *unk8;
    Heap *unkC;
    Heap *unk10;
    s32 unk14;
    s32 unk18;
    u8 pad1C[0x10];
    void *unk2C;
    s32 unk30;
    u8 pad34[0x4];
    void *unk38;
    s32 unk3C;
    u8 buf40[0x20];
    u8 buf60[0x28];
};

struct Vec3 { f32 x, y, z, w; };

struct T2dc0f0 {
    u8 pad0[0x14];
    s16 unk14;
    u8 pad16[0x6a];
    VObj *unk80;
    s32 unk84;
    u8 pad88[0x14];
    s32 unk9C;
    u8 padA0[0x4];
    Heap *unkA4;
    u8 padA8[0xc];
    s16 unkB4;
};

extern "C" {
void Sprintf_1343b8(char *, void *, s32);
s32 MemStackPeekQw_14d9d0(Heap *, u32);
void MemStackReturnToOwnerMaybe_14dad0(Heap *);
s32 MemStackHeapAlloc_14db10(Heap *, s32, u32, s32);
u8 *MemStackNew_14e230(s32, Heap *);
void ModelSetScale_150ff0(VObj *, Vec3 *);
void ModelSetRot_151080(VObj *, Vec3 *);
void ModelSetPos_151110(VObj *, Vec3 *);
void NameTableFreeGroup_158ac0(u8 *, s32);
u8 *GetDrawCtxNameTable_15de40(void);
void InfoCfgParseAll_1afd00(VObj *, Desc *);
void ModelObjExCtor_1c4920(u8 *, int, int, int);
s32 GetEffectMgr_2d9040(void);
void *memset(void *, s32, u32);
char *strcpy(char *, const char *);
extern u8 D_00461728[];
extern u8 D_00461738[];
extern u8 D_00470F50[];
extern volatile f32 D_0047D7A4;
extern s32 D_0047E180;
extern f32 D_0047EED0;
extern f32 D_0047EED4;
extern f32 D_0047EED8;
extern f32 D_0047EEDC;
}

static inline void zero3(Vec3 *p) { *(s32 *)&p->x = 0; *(s32 *)&p->y = 0; *(s32 *)&p->z = 0; }
#define ZERO16(d) { u8 *p_ = (u8 *)(d); u32 n_ = 16; if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

inline bool heapBusy(Heap *h) { return h->unk28 != 0; }
inline bool heapBusy2(Heap *h) { return heapBusy(h); }

extern "C" s32 EffectEntryBuildChr_2dc0f0(T2dc0f0 *self, s32 arg1, s32 arg2, u32 size) {
    u32 rem;
    u32 blocks;
    u32 n;
    bool lock;
    u8 *obj;
    u8 *res;
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(Desc)) + (0x88) + (0x90)];
    char name[16] __attribute__((aligned(16)));
    VObj *o;
    Vec3 v0 __attribute__((aligned(16)));
    union { Vec3 v; s32 i[4]; } u0;
    Vec3 v1 __attribute__((aligned(16)));
    Vec3 v2 __attribute__((aligned(16)));

    if (GetEffectMgr_2d9040() == 0) {
        return 1;
    }
    rem = size & 0xF;
    n = (rem ? (size >> 4) + 1 : (size >> 4)) + 0x79;
    lock = !(heapBusy(self->unkA4) != 0);
    if (lock) {
        self->unk84 = MemStackHeapAlloc_14db10(self->unkA4, 3, n, 0x40);
    } else {
        self->unk84 = 0;
    }
    if (MemStackPeekQw_14d9d0(self->unkA4, n) == 0) {
        if (lock) MemStackReturnToOwnerMaybe_14dad0(self->unkA4);
        return 2;
    }
    {
        Heap *h = self->unkA4;
        s32 fr = h->unk34 - h->unk2C;
        f32 fn = (f32)((rem ? (size >> 4) + 1 : (size >> 4)) + 0x79);
        if (!(D_0047D7A4 * fn < (f32)fr)) {
            if (lock) MemStackReturnToOwnerMaybe_14dad0(h);
            return 1;
        }
    }
    blocks = size >> 4;
    blocks = rem ? blocks + 1 : blocks;
    self->unk9C = (s32)(D_0047D7A4 * (f32)(blocks + 0x79));
    obj = MemStackNew_14e230(0x790, self->unkA4);
    if (obj != 0) {
        ModelObjExCtor_1c4920(obj, 0, 0, 0);
        *(void **)(obj + 0x1B0) = D_00470F50;
    }
    self->unk80 = (VObj *)obj;
    if (obj == 0) {
        if (lock) MemStackReturnToOwnerMaybe_14dad0(self->unkA4);
        return 2;
    }
    res = GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(res, self->unk14);
    memset(&(*(Desc *)(rgp_blk1 + 0x0)), 0, sizeof((*(Desc *)(rgp_blk1 + 0x0))));
    (*(Desc *)(rgp_blk1 + 0x0)).unk2C = (*(Desc *)(rgp_blk1 + 0x0)).buf40;
    (*(Desc *)(rgp_blk1 + 0x0)).unk30 = 8;
    (*(Desc *)(rgp_blk1 + 0x0)).unk38 = (*(Desc *)(rgp_blk1 + 0x0)).buf60;
    (*(Desc *)(rgp_blk1 + 0x0)).unk3C = 8;
    (*(Desc *)(rgp_blk1 + 0x0)).unk0 = arg2;
    (*(Desc *)(rgp_blk1 + 0x0)).unk4 = D_00461728;
    (*(Desc *)(rgp_blk1 + 0x0)).unk8 = self->unkA4;
    (*(Desc *)(rgp_blk1 + 0x0)).unkC = self->unkA4;
    (*(Desc *)(rgp_blk1 + 0x0)).unk10 = self->unkA4;
    (*(Desc *)(rgp_blk1 + 0x0)).unk14 = self->unk14;
    (*(Desc *)(rgp_blk1 + 0x0)).unk18 = 0;
    Sprintf_1343b8(name, D_00461738, arg1);
    strcpy((char *)(res + 0x1E4), name);
    self->unk80->f();
    {
        s32 t = GetEffectMgr_2d9040() + 0x58;
        VObj *o = self->unk80;
        *(s32 *)((u8 *)o + 0x53C) = t;
        if (t != 0) {
            s32 c = D_0047E180;
            D_0047E180 = c + 1;
            *(s32 *)((u8 *)o + 0x538) = c;
        }
    }
    InfoCfgParseAll_1afd00(self->unk80, &(*(Desc *)(rgp_blk1 + 0x0)));
    o = self->unk80;
    v0.x = D_0047EED0;
    v0.y = D_0047EED4;
    v0.z = D_0047EED8;
    v0.w = D_0047EEDC;
    { s32 *pi = (s32 *)&v0; pi[0] = 0; pi[1] = 0; pi[2] = 0; }
    ModelSetPos_151110(o, &v0);
    o = self->unk80;
    ZERO16(&v1);
    v1.x = 0.0f;
    v1.y = 0.0f;
    v1.z = 0.0f;
    ModelSetRot_151080(o, &v1);
    o = self->unk80;
    ZERO16(&v2);
    v2.x = 1.0f;
    v2.y = 1.0f;
    v2.z = 1.0f;
    ModelSetScale_150ff0(o, &v2);
    res[0x1E4] = 0;
    if (lock) MemStackReturnToOwnerMaybe_14dad0(self->unkA4);
    self->unkB4 |= 1;
    return 0;
}
