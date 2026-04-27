#!/usr/bin/python3

import argparse
import functools
import re
import sys


BITS_PER_LINE = 8
HEIGHT = 16
BYTES_PER_CHAR = HEIGHT
BITS_PER_CHAR = BITS_PER_LINE * HEIGHT


class Error(Exception):
    def __init__(self, msg):
        self.message = msg


def compile(src):
    src = re.sub(r'^\s*#.*$', '', src, flags=re.MULTILINE)
    src = re.sub(r'(\.|@|x)([^\.@x\s])', r'\1\n\2', src)
    src = re.sub(r'([^\.@x\s])(\.|@|x)', r'\1\n\2', src)

    bitmap_pat = re.compile(r'([\.@x]{8})\s*')
    bitmaps = bitmap_pat.findall(src)
    if len(bitmaps) % HEIGHT != 0:
        raise Error('# of bitmap lines must be a multiple of {}'.format(HEIGHT))

    num_chars = len(bitmaps) // HEIGHT
    bytes_data = bytearray(num_chars * BYTES_PER_CHAR)
    for i, line in enumerate(bitmaps):
        byte = functools.reduce(
            lambda a, b: 2*a + b,
            map(lambda x: 0 if x == '.' else 1, line))
        bytes_data[i] = byte
    return bytes_data


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('font_file', help='path to a font file')
    parser.add_argument('-o', help='path to an output file')
    ns = parser.parse_args()

    with open(ns.font_file) as font_file:
        src = font_file.read()

    try:
        bytes_data = compile(src)
    except Error as e:
        print(e.message, file=sys.stderr)
        sys.exit(1)

    if ns.o is None:
        sys.stdout.buffer.write(bytes_data)
    else:
        with open(ns.o, 'wb') as out_file:
            out_file.write(bytes_data)


if __name__ == '__main__':
    main()
