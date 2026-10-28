/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsLoadSlotListConfirm_4f5f70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F5F70 (524 bytes) -- the id-chain family's widest member: the
 * cursor-index commit (D_00484340 = row + col), then TWO id chains over the
 * same `hnd->field24->field1188->field08`.
 *
 * !! THE WHOLE FUNCTION HANGS ON ONE STRUCTURAL READING, and getting it wrong
 * costs 98 of 131 words AT THE RIGHT LENGTH.  Retail's
 * `func_376B20(6); return 1;` is NOT an early-return guard body -- it is the
 * function's FALL-OUT.  `beql $2, $0, .L004F615C` branches to a block placed
 * PHYSICALLY LAST, after the main tail's `b .L004F6168`, so everything from
 * `hnd = func_1FEDE0();` to the final `return 1;` lives INSIDE
 * `if (func_373440(...) != 0) { ... }`, and the func_376B20(6) block is what the
 * function runs into when that test fails.  Writing it the other way round --
 * `if (... == 0) { func_376B20(6); return 1; }` as a guard -- emits the block
 * INLINE and shifts every following word by four: the first draft scored 98 bad
 * words whose diff was a pure +0x10 displacement, and this one edit took it to
 * 0.  Chains 1 and 2 and the whole prologue were already byte-exact under the
 * shift.
 *
 * Chain 1 is a nine-term `||` whose body is the single `flag = 0;`: the first
 * eight terms branch INTO .L004F605C and the ninth (0x25A) is a `bnel` PAST it,
 * which is the `||` signature, not an if/else chain.  `flag = 1;` rides the
 * first `beq`'s delay slot as `daddiu $17, $0, 0x1` -- the
 * u8-boolean-in-a-callee-saved-register rule from insmenu_InsectVsPwEntryOpen_4f7810.
 * MEASURED: `s32 flag` is 1 bad word (`addiu` where retail has `daddiu`);
 * `if (flag != 0)` instead of `if (flag)` is THREE WORDS LONG (0x210).
 *
 * Chain 2 is a six-term `||` whose first three terms are `&&`-guarded by
 * `D_0048436C == 2`, written out THREE times because mwcc does not CSE the gp
 * load -- retail has three `lh $5, -0xE04($28)`.  A failing inner test falls
 * through the REST of the chain onto .L004F6118, which is what makes it one
 * `if`, not three.
 *
 * The `e` test is an if/ELSE with the arm duplicated, not a `||`: MEASURED,
 * `if (e == 0 || e->field34E == 0)` is 3 words SHORT (0x200) and two separate
 * `if`s are 1 word short (0x208).  Compare insmenu_InsectVsTeamListConfirm_4f4f00, where the same
 * `beql` + duplicated-first-instruction shape IS an `||` -- the tell is that
 * here the two arms are separate blocks, there they share one.
 *
 * The opening `dsll32/dsra32 ..,16` is the truncation of the sum into an s16
 * LOCAL, not a reload -- 004F4F00 proves `func_37B9C0(D_00484340)` emits a plain
 * `lh $4, -0xE30($28)`.  MEASURED INERT, all four give the identical object
 * 9292f007: `s16 v`; `s32 v` + an `(s16)` cast; `s32 v` + an `s16` prototype;
 * and no local at all with the global forwarded.  Do not spend a build there.
 *
 * Also MEASURED INERT: declaring `n` before `flag` -- register allocation here
 * is decided by live range, not declaration order.
 *
 * Tail is 004F4F00's verbatim: func_376B20(5) then func_28EA90(insmenu_D_004FA1A0, id,
 * c) with the `ori $5` zero-extended constant.
 */

typedef struct Panel Panel;
struct Panel {
    u8  pad00[0x12];
    s16 field12;
    u8  pad14[2];
    s16 field16;
};

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

typedef struct Entry Entry;
struct Entry {
    u8  pad000[0x34E];
    u8  field34E;
};

typedef struct Scene Scene;

extern u8 insmenu_D_004FA1A0[];
extern s16 D_00484340;          /* gp - 0xE30 */
extern u8  D_00484344;          /* gp - 0xE2C */
extern s16 D_0048436C;          /* gp - 0xE04 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsLoadSlotListConfirm_4f5f70(Panel *p)
{
    u8 flag;
    s32 n;
    Handle *hnd;
    Entry *e;
    s32 id;
    s16 v;

    v = p->field16 + p->field12;
    D_00484340 = v;
    SaveMgrSetSlot_37b9c0(v);
    if (((Handle *)GetGameData_1fede0()) == 0) {
        return 0;
    }
    n = SaveRecCountInsectsMaybe_378f70(D_00484340);
    if (SaveSlotEntryIsValidAt_373440(((Scene *)insmenu_InsectVsGetSaveCtx_4f3850()), D_00484340) != 0) {
        hnd = ((Handle *)GetGameData_1fede0());
        id = hnd->field24->field1188->field08;
        flag = 1;
        if (id == 0x1F6 || id == 0x1F7 || id == 0x193 || id == 0x25D ||
            id == 0x26E || id == 0x268 || id == 0x278 || id == 0x264 ||
            id == 0x25A) {
            flag = 0;
        }
        if ((id == 0x1F6 && D_0048436C == 2) ||
            (id == 0x1F7 && D_0048436C == 2) ||
            (id == 0x193 && D_0048436C == 2) ||
            id == 0x26E || id == 0x278 || id == 0x264) {
            e = ((Entry *)SlotRecordFindById_3e4e80(hnd, D_00484340));
            if (e != 0) {
                if (e->field34E == 0) {
                    PlayMenuSeThunk_289ef0(6);
                    return 1;
                }
            } else {
                PlayMenuSeThunk_289ef0(6);
                return 1;
            }
        }
        if (flag) {
            if (n < 5) {
                D_00484344 = 1;
            }
        }
        PlayMenuSeThunk_289ef0(5);
        UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88BC, 0);
        return 1;
    }
    PlayMenuSeThunk_289ef0(6);
    return 1;
}
