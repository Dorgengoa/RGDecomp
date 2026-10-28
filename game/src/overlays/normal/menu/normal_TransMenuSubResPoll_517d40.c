/* rgp:protos */
#define RGP_SELF_normal_TransMenuSubResPoll_517d40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00517D40 (768 B / 192 words) -- pumps one page of the 0x38-byte
 * record ring (the same ring normal_TransMenuSubResRequest_518040 fills) and hands each ready
 * record to the renderer the way the current page mode D_004806CC wants it.
 * Returns 1 only when the page is finished AND the retry counter has run out.
 *
 * Read off the listing:
 *  - `sll $3,$19,3 / subu $3,$3,$19 / sll $16,$3,3` is i * 0x38, i.e.
 *    &((Rec *)D_0048478C)[i] with sizeof(Rec) == 56 -- the base pointer is
 *    RELOADED from gp at every use, only the scaled index is CSE'd.
 *  - `bgez / sra 4 / addiu 0xF / sra 4` is a signed `w / 16`.
 *  - the eight `beq` against 2,3,4,5,6,7,8,1 followed by `bnel $3,$0` is ONE
 *    `||` chain in SOURCE ORDER, not a jump table; the last term is the
 *    `(mode == 0 && i == 0)` pair.
 *  - `beql $2,$3,.L00517FC4` with the increment in the delay slot is the FIRST
 *    predecessor of the shared continue being threaded
 *    (levers.d/mwcc-branch-likely-duplication.md FIX 3); the other two guards
 *    reach the increment label plainly.
 */
typedef struct Rec { u8 pad000[56]; } Rec;

extern void *D_004846E4;          /* gp - 0xA8C  */
extern s16   D_00484750;          /* gp - 0xA20  */
extern s16   D_00484754;          /* gp - 0xA1C  */
extern void *D_0048475C;          /* gp - 0xA14  */
extern void *D_00484784;          /* gp - 0x9EC  */
extern void *D_0048478C;          /* gp - 0x9E4  */
extern void *D_00484794;          /* gp - 0x9DC  */
extern s16   D_004806CC;          /* gp - 0x4AA4 */
extern s8    normal_D_00526590[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void  memcpy(void *a, void *b, s32 c);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransMenuSubResPoll_517d40(void)
{
    void *p;
    s32   n;
    s32   i;
    void *h;
    void *q;
    void *r;
    s32   w;

    if (D_004806CC < 0) {
        return 0;
    }
    p = D_004846E4;
    n = normal_D_00526590[D_004806CC];
    for (i = 0; i < n; i++) {
        if (LoadHandleGetId_28b220(&((Rec *)D_0048478C)[i]) == -1) {
            continue;
        }
        if (((unsigned char)LoadHandleIsPending_28b210(&((Rec *)D_0048478C)[i])) == 0) {
            continue;
        }
        if (LoadHandleGetStatus_28b2e0(&((Rec *)D_0048478C)[i]) != 1) {
            continue;
        }
        h = GetDrawCtxNameTable_15de40();
        q = LoadHandleGetData_28b270(&((Rec *)D_0048478C)[i], &w);
        MemStackAlign64_14d8e0(p);
        if (D_004806CC == 2 || D_004806CC == 3 || D_004806CC == 4 ||
            D_004806CC == 5 || D_004806CC == 6 || D_004806CC == 7 ||
            D_004806CC == 8 || D_004806CC == 1 ||
            (D_004806CC == 0 && i == 0)) {
            if (D_004806CC == 0) {
                r = MemStackAllocAligned64_14da10(p, w / 16 + 1);
                memcpy(r, q, w);
                D_00484794 = r;
                NameTableRegisterImArchive_1594d0(h, r, 0x32D, p, 0);
            } else if (D_004806CC == 1) {
                MemMoveIfDiff_289c60(q, w, D_00484784);
                NameTableRegisterImArchive_1594d0(h, D_00484784, 0x32C, p, 0);
                normal_TransMenuIconClutBuild_518590();
            } else {
                r = MemStackAllocAligned64_14da10(p, w / 16 + 1);
                memcpy(r, q, w);
                NameTableRegisterImArchive_1594d0(h, r, 0x32C, p, 0);
            }
        } else {
            r = MemStackAllocAligned64_14da10(p, w / 16 + 1);
            memcpy(r, q, w);
            SaveIconFilesLoad_37bbd0(D_0048475C, r);
            normal_TransSaveIconSysInit_518a50(D_0048475C);
        }
        LoadHandleFree_28b230(&((Rec *)D_0048478C)[i]);
    }
    if (((unsigned char)LoadHandlesAllReady_28b070(D_0048478C, n)) == 1) {
        if (D_00484754 < 10) {
            D_00484754 = D_00484754 + 1;
        } else {
            D_00484750 = 1;
            D_00484754 = 10;
            return 1;
        }
    }
    return 0;
}
