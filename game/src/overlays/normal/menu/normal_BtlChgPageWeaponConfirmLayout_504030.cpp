/* rgp:protos */
#line 1
#include "types.h"
/* normal 0x00504030 -- the 0x4F/0x4B/0x4D widget triple for one roster slot.
 *
 * FIVE `jalr $25` sites, so this is C++ VIRTUAL DISPATCH and the unit is a
 * .cpp (see levers.d/jalr-is-cpp-virtual.md).  Every vptr load here is
 * `lw $25,0x0($obj)` -> vptr offset 0, and slot = 8 + 4*N:
 *   0x4C  -> 17    0x60  -> 22    0x388 -> 224   0x38C -> 225   0x3C4 -> 239
 * so the placeholder class carries 240 declared-and-never-defined virtuals.
 * The class is never constructed, so no vtable lands in the object.
 *
 * The data side of the same objects is reached through a separate `ObjD`
 * view rather than data members inside the virtual class -- the vptr must
 * stay at offset 0 and the cast costs nothing.
 *
 * `(x % 8) * 32` / `(x / 8) * 32` are the andi-7 + `-8` correction and the
 * sra-3 + `+7` correction; both are plain SIGNED % and / by 8.
 * normal_D_005259C0 is copied halfword-at-a-time into a 0x21-entry stack table
 * (11 rows of 3), and the search runs over the first 10 rows only. */

struct Obj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void s017(void *dst) { VCM(void, (void *, void *), 0x4C, dst); }  /* slot 17 -> vtable +0x4C */
    
    
    
    
    s32 s022() { return VCM0(s32, 0x60); }  /* slot 22 -> vtable +0x60 */
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Obj * s224() { return VCM0(Obj *, 0x388); }  /* slot 224 -> vtable +0x388 */
    Obj * s225() { return VCM0(Obj *, 0x38C); }  /* slot 225 -> vtable +0x38C */
    
    
    
    
    
    
    
    
    
    
    
    
    
    Obj * s239() { return VCM0(Obj *, 0x3C4); }  /* slot 239 -> vtable +0x3C4 */
};

typedef struct Info {
    u8   pad000[2];
    s8   f002;
    u8   pad003[0x2E - 3];
    s16  f02E;
} Info;

typedef struct ObjD {
    u8    pad000[0x10];
    Info *f010;
} ObjD;

typedef struct Host {
    u8    pad000[0x7C];
    Obj  *f07C[1];
    u8    pad080[0x450 - 0x80];
    s16   f450;
    s16   f452;
} Host;

typedef struct W {
    u8   pad000[4];
    s16  f004;
    s16  f006;
    s16  f008;
    s16  f00A;
    s16  f00C;
    s16  f00E;
    u8   pad010[0xC];
    u16  f01C;
    u8   pad01E[6];
    s16  f024;
    s16  f026;
    s16  f028;
    s16  f02A;
    s16  f02C;
    s16  f02E;
    u8   pad030[0xC];
    u16  f03C;
} W;

typedef struct T {
    u8    pad000[4];
    void *f004;
    u8    pad008[0xC];
    void *f014;
    u8    pad018[0xC];
    void *f024;
} T;

typedef struct Head {
    u8   pad000[0x2C];
    s16  f02C;
} Head;

extern "C" s16 normal_D_005259C0[];
extern "C" s32       D_0044B710[][2];
extern "C" void *D_00481BBC;          /* gp - 0x35B4 */

extern "C" void *normal_UiPageGetLayout_289b60(Host *a);
extern "C" Obj  *ItemFindOwnerChara_3d4d80(Obj *o, s32 a);
extern "C" Head *CharaGetIconRecMaybe_3ae3e0(Obj *h);
extern "C" W    *UiGetWidgetSprite_28fe10(void *ctx, s32 id, s32 a);
extern "C" T    *UiGetWidgetText_28f620(void *ctx, s32 id, s32 a);
extern "C" s32   MsgTableLookup_28aa30(void *p, s32 id);
extern "C" void  Sprintf_1343b8(void *dst, s32 a, s32 b);
extern "C" void  UiSetWidgetTexName_290ac0(void *ctx, s32 id, s32 v);
extern "C" s32   UiGetWidgetTextWidth_28f400(void *ctx, s32 id, s32 k);
extern "C" void  UiSetSpriteX_28fcd0(void *ctx, s32 id, s32 v, s32 k);

extern "C" s32 normal_BtlChgPageWeaponConfirmLayout_504030(Host *a, s16 idx);

s32 normal_BtlChgPageWeaponConfirmLayout_504030(Host *a, s16 idx)
{
    s16        buf[0x21] __attribute__((aligned(16)));
    const s16 *src;
    s16       *dst;
    s32        n;
    Obj       *o;
    void      *ctx;
    Obj       *h;
    s32        key;
    W         *q;
    W         *u;
    T         *t;
    Obj       *v;
    s32        c;
    s32        x;
    s32        i;
    s32        p1;
    s32        p2;

    src = normal_D_005259C0;
    n = 0x21;
    dst = buf;
    do {
        n--;
        *dst = *src;
        src++;
        dst++;
    } while (n > 0);

    o = a->f07C[idx];
    if (o == NULL) {
        return 0;
    }
    ctx = normal_UiPageGetLayout_289b60(a);
    if (ctx == NULL) {
        return 0;
    }
    h = ItemFindOwnerChara_3d4d80(o, 0);
    if (h == NULL) {
        return 0;
    }
    key = CharaGetIconRecMaybe_3ae3e0(h)->f02C;
    q = UiGetWidgetSprite_28fe10(ctx, 0x4F, 0);
    if (q == NULL) {
        return 0;
    }
    for (i = 0; i < 0xA; i++) {
        if (key == buf[i * 3]) {
            q->f008 = buf[i * 3 + 1];
            q->f00A = buf[i * 3 + 2];
            q->f00C = 0x36;
            q->f004 = 0x36;
            q->f00E = 0x42;
            q->f006 = 0x42;
            break;
        }
    }
    t = UiGetWidgetText_28f620(ctx, 0x4B, 0);
    if (t == NULL) {
        return 0;
    }
    Sprintf_1343b8((u8 *)a + 0x4D7, MsgTableLookup_28aa30(D_00481BBC, 0x5D), h->s022());
    t->f004 = (void *)((s32)a + 0x4D7);
    c = ((ObjD *)o)->f010->f002;
    v = (Obj *)0;
    if (c == 0) {
        v = h->s224();
    } else if (c == 1) {
        v = h->s225();
    } else if (c == 2) {
        v = h->s239();
    }
    if (v == NULL) {
        return 0;
    }
    v->s017((u8 *)a + 0x457);
    o->s017((u8 *)a + 0x497);
    t->f014 = (void *)((s32)a + 0x457);
    t->f024 = (void *)((s32)a + 0x497);
    UiSetWidgetTexName_290ac0(ctx, 0x4D, D_0044B710[a->f450][a->f452]);
    u = UiGetWidgetSprite_28fe10(ctx, 0x4D, 0);
    if (u == NULL) {
        return 0;
    }
    x = ((ObjD *)v)->f010->f02E;
    u->f004 = 0x28;
    u->f006 = 0x2D;
    u->f00C = 0x20;
    u->f00E = 0x20;
    u->f008 = (x % 8) * 32;
    u->f00A = (x / 8) * 32;
    u->f01C |= 2;
    x = (*(Info **)((u8 *)o + 0x10))->f02E;
    u->f024 = 0x28;
    u->f026 = 0x2D;
    u->f02C = 0x20;
    u->f02E = 0x20;
    u->f028 = (x % 8) * 32;
    u->f02A = (x / 8) * 32;
    u->f03C |= 2;
    p1 = UiGetWidgetTextWidth_28f400(ctx, 0x4B, 1);
    p2 = UiGetWidgetTextWidth_28f400(ctx, 0x4B, 2);
    UiSetSpriteX_28fcd0(ctx, 0x4A, (p1 / 2 + p2 / 2) / 2 + 0x69, 2);
    return 1;
}
