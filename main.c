#include "mod_ISA.h"



int main()
{
    char inrec[MAX_REC_LEN], orig_rec[MAX_REC_LEN];
    unsigned int segment;

    infile = fopen("A1test.asm", "r");
    outfile = fopen("new_A1test.asm", "w");

    if (outfile == NULL)
    {
        printf("Error opening outfile!\n");
        return -1;
    }

    while (fgets(inrec, MAX_REC_LEN, infile) > 0)
    {
        segment = 0;
        strcpy(orig_rec, inrec);

        // ie. ADDX   A0,A0   ; comments
        char *piece = strtok(inrec, TAB);
        while (piece != NULL)
        {
            // printf("%s\n", piece);
            fprintf(outfile, "%s ", piece);

            // TODO: check if label
            // instr name or label
            if (segment == 0)
            {
                if (strcmp(piece, "ADDX") == 0)
                {
                    printf("ADDX");
                }
                else if (strcmp(piece, "SUBX") == 0)
                {
                    printf("SUBX");
                }
                else if (strcmp(piece, "CMPX") == 0)
                {
                    printf("CMPX");
                }
                else
                {
                    // TODO: could be label
                    // TODO: ie. label ADDX A0,A0
                    fprintf(outfile, "Not new instr, print inrec\n");
                    fprintf(outfile, "%s", inrec);
                }

                segment++;
            }

            piece = strtok(NULL, TAB);
        }
    }

    fclose(infile);
    return 0;
}
