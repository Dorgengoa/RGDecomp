typedef unsigned int U;
typedef struct B { unsigned char flag:1; unsigned char length:7; } B;
typedef struct S { U flags; U size; char *data; } S;
extern U StringFindChar_107550(S *, char, U);
int DecimalCompareToHalf_106ab0(S *s, U pos) {
    unsigned char small = !(s->flags & 1);
    U size = small ? ((B *)s)->length : s->size;
    char *data;
    char c;
    if (pos >= size) return -1;
    data = small ? (char *)s + 1 : s->data;
    c = data[pos];
    if (c > 5) return 1;
    if (c < 5) return -1;
    return StringFindChar_107550(s, 0, pos + 1) != (U)-1;
}
