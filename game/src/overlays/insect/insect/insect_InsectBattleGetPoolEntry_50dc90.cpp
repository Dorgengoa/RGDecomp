/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x0050DC90 -- C++ virtual dispatch, vptr at offset 0, 108 slots.
 * [[jalr-is-cpp-virtual]]  Same class as insect_InsectPieceLoadFromItem_516360.
 *
 * The `andi $2,$2,0xFF` after the 0x1A0 call is the RETURN-SIDE s16/u8
 * prototype lever: that one virtual is declared `u8` and the rest `s32`.
 *
 * `dsll32 $2,$2,30 / dsrl32 $2,$2,31` off an `lbu` is mwcc extracting BIT 1
 * of a u8 bitfield, not a shift-and-mask.
 *
 * The compare chain 6, 5, 4, 3 is `beql` INTO each arm, so the source case
 * order is the REVERSE 3, 4, 5, 6 -- and the arm addresses ascend that way.
 */

struct Sub { u8 pad000[0xC]; s32 f0C; };

class S {
public:
    VC_VPTR_MEMBER;  
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
     
    s32 v068(s32 a) { return VCM(s32, (void *, s32), 0x118, a); }   /* slot 0x118 */
      
      
      
      
      
      
      
      
      
       /* slot 0x188 */
      s32 v099() { return VCM0(s32, 0x194); }
      u8 v102() { return VCM0(u8, 0x1A0); }
    s32 v103() { return VCM0(s32, 0x1A4); }  
     s32 v107() { return VCM0(s32, 0x1B4); }
    u8    pad004[0x10 - 0x4];
    Sub  *f010;                     /* +0x10 */
};

struct E {
    u8   pad000[0x16];
    u8   f16;                       /* +0x16 */
    u8   pad017;
    u8   f18;                       /* +0x18 */
    u8   pad019[0x20 - 0x19];
    u8   f20a : 1;                  /* +0x20 bit 0 */
    u8   f20b : 1;                  /* +0x20 bit 1 */
    u8   pad021[0x24 - 0x21];
    Sub *f24;                       /* +0x24 */
};

struct D {
    void *f00;
    s32   f04;
    s32   f08;
    s32   f0C;
    s32   f10;
    s32   f14;
};

struct A {
    u8  pad000[0x5DA8];
    s32 f5DA8;                      /* +0x5DA8 */
};

struct G {
    u8    pad000[0x18];
    void *f18;                      /* +0x18 */
    u8    pad01C[0x24 - 0x1C];
    void *f24;                      /* +0x24 */
};

extern "C" G   *GetGameData_1fede0(void);
extern "C" void InvCollectInsects_3c4d90(void *h, S **out, s32 n);
extern "C" u8  *RecordGetPayloadIfKind3D_430af0(void *k);
extern "C" u8  *RecordGetPayloadIfKind32_430b30(void *k);
extern "C" u8  *RecordGetPayloadIfKind28_430b50(void *k);
extern "C" u8  *RecordGetPayloadIfKind1E_430b70(void *k);
extern "C" s32  insect_InsectBattleTestFlag_50da40(A *a, s32 k);

extern "C" s32 insect_InsectBattleGetPoolEntry_50dc90(A *a, s32 b, s32 c, D *d)
{
    G  *g;
    u8 *p;
    u8 *q;
    s32 n;
    E  *e;
    S **pp;
    s32 i;
    S  *buf[0x20];

    g = GetGameData_1fede0();
    if (g != 0) {
    if (insect_InsectBattleTestFlag_50da40(a, 2) != 0) {
        q = 0;
        n = 0;
        switch (a->f5DA8) {
        case 3:
            p = RecordGetPayloadIfKind1E_430b70(g->f24);
            q = p + c * 600 + 0x10;
            n = *(s8 *)(c + (s32)p + 0xD);
            break;
        case 4:
            p = RecordGetPayloadIfKind28_430b50(g->f24);
            n = *(s32 *)(p + 0x10);
            q = p + 0x14;
            if (c != 0) {
                q = p + 0x288;
                n = 5;
            }
            break;
        case 5:
            p = RecordGetPayloadIfKind32_430b30(g->f24);
            q = p + c * 224 + 0x28;
            break;
        case 6:
            p = RecordGetPayloadIfKind3D_430af0(g->f24);
            n = *(s32 *)(p + 0xF0);
            q = p + 0xF4;
            break;
        }
        if (q != 0) {
        if (b >= n) {
            return 0;
        }
        e = (E *)(q + b * 40);
        d->f00 = e;
        d->f04 = e->f24->f0C;
        d->f08 = e->f18;
        d->f0C = 0;
        d->f14 = e->f20b;
        d->f10 = e->f16;
        if (d->f08 >= 6) {
            d->f08 = 5;
            d->f0C = 0x2BC;
        }
        }
        return 1;
    }
    for (i = 0; i < 0x20; i++) {
        buf[i] = 0;
    }
    InvCollectInsects_3c4d90(g->f18, buf, 0x20);
    pp = &buf[b];
    if (*pp == 0) {
        return 0;
    }
    d->f00 = (void *)(*pp)->v068(0);
    d->f04 = (*pp)->f010->f0C;
    d->f08 = (*pp)->v103();
    d->f0C = (*pp)->v107();
    d->f14 = (*pp)->v102();
    d->f10 = (*pp)->v099();
    return 1;
    }
    return 0;
}
