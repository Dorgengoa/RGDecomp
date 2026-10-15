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
    virtual s32 v000(); virtual s32 v001(); virtual s32 v002();
    virtual s32 v003(); virtual s32 v004(); virtual s32 v005();
    virtual s32 v006(); virtual s32 v007(); virtual s32 v008();
    virtual s32 v009(); virtual s32 v010(); virtual s32 v011();
    virtual s32 v012(); virtual s32 v013(); virtual s32 v014();
    virtual s32 v015(); virtual s32 v016(); virtual s32 v017();
    virtual s32 v018(); virtual s32 v019(); virtual s32 v020();
    virtual s32 v021(); virtual s32 v022(); virtual s32 v023();
    virtual s32 v024(); virtual s32 v025(); virtual s32 v026();
    virtual s32 v027(); virtual s32 v028(); virtual s32 v029();
    virtual s32 v030(); virtual s32 v031(); virtual s32 v032();
    virtual s32 v033(); virtual s32 v034(); virtual s32 v035();
    virtual s32 v036(); virtual s32 v037(); virtual s32 v038();
    virtual s32 v039(); virtual s32 v040(); virtual s32 v041();
    virtual s32 v042(); virtual s32 v043(); virtual s32 v044();
    virtual s32 v045(); virtual s32 v046(); virtual s32 v047();
    virtual s32 v048(); virtual s32 v049(); virtual s32 v050();
    virtual s32 v051(); virtual s32 v052(); virtual s32 v053();
    virtual s32 v054(); virtual s32 v055(); virtual s32 v056();
    virtual s32 v057(); virtual s32 v058(); virtual s32 v059();
    virtual s32 v060(); virtual s32 v061(); virtual s32 v062();
    virtual s32 v063(); virtual s32 v064(); virtual s32 v065();
    virtual s32 v066(); virtual s32 v067();
    virtual s32 v068(s32 a);   /* slot 0x118 */
    virtual s32 v069(); virtual s32 v070(); virtual s32 v071();
    virtual s32 v072(); virtual s32 v073(); virtual s32 v074();
    virtual s32 v075(); virtual s32 v076(); virtual s32 v077();
    virtual s32 v078(); virtual s32 v079(); virtual s32 v080();
    virtual s32 v081(); virtual s32 v082(); virtual s32 v083();
    virtual s32 v084(); virtual s32 v085(); virtual s32 v086();
    virtual s32 v087(); virtual s32 v088(); virtual s32 v089();
    virtual s32 v090(); virtual s32 v091(); virtual s32 v092();
    virtual s32 v093(); virtual s32 v094(); virtual s32 v095();
    virtual s32 v096(s32 a);   /* slot 0x188 */
    virtual s32 v097(); virtual s32 v098(); virtual s32 v099();
    virtual s32 v100(); virtual s32 v101(); virtual u8  v102();
    virtual s32 v103(); virtual s32 v104(); virtual s32 v105();
    virtual s32 v106(); virtual s32 v107();
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

extern "C" G   *func_1FEDE0(void);
extern "C" void func_3C4D90(void *h, S **out, s32 n);
extern "C" u8  *func_430AF0(void *k);
extern "C" u8  *func_430B30(void *k);
extern "C" u8  *func_430B50(void *k);
extern "C" u8  *func_430B70(void *k);
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

    g = func_1FEDE0();
    if (g != 0) {
    if (insect_InsectBattleTestFlag_50da40(a, 2) != 0) {
        q = 0;
        n = 0;
        switch (a->f5DA8) {
        case 3:
            p = func_430B70(g->f24);
            q = p + c * 600 + 0x10;
            n = *(s8 *)(c + (s32)p + 0xD);
            break;
        case 4:
            p = func_430B50(g->f24);
            n = *(s32 *)(p + 0x10);
            q = p + 0x14;
            if (c != 0) {
                q = p + 0x288;
                n = 5;
            }
            break;
        case 5:
            p = func_430B30(g->f24);
            q = p + c * 224 + 0x28;
            break;
        case 6:
            p = func_430AF0(g->f24);
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
    func_3C4D90(g->f18, buf, 0x20);
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
