/* rgp:protos */
#define RGP_SELF_BlurWorkTexRegister_2f67b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN BlurWorkTexRegister_2f67b0 -- two 0xC0x0xC0 surfaces off resource 0x325.
   NameTableAddEntry_159b70's prototype is the one already established by
   src/wf/main/MenuCaptureScreenTex_298810.c (10 integer arguments, the last two on
   the stack). */

/*rgp*/
/*rgp*/

extern u8 D_00461CB8[];
extern u8 D_00461CC8[];

void BlurWorkTexRegister_2f67b0(void)
{
    void *w;

    w = GetDrawCtxNameTable_15de40();
    NameTableAddEntry_159b70(w, 0x325, D_00461CB8, 0, 0xC0, 0xC0, 0x20, 0, (long long)(0), 0);
    NameTableAddEntry_159b70(w, 0x325, D_00461CC8, 0, 0xC0, 0xC0, 0x20, 0, (long long)(0), 0);
}
