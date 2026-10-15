#include "types.h"

extern s32 strcmp(const void *, const void *);
extern s32 EventCastSetTexAnim_258150(void *, s32, s32, const void *);
extern u8 D_004BDDB0[];
extern u8 D_0045EDA0[];

struct Obj0 {
    u8 pad000[0x20];
    s32 m20;
    u8 pad024[0x8];
    u8 m2C[0x4];
};

struct Obj1 {
    u8 pad000[0x60];
    s32 m60;
};

/* Retail falls through into the strcmp()==0 arm. */
s32 EvSubNodeSetTexAnim_252410(struct Obj0 *p0, struct Obj1 *p1)
{
    if (strcmp(p0->m2C, D_0045EDA0) == 0) {
        EventCastSetTexAnim_258150(D_004BDDB0, p1->m60, p0->m20, 0);
    } else {
        EventCastSetTexAnim_258150(D_004BDDB0, p1->m60, p0->m20, p0->m2C);
    }
    return 0;
}
