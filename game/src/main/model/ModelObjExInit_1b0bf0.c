/* rgp:protos */
#define RGP_SELF_ModelObjExInit_1b0bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s32 memset(void *, s32, s32);
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4F0];
    s32 m4F0;
    u8 pad4F4[0x4];
    s32 m4F8;
    s32 m4FC;
    s32 m500;
    s32 m504;
    s32 m508;
    s32 m50C;
    s32 m510;
    s32 m514;
    s32 m518;
    s32 m51C;
    s32 m520;
    s32 m524;
    s32 m528;
    s32 m52C;
    s32 m530;
    s32 m534;
    u8 pad538[0x4];
    s32 m53C;
    u8 m540;
    u8 pad541[0x3];
    s32 m544;
    u8 pad548[0xC];
    s32 m554;
};

void ModelObjExInit_1b0bf0(struct Obj0 *p0)
{
    s32 r1;

    ModelObjInit_1ae420(p0);
    r1 = ((s32)memset((struct Obj0 *)((u8 *)p0 + 0x4F0), 0, 0x2C));
    p0->m4F0 = -1;
    p0->m4FC = -1;
    p0->m500 = -1;
    p0->m4F8 = 1;
    p0->m504 = 1;
    p0->m508 = 0x3F800000;
    p0->m50C = 0;
    p0->m510 = -1;
    p0->m514 = 0;
    p0->m518 = 0;
    p0->m51C = 0;
    p0->m520 = 0x43200000;
    p0->m524 = 0x44960000;
    p0->m528 = 0;
    p0->m52C = 0x3F800000;
    p0->m530 = 0x3F800000;
    p0->m534 = 0;
    MotionEventListClear_1b4aa0((struct Obj0 *)((u8 *)p0 + 0x568));
    p0->m53C = 0;
    p0->m540 = 0;
    p0->m544 = 0;
    p0->m554 = 0;
}
