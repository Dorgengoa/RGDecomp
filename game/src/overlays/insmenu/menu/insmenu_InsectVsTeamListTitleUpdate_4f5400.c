/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTeamListTitleUpdate_4f5400 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F5400 (120 bytes) -- close the sub-panel when the running scene
 * is one of the three lab scenes and the menu is in mode 2.
 *
 * ★ Each of the three terms carries its OWN `hit = 1;` -- an if/else CHAIN, not
 * `if (a || b || c)`, which is the recorded insmenu shape.
 * ★ `daddiu $6, $0, 0x1` is the u8 flag's own materialisation and `beql $6, $0`
 * is the BARE test of it. */

typedef struct Kind Kind;
struct Kind {
    u8  pad00[8];
    s32 field08;
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

extern s16 D_0048436C;          /* gp - 0xE04 */

/*rgp*/
/*rgp*/

void insmenu_InsectVsTeamListTitleUpdate_4f5400(void)
{
    s32 scene;
    u8 hit;

    scene = ((Handle *)GetGameData_1fede0())->field24->field1188->field08;
    hit = 0;
    if (D_0048436C == 2) {
        if (scene == 0x193) {
            hit = 1;
        } else if (scene == 0x1F6) {
            hit = 1;
        } else if (scene == 0x1F7) {
            hit = 1;
        }
    }
    if (hit) {
        InsectVsTeamListTitleCenter_37aa20();
    }
}
