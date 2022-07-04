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
        TRUNCATE(inrec);  // removes LF
        found_cust_inst = FALSE;
        char *piece = strtok(inrec, "\t ");

        while (piece != NULL)
        {
            if (found_cust_inst)
            {
                char regs[MAX_REC_LEN];
                sscanf(piece, "%s", regs);
                translate_inst(regs);
                found_cust_inst = FALSE;
                piece = strtok(NULL, "\t ");
                continue;
            }


            if (find_cust_inst(piece))
                found_cust_inst = TRUE;
            else
                fprintf(outfile, "%s ", piece);

            piece = strtok(NULL, "\t ");
        }
        fprintf(outfile, "\n");
    }

    fclose(infile);
    return 0;
}


int find_cust_inst(char *token)
{
    for (int i = 0; i < CUST_INST_NUM; i++)
        if (strcasecmp(token, new_inst[i]) == 0)  // compares while insensitive to lower/upper case
        {
            instr_index = i;
            printf("found %s\n", new_inst[i]);
            return TRUE;
        }
    return FALSE;
}


void translate_inst(char *registers)
{
    char src[MAX_REC_LEN], dst[MAX_REC_LEN];
    short translated_inst;

    if (instr_index >= ADDX && instr_index <= ADDXb)  // ADDX or ADDX.w or ADDX.b
        translated_inst = (instr_index != ADDXb)? 0x6000 : 0x6000 + (1 << 6);  // set W/B bit if byte inst
    else if (instr_index >= SUBX && instr_index <= SUBXb)  // SUBX or SUBX.w or SUBX.b
        translated_inst = (instr_index != SUBXb)? 0x6400 : 0x6400 + (1 << 6);  // set W/B bit if byte inst
    else // CMPX or CMPX.w or CMPX.b
        translated_inst = (instr_index != CMPXb)? 0x6800 : 0x6800 + (1 << 6);  // set W/B bit if byte inst

    sscanf(registers, "%[^,],%s", src, dst);

    // SRC
    if (src[0] == 'A')
        translated_inst += (1 << 9);  // set SRA bit
    else if (src[0] == '$')
        translated_inst += (1 << 7);  // set R/C bit to 1 for constant

    if (dst[0] == 'A')
        translated_inst += (1 << 8);  // set DRA bit

    // convert ie. char '7' to number 7
    translated_inst += ((src[1] - '0') << 3);
    translated_inst += (dst[1] - '0');

    // check

    fprintf(outfile, "WORD #%04X", translated_inst);
}
