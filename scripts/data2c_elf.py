"""Small strict ELF32 reader for data conversion proofs (no external tools)."""
import struct
from pathlib import Path


class ELF:
    def __init__(self, path):
        self.data = Path(path).read_bytes()
        if self.data[:6] != b'\x7fELF\x01\x01':
            raise ValueError('expected little-endian ELF32')
        off = struct.unpack_from('<I', self.data, 32)[0]
        entsize, count, names = struct.unpack_from('<HHH', self.data, 46)
        self.sections = [dict(zip(('nameoff', 'type', 'flags', 'addr', 'offset', 'size',
            'link', 'info', 'align', 'entsize'), struct.unpack_from('<10I', self.data, off+i*entsize))) for i in range(count)]
        strings = self.section_bytes(names)
        for sec in self.sections:
            sec['name'] = strings[sec['nameoff']:].split(b'\0', 1)[0].decode()
        self.symbols = []
        for i, sec in enumerate(self.sections):
            if sec['type'] != 2:
                continue
            self.symtab_index = i
            strings = self.section_bytes(sec['link'])
            for off in range(sec['offset'], sec['offset']+sec['size'], sec['entsize']):
                name, value, size, info, other, shndx = struct.unpack_from('<IIIBBH', self.data, off)
                self.symbols.append({'name': strings[name:].split(b'\0', 1)[0].decode(),
                    'value': value, 'size': size, 'bind': info >> 4, 'type': info & 15, 'section': shndx})

    def section_bytes(self, i):
        sec = self.sections[i]
        return b'\0' * sec['size'] if sec['type'] == 8 else self.data[sec['offset']:sec['offset']+sec['size']]

    def summary(self):
        return {'sections': [{'index': i, **s} for i, s in enumerate(self.sections) if s['flags'] & 2],
                'symbols': [{**s, 'section_name': self.sections[s['section']]['name'] if 0 < s['section'] < len(self.sections) else str(s['section'])}
                            for s in self.symbols if s['bind'] == 1 and s['name']]}

    def relocated(self, index, base, addresses):
        data = bytearray(self.section_bytes(index))
        for sec in self.sections:
            if sec['type'] not in (9, 4) or sec['info'] != index:
                continue
            if sec['type'] != 9:
                raise ValueError('unexpected RELA')
            for off in range(sec['offset'], sec['offset']+sec['size'], sec['entsize']):
                target, info = struct.unpack_from('<II', self.data, off)
                kind, symbol = info & 255, self.symbols[info >> 8]
                if kind != 2:
                    raise ValueError('unexpected data relocation %d' % kind)
                if symbol['name'] in addresses:
                    address = addresses[symbol['name']]
                elif symbol['section'] == index:
                    address = base + symbol['value']
                elif symbol['section'] == 0xfff1:
                    address = symbol['value']
                else:
                    raise ValueError('unresolved data relocation: ' + symbol['name'])
                addend = struct.unpack_from('<I', data, target)[0]
                struct.pack_into('<I', data, target, (address + addend) & 0xffffffff)
        return bytes(data)
