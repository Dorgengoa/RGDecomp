#include "types.h"

typedef struct {
    s32 x0;
    void *x4;
    void *x8;
    void *xC;
    s8 n10;
    s8 n11;
    s16 n12;
} Obj;

extern void *ConstructNewArray_100710(void *, s32, s32, s32, s32);
extern s32 MemStackStrDup_14cff0(s32, s32);
extern void *MemStackNew_14e1b0(s32, s32);
extern s32 ReturnTrue_1ed0a0(Obj *);
extern void *memcpy(void *, const void *, u32);

s32 MapBlockBoxListClone_1e03c0(Obj *arg0, s32 arg1)
{
    void *p;
    s32 n;

    if (ReturnTrue_1ed0a0(arg0) == 0) {
        return 0;
    }
    if (arg0->x4 != 0 && arg0->n10 > 0) {
        p = MemStackNew_14e1b0(arg0->n10 * 2, arg1);
        if (p == 0) {
            return 0;
        }
        memcpy(p, arg0->x4, arg0->n10 * 2);
        arg0->x4 = p;
    }
    if (arg0->x8 != 0) {
        n = arg0->n11;
        if (n > 0) {
            p = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x4C + 0x10, arg1), 0, 0, 0x4C, n);
            if (p == 0) {
                return 0;
            }
            memcpy(p, arg0->x8, arg0->n11 * 0x4C);
            arg0->x8 = p;
        }
    }
    if (arg0->xC != 0) {
        n = arg0->n12;
        if (n > 0) {
            p = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x4C + 0x10, arg1), 0, 0, 0x4C, n);
            if (p == 0) {
                return 0;
            }
            memcpy(p, arg0->xC, arg0->n12 * 0x4C);
            arg0->xC = p;
        }
    }
    arg0->x0 = MemStackStrDup_14cff0(arg0->x0, arg1);
    return 1;
}
