/* rgp:protos */
#define RGP_SELF_FilePathApplyAlias_181590 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Entry00181590 {
    s32 unk0;
    s32 unk4;
    s8 *unk8;
} Entry00181590;

/*rgp*/
extern void strcat(s32 arg0, s8 *arg1);
extern void strcpy(s32 arg0, s8 *arg1);
extern s32 strlen(s8 *arg0);
extern s32 D_00481214;
extern Entry00181590 D_0049BF10[];

void FilePathApplyAlias_181590(s32 arg0, s8 *arg1)
{
    s8 *var_19;
    s32 temp_4;
    s32 temp_6;
    s32 var_18;
    s32 temp_17;
    s8 temp_2;
    Entry00181590 *temp_16;

    var_19 = arg1;
    strcpy(arg0, arg1);
    for (; (temp_2 = *var_19) != 0; var_19++) {
        if (temp_2 == 0x3A) {
            var_19 += 1;
            break;
        }
    }
    temp_17 = strlen(var_19);
    var_18 = 0;
    while (var_18 < D_00481214) {
        temp_16 = &D_0049BF10[var_18];
        temp_6 = temp_16->unk4;
        if (temp_17 >= temp_6) {
            temp_4 = temp_16->unk0;
            if ((temp_4 != 0) && (temp_16->unk8 != NULL) && (Strncasecmp_134ce8(temp_4, var_19, temp_6) == 0)) {
                strcpy(arg0, temp_16->unk8);
                strcat(arg0, &var_19[temp_16->unk4]);
                return;
            }
        }
        var_18 += 1;
    }
}
