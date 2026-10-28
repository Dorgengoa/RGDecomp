/* rgp:protos */
#define RGP_SELF_SwordTrailSetup_215a10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern char *strcpy(char *d, const char *s);

void SwordTrailSetup_215a10(void *obj, s32 n, char *s, f32 a, f32 b, f32 c, f32 d)
{
    TargetRefClear_2e71d0((u8 *)obj + 0x30);
    TargetRefClear_2e71d0((u8 *)obj + 0x60);
    SwordTrailStop_2d7620(obj);
    if (n < 0 || s == 0 || *s == 0) {
        return;
    }
            *(s32 *)((u8 *)obj + 0x90) = n;
            strcpy((char *)((u8 *)obj + 0x94), s);
            SwordTrailStart_2d76d0(obj, b);
            *(f32 *)((u8 *)obj + 0x2C) = a;
}
/* MEASURED: the three guards are ONE `||` chain in ONE `if`.  Seven other
   spellings - three nested ifs, `&&` at either level, early returns at
   any level, s[0] vs *s - are a single INERT cell (object 52a9935d, two
   words short: they lose retail's `bnel`+duplicated delay slot at
   0x00215A7C). */
