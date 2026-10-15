#include "types.h"
/* normal 0x00512A70 -- the equip screen's cursor/caption placer.  The grid cell
 * under the cursor names a key; the nine-entry D_00525AF0 table maps that key
 * to a slot id and to func_3ED680's availability answer.  The 0x1E caret is
 * parked on the slot's widget origin plus the func_2910A0 offset, the 0x7 frame
 * is sized from one of three layouts (slot 7, slot 5, everything else), and the
 * 0x22 label finally takes the two strings the item's virtual slot 26 returns.
 *
 * ONE VIRTUAL call, so the unit is .cpp; the slot is (0x70-8)/4 = 26 and the
 * argument is the key widened by `dsll32/dsra32 ..,16`, i.e. an explicit (s16).
 * The three gp id tables are addressed as `addiu $2,$28,-0x4AD0 / addu`, so
 * they must stay INSIDE small data -- declare them at the 8-byte threshold.
 * `cvt.w.s` then `cvt.s.w` on the widget's 0x30 float is one named integer
 * local that is stored back as a float and also doubled for the 0x40 field.
 * The layout chain is `== 7` then `!= 5`: retail puts the DEFAULT arm before
 * the `== 5` arm, which only the negated second test reproduces. */

typedef struct Wid {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
    u8  pad10[0x20 - 0x10];
    s16 f20;
    s16 f22;
    u8  pad24[0x30 - 0x24];
    f32 f30;
    s32 f34;
    s16 f38;
    s16 f3A;
    u8  pad3C[4];
    s16 f40;
    s16 f42;
} Wid;

typedef struct Hold { u8 pad00[0x20]; Wid *f20; u8 pad24[4]; void *f28; } Hold;

typedef struct Menu {
    u8  pad00[0x3C];
    s16 f3C;
    s16 f3E;
    u8  pad40[0x4A - 0x40];
    s16 f4A[1][4];
} Menu;

typedef struct Key { s16 f00; s16 f02; u8 pad04[4]; } Key;

typedef struct Lbl { u8 pad00[4]; s32 f04; u8 pad08[4]; s32 f0C;
                     u8 pad10[4]; s32 f14; u8 pad18[4]; s32 f1C; } Lbl;

typedef struct Txt { u8 pad00[0x14]; s32 f14; s32 f18; } Txt;

struct Bag {
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void s017();
    virtual void s018();
    virtual void s019();
    virtual void s020();
    virtual void s021();
    virtual void s022();
    virtual void s023();
    virtual void s024();
    virtual void s025();
    virtual Txt *find(s32 key);            /* slot 26 -> vtable +0x70 */
};

typedef struct Set { u8 pad00[0x14]; Bag *f14; } Set;
typedef struct Grp { u8 pad00[0x34]; Set *f34; } Grp;
typedef struct Own { u8 pad00[8]; Grp *f08; } Own;

extern const Key D_00525AF0[];

extern "C" u16 D_004806A0[4];     /* gp - 0x4AD0 */
extern "C" u16 D_00480680[4];     /* gp - 0x4AF0 */
extern "C" u16 D_00480690[4];     /* gp - 0x4AE0 */

extern "C" Own  *func_1FEDE0(void);
extern "C" Hold *func_290460(Menu *p, u16 id);
extern "C" void  func_2910A0(Menu *p, u16 id, s32 *x, s32 *y);
extern "C" void  func_291110(Menu *p, u16 id, s32 c, s32 d);
extern "C" s32   func_3ED680(Own *p, s16 a);

extern "C" s32 normal_SpaceMenuSelectionRefresh_512a70(Menu *a);

s32 normal_SpaceMenuSelectionRefresh_512a70(Menu *a)
{
    Own *p;
    Wid *r;
    Wid *u;
    Wid *v;
    Wid *w;
    Lbl *l;
    Txt *tx;
    s32  x;
    s32  y;
    s32  i;
    s32  got;
    s32  key;
    s32  sel;
    s32  z;
    s32  rx;
    s32  ry;

    p = func_1FEDE0();
    if (p == 0) {
        return 0;
    }
    sel = 0;
    got = 0;
    key = a->f4A[a->f3E][a->f3C];
    for (i = 0; i < 9; i++) {
        if (key == D_00525AF0[i].f00) {
            sel = D_00525AF0[i].f02;
            got = func_3ED680(p, D_00525AF0[i].f00);
        }
    }
    func_2910A0(a, D_004806A0[(s16)sel], &x, &y);
    r = func_290460(a, D_00480680[(s16)sel])->f20;
    rx = r->f00;
    ry = r->f02;
    z = (s32)r->f30;
    u = func_290460(a, 0x1E)->f20;
    u->f00 = (s16)(rx + x);
    u->f02 = (s16)(ry + y);
    u->f20 = (s16)(u->f00 + u->f04);
    u->f22 = u->f02;
    u->f30 = (f32)z;
    u->f34 = 0;
    u->f38 = 2;
    u->f3A = 0xC;
    u->f40 = (s16)(u->f00 + u->f04 + z * 2);
    u->f42 = u->f02;
    v = func_290460(a, D_00480690[(s16)sel])->f20;
    w = func_290460(a, 7)->f20;
    if (key == 8 || got == 1) {
        func_291110(a, 7, 0, 1);
        if (got == 1) {
            func_291110(a, 0x1E, 0, 1);
        } else {
            func_291110(a, 0x1E, 1, 1);
        }
    } else {
        func_291110(a, 7, 1, 1);
        func_291110(a, 0x1E, 1, 1);
        if ((s16)sel == 7) {
            w->f00 = (s16)(x + 6);
            w->f02 = (s16)(y + 5);
            w->f08 = 0x4C;
            w->f0A = 0x46;
            w->f04 = (s16)(v->f04 - 0xC);
            w->f0C = 0x4A;
            w->f06 = (s16)(v->f06 - 0xC);
            w->f0E = 0x56;
        } else if ((s16)sel != 5) {
            w->f00 = (s16)(x + 2);
            w->f02 = (s16)(y + 2);
            w->f08 = 0x4C;
            w->f0A = 0x46;
            w->f04 = (s16)(v->f04 - 4);
            w->f0C = 0x4A;
            w->f06 = (s16)(v->f06 - 4);
            w->f0E = 0x56;
        } else {
            w->f00 = (s16)x;
            w->f02 = (s16)y;
            w->f08 = 0x96;
            w->f0A = 0x88;
            w->f0C = 0x64;
            w->f04 = 0x64;
            w->f0E = 0x3A;
            w->f06 = 0x3A;
        }
    }
    l = (Lbl *)func_290460(a, 0x22)->f28;
    tx = p->f08->f34->f14->find((s16)key);
    if (tx != 0) {
        l->f04 = tx->f14;
        l->f0C = 0xFF303030;
        l->f14 = tx->f18;
        l->f1C = 0xFF303030;
    }
    return 0;
}
