/* rgp:protos */
#define RGP_SELF_insect_InsectSeqStep_4ea0a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EA0A0 -- 656 bytes, 164 instructions, 21 calls, 15 conditional
 * branches.  The ONE open `jalr` unit on this image whose target register is
 * $2, not $25, so it is ordinary C: an indirect call through the function
 * pointer at +0x14 of the handle in o->f190 ([[jalr-is-cpp-virtual]] screens
 * $25 only).
 *
 * TWO NESTED SWITCHES, both read off the compare chain REVERSED:
 *   outer, insect_InsectSeqGetState_4ea340(o) == o->f24: chain 3,2,1,0 -> source 0,1,2,3,
 *     block addresses 4EA11C, 4EA144, 4EA160 ascending and `case 3:` EMPTY and
 *     LAST -- its `beql` targets 4EA2D8, the join PLUS ONE, because the join's
 *     `daddu $4,$16,$0` already rides the branch's own delay slot;
 *   inner, insect_InsectSeqGetSubState_4ea330(o) == o->f28: chain 3,1,2,0 -> source 0,2,1,3,
 *     block addresses 4EA19C, 4EA1DC, 4EA200, 4EA2C4.
 * The inner chain's first compare materialises 3 into $5, and case 3's body
 * then passes that same $5 to insect_InsectSeqSetState_4ea3c0 with an EMPTY argument set,
 * so the dispatch constant is CSE'd into the arm.
 *
 * THREE STORES RIDE ANNULLED DELAY SLOTS and so are the FIRST statement of the
 * arm they belong to: `sw $4,0x1DC($16)` ($4 == 1) opens inner case 1,
 * `sw $4,0x1E0($16)` opens inner case 0, and `sw $0,0x4C($29)` opens the
 * rc == 1 block.
 *
 * `if (o->f000 != 0) func_14DE90(o->f000);` -- the branch tests $4, the
 * argument register itself, so the guard and the argument are the same load.
 */

typedef struct Sub Sub;
typedef struct Hnd Hnd;
typedef struct Obj Obj;

struct Sub {
    s32 f00;
};

struct Hnd {
    u8   pad00[0x14];
    s32 (*f14)(Sub *s);             /* +0x14 */
};

struct Obj {
    void *f000;                     /* +0x000 */
    u8    pad004[0x2C - 0x4];
    u8    f02C[0x190 - 0x2C];       /* +0x02C */
    Hnd  *f190;                     /* +0x190 */
    u8    pad194[0x198 - 0x194];
    s32   f198;                     /* +0x198 */
    u8    pad19C[0x1D8 - 0x19C];
    s32   f1D8;                     /* +0x1D8 */
    s32   f1DC;                     /* +0x1DC */
    s32   f1E0;                     /* +0x1E0 */
};

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectSeqStep_4ea0a0(Obj *o, void *a)
{
    s32   sp4C;
    void *p;
    void *q;

    if (o->f000 == 0) {
        insect_InsectSeqStateHistClear_4ea460(o);
        insect_InsectSeqSubStateHistClear_4ea430(o);
        insect_InsectSeqSetState_4ea3c0(o, 0);
    }

    switch (insect_InsectSeqGetState_4ea340(o)) {
    case 0:
        insect_InsectSeqInit_4ea550(o);
        insect_InsectSeqSetHeap_4ea530(o, a);
        insect_InsectSeqSetState_4ea3c0(o, 1);
        break;
    case 1:
        insect_InsectSeqReset_4ea4d0(o);
        insect_InsectSeqSetState_4ea3c0(o, 3);
        break;
    case 2:
        switch (insect_InsectSeqGetSubState_4ea330(o)) {
        case 0:
            o->f1E0 = 1;
            o->f1DC = 0;
            o->f1D8 = -1;
            p = GetLoaderMgr_1f59d0();
            if (p != 0) {
                o->f1D8 = LoaderRequestFile_1cd870(p, &o->f198, 0);
            }
            insect_InsectSeqSetSubState_4ea350(o, 2);
            break;
        case 2:
            if (((unsigned char)insect_InsectSeqIsCmdIdle_4e9f80(o)) != 0) {
                insect_InsectSeqSetSubState_4ea350(o, 1);
            }
            break;
        case 1:
            o->f1DC = 1;
            p = GetLoaderMgr_1f59d0();
            if (p != 0) {
                switch (LoaderGetStatus_1cd4f0(p, o->f1D8)) {
                case -1:
                    break;
                case 0:
                    break;
                case 1:
                    sp4C = 0;
                    q = LoaderGetData_1cd490(p, o->f1D8, &sp4C);
                    if (o->f000 != 0) {
                        MemStackHeapReinit_14de90(o->f000);
                    }
                    insect_InsectSeqCmdQueueClear_4ea710(o->f02C);
                    insect_InsectSeqParseScript_4ea620(o->f02C, q, sp4C, o->f000);
                    insect_InsectSeqSetSubState_4ea350(o, 3);
                    LoaderReleaseById_1cd340(p, o->f1D8);
                    break;
                default:
                    insect_InsectSeqSetState_4ea3c0(o, 3);
                    insect_InsectSeqSetSubState_4ea350(o, 0);
                    break;
                }
            }
            break;
        case 3:
            o->f1DC = 2;
            o->f1E0 = 0;
            insect_InsectSeqSetState_4ea3c0(o, 3);
            break;
        }
        break;
    case 3:
        break;
    }

    insect_InsectSeqBindHeadHandler_4ea060(o);
    if (o->f190 != 0) {
        if (o->f190->f14(((Sub *)insect_InsectSeqCmdQueueHead_4ea5c0(o->f02C))) != 0) {
            insect_InsectSeqCmdQueuePop_4ea590(o->f02C);
        }
    }
}
