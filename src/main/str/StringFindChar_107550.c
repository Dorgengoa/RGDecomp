typedef unsigned int U;
typedef struct B { unsigned char flag:1; unsigned char length:7; } B;
typedef struct S { U flags; U size; char *data; } S;
U StringFindChar_107550(const S *s, char c, U pos) {
    const char *data;
    U size;
    if (!(s->flags & 1)) { data = (const char *)s + 1; size = ((const B *)s)->length; }
    else { data = s->data; size = s->size; }
    if (pos < size) {
        const char *end = data + size;
        const char *p = data + pos;
        while (p < end) {
            if (*p != c) return p - data;
            ++p;
        }
    }
    return -1;
}
