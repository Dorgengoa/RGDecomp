"""Read words from the retail EE ELF by virtual address (own code, CC0).
usage: eeread.py ADDR_HEX COUNT"""
import struct, sys
b = open("data/SCUS_974.90" if __import__('os').path.exists("data/SCUS_974.90") else "../work/SCUS_974.90", "rb").read()
phoff, = struct.unpack_from("<I", b, 0x1C); phnum, = struct.unpack_from("<H", b, 0x2C)
segs = [struct.unpack_from("<8I", b, phoff + 32 * i) for i in range(phnum)]
def rd(va, n):
    for ty, off, v, pa, fsz, msz, fl, al in segs:
        if ty == 1 and v <= va < v + fsz:
            return b[off + va - v: off + va - v + n]
    return None
if __name__ == "__main__":
    a = int(sys.argv[1], 16); n = int(sys.argv[2])
    d = rd(a, 4 * n)
    for i in range(n):
        print(f"{a+4*i:08x}: [{i:#x}] {struct.unpack_from('<I', d, 4*i)[0]:08x}")
