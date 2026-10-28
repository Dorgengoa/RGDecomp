/* rgp:protos */
#line 1
#include "types.h"
typedef rg_u128 u128;

typedef struct Slot {
    u8 b[8];
} Slot;

typedef struct Vec4f {
    f32 x, y, z, w;
} Vec4f;

class Obj {
    u8 pad000[0x80];
public:
    VC_VPTR_MEMBER; void init() { VCM0(void, 0x8); }
    u8 pad084[0xC];
};

typedef struct Part {
    u8 pad00[0x10];
    s32 x20;      /* +0x10 in part = +0x20 in obj? no: part-relative */
} Part_unused;

typedef struct Sub {
    u8 pad00[0x20];
    s32 x20;
    f32 x24;
    u8 pad28[0x18];
    Vec4f x40;
    u8 pad50[0x10];
    s32 x60;
    s32 x64;
} Sub;

typedef struct Owner {
    u8 pad000[0x474];
    s32 x474;
} Owner;

extern "C" {
extern u8 D_0049D3A8[0x400];
extern u8 D_0049D398[0x400];
extern u8 D_0049D3A4[0x400];
extern u8 D_0049D418[0x400];
extern u8 D_0049D42C[0x400];
extern u8 D_0049D43C[0x400];
extern u8 D_0049D440[0x400];
extern u8 D_00470F30[];
extern char D_0045A940[];
extern s32 D_0047E1D4;

extern s32 GetDrawCtxNameTable_15de40(void);
extern char *SlotGetInt_15f720(Slot *slot);
extern f32 VariantGetFloat_15f740(Slot *slot);
extern s32 VariantGetInt_15f780(Slot *slot);
extern char *strcpy(char *dst, const char *src);
extern s32 GetDrawCtx_15de80(void);
extern s32 DrawEnvGetWidth_1451e0(s32 x);
extern s32 DrawEnvGetHeight_1451d0(s32 x);
extern s32 DrawEnvGetPsmBpp_145140(s32 x);
extern void *MemStackNew_14e230(s32 size, s32 heap);
extern void OutlineParamsInit_16b8b0(void *p);
extern void Sprintf_1343b8(char *dst, const char *fmt, s32 n);
extern s32 NameTableAddEntry_159b70(s32, s32, char *, s32, s32, s32, s32, s32, s64, int);
extern void ModelObjAppendOutlineMaybe_1ad460(Owner *owner, char *name, Obj *obj);
}

#define G(x) (*(s32 *)(x))

extern "C" s32 InfoCfgOutlineCmd_1aaf20(Slot *args, s32 argc)
{
    char name[64] __attribute__((aligned(16)));
    Vec4f v __attribute__((aligned(16)));
    char label[32] __attribute__((aligned(16)));
    s32 heap;
    s32 mode;
    Owner *owner;
    s32 ctx;
    f32 scale;
    s32 flag;
    s32 h;
    s32 a;
    s32 b;
    s32 c;
    Obj *obj;
    Sub *sub;
    s32 r;

    if (G(D_0049D3A8) == 0) {
        return 1;
    }
    heap = G(D_0049D398);
    owner = *(Owner **)D_0049D418;
    mode = G(D_0049D3A4);
    ctx = GetDrawCtxNameTable_15de40();
    if (heap == 0 || owner == 0) {
        return 0;
    }
    if (ctx == 0 || mode < 0) {
        return 0;
    }
    strcpy(name, SlotGetInt_15f720(args++));
    scale = VariantGetFloat_15f740(args++);
    flag = 1;
    if (argc >= 3) {
        flag = VariantGetInt_15f780(args++);
    }
    h = GetDrawCtx_15de80();
    a = DrawEnvGetWidth_1451e0(h);
    b = DrawEnvGetHeight_1451d0(h);
    c = DrawEnvGetPsmBpp_145140(h);
    obj = (Obj *)MemStackNew_14e230(0x90, heap);
    if (obj != 0) {
        *(u8 **)((u8 *)obj + 0x80) = D_00470F30;
        OutlineParamsInit_16b8b0((u8 *)obj + 0x10);
        obj->init();
    }
    sub = (Sub *)((u8 *)obj + 0x10);
    if (sub == 0) {
        return 0;
    }
    OutlineParamsInit_16b8b0(sub);
    sub->x24 = scale;
    sub->x60 = flag;
    if (argc >= 6) {
        v.x = VariantGetFloat_15f740(args++);
        v.y = VariantGetFloat_15f740(args++);
        v.z = VariantGetFloat_15f740(args++);
        v.w = 0;
        *(u128 *)&sub->x40 = *(u128 *)&v;
    }
    if (G(D_0049D42C) == 0 && !(scale < 0.0f)) {
        r = D_0047E1D4 + 1;
        D_0047E1D4 = r;
        Sprintf_1343b8(label, D_0045A940, r);
        r = NameTableAddEntry_159b70(ctx, mode, label, 0, a, b, c, 0, 0, (int)(0));
        if (r == 0) {
            return 0;
        }
        G(D_0049D42C) = r;
        owner->x474 = r;
    }
    if (G(D_0049D43C) != 0) {
        sub->x64 = G(D_0049D440);
    }
    sub->x20 = G(D_0049D42C);
    ModelObjAppendOutlineMaybe_1ad460(owner, name, obj);
    return 1;
}
