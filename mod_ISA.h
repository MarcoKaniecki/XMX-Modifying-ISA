//
// Created by Marco Kaniecki on 2022-06-27.
//

#ifndef XMX_MODIFYING_ISA_MOD_ISA_H
#define XMX_MODIFYING_ISA_MOD_ISA_H

#include <stdio.h>
#include <string.h>

#define MAX_REC_LEN 128
#define CUST_INST_NUM 9
#define TRUE 1
#define FALSE 0
#define NUM_CONST 8
#define TRUNCATE(name)  name[strlen(name)-1] = '\0'

FILE *infile;
FILE *outfile;

int instr_index;

enum NEW_INSTR {ADDX, ADDXw, ADDXb, SUBX, SUBXw, SUBXb, CMPX, CMPXw, CMPXb};

char *constants[] = {"0", "1", "2", "4", "8", "16", "32", "-1"};

char *new_inst[] = {"ADDX","ADDX.w","ADDX.b",
                    "SUBX","SUBX.w","SUBX.b",
                    "CMPX","CMPX.w","CMPX.b"};

extern int find_cust_inst(char *token);
extern void translate_inst(char *registers);

#endif //XMX_MODIFYING_ISA_MOD_ISA_H
