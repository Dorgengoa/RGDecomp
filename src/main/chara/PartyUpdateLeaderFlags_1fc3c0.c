#include "types.h"

extern u8 *GetGameData_1fede0(void);
extern u8 *ActionMgrFindById_233b50(void *, s32);
extern s32 PartyCountMembers_3c2010(void *, s32, s32);
extern s32 PartyGetMemberId_3c2490(void *, s32);
extern u8 D_004B8680[0x400];

static inline s32 GetN(void *a) { return PartyCountMembers_3c2010(a, 1, 1); }
static inline u8 *GetM(void) { return GetGameData_1fede0(); }
static inline s32 GetId(void *a, s32 i) { return PartyGetMemberId_3c2490(a, i); }
s32 PartyUpdateLeaderFlags_1fc3c0(void) {
    u8 *m;
    s32 n;
    u8 *d;
    s32 i;
    s32 id;
    u8 *o;
    s32 f;

    m = GetGameData_1fede0();
    d = D_004B8680;
    n = GetN(*(void **)(m + 0x18));
    for (i = 0; i < n; i++) {
        id = GetId(*(void **)(m + 0x18), i);
        o = ActionMgrFindById_233b50(d, id);
        if (o != NULL) {
            if (id != *(s16 *)(*(u8 **)(m + 0x18) + 0x18E)) {
                f = *(s32 *)(o + 0xA44) | 0x1000000;
            } else {
                f = *(s32 *)(o + 0xA44) & 0xFEFFFFFF;
            }
            *(s32 *)(o + 0xA44) = f;
            *(s32 *)(o + 0xA44) = f & 0xFF7FFFFF;
        }
    }
    return 1;
}
