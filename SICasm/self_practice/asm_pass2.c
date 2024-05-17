#include "asm_pass1.c"

line_record **lines_ind = &lines_head;
LINE *line;
bool is_newline = true;
int startaddr, reclen, objcode, ret=0;
int symloc;
char recline[71];

int process_pass1(char *objrec) {

    line = &((*lines_ind)->line);

    if (line->op == OP_END) {

    }

    if (lines_ind == NULL) {

    }
    
    if (line->op == OP_START) {
        fprintf(ASM_ofp, "H%6s%06X%06X\n", line->symbol, atoi(line->operand1), pc);
        lines_ind = (*lines_ind)->next;
        line = &((*lines_ind)->line);
    } else {
        fprintf(ASM_ofp, "H%6s%06X%06X\n", "", 0, pc);
    }
    
    if (*lines_ind && line->op != OP_END) {


        if (is_newline) {
            startaddr = line->addressing;
            is_newline = false;
        }
        if (line->fmt != FMT0) {
            if (isalpha(line->operand1[0]) || isalpha(line->operand1[1])) {
                if (lookup(line->operand1)) {
                    symloc = lookup(line->operand1);
                } else {
                    symloc = 0;
                    ret = LINE_ERROR;
                }
            }

        } else if (line->op == OP_BYTE || line->op == OP_WORD) {

        }

        lines_ind = (*lines_ind)->next;
    }
    
}