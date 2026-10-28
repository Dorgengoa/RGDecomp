/* rgp:protos */
#define RGP_SELF_DrawWorkHeapInit_2f6f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MAIN DrawWorkHeapInit_2f6f10 -- builds a 0x163-entry identity id table on the
   stack and hands it to DrawListSortWorkInit_140af0 together with the name buffer
   D_004E6420.  The `sltiu 0x10` guard is `strlen(...) < 0x10` (size_t
   is unsigned); retail falls THROUGH into the strcpy, so the strcpy is
   the `if` body. */

/*rgp*/
/*rgp*/
extern u32 strlen(const char *);
extern char *strcpy(char *, const char *);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char D_004E6420[];
extern char D_00461D90[];

void DrawWorkHeapInit_2f6f10(void)
{
    s32 tbl[0x163] __attribute__((aligned(16)));
    u8 *h;
    void *q;
    s32 i;

    MemStackClear_14dff0(D_004E6420);
    MemStackHeapReinit_14de90(D_004E6420);
    if (strlen(D_00461D90) < 0x10) {
        strcpy(D_004E6420, D_00461D90);
    }
    h = ((u8 *)GetCurrentScene_1f5be0());
    if (*(s32 *)(h + 0x180C) != 0) {
        q = MemStackHeapAllocFront_14dd10(*(s32 *)(h + 0x180C), 0x2000);
        if (q != 0) {
            MemStackHeapInit_14dee0(D_004E6420, q, 0x2000);
        }
    }
    for (i = 0; i < 0x163; i++) {
        tbl[i] = i;
    }
    tbl[0x162] = -1;
    DrawListSortWorkInit_140af0(GetDrawCtx_15de80(), D_004E6420, tbl, 0x800);
}
