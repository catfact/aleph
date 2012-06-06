#include "compiler.h"
#include "font.h"

const U8 rom_font[FONT_NBYTES] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 000 (.)
  0x7E, 0x81, 0xA5, 0x81, 0xA5, 0x99, 0x81, 0x7E,	// Char 001 (.)
  0x3C, 0x7E, 0xDB, 0xFF, 0xC3, 0x7E, 0x3C, 0x00,	// Char 002 (.)
  0x00, 0x6C, 0xFE, 0xFE, 0x7C, 0x38, 0x10, 0x00,	// Char 003 (.)
  0x10, 0x38, 0x7C, 0xFE, 0x7C, 0x38, 0x10, 0x00,	// Char 004 (.)
  0x00, 0x3C, 0x18, 0xFF, 0xFF, 0x08, 0x18, 0x00,	// Char 005 (.)
  0x10, 0x38, 0x7C, 0xFE, 0xFE, 0x10, 0x38, 0x00,	// Char 006 (.)
  0x00, 0x00, 0x18, 0x3C, 0x18, 0x00, 0x00, 0x00,	// Char 007 (.)
  0xFF, 0xFF, 0xE7, 0xC3, 0xE7, 0xFF, 0xFF, 0xFF,	// Char 008 (.)
  0x00, 0x3C, 0x42, 0x81, 0x81, 0x42, 0x3C, 0x00,	// Char 009 (.)
  0xFF, 0xC3, 0xBD, 0x7E, 0x7E, 0xBD, 0xC3, 0xFF,	// Char 010 (.)
  0x1F, 0x07, 0x0D, 0x7C, 0xC6, 0xC6, 0x7C, 0x00,	// Char 011 (.)
  0x00, 0x7E, 0xC3, 0xC3, 0x7E, 0x18, 0x7E, 0x18,	// Char 012 (.)
  0x04, 0x06, 0x07, 0x04, 0x04, 0xFC, 0xF8, 0x00,	// Char 013 (.)
  0x0C, 0x0A, 0x0D, 0x0B, 0xF9, 0xF9, 0x1F, 0x1F,	// Char 014 (.)
  0x00, 0x92, 0x7C, 0x6C, 0xC6, 0x6C, 0x7C, 0x92,	// Char 015 (.)
  0x00, 0x00, 0x60, 0x78, 0x7E, 0x78, 0x60, 0x00,	// Char 016 (.)
  0x00, 0x00, 0x06, 0x1E, 0x7E, 0x1E, 0x06, 0x00,	// Char 017 (.)
  0x18, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x18,	// Char 018 (.)
  0x24, 0x24, 0x24, 0x24, 0x24, 0x00, 0x24, 0x00,	// Char 019 (.)
  0xFF, 0xB6, 0x76, 0x36, 0x36, 0x36, 0x36, 0x00,	// Char 020 (.)
  0x7E, 0xC1, 0xDC, 0x22, 0x22, 0x1F, 0x83, 0x7E,	// Char 021 (.)
  0x00, 0x00, 0x00, 0x7E, 0x7E, 0x00, 0x00, 0x00,	// Char 022 (.)
  0x18, 0x7E, 0x18, 0x18, 0x7E, 0x18, 0x00, 0xFF,	// Char 023 (.)
  0x08, 0x1C, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00,	// Char 024 (.)
  0x08, 0x08, 0x08, 0x08, 0x08, 0x1C, 0x08, 0x00,	// Char 025 (.)
  0x00, 0x00, 0x02, 0xFF, 0x02, 0x00, 0x00, 0x00,	// Char 026 (.)
  0x00, 0x00, 0x40, 0xFF, 0x40, 0x00, 0x00, 0x00,	// Char 027 (.)
  0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xFF, 0x00,	// Char 028 (.)
  0x00, 0x24, 0x66, 0xFF, 0x66, 0x24, 0x00, 0x00,	// Char 029 (.)
  0x00, 0x00, 0x10, 0x38, 0x7C, 0xFE, 0x00, 0x00,	// Char 030 (.)
  0x00, 0x00, 0x00, 0xFE, 0x7C, 0x38, 0x10, 0x00,	// Char 031 (.)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 032 ( )
  0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x10, 0x00,	// Char 033 (!)
  0x44, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 034 (")
  0x28, 0x28, 0xFE, 0x28, 0xFE, 0x28, 0x28, 0x00,	// Char 035 (#)
  0x28, 0x7C, 0xA8, 0x7C, 0x2A, 0x7C, 0x28, 0x00,	// Char 036 ($)
  0x60, 0x94, 0x68, 0x10, 0x2C, 0x52, 0x8C, 0x00,	// Char 037 (%)
  0x30, 0x48, 0x30, 0x48, 0x86, 0x84, 0x78, 0x00,	// Char 038 (&)
  0x04, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 039 (')
  0x10, 0x20, 0x40, 0x40, 0x40, 0x20, 0x10, 0x00,	// Char 040 (()
  0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x10, 0x00,	// Char 041 ())
  0x00, 0x54, 0x38, 0x7C, 0x38, 0x54, 0x00, 0x00,	// Char 042 (*)
  0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00, 0x00,	// Char 043 (+)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10,	// Char 044 (,)
  0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00,	// Char 045 (-)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00,	// Char 046 (.)
  0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00,	// Char 047 (/)
  0x00, 0x18, 0x24, 0x2C, 0x34, 0x24, 0x18, 0x00,	// Char 048 (0)
  0x00, 0x10, 0x30, 0x10, 0x10, 0x10, 0x38, 0x00,	// Char 049 (1)
  0x00, 0x18, 0x24, 0x04, 0x18, 0x20, 0x3C, 0x00,	// Char 050 (2)
  0x00, 0x38, 0x04, 0x18, 0x04, 0x04, 0x38, 0x00,	// Char 051 (3)
  0x00, 0x20, 0x28, 0x28, 0x3C, 0x08, 0x08, 0x00,	// Char 052 (4)
  0x00, 0x3C, 0x20, 0x38, 0x04, 0x04, 0x38, 0x00,	// Char 053 (5)
  0x00, 0x1C, 0x20, 0x38, 0x24, 0x24, 0x18, 0x00,	// Char 054 (6)
  0x00, 0x3C, 0x04, 0x08, 0x10, 0x10, 0x10, 0x00,	// Char 055 (7)
  0x00, 0x18, 0x24, 0x18, 0x24, 0x24, 0x18, 0x00,	// Char 056 (8)
  0x00, 0x18, 0x24, 0x24, 0x1C, 0x04, 0x38, 0x00,	// Char 057 (9)
  0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,	// Char 058 (:)
  0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x20, 0x00,	// Char 059 (;)
  0x00, 0x08, 0x10, 0x20, 0x10, 0x08, 0x00, 0x00,	// Char 060 (<)
  0x00, 0x00, 0x7E, 0x00, 0x7E, 0x00, 0x00, 0x00,	// Char 061 (=)
  0x00, 0x20, 0x10, 0x08, 0x10, 0x20, 0x00, 0x00,	// Char 062 (>)
  0x7C, 0x82, 0x04, 0x08, 0x10, 0x00, 0x10, 0x00,	// Char 063 (?)
  0x7C, 0x82, 0x9A, 0xAA, 0xAA, 0x9E, 0x7C, 0x00,	// Char 064 (@)
  0x00, 0x18, 0x24, 0x24, 0x3C, 0x24, 0x24, 0x00,	// Char 065 (A)
  0x00, 0x38, 0x24, 0x38, 0x24, 0x24, 0x38, 0x00,	// Char 066 (B)
  0x00, 0x18, 0x24, 0x20, 0x20, 0x24, 0x18, 0x00,	// Char 067 (C)
  0x00, 0x38, 0x24, 0x24, 0x24, 0x24, 0x38, 0x00,	// Char 068 (D)
  0x00, 0x3C, 0x20, 0x38, 0x20, 0x20, 0x3C, 0x00,	// Char 069 (E)
  0x00, 0x3C, 0x20, 0x38, 0x20, 0x20, 0x20, 0x00,	// Char 070 (F)
  0x00, 0x18, 0x24, 0x20, 0x2C, 0x24, 0x18, 0x00,	// Char 071 (G)
  0x00, 0x24, 0x24, 0x3C, 0x24, 0x24, 0x24, 0x00,	// Char 072 (H)
  0x00, 0x38, 0x10, 0x10, 0x10, 0x10, 0x38, 0x00,	// Char 073 (I)
  0x00, 0x04, 0x04, 0x04, 0x04, 0x24, 0x18, 0x00,	// Char 074 (J)
  0x00, 0x28, 0x28, 0x30, 0x28, 0x24, 0x24, 0x00,	// Char 075 (K)
  0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x00,	// Char 076 (L)
  0x00, 0x44, 0x6C, 0x54, 0x44, 0x44, 0x44, 0x00,	// Char 077 (M)
  0x00, 0x24, 0x34, 0x34, 0x2C, 0x2C, 0x24, 0x00,	// Char 078 (N)
  0x00, 0x18, 0x24, 0x24, 0x24, 0x24, 0x18, 0x00,	// Char 079 (O)
  0x00, 0x38, 0x24, 0x24, 0x38, 0x20, 0x20, 0x00,	// Char 080 (P)
  0x00, 0x18, 0x24, 0x24, 0x24, 0x24, 0x1C, 0x02,	// Char 081 (Q)
  0x00, 0x38, 0x24, 0x24, 0x38, 0x24, 0x24, 0x00,	// Char 082 (R)
  0x00, 0x1C, 0x20, 0x18, 0x04, 0x04, 0x38, 0x00,	// Char 083 (S)
  0x00, 0x38, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00,	// Char 084 (T)
  0x00, 0x24, 0x24, 0x24, 0x24, 0x24, 0x3C, 0x00,	// Char 085 (U)
  0x00, 0x24, 0x24, 0x24, 0x24, 0x14, 0x0C, 0x00,	// Char 086 (V)
  0x00, 0x44, 0x44, 0x44, 0x54, 0x6C, 0x44, 0x00,	// Char 087 (W)
  0x00, 0x24, 0x24, 0x10, 0x08, 0x24, 0x24, 0x00,	// Char 088 (X)
  0x00, 0x22, 0x22, 0x14, 0x08, 0x08, 0x08, 0x00,	// Char 089 (Y)
  0x00, 0x3C, 0x04, 0x08, 0x10, 0x20, 0x3C, 0x00,	// Char 090 (Z)
  0x1C, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1C, 0x00,	// Char 091 ([)
  0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00,	// Char 092 (\)
  0x70, 0x10, 0x10, 0x10, 0x10, 0x10, 0x70, 0x00,	// Char 093 (])
  0x00, 0x00, 0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00,	// Char 094 (^)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,	// Char 095 (_)
  0x10, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,	// Char 096 (`)
  0x00, 0x00, 0x18, 0x24, 0x3C, 0x24, 0x24, 0x00,	// Char 097 (a)
  0x00, 0x00, 0x38, 0x24, 0x38, 0x24, 0x38, 0x00,	// Char 098 (b)
  0x00, 0x00, 0x18, 0x24, 0x20, 0x24, 0x18, 0x00,	// Char 099 (c)
  0x00, 0x00, 0x38, 0x24, 0x24, 0x24, 0x38, 0x00,	// Char 100 (d)
  0x00, 0x00, 0x3C, 0x20, 0x38, 0x20, 0x3C, 0x00,	// Char 101 (e)
  0x00, 0x00, 0x3C, 0x20, 0x38, 0x20, 0x20, 0x00,	// Char 102 (f)
  0x00, 0x00, 0x1C, 0x20, 0x2C, 0x24, 0x18, 0x00,	// Char 103 (g)
  0x00, 0x00, 0x24, 0x24, 0x3C, 0x24, 0x24, 0x00,	// Char 104 (h)
  0x00, 0x00, 0x1C, 0x08, 0x08, 0x08, 0x1C, 0x00,	// Char 105 (i)
  0x00, 0x00, 0x04, 0x04, 0x04, 0x24, 0x18, 0x00,	// Char 106 (j)
  0x00, 0x00, 0x24, 0x28, 0x30, 0x28, 0x24, 0x00,	// Char 107 (k)
  0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x3C, 0x00,	// Char 108 (l)
  0x00, 0x00, 0x42, 0x66, 0x5A, 0x42, 0x42, 0x00,	// Char 109 (m)
  0x00, 0x00, 0x24, 0x34, 0x3C, 0x2C, 0x24, 0x00,	// Char 110 (n)
  0x00, 0x00, 0x18, 0x24, 0x24, 0x24, 0x18, 0x00,	// Char 111 (o)
  0x00, 0x00, 0x38, 0x24, 0x38, 0x20, 0x20, 0x00,	// Char 112 (p)
  0x00, 0x00, 0x18, 0x24, 0x24, 0x24, 0x1C, 0x02,	// Char 113 (q)
  0x00, 0x00, 0x38, 0x24, 0x38, 0x24, 0x24, 0x00,	// Char 114 (r)
  0x00, 0x00, 0x1C, 0x20, 0x18, 0x04, 0x38, 0x00,	// Char 115 (s)
  0x00, 0x00, 0x38, 0x10, 0x10, 0x10, 0x10, 0x00,	// Char 116 (t)
  0x00, 0x00, 0x24, 0x24, 0x24, 0x24, 0x3C, 0x00,	// Char 117 (u)
  0x00, 0x00, 0x24, 0x24, 0x24, 0x14, 0x0C, 0x00,	// Char 118 (v)
  0x00, 0x00, 0x42, 0x42, 0x5A, 0x66, 0x42, 0x00,	// Char 119 (w)
  0x00, 0x00, 0x44, 0x28, 0x10, 0x28, 0x44, 0x00,	// Char 120 (x)
  0x00, 0x00, 0x44, 0x28, 0x10, 0x10, 0x10, 0x00,	// Char 121 (y)
  0x00, 0x00, 0x7C, 0x08, 0x10, 0x20, 0x7C, 0x00,	// Char 122 (z)
  0x0E, 0x10, 0x10, 0x20, 0x10, 0x10, 0x0E, 0x00,	// Char 123 ({)
  0x08, 0x08, 0x08, 0x00, 0x08, 0x08, 0x08, 0x00,	// Char 124 (|)
  0xE0, 0x10, 0x10, 0x08, 0x10, 0x10, 0xE0, 0x00,	// Char 125 (})
  0x00, 0x00, 0x60, 0x92, 0x0C, 0x00, 0x00, 0x00,	// Char 126 (~)
  0x00, 0x00, 0x18, 0x24, 0x42, 0xFF, 0x00, 0x00,	// Char 127 (.)
};
