/* rgp:protos */
#define RGP_SELF_EvCmdLoaderRequestFiles_268a30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 id; char name[0x80]; } E268a30;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
char *strcpy(char *, const char *);
extern s32 D_00482074;
extern E268a30 D_004BE170[8];

s32 EvCmdLoaderRequestFiles_268a30(s64 *arg0, s32 arg1) {
    s32 h;
    s32 i;
    s32 name;
    s32 r;

    h = ((s32)GetLoaderMgr_1f59d0());
    D_00482074 = 0;
    for (i = 0; i < arg1; i++) {
        if (D_00482074 == 8) break;
        name = ScriptGetCodeAddr_26a200((s32)arg0++);
        r = LoaderRequestFile_1cd870(h, name, 0);
        if (r >= 0) {
            D_004BE170[D_00482074].id = r;
            strcpy(D_004BE170[D_00482074].name, (char *)name);
            D_00482074++;
        }
    }
    if (D_00482074 > 0) {
        LoaderQueueAppendSeparator_1cd670(h);
    }
    return 1;
}
