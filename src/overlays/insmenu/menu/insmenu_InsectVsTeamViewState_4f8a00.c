#include "types.h"

/* insmenu 0x004F8A00 (940 bytes, 235 instructions, 33 calls) -- the map-marker
 * toggle.  ⚠ TWO parameters: the flag it tests arrives in $5, so it is the
 * SECOND one, and the first is never read.  m2c reads the `daddu $16, $5, $0`
 * as `arg1`.
 */

typedef struct Kind Kind;
struct Kind {
    u8  pad00[8];
    s16 field08;
};

typedef struct Ctx Ctx;
struct Ctx {
    u8   pad0000[0x1188];
    Kind *field1188;
};

typedef struct Handle Handle;
struct Handle {
    u8  pad00[0x24];
    Ctx *field24;
};

typedef struct Obj Obj;
struct Obj {
    u8  pad00[0xE6];
    s16 fieldE6;
};

extern const u8 D_004FA180[];
extern const u8 D_004FA1A0[];
extern const u8 D_004B2570[];
extern const u8 D_004B27E0[];

extern u8   D_004842E8;     /* gp - 0xE88, passed by address */
extern s16  D_00484364;     /* gp - 0xE0C */
extern volatile s16 D_00484368;     /* gp - 0xE08 */
extern u8   D_00484360;     /* gp - 0xE10 */
extern u8   D_00484358;     /* gp - 0xE18 */
extern Obj *D_00484104;     /* gp - 0x106C */
extern f32  D_0047D3C8;     /* gp - 0x7DA8 */

extern Handle *func_1FEDE0(void);
extern void func_28EA90(const void *a, s32 b, s32 c);
extern s32  func_28E100(const void *a, const void *b, const void *c, s32 d);
extern s32  func_430580(Ctx *a, s32 b);
extern void func_379400(s32 a, s32 b);
extern void func_379000(s32 a, s32 b);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
extern s32  func_2F6660(void);
extern s32  func_1839F0(const void *a, s32 b);
extern s32  func_2882C0(void);
extern void func_436450(Obj *a, s32 b);
extern void func_434410(Obj *a, s32 b, s32 c);
extern void func_4319F0(Ctx *a, char *b, s32 c);
extern void func_4356D0(Obj *a, s32 b, char *c);
extern s32  insmenu_InsectVsBattleTeamPending_4f9680(void);

s32 insmenu_InsectVsTeamViewState_4f8a00(s32 p1, s32 show)
{
    Handle *hnd;
    Handle *cur;
    s32 mode;
    s16 kind;
    u8  ok;
    s32 arg;
    s32 tag;
    s32 arg2;
    s32 tag2;
    char buf[0x100];
    char *p;
    u32 n;

    hnd = func_1FEDE0();
    if (show != 0) {
        func_28EA90(D_004FA1A0, 0x7534, 0);
    }
    mode = func_28E100(D_004FA1A0, D_004B2570, D_004B27E0, 0);
    if ((u32)(mode - 1) < 2) {
        cur = func_1FEDE0();
        kind = cur->field24->field1188->field08;
        ok = 0;
        if ((kind == 0x1F6) || (kind == 0x1F7) || (kind == 0x193)) {
            ok = 1;
        }
        if ((mode == 1) && ok && (D_00484358 == 0)) {
            D_00484368 = 0;
            D_00484360 = 0;
            func_379400(func_430580(cur->field24, 0), 2);
            D_00484364 = 0;
            func_28EDE0(&D_004842E8, 0x88CC, 0);
        } else if ((mode == 2) && ok && (D_00484358 == 0)) {
            D_00484368 = 0;
            D_00484360 = 0;
            func_379400(func_430580(cur->field24, 0), 2);
            D_00484364 = 1;
            func_28EDE0(&D_004842E8, 0x88CC, 0);
        } else if (D_00484358 != 0) {
            if (mode == 2) {
                D_00484358 = 0;
            }
            if (D_00484360 != 0) {
                func_379400(func_430580(cur->field24, 0), 2);
                D_00484360 = 0;
            }
            func_290690(D_004FA180, 0x9CA7, 0.0f, D_0047D3C8, -1.0f);
            func_28EDE0(&D_004842E8, 0x88C5, 0);
        } else {
            func_290690(D_004FA180, 0x9CA7, 0.0f, D_0047D3C8, -1.0f);
            if (D_00484360 != 0) {
                func_379400(func_430580(cur->field24, 0), 0);
            }
            D_00484360 = 0;
            func_28EDE0(&D_004842E8, 0x88C5, 0);
        }
    }
    if ((func_2F6660() == 0) &&
        ((func_1839F0(D_004B2570, 0x10) != 0) ||
         ((func_2882C0() != 0) && (func_1839F0(D_004B27E0, 0x10) != 0)))) {
        if (D_00484368 == 0) {
            D_00484368 = 1;
        } else {
            D_00484368 = 0;
        }
        if (D_00484368 == 0) {
            D_00484360 = 0;
            tag = func_430580(hnd->field24, 0);
            arg = 0;
            if (insmenu_InsectVsBattleTeamPending_4f9680() != 0) {
                arg = 2;
            }
            func_379400(tag, arg);
        } else {
            D_00484360 = 1;
            if (D_00484104 != 0) {
                func_436450(D_00484104, 4);
                func_434410(D_00484104, 0x6D61, 1);
                D_00484104->fieldE6 = 0;
                tag2 = func_430580(hnd->field24, 0);
                p = buf;
                n = 0x100;
                if (p != 0) {
                    do {
                        *p = 0;
                        n -= 1;
                        p += 1;
                    } while (n != 0);
                }
                func_4319F0(func_1FEDE0()->field24, buf, tag2);
                func_4356D0(D_00484104, 0, buf);
                arg2 = 0;
                if (insmenu_InsectVsBattleTeamPending_4f9680() != 0) {
                    arg2 = 2;
                }
                func_379000(tag2, arg2);
            }
        }
    }
    return 1;
}
