/* rgp:protos */
#define RGP_SELF_TaskDrawFocus_2f6840 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN TaskDrawFocus_2f6840 -- posts a four-line debug record when the
   +0xB55C float is positive.  The `c.le.s`/`bc1f` pair with the
   `andi 0xFF` afterwards is a u8 flag local, not a direct branch.
   Offset 0xB55C is out of `addiu` range, hence the lui+addu pair. */

typedef struct Obj6840 {
    u8  pad0000[0xB55C];
    f32 mB55C;
} Obj6840;

typedef struct Rec6840 {
    s32  code;          /* 0x00 */
    char a[0x20];       /* 0x04 */
    char b[0x20];       /* 0x24 */
    char c[0x20];       /* 0x44 */
    char d[0x20];       /* 0x64 */
    f32  val;           /* 0x84 */
    s32  m88;           /* 0x88 */
} Rec6840;

/*rgp*/
extern char *strcpy(char *, const char *);
/*rgp*/
extern char D_00461CD8[];
extern char D_00461CE8[];
extern char D_00461CF8[];
extern char D_00461D08[];

void TaskDrawFocus_2f6840(void)
{
    Rec6840 r __attribute__((aligned(16)));
    Obj6840 *o;
    u8 ok;

    o = GetCurrentScene_1f5be0();
    ok = (o->mB55C > 0.0f);
    if (ok != 0) {
        r.code = 0x324;
        r.val = 0.0f;
        r.m88 = 0;
        r.a[0] = 0;
        r.b[0] = 0;
        r.c[0] = 0;
        r.d[0] = 0;
        strcpy(r.a, D_00461CD8);
        strcpy(r.b, D_00461CE8);
        strcpy(r.c, D_00461CF8);
        strcpy(r.d, D_00461D08);
        r.val = o->mB55C;
        FocusFilterDrawMaybe_17c000(&r);
    }
}
