#include "types.h"

typedef struct Ent00181be0 {
    s8 name[0x40];
    s32 unk40;
    s32 unk44;
    s32 unk48;
} Ent00181be0;

extern s32 Strcasecmp_1345b8(s32 arg0, s8 *arg1);

s32 ArchiveFindByExt_181be0(Ent00181be0 *arg0, s32 arg1, u8 **arg2, s32 limit_in, s32 *arg4, Ent00181be0 **arg5)
{
    s32 n;
    s32 idx;
    Ent00181be0 *e;
    Ent00181be0 *found;
    u8 *data;
    s32 i;
    s8 *p;
    volatile struct { s32 limit;s32 val;} st;
    st.limit=limit_in;
    n = 0;
    for (idx = 0; ; idx++) {
        if (arg0 == NULL) {
            data = NULL;
        } else {
            e = arg0;
            i = 0;
            while (e->name[0] != 0) {
                if (idx == i) {
                    found = e;
                    data = (u8 *)e + e->unk40;
                    st.val = e->unk44;
                    goto got;
                }
                i++;
                e = (Ent00181be0 *)((u8 *)e + e->unk48);
            }
            data = NULL;
        }
    got:
        if (data == NULL) {
            break;
        }
        p = found->name;
        while (*p != 0) {
            if ((s64)*p == '.') {
                p++;
                break;
            }
            p++;
        }
        if (Strcasecmp_1345b8(arg1, p) != 0) {
            continue;
        }
        arg2[n] = data;
        if (arg5 != NULL) {
            arg5[n] = found;
        }
        if (arg4 != NULL) {
            arg4[n] = st.val;
        }
        n++;
        if (n >= st.limit) {
            break;
        }
    }
    return n;
}
