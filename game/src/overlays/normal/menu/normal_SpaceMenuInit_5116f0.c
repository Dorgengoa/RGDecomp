/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuInit_5116f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005116F0 -- allocates the map-marker module: a 0xC-byte descriptor
 * and a 0x70-byte node off the same pool, then clears the descriptor and hands
 * it its list handle.  Pass-33 LIST rank: 140 bytes, 35 instructions, ONE
 * conditional branch, 7 calls.
 *
 * The three gp globals are all WRITTEN, and all three are `%gp_rel` in the
 * listing, so they stay plain 4-byte externs -- the incomplete-array escape of
 * levers.d/main-pass33-lists is only needed when retail addresses a written
 * global through %hi/%lo.
 *
 * `D_004846B0 = p;` is written BEFORE the first call, which is what sinks its
 * store into that call's delay slot; the SECOND allocation then re-reads the
 * global rather than reusing the parameter, so its argument is the global.
 *
 * Two levers, each worth exactly what it cost:
 *  * the node is REASSIGNED (`q = normal_SpaceMenuObjCtor_514750(q);`) and stored once
 *    after the guard, not stored in both arms of an if/else.  mwcc duplicates
 *    the single store into the branch-likely slot by itself -- writing the
 *    duplicate in the SOURCE is one word long and re-normalises the value
 *    through `dsll32`/`dsra32`.
 *  * `b` NAMES the descriptor for the three clears.  Written as three
 *    `D_004846B4->f..` stores mwcc re-loads the handle before each one -- a
 *    load will not cross a store that might alias the global it came from
 *    (levers.d/insect-load-across-store, seen here on NORMAL).  The two uses
 *    AFTER the calls are written through the global on purpose: retail reloads
 *    there, because the call clobbered it. */

typedef struct Blk { s16 f00; u8 pad02[2]; s32 f04; s32 f08; } Blk;

extern void *D_004846B0;          /* gp - 0xAC0 */
extern Blk  *D_004846B4;          /* gp - 0xABC */
extern void *D_004846B8;          /* gp - 0xAB8 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern s32 normal_SpaceMenuInit_5116f0(void *p);

s32 normal_SpaceMenuInit_5116f0(void *p)
{
    Blk  *b;
    void *q;

    D_004846B0 = p;
    D_004846B4 = MemStackNew_14e230(0xC, p);
    q = MemStackNew_14e230(0x70, D_004846B0);
    if (q != 0) {
        q = normal_SpaceMenuObjCtor_514750(q);
    }
    D_004846B8 = q;
    normal_SpaceMenuObjInit_5146b0(q);
    b = D_004846B4;
    b->f04 = 0;
    b->f08 = 0;
    b->f00 = 0;
    D_004846B4->f08 = MenuStateTableForId_42c950(GetMenuResGroup_206a40(), 0xA);
    StateMachineSetState_28ede0(D_004846B4, 1, 1);
    return 1;
}
