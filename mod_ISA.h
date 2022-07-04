//
// Created by Marco Kaniecki on 2022-06-27.
//

#ifndef XMX_MODIFYING_ISA_MOD_ISA_H
#define XMX_MODIFYING_ISA_MOD_ISA_H

#include <stdio.h>
#include <string.h>

#define MAX_REC_LEN 128
#define TAB "\t"
#define REG_INST_NUM 32
#define CUST_INST_NUM 3
#define REG_LEN 2
#define TRUE 1
#define FALSE 0

FILE *infile;
FILE *outfile;

int instr_index;

char *new_inst[] = {"ADDX", "SUBX", "CMPX"};

extern int find_cust_inst(char *token);
extern void translate_inst(char *registers);

#endif //XMX_MODIFYING_ISA_MOD_ISA_H
