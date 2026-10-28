/* rgp:protos */
#define RGP_SELF_MenuItemTempRBufInit_2a8a20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern char *strcpy(char *, const char *);
extern u32 strlen(const char *);

extern char D_00461480[32];
extern char D_004DB3D0[32];

void MenuItemTempRBufInit_2a8a20(void) {
    s32 temp_2;

    temp_2 = ((s32)GetLoaderMgr_1f59d0());
    if (temp_2 != 0) {
        MemStackInit_14d810(D_004DB3D0, HeapHandleAllocBack_1cdb10(temp_2, 0x1E00), 0x1E00);
        if (strlen(D_00461480) < 0x10U) {
            strcpy(D_004DB3D0, D_00461480);
        }
        MemStackReset_14d830(D_004DB3D0);
        MemStackAlign64_14d8e0(D_004DB3D0);
    }
}
