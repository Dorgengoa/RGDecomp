#include "types.h"

extern s32 GetMapMgr_201a90(void);
extern s32 CharaGetAreaId_213c90(s32);
extern s32 MapSlotsFindBlockById_1e49b0(s32, s32, s32);
extern s32 GetNavMgr_2d1950(void);
extern s32 MapBlockGetNavGraphId_1e0050(s32);
extern s32 NavMgrFindGraphById_30cae0(s32, s32);
extern s32 NavFindNearestEdgePoint_310380(s32, void *, s32, s32);
extern s32 NavEdgeGetFlags_311710(s32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 NavEdgeAtPosIsRowLine_2bd1e0(s32 p0, s32 p1)
{
    u128 v30;
    s32 rv11;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 rv10;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 rv9;
    s32 r6;
    s32 rv8;
    s32 r7;

    if (p1 == 0) {
        rv11 = 0;
    } else {
        r0 = GetMapMgr_201a90();
        r1 = CharaGetAreaId_213c90(p1);
        r2 = MapSlotsFindBlockById_1e49b0(r0, r1, 0);
        if (r2 == 0) {
            rv10 = 0;
        } else {
            r3 = GetNavMgr_2d1950();
            r4 = MapBlockGetNavGraphId_1e0050(r2);
            r5 = NavMgrFindGraphById_30cae0(r3, r4);
            if (r5 == 0) {
                rv9 = 0;
            } else {
                r6 = NavFindNearestEdgePoint_310380(r5, &v30, p0, 0);
                if (r6 == 0) {
                    rv8 = 0;
                } else {
                    r7 = NavEdgeGetFlags_311710(r6);
                    rv8 = ((r7 & 0x40000) != 0);
                }
                rv9 = rv8;
            }
            rv10 = rv9;
        }
        rv11 = rv10;
    }
    return rv11;
}
