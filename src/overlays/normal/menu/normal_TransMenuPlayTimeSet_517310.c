#include "types.h"
/* normal 0x00517310 -- the four out-parameters land at sp+0x2C/0x28/0x24/0x20
 * and three of them are stored back with `sd`, so those fields are 64-bit. */

typedef struct Obj {
    u8  pad00[8];
    s64 f08;
    s16 f10;
    u8  pad12[0x28 - 0x12];
    s64 f28;
    u8  pad30[0x48 - 0x30];
    s64 f48;
} Obj;

extern void *D_004846E8;          /* gp - 0xA88 */

extern Obj *func_28F2B0(void *w, s32 id, s32 a);
extern void func_28AEB0(s32 *a, s32 *b, s32 *c, s32 *d);
extern void func_28FCD0(void *w, u16 id, s32 a, s32 b);

void normal_TransMenuPlayTimeSet_517310(s32 id)
{
    Obj *p;
    s32  a;
    s32  b;
    s32  c;
    s32  d;

    p = func_28F2B0(D_004846E8, id, 0);
    if (p != NULL) {
        func_28AEB0(&a, &b, &c, &d);
        if (a > 99) {
            p->f10 = 3;
            func_28FCD0(D_004846E8, 0x754C, 0xE7, 4);
        } else {
            p->f10 = 2;
            func_28FCD0(D_004846E8, 0x754C, 0xF1, 4);
        }
        p->f08 = a;
        p->f28 = b;
        p->f48 = c;
    }
}
