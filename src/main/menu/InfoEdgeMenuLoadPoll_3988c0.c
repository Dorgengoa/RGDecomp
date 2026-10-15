#include "types.h"

extern s32 GetLoaderMgr_1f59d0(void);
extern s32 LoaderGetStatus_1cd4f0(s32, s32);
extern s32 LoaderGetData_1cd490(s32, s32, void *);
extern void * GetWorldDataMgr_1fedf0(void);
extern s32 MemStackAlign64_14d8e0(s32);
extern s32 MsgTableParseText_28aab0(s32, s32, s32);
extern s32 LoaderReleaseById_1cd340(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047FF64;
extern s32 D_0047FF68;
extern s32 D_004835B0;
extern u8 D_004835B4;

struct Obj0;

struct Obj0 {
    u8 pad000[0x24];
    s32 m24;
};

s32 InfoEdgeMenuLoadPoll_3988c0(void)
{
    s32 v4C;
    s32 t0;
    s32 rv9;
    s32 t1;
    s32 rv8;
    s32 r0;
    s32 t2;
    s32 r1;
    s32 rv7;
    s32 t3;
    s32 r2;
    struct Obj0 *r3;
    s32 t4;
    s32 r4;
    s32 t5;
    s32 r5;
    s32 t6;
    s32 r6;

    t0 = D_0047FF68;
    if (t0 != 0) {
        rv9 = 0;
    } else {
        t1 = D_0047FF64;
        rv8 = 1;
        if (t1 == -1) {
            rv8 = 0;
        } else {
            r0 = GetLoaderMgr_1f59d0();
            t2 = D_0047FF64;
            r1 = LoaderGetStatus_1cd4f0(r0, t2);
            D_0047FF68 = r1;
            rv7 = r1;
            if (r1 == 1) {
                t3 = D_0047FF64;
                r2 = LoaderGetData_1cd490(r0, t3, &v4C);
                r3 = GetWorldDataMgr_1fedf0();
                t4 = r3->m24;
                r4 = MemStackAlign64_14d8e0(t4);
                t5 = v4C;
                r5 = MsgTableParseText_28aab0(t4, r2, t5);
                t6 = D_0047FF64;
                D_004835B0 = r5;
                r6 = LoaderReleaseById_1cd340(r0, t6);
                D_0047FF64 = -1;
                D_004835B4 = 1;
                rv7 = 1;
            }
            rv8 = 1;
        }
        rv9 = rv8;
    }
    return rv9;
}
