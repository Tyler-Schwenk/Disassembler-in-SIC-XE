# Disassembler-in-SIC-XE

compilation command:
$ g++ /home/cs/kaili1993/cssc1808/dissem.cpp -o dissem -std=c++11 -g
./dissem [input file]

HSUM   000000002F00

T0000001A0500000320146910178D1BA0101BC0002F20073B2FF40F102EFD

M00000705

M00001705

E000000

INSTR           FORMAT          OAT             TAAM            OBJ
LDX             3               immediate       absolute        050000
LDA             3               simple          pc              032014
LDB             4               immediate       absolute        6910178D
ADD             3               simple          pc_indexed      1BA010
ADD             3               simple          base_indexed    1BC000
TIX             3               simple          pc              2F2007
JLT             3               simple          pc              3B2FF4
STA             4               simple          absolute        0F102EFD
ADDR          2                                                         9401
