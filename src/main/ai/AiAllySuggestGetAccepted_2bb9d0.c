#include "types.h"
struct Obj0 {
    u8 pad000[0x130];
    s16 m130; s16 m132; s16 m134; s16 m136; s16 m138;
    u8 pad13A[0x9];
    u8 m143;
};
struct Obj1 { s16 m00; s16 m02; s16 m04; s16 m06; s16 m08; };
s32 AiAllySuggestGetAccepted_2bb9d0(struct Obj0 *p0, struct Obj1 *p1)
{
    s16 t0;
    s16 t1;
    s16 t2;
    s16 t3;

    if (p1 == 0) {
        return -1;
    }
    p1->m00 = p0->m130;
    t0 = *(volatile s16 *)&p0->m132;
    t1 = p0->m134;
    p1->m02 = t0;
    p1->m04 = t1;
    t2 = *(volatile s16 *)&p0->m136;
    t3 = p0->m138;
    p1->m06 = t2;
    p1->m08 = t3;
    return p0->m143;
}
