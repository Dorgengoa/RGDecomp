#include "types.h"

extern s32 GetLoaderMgr_1f59d0(void);
extern s32 LoaderGetStatus_1cd4f0(s32, s32);
extern s32 NpcTalkTextRelease_41ddb0(void *);
extern s32 LoaderGetData_1cd490(s32, s32, void *);
extern s32 NpcTalkTextCfgExec_41dbb0(void *, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
};

s32 NpcTalkTextPoll_41dca0(struct Obj0 *p0)
{
    s32 v3C;
    s32 t0;
    s32 rv11;
    s32 t1;
    s32 rv10;
    s32 r0;
    s32 rv9;
    s32 t2;
    s32 r1;
    s32 rv8;
    s32 r2;
    s32 rv7;
    s32 t3;
    s32 r3;
    s32 t4;
    s32 t5;
    s32 t6;
    s32 r4;
    s32 rv5;
    s32 r6;
    s32 t7;

    t0 = p0->m10;
    if (t0 == 3) {
        return 3;
    }
    if (t0 != 2) {
        rv11 = 1;
    } else {
        t1 = p0->m14;
        if (t1 < 0) {
            p0->m10 = 1;
            rv10 = 1;
        } else {
            r0 = GetLoaderMgr_1f59d0();
            if (r0 == 0) {
                rv9 = 2;
            } else {
                t2 = p0->m14;
                r1 = LoaderGetStatus_1cd4f0(r0, t2);
                if (r1 == -1) {
                    r2 = NpcTalkTextRelease_41ddb0(p0);
                    p0->m10 = 1;
                    rv8 = 1;
                } else {
                    if (r1 != 1) {
                        rv7 = 2;
                    } else {
                        v3C = 0;
                        t3 = p0->m14;
                        r3 = LoaderGetData_1cd490(r0, t3, &v3C);
                        t4 = v3C;
                        t5 = p0->m1C;
                        t6 = p0->m18;
                        r4 = NpcTalkTextCfgExec_41dbb0(p0, r3, t4, t5, t6);
                        rv5 = 1;
                        if (r4 != 0) {
                            p0->m10 = 3;
                            rv5 = 3;
                        } else {
                            p0->m10 = 1;
                            rv5 = 1;
                        }
                        r6 = NpcTalkTextRelease_41ddb0(p0);
                        t7 = p0->m10;
                        rv7 = t7;
                    }
                    rv8 = rv7;
                }
                rv9 = rv8;
            }
            rv10 = rv9;
        }
        rv11 = rv10;
    }
    return rv11;
}
