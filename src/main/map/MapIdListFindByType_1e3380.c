#include "types.h"

extern s32 MapAreaIdListFind_1e3370(s32, s32);
extern s32 MapShareIdListFind_1e3360(s32, s32);
extern s32 MapBlockIdListFind_1e3350(s32, s32);

s32 MapIdListFindByType_1e3380(s32 p0, s32 p1, s32 p2)
{
    switch (p2) {
    case 2:
        return MapAreaIdListFind_1e3370(p0, p1);
    case 3:
        return MapShareIdListFind_1e3360(p0, p1);
    case 4:
        return MapBlockIdListFind_1e3350(p0, p1);
    }
    return 0;
}
