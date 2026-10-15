#include "types.h"
#pragma opt_common_subs off
extern s32 strcmp(const char *, const char *);

typedef struct E00302f50 {
    char *name;
    s32 val;
} E00302f50;

s32 NameValueTableLookup_302f50(E00302f50 *arr, const char *key)
{
    if (arr == NULL || key == NULL) {
        return 0;
    }
    while (!(!arr->name || arr->val == 0)) {
        if (strcmp(key, arr->name) == 0) {
            return arr->val;
        }
        arr++;
    }
    return 0;
}
