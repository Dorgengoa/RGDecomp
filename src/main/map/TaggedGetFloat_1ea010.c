#include "types.h"

f32 TaggedGetFloat_1ea010(void *arg0)
{
    s32 tag = *(s32 *)arg0;

    switch (tag) {
    case 0:
        return (f32) *(s32 *)((u8 *)arg0 + 4);
    case 1:
        return *(f32 *)((u8 *)arg0 + 4);
    }
    return 0.0f;
}
