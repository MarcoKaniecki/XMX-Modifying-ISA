#include "mod_ISA.h"

int main()
{
    char inrec[MAX_REC_LEN];
    int found_cust_inst;

    infile = fopen("A1test.asm", "r");
    outfile = fopen("new_A1test.asm", "w");

    if (outfile == NULL)
    {
        printf("Error opening outfile!\n");
        return -1;
    }

    while (fgets(inrec, MAX_REC_LEN, infile) > 0)
    {
        found_cust_inst = FALSE;
        char *piece = strtok(inrec, "\t ");

        while (piece != NULL)
        {
            if (found_cust_inst)
            {
                char regs[MAX_REC_LEN], comments[MAX_REC_LEN];

                // separate regs from any comments
                sscanf(piece, "%s\t%128c", regs, comments);
                translate_inst(regs);

                found_cust_inst = FALSE;
                fprintf(outfile, "%s", comments);
                break;
            }


            if (find_cust_inst(piece))
                found_cust_inst = TRUE;
            else
                fprintf(outfile, " %s", piece);  // TODO: now everything is offset by 1 whitespace


            piece = strtok(NULL, "\t ");
        }
    }

    fclose(infile);
    return 0;
}


void translate_inst(char *registers)
{
    char src[MAX_REC_LEN], dst[MAX_REC_LEN];
    short translated_inst;

    if (strcmp(new_inst[instr_index], "ADDX") == 0)
        translated_inst = 0x6000;
    else if (strcmp(new_inst[instr_index], "SUBX") == 0)
        translated_inst = 0x6400;
    else  // CMPX
        translated_inst = 0x6800;

    sscanf(registers, "%[^,],%s", src, dst);

    if (src[0] == 'A')
        translated_inst += (1 << 9);  // set SRA bit
    else if (src[0] == '$')
        translated_inst += (1 << 7);  // set R/C bit to 1 for constant

    if (dst[0] == 'A')
        translated_inst += (1 << 8);  // set DRA bit

    // convert ie. char '7' to number 7
    translated_inst += ((src[1] - '0') << 3);
    translated_inst += (dst[1] - '0');

    fprintf(outfile, "WORD\t#%04X\t", translated_inst);
}


int find_cust_inst(char *token)
{
    for (int i = 0; i < CUST_INST_NUM; i++)
        if (strcasecmp(token, new_inst[i]) == 0)  // compares while insensitive to lower/upper case
        {
            instr_index = i;
            return TRUE;
        }
    return FALSE;
}