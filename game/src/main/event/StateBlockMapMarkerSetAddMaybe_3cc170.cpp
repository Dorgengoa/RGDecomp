/* rgp:protos */
#line 1
#include "types.h"

struct Info {
    u8 pad0[2];
    s16 type;
    u8 pad4[4];
    s16 sub;
};

class Mgr {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Info * Get(s32 id, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(Info *, (void *, s32, int, int), 0x70, id, rgp_fwd2, rgp_fwd3); }
};

struct Sys {
    u8 pad0[0x1C];
    Mgr *mgr;
};

struct Obj {
    u8 pad0[4];
    Sys *sys;
    u8 pad8[0x340];
    s16 count;
    s32 ids[4];
};

extern "C" s32 D_004838C0;

extern "C" s32 StateBlockMapMarkerSetAddMaybe_3cc170(Obj *obj, s32 id, int rgp_a2, int rgp_a3)
{
    s32 tmp[4] __attribute__((aligned(16)));
    Info *info;
    s32 type;
    s32 sub;
    s32 first;
    s32 match;
    s32 i;

    if (D_004838C0 == 0) {
        return 0;
    }
    info = obj->sys->mgr->Get(id, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if (info == 0) {
        return 0;
    }
    type = info->type;
    first = -1;
    sub = info->sub;
    match = first;
    for (i = 0; i < obj->count; i++) {
        Info *o = obj->sys->mgr->Get(obj->ids[i]);
        if (o == 0) continue;
        if (type != o->type) continue;
        if (first < 0) {
            first = i;
        }
        if (sub != o->sub) continue;
        match = i;
        break;
    }
    if (first < 0) {
        if (type < 0xE) {
            s32 n = 0;
            s32 j;
            for (i = 0; i < obj->count; i++) {
                s32 k = obj->ids[i];
                Info *o = obj->sys->mgr->Get(k);
                if (o == 0) continue;
                if (o->type > 0xD) {
                    tmp[n++] = k;
                }
            }
            obj->count = n;
            for (j = 0; j < n; j++) {
                obj->ids[j] = tmp[j];
            }
        }
        {
            s32 c = obj->count;
            if (c >= 4) {
                return 0;
            }
            obj->count = c + 1;
            obj->ids[c] = id;
        }
    } else if (match < 0) {
        s32 c = obj->count;
        if (c >= 4) {
            return 0;
        }
        obj->count = c + 1;
        obj->ids[c] = id;
    } else {
        obj->ids[match] = id;
    }
    return 1;
}
