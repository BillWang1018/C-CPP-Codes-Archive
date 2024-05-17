#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LEN_SYMBOL (20)

/* Public variables and functions */
FILE *ASM_open(char *fname); /* Open a SIC/XE asm file */
							 /* return NULL if failed */
void ASM_close(void);		 /* Cloase the asm file */
int ASM_token(char *buf);	 /* Get a token from the file */
							 /* The token is stored at buf. */
							 /* Return the length of the token. Return EOF if end of file reached. */

/* Private variable and functions */
FILE *ASM_fp, *ASM_ofp;
int ASM_buf;                                /*ASM_buf, ASM_flag is for one symble look ahead*/
bool ASM_flag = false;                       /*use ASM_buf first if ASM_flag is true*/
char DELIMITER[] = " ,\t\r\n";
int LEN_DELIMITER = sizeof(DELIMITER) - 1;  /* subtract the last character '\0' */
char SPECIAL[] = "#@+*,.";				    /* , in DELIMINTER and SPECIAL */
int LEN_SPECIAL = sizeof(SPECIAL) - 1;	    /* subtract the last character '\0' */

FILE *ASM_open(char *fname) {
    ASM_fp = fopen(fname, "r");
    if (ASM_fp)
        return ASM_fp;
    else 
        return NULL;
}

FILE *ASM_out(char *fname) {
    ASM_ofp = fopen(strcat(fname, ".obj"), "w");
    if (ASM_ofp)
        return ASM_ofp;
    else 
        return NULL;
}

void ASM_close() {
    fclose(ASM_fp);
    fclose(ASM_ofp);
}

int ASM_getc() {
    if (ASM_flag) {
        ASM_flag = false;
        return ASM_buf;
    }
    return fgetc(ASM_fp);
}

void ASM_ungetc(int c) {
    ASM_buf = c;
    ASM_flag = true;
}

bool is_delimiter(char c) {
    for (int i=0; i<LEN_DELIMITER; i++) {
        if (c == DELIMITER[i]) return true;
    }
    return false;
}

bool is_special(char c) {
    for (int i=0; i<LEN_SPECIAL; i++) {
        if (c == SPECIAL[i]) return true;
    }
    return false;
}

int ASM_token(char *buf) {
    int c, len;
    buf[0] = '\0';

    c = ASM_getc();

    // skip tabs and spaces until first character
    while (c == '\t' || c == ' ') {
        c = ASM_getc();
    }
    if (c == EOF) return EOF;

    if (is_special(c)) {                /*special chars*/
        buf[0] = c;
        buf[1] = '\0';
        len = 1;
    } else if (c == '\r' || c == '\n') {/*new line indicator*/
        c = ASM_getc();
        if (c != '\r' && c != '\n') {   /*put back if not new line sym*/
            ASM_ungetc(c);
        }
        buf[0] = '\n';                  /*unify "\r\n"(linux) and "\n"(windows) to \n*/
        buf[1] = '\0';
        len = 1;
    } else {                            /*read symbol until delimiter or max_len reached*/
        for (len=0; c != EOF && !is_delimiter(c); c = ASM_getc()) {
            if (len < LEN_SYMBOL-1) {     /*still get all remaining chars out of max len*/
                buf[len++] = c;
            }
        }

        if (c != '\t' && c != ' ') {    /*put back if not space\tab (others delimiter)*/
            ASM_ungetc(c);
        }

        buf[len] = '\0';
    }

    return len;
}