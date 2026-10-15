#include "types.h"
/* normal 0x00516290 -- the scene-enter REGISTRATION LIST: two overlay
 * bring-up calls, the 0x4B2570 text-device open/close pair, the block of
 * eight gp state stores, then a null-guarded chain that hands the current
 * selection to the camera.
 *
 * Every `beqz` in the chain jumps to the SHARED TAIL, and what retail falls
 * through into is the `if` body -- so the guards are NESTED ifs, not early
 * returns.  `sh $0, -0xA20($28)` and `sw $0, 0x518($16)` each sit in the
 * following call's delay slot, so both stores precede their call in source.
 * `lui $2,0x4170 / mtc1 $2,$f12` is the literal 15.0f. */

typedef struct Act { u8 pad00[0x30]; s16 f30; } Act;
typedef struct Ent { u8 pad00[0x18]; Act *f18; } Ent;
typedef struct Cam { u8 pad00[0x518]; s32 f518; } Cam;

extern const u8 D_004B2570[];

extern s32   D_00484770;          /* gp - 0xA00  */
extern s16   D_004806C8;          /* gp - 0x4AA8 */
extern void *D_00484740;          /* gp - 0xA30  */
extern void *D_00484724;          /* gp - 0xA4C  */
extern void *D_0048475C;          /* gp - 0xA14  */
extern s16   D_0048474C;          /* gp - 0xA24  */
extern s8    D_00484748;          /* gp - 0xA28  */
extern s16   D_00484750;          /* gp - 0xA20  */

extern void  normal_TransMenuResFree_5181a0(void);
extern void  normal_TransMenuSubResFree_517cf0(void);
extern void  func_183960(const void *a);
extern void  func_183940(const void *a);
extern void  normal_TransWarpListFree_51a990(void);
extern void *func_15DE40(void);
extern void  func_158AC0(void *a, s32 b);
extern Ent  *func_1FEDE0(void);
extern s32   func_201A90(void);
extern void  func_1E49B0(s32 a, s16 b, s32 *c);
extern s32   func_1DCB50(s32 a);
extern Cam  *func_201A70(void);
extern void  func_321E80(Cam *a, f32 b);
extern void  func_321770(Cam *a);
extern void *func_206A40(void);
extern void  func_42B650(void *a, s32 b);

void normal_TransMenuRelease_516290(void)
{
    Ent *e;
    Cam *cam;
    s32  h;
    s32  sel;

    normal_TransMenuResFree_5181a0();
    normal_TransMenuSubResFree_517cf0();
    func_183960(D_004B2570);
    func_183940(D_004B2570);
    D_00484770 = 0;
    D_004806C8 = 2;
    D_00484740 = 0;
    D_00484724 = 0;
    D_0048475C = 0;
    D_0048474C = 0;
    D_00484748 = 0;
    D_00484750 = 0;
    normal_TransWarpListFree_51a990();
    func_158AC0(func_15DE40(), 0x32D);
    e = func_1FEDE0();
    h = func_201A90();
    if (h != 0) {
        sel = 0;
        func_1E49B0(h, e->f18->f30, &sel);
        if (sel != 0) {
            if (func_1DCB50(sel) != 0) {
                cam = func_201A70();
                if (cam != 0) {
                    cam->f518 = 0;
                    func_321E80(cam, 15.0f);
                    func_321770(cam);
                }
            }
        }
    }
    func_42B650(func_206A40(), 2);
}
