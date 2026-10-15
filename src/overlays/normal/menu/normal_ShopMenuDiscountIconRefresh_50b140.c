#include "types.h"
/* normal 0x0050B140 -- picks which of the three 0x40FB..0x40FD shop lists the
 * player is standing at.  The u8 at gp-0xB30 is the 3/2/1 rank (0 = none);
 * with no list the three panels are just switched off. */

typedef struct Root { u8 pad00[0x18]; s32 f18; } Root;
typedef struct Rec  { u8 pad00[0x2C]; s16 f2C; } Rec;
typedef struct Ent  { u8 pad00[0x10]; Rec *f10; } Ent;

extern void *D_004845C8;          /* gp - 0xBA8 */
extern volatile u8 D_00484640;          /* gp - 0xB30 */

extern Root *func_1FEDE0(void);
extern s32   func_3C7F40(s32 a, s32 b, s32 c, s32 d);
extern void  func_291110(void *w, u16 id, s32 c, s32 d);
extern void *func_28FE10(void *w, u16 id, s32 k);
extern Ent  *func_3C8370(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
extern void  func_288E50(void *p, s32 k, s32 a, s32 b);

s32 normal_ShopMenuDiscountIconRefresh_50b140(void)
{
    Root *root;
    s32   id;
    void *w;
    Ent  *e;
    Rec  *rc;

    root = func_1FEDE0();
    id = -1;
    if (func_3C7F40(root->f18, 0x40FB, 0xA, 0) != 0) {
        D_00484640 = 3;
        id = 0x40FB;
    } else if (func_3C7F40(root->f18, 0x40FC, 0xA, 0) != 0) {
        D_00484640 = 2;
        id = 0x40FC;
    } else if (func_3C7F40(root->f18, 0x40FD, 0xA, 0) != 0) {
        D_00484640 = 1;
        id = 0x40FD;
    } else {
        D_00484640 = 0;
    }
    if (D_00484640 == 0) {
        func_291110(D_004845C8, 0x1F, 0, 1);
        func_291110(D_004845C8, 0x1E, 0, 1);
        func_291110(D_004845C8, 0x26, 0, 1);
        return 1;
    }
    w = func_28FE10(D_004845C8, 0x26, 0);
    if (w == 0) {
        return 0;
    }
    e = func_3C8370(root->f18, id, 0xA, -1, 0, 0);
    if (e == 0) {
        return 0;
    }
    rc = e->f10;
    func_288E50(w, rc->f2C, 0x20, 0x20);
    return 1;
}
