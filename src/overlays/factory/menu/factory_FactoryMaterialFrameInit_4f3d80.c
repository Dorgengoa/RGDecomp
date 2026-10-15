#include "types.h"

/* factory.bin overlay, 0x004F3D80 -- 124 bytes / 31 words.  Straight-line
 * six-call list that (re)builds the scrolling text box embedded at +0x50.
 *
 * * Every call recomputes `addiu $4, $16, 0x50`, so the sub-object address is
 *   written at each call site (`&o->f50`) and is NOT a named local -- a local
 *   would be materialised once in a callee-saved register.
 * * `daddu $7, $6, $0` after `addiu $6, $0, 0x17` is mwcc sharing ONE constant
 *   between the third and fourth arguments: the source passes 0x17 twice.
 * * The 28Dxxx family's spellings come from factory_FUN_004EC5E0 (func_28DB70
 *   takes `void *`, the rest `const u8 *`).
 */

typedef struct Mod {
    u8    pad00[0x40];
    void *f40;
    u8    pad44[0xC];
    u8    f50;
} Mod;

extern void func_28D820(const u8 *p, s32 a);
extern void func_28D9C0(const u8 *p, s32 a);
extern void func_28D9D0(const u8 *p);
extern void func_28DA30(const u8 *p, void *q, s32 a);
extern void func_28DB40(const u8 *p, s32 a, s32 b, s32 c, s32 d, s32 e,
                        s32 f, s32 g);
extern void func_28DB70(void *p);

void factory_FactoryMaterialFrameInit_4f3d80(Mod *o)
{
    func_28DB70(&o->f50);
    func_28DA30(&o->f50, o->f40, 0x63);
    func_28DB40(&o->f50, 0x63, 0x17, 0x17, 0x2B, 0x2E, 0, 0);
    func_28D9D0(&o->f50);
    func_28D9C0(&o->f50, 1);
    func_28D820(&o->f50, 0x63);
}
