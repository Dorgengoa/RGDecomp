#include "types.h"
/* normal 0x004F53D0 -- state-2 settle test: walk the n rows and return 1 only
 * when every row's current position already equals its target. */

typedef struct Obj {
    u8  pad000[0x378];
    s16 f378;
} Obj;

extern s32  func_1FEDE0(void);
extern s32  normal_FieldHudPartyRowCount_4f9c50(Obj *p);
extern void func_2910A0(void *p, u16 id, s32 *outX, s32 *outY);
extern void func_290D90(void *p, u16 id, s32 *outX, s32 *outY);

s32 normal_FieldHudRowsSettled_4f53d0(Obj *p)
{
    u16 id;
    s32 i;
    s32 n;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 v;

    v = p->f378;
    if (v == 0) {
        return 0;
    }
    id = 6;
    if ((s16)v != 2) {
        return 0;
    }
    if (func_1FEDE0() == 0) {
        return 0;
    }
    n = normal_FieldHudPartyRowCount_4f9c50(p);
    for (i = 0; i < n; i++) {
        func_2910A0(p, id, &x0, &y0);
        func_290D90(p, id, &x1, &y1);
        if (x0 != x1 || y0 != y1) {
            return 0;
        }
        id += 7;
    }
    return 1;
}
