#include "types.h"
/* normal 0x0051A020 -- two guarded blocks around a widget teardown.
 * ⚠ `$4` is never read: the first parameter leaves no trace, so its presence
 * is inferred from the callers rather than measured.
 * One of the 55 unnamed functions; see scripts/n_unnamed.py. */
extern const u8 D_00526818;
extern const u8 D_00527F10;

extern void func_37B460(s32 id);
extern void func_1782A0(const u8 *p, s32 n, f32 x, f32 y, f32 z);
extern s32  func_178110(const u8 *p);
extern void func_373100(void);
extern void normal_TransMenuSetOpen_516a40(s32 a);
extern void func_27C2A0(s32 a, const u8 *p);
extern void func_288300(void);

s32 normal_TransSaveQuitState_51a020(void *a, s32 b)
{
    if (b != 0) {
        func_37B460(0x75A2);
        func_1782A0(&D_00527F10, 0x14, 0.0f, 0.0f, 0.0f);
    }
    if (func_178110(&D_00527F10) != 0) {
        func_373100();
        normal_TransMenuSetOpen_516a40(0);
        func_27C2A0(1, &D_00526818);
        func_288300();
    }
    return 1;
}
