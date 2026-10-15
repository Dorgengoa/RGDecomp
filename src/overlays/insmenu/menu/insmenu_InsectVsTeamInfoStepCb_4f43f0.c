#include "types.h"

/* insmenu 0x004F43F0 (484 bytes, 121 instructions, 21 calls) -- the map's
 * cancel path.  Both arms of the outer chain are the same four-term
 * short-circuit against a different mask, and the `func_2F6660` guard is a
 * single condition rather than an early return so the shared epilogue keeps
 * its predecessors and the branch into it stays LIKELY.
 */

typedef struct Ctx Ctx;

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

extern u8   D_00484360;     /* gp - 0xE10 */
extern Obj *D_00484104;     /* gp - 0x106C */

extern s32  func_2F6660(void);
extern s32  func_1839F0(const void *a, s32 b);
extern s32  func_2882C0(void);
extern void func_291110(const void *a, s32 b, s32 c, s32 d);
extern void func_37B490(s32 a);
extern void func_28EA90(const void *a, s32 b, s32 c);
extern void func_436450(Obj *a, s32 b);
extern void func_434410(Obj *a, s32 b, s32 c);
extern s32  insmenu_InsectVsTeamListGetSelRec_4f93b0(void);
extern Handle *func_1FEDE0(void);
extern void func_4319F0(Ctx *a, char *b, s32 c);
extern void func_4356D0(Obj *a, s32 b, char *c);

s32 insmenu_InsectVsTeamInfoStepCb_4f43f0(void)
{
    char buf[0x100];
    char *p;
    u32 n;
    s32 tag;

    if (func_2F6660() == 0) {
        if ((func_1839F0(D_004B2570, 0x20) != 0) ||
            ((func_2882C0() != 0) && (func_1839F0(D_004B27E0, 0x20) != 0))) {
            func_291110(D_004FA180, 0x9CA7, 0, 1);
            func_291110(D_004FA180, 0x9CAA, 1, 1);
            func_291110(D_004FA180, 0x88CC, 1, 1);
            func_291110(D_004FA180, 0x88E0, 1, 1);
            func_291110(D_004FA180, 0x88F4, 1, 1);
            func_37B490(0x890D);
            func_28EA90(D_004FA1A0, 0x88BD, 0);
        } else if ((func_1839F0(D_004B2570, 0x10) != 0) ||
                   ((func_2882C0() != 0) && (func_1839F0(D_004B27E0, 0x10) != 0))) {
            D_00484360 = 1;
            if (D_00484104 != 0) {
                func_436450(D_00484104, 4);
                func_434410(D_00484104, 0x6D61, 1);
                D_00484104->fieldE6 = 0;
                tag = insmenu_InsectVsTeamListGetSelRec_4f93b0();
                p = buf;
                n = 0x100;
                if (p != 0) {
                    do {
                        *p = 0;
                        n -= 1;
                        p += 1;
                    } while (n != 0);
                }
                func_4319F0(func_1FEDE0()->field24, buf, tag);
                func_4356D0(D_00484104, 0, buf);
                func_28EA90(D_004FA1A0, 0x88C1, 0);
            }
        }
    }
    return 1;
}
