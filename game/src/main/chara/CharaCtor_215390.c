/* rgp:protos */
#define RGP_SELF_CharaCtor_215390 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x424];
    s16 m424;
    s16 m426;
    u8 pad428[0xD8];
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
    u8 pad530[0x20];
    s16 m550;
    s16 m552;
    u8 pad554[0x4];
    s16 m558;
    s16 m55A;
    s16 m55C;
    s16 m55E;
    u8 pad560[0x20];
    s32 m580;
    s32 m584;
    s32 m588;
};

struct Obj0 *CharaCtor_215390(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 l3;

    SrtCtor_1c7320(p0);
    SrtCtor_1c7320((struct Obj0 *)((u8 *)p0 + 0x50));
    p0->m550 = 2;
    p0->m552 = 0;
    p0->m558 = 0;
    p0->m55E = -1;
    p0->m55A = -1;
    p0->m55C = -1;
    p0->m500 = 0;
    p0->m504 = 0;
    p0->m508 = 0;
    p0->m50C = 0x3F800000;
    p0->m510 = 0;
    p0->m514 = 0;
    p0->m518 = 0;
    p0->m51C = 0x3F800000;
    p0->m520 = 0;
    p0->m524 = 0;
    p0->m528 = 0;
    p0->m52C = 0x3F800000;
    XformRecSetDefaultNameMaybe_1c6940((struct Obj0 *)((u8 *)p0 + 0x500));
    l3 = 0;
    do {
        *(s32 *)((u8 *)p0 + (l3 << 2) + 0x530) = 0x41000000;
        l3 = (l3 + 1);
    } while (l3 < 4);
    p0->m580 = 0;
    p0->m584 = 0;
    p0->m588 = 0;
    ScriptVmCtor_176be0((struct Obj0 *)((u8 *)p0 + 0x590));
    ScriptVmCtor_176be0((struct Obj0 *)((u8 *)p0 + 0x5E4));
    ExecInfoInit_3a7940((struct Obj0 *)((u8 *)p0 + 0x8B0));
    TargetRefCtor_2e71f0((struct Obj0 *)((u8 *)p0 + 0x97C));
    TargetRefCtor_2e71f0((struct Obj0 *)((u8 *)p0 + 0x9AC));
    TargetRefCtor_2e71f0((struct Obj0 *)((u8 *)p0 + 0x9DC));
    CharaInit_2150c0(p0);
    if (p1 >= 0) {
        if (p2 >= 0) {
            p0->m424 = p1;
            p0->m426 = p2;
        }
    }
    return p0;
}
