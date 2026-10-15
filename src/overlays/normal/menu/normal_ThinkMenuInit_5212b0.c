#include "types.h"
/* normal 0x005212B0 -- an 81-instruction, ZERO-conditional-branch scene
 * builder: 18 calls and 11 gp publishes.  Every value is re-read from its
 * global at each use because a call separates the uses (mwcc's per-basic-block
 * CSE reproduces that for free); the two allocator results that are used
 * immediately are held in locals instead.
 *
 * The overlay-data addresses (`D_00528030`, `D_00526050`, `D_00528060`) and
 * the two main-image addresses are all `const` -- 0x00528030 is 0xA2EC0 past
 * `_gp`, so a `%gp_rel` relocation would not resolve and the LINK would fail
 * with a GP offset overflow while the object compiled clean.
 * One of the 55 unnamed functions; see scripts/n_unnamed.py. */
extern void *D_00484918;
extern void *D_0048491C;
extern void *D_00484920;
extern s16   D_00484928;
extern s32   D_0048492C;
extern void *D_00484930;
extern void *D_00484934;
extern u8    D_00484938;
extern u8    D_0048493C;
extern u8    D_00484940;
extern u8    D_00480788;

extern const u8  D_00526050;
extern const u8  D_00528030;
extern const u8  D_00528060;
extern const u8  D_004B2570;
extern const s32 D_004659E8;

extern void *func_206A60(void);
extern void *func_206A50(void);
extern void  func_14D830(void *p);
extern void *func_14E230(s32 id, void *h);
extern void  func_2912E0(void *p);
extern void  func_28EC80(const u8 *p);
extern void  func_183960(const u8 *p);
extern void  func_183D50(const u8 *p, u32 a, s32 b, s32 c);
extern void  func_183950(const u8 *p, s32 a);
extern void  func_28DB70(const u8 *p);
extern void *func_15DE40(void);
extern void  func_158AC0(void *p, s32 id);
extern void  func_2A5920(void *p, s32 n, f32 x, f32 y, s32 a, s32 b);
extern void  func_2A5900(void *a, void *b, const u8 *c, s16 *d, void *e);
extern void  normal_ThinkMenuResRequest_5218d0(void);
extern void  normal_ThinkMenuResPoll_5217e0(void);

void normal_ThinkMenuInit_5212b0(void)
{
    void *h;

    D_00484940 = 0;
    h = func_206A60();
    D_00484918 = h;
    func_14D830(h);
    h = func_206A50();
    D_0048491C = h;
    func_14D830(h);
    h = func_14E230(0x14, D_00484918);
    D_00484920 = h;
    func_2912E0(h);
    func_28EC80(&D_00528030);
    D_00484930 = (void *)&D_00526050;
    D_0048492C = 0;
    D_00484928 = 0;
    func_183960(&D_004B2570);
    func_183D50(&D_004B2570, 0xF00C, 0xA, 3);
    func_183950(&D_004B2570, 0x78);
    D_0048493C = 1;
    D_00484938 = 1;
    D_00480788 = 1;
    func_28DB70(&D_00528060);
    func_158AC0(func_15DE40(), 0x32D);
    h = func_14E230(0x1B4, D_00484918);
    D_00484934 = h;
    func_2A5920(h, (s8)(D_004659E8 + 1), 0.0f, 0.0f, 0, 1);
    func_2A5900(D_00484934, D_00484920, &D_00528030, &D_00484928, D_00484918);
    normal_ThinkMenuResRequest_5218d0();
    normal_ThinkMenuResPoll_5217e0();
}
