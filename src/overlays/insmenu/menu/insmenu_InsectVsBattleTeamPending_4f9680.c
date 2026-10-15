#include "types.h"

/* insmenu 0x004F9680 (128 bytes) -- may the lab menu be opened right now?
 *
 * ★ All three scene terms are one `||` with a SINGLE `hit = 1;`: mwcc duplicates
 * that store into the first term's likely delay slot, which is what makes it
 * look like a separate arm.
 * ★ The RETURN TYPE is u8, not s32.  Returning the u8 flag as s32 adds an
 * `andi $2, $17, 0xFF` at both exits; u8 (or a u16 flag returned as u16) gives
 * retail's bare `daddu $2, $17, $0`.
 * ★ Both flags are u8 and both tests are BARE, which is what gives `daddiu`
 * for the 1 and `beql`/`bnez` with no re-masking. */

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

extern u8 D_00484358;           /* gp - 0xE18 */

extern Handle *func_1FEDE0(void);

u8 insmenu_InsectVsBattleTeamPending_4f9680(void)
{
    u8 ok;
    u8 hit;
    s16 scene;

    ok = 0;
    hit = 0;
    scene = func_1FEDE0()->field24->field1188->field08;
    if (scene == 0x1F6 || scene == 0x1F7 || scene == 0x193) {
        hit = 1;
    }
    if (hit) {
        if (D_00484358 == 0) {
            ok = 1;
        }
    }
    return ok;
}
