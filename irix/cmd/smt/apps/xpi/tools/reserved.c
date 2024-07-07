/* RESERVED.C -- RESERVED-SYMBOL TABLE                          */

#include "asm29.h"

/*
 * Reserved symbol-table declarations.  The structure of each record is:
 *              structure res
 *                      {
 *                      char name[8]    = symbol name
 *                      char format             = mnemonic format
 *                      char flags              = line format
 *                      short opcode    = the opcode
 *                      }
 */

struct res restab[] =
        {
    {".align",  F_PSOP, R_NOLAB, 44},
    {".ascii",  F_PSOP, 0, 38},
    {".block",  F_PSOP, 0, 45},
    {".byte",   F_PSOP, 0, 39},
    {".comm",   F_PSOP, R_NOLAB, 58},
    {".data",   F_PSOP, R_NOLAB, 60},
    {".def",    F_PSOP, R_NOLAB, 47},
    {".dim",    F_PSOP, R_NOLAB, 54},
    {".double", F_PSOP, 0, 43},
    {".dsect",  F_PSOP, R_NOLAB,PS_DSECT},
    {".eject",  F_PSOP, R_NOLAB, 18},
    {".else",   F_PSOP, R_NOLAB+R_UNCOND, 13},
    {".end",    F_PSOP, R_NOLAB, 3},
    {".endef",  F_PSOP, R_NOLAB, 55},
    {".endif",  F_PSOP, R_NOLAB+R_UNCOND, 14},
    {".endm",   F_PSOP, R_NOLAB, 32},
    {".endr",   F_PSOP, R_NOLAB, 37},
    {".equ",    F_PSOP, R_LABEL+R_PASSLAB, 26},
    {".err",    F_PSOP, R_NOLAB, 5},
    {".exitm",  F_PSOP, R_NOLAB, 31},
    {".extend", F_PSOP, 0, PS_EXTEND},
    {".extern", F_PSOP, R_NOLAB, 23},
    {".file",   F_PSOP, R_NOLAB, 57},
    {".float",  F_PSOP, 0, 42},
    {".global", F_PSOP, R_NOLAB, 22},
    {".hword",  F_PSOP, 0, 40},
    {".ident",  F_PSOP, R_NOLAB, 1},
    {".if",             F_PSOP, R_NOLAB+R_UNCOND, 6},
    {".ifdef",  F_PSOP, R_NOLAB+R_UNCOND, 7},
    {".ifeqs",  F_PSOP, R_NOLAB+R_UNCOND, 9},
    {".ifndef", F_PSOP, R_NOLAB+R_UNCOND, 8},
    {".ifnes",  F_PSOP, R_NOLAB+R_UNCOND, 10},
    {".include",F_PSOP, R_NOLAB, 2},
    {".irep",   F_PSOP, R_NOLAB, 35},
    {".irepc",  F_PSOP, R_NOLAB, 36},
    {".lcomm",  F_PSOP, R_NOLAB, 63},
    {".lflags", F_PSOP, R_NOLAB, 62},
    {".line",   F_PSOP, R_NOLAB, 53},
    {".list",   F_PSOP, R_NOLAB, 15},
    {".ln",             F_PSOP, R_NOLAB, 56},
    {".macro",  F_PSOP, R_NOLAB+R_PASSLAB, 29},
    {".nolist", F_PSOP, R_NOLAB, 16},
    {".print",  F_PSOP, R_NOLAB, 17},
    {".purgem", F_PSOP, R_NOLAB, 33},
    {".reg",    F_PSOP, R_NOLAB+R_PASSLAB, 28},
    {".rep",    F_PSOP, R_NOLAB, 34},
    {".sbttl",  F_PSOP, R_NOLAB, 21},
    {".scl",    F_PSOP, R_NOLAB, 51},
    {".sect",   F_PSOP, R_NOLAB+R_PASSLAB, 24},
    {".set",    F_PSOP, R_NOLAB+R_PASSLAB, 27},
    {".size",   F_PSOP, R_NOLAB, 49},
    {".space",  F_PSOP, R_NOLAB, 19},
    {".tag",    F_PSOP, R_NOLAB, 52},
    {".text",   F_PSOP, R_NOLAB, 59},
    {".title",  F_PSOP, R_NOLAB, 20},
    {".type",   F_PSOP, R_NOLAB, 50},
    {".use",    F_PSOP, R_NOLAB, 25},
    {".val",    F_PSOP, R_NOLAB,PS_VAL},
    {".word",   F_PSOP, 0, 41},
    {"add",             F_MCAB, 0, 0X1400},
    {"addc",    F_MCAB, 0, 0X1C00},
    {"addcs",   F_MCAB, 0, 0X1800},
    {"addcu",   F_MCAB, 0, 0X1A00},
    {"adds",    F_MCAB, 0, 0X1000},
    {"addu",    F_MCAB, 0, 0X1200},
    {"and",             F_MCAB, 0, 0X9000},
    {"andn",    F_MCAB, 0, 0X9C00},
    {"aseq",    F_MVAB, 0, 0X7000},
    {"asge",    F_MVAB, 0, 0X5C00},
    {"asgeu",   F_MVAB, 0, 0X5E00},
    {"asgt",    F_MVAB, 0, 0X5800},
    {"asgtu",   F_MVAB, 0, 0X5A00},
    {"asle",    F_MVAB, 0, 0X5400},
    {"asleu",   F_MVAB, 0, 0X5600},
    {"aslt",    F_MVAB, 0, 0X5000},
    {"asltu",   F_MVAB, 0, 0X5200},
    {"asneq",   F_MVAB, 0, 0X7200},
    {"call",    F_A2A,  0, 0XA800},
    {"calli",   F_AB,   0, 0XC800},
    {"callx",   F_CALLX, 0, 0X0000},
    {"clz",             F_MCB,  0, 0X0800},
    {"const",   F_0A,   0, 0X0300},
    {"consth",  F_0A,   0, 0X0200},
    {"constn",  F_0A,   0, 0X0100},
    {"convert", F_CACA, 0, 0XE400},
    {"cpbyte",  F_MCAB, 0, 0X2E00},
    {"cpeq",    F_MCAB, 0, 0X6000},
    {"cpge",    F_MCAB, 0, 0X4C00},
    {"cpgeu",   F_MCAB, 0, 0X4E00},
    {"cpgt",    F_MCAB, 0, 0X4800},
    {"cpgtu",   F_MCAB, 0, 0X4A00},
    {"cple",    F_MCAB, 0, 0X4400},
    {"cpleu",   F_MCAB, 0, 0X4600},
    {"cplt",    F_MCAB, 0, 0X4000},
    {"cpltu",   F_MCAB, 0, 0X4200},
    {"cpneq",   F_MCAB, 0, 0X6200},
    /*
    {"cvdf",    F_CA,   0, 0XE900},
    {"cvdint",  F_CA,   0, 0XE700},
    {"cvfd",    F_CA,   0, 0XE800},
    {"cvfint",  F_CA,   0, 0XE600},
    {"cvintd",  F_CA,   0, 0XE500},
    {"cvintf",  F_CA,   0, 0XE400},
    */
    {"dadd",    F_CAB,  0, 0XF100},
    {"ddiv",    F_CAB,  0, 0XF700},
    {"deq",             F_CAB,  0, 0XEB00},
    {"dge",             F_CAB,  0, 0XEF00},
    {"dgt",             F_CAB,  0, 0XED00},
    {"div",             F_MCAB, 0, 0X6A00},
    {"div0",    F_MCB,  0, 0X6800},
    {"divide",  F_CAB,  0, 0XE100},
    {"dividu",  F_CAB,  0, 0XE300},
    {"divl",    F_MCAB, 0, 0X6C00},
    {"divrem",  F_MCAB, 0, 0X6E00},
    {"dmul",    F_CAB,  0, 0XF500},
    {"dsub",    F_CAB,  0, 0XF300},
    {"emulate", F_MVAB, 0, 0XD700}, /* was F8, change due to chip rev */
    {"exbyte",  F_MCAB, 0, 0X0A00},
    {"exhw",    F_MCAB, 0, 0X7C00},
    {"exhws",   F_CA,   0, 0X7E00},
    {"extract", F_MCAB, 0, 0X7A00},
    {"fadd",    F_CAB,  0, 0XF000},
    {"fdiv",    F_CAB,  0, 0XF600},
    {"feq",             F_CAB,  0, 0XEA00},
    {"fge",             F_CAB,  0, 0XEE00},
    {"fgt",             F_CAB,  0, 0XEC00},
    {"fmul",    F_CAB,  0, 0XF400},
    {"fsub",    F_CAB,  0, 0XF200},
    {"halt",    F_,             0, 0X8900},
    {"inbyte",  F_MCAB, 0, 0X0C00},
    {"inhw",    F_MCAB, 0, 0X7800},
    {"inv",             F_,             0, 0X9F00},
    {"iret",    F_,             0, 0X8800},
    {"iretinv", F_,             0, 0X8C00},
    {"jmp",             F_A2A,  0, 0XA000},
    {"jmpf",    F_A2A,  0, 0XA400},
    {"jmpfdec", F_A2A,  0, 0XB400},
    {"jmpfi",   F_AB,   0, 0XC400},
    {"jmpi",    F_B,    0, 0XC000},
    {"jmpt",    F_A2A,  0, 0XAC00},
    {"jmpti",   F_AB,   0, 0XCC00},
    {"load",    F_MEAB, 0, 0X1600},
    {"loadl",   F_MEAB, 0, 0X0600},
    {"loadm",   F_MEAB, 0, 0X3600},
    {"loadset", F_MEAB, 0, 0X2600},
    {"mfsr",    F_CS,   0, 0XC600},
    {"mftlb",   F_CA,   0, 0XB600},
    {"mtsr",    F_SB,   0, 0XCE00},
    {"mtsrim",  F_0S,   0, 0X0400},
    {"mttlb",   F_AB,   0, 0XBE00},
    {"mul",             F_MCAB, 0, 0X6400},
    {"mull",    F_MCAB, 0, 0X6600},
    {"multiplu", F_CAB, 0, 0XE200},
    {"multiply", F_CAB, 0, 0XE000},
    {"mulu",    F_MCAB, 0, 0X7400},
    {"nand",    F_MCAB, 0, 0X9A00},
    {"nop",             F_NOP,  0, 0X7000},
    {"nor",             F_MCAB, 0, 0X9800},
    {"or",              F_MCAB, 0, 0X9200},
    {"setip",   F_CAB,  0, 0X9E00},
    {"sll",             F_MCAB, 0, 0X8000},
    {"sra",             F_MCAB, 0, 0X8600},
    {"srl",             F_MCAB, 0, 0X8200},
    {"store",   F_MEAB, 0, 0X1E00},
    {"storel",  F_MEAB, 0, 0X0E00},
    {"storem",  F_MEAB, 0, 0X3E00},
    {"sub",             F_MCAB, 0, 0X2400},
    {"subc",    F_MCAB, 0, 0X2C00},
    {"subcs",   F_MCAB, 0, 0X2800},
    {"subcu",   F_MCAB, 0, 0X2A00},
    {"subr",    F_MCAB, 0, 0X3400},
    {"subrc",   F_MCAB, 0, 0X3C00},
    {"subrcs",  F_MCAB, 0, 0X3800},
    {"subrcu",  F_MCAB, 0, 0X3A00},
    {"subrs",   F_MCAB, 0, 0X3000},
    {"subru",   F_MCAB, 0, 0X3200},
    {"subs",    F_MCAB, 0, 0X2000},
    {"subu",    F_MCAB, 0, 0X2200},
    {"xnor",    F_MCAB, 0, 0X9600},
    {"xor",             F_MCAB, 0, 0X9400},
        };

int nres = sizeof(restab) / sizeof(struct res);