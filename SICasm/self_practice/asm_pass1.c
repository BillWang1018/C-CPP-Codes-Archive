#include "optable.c"

/* Public variables and functions */
#define	ADDR_SIMPLE			0x01
#define	ADDR_IMMEDIATE		0x02
#define	ADDR_INDIRECT		0x04
#define	ADDR_INDEX			0x08

#define	LINE_EOF			(-1)
#define	LINE_COMMENT		(-2)
#define	LINE_ERROR			( 0)
#define	LINE_CORRECT		( 1)

#define HASHSIZE 101

/* nlist for hashmap */
typedef struct nlist{ /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    unsigned  loc; /* location */
}  nlist;

/* line for a line of asm command*/
typedef struct LINE
{
	char		symbol[LEN_SYMBOL];
	char		op[LEN_SYMBOL];
	char		operand1[LEN_SYMBOL];
	char		operand2[LEN_SYMBOL];
	unsigned	code;
	unsigned	fmt;
	unsigned	addressing;	
    unsigned    memloc;
} LINE;

typedef struct sym_record {
    char *name;
    struct sym_record *next;
} sym_record;

typedef struct line_record {
	LINE line;
	struct line_record *next;
} line_record;

nlist *symtab[HASHSIZE]; /* pointer table */
sym_record *records_head, **records_indir;
line_record *lines_head, **lines_tail;
unsigned pc=0, saddr=0;


/* return LINE_EOF, LINE_COMMENT, LINE_ERROR, LINE_CORRECT and Instruction information in *line*/
int process_line(LINE *line);

/* (private) */
void init_LINE(LINE *line)
{
	line->symbol[0] = '\0';
	line->op[0] = '\0';
	line->operand1[0] = '\0';
	line->operand2[0] = '\0';
	line->code = 0x0;
	line->fmt = 0x0;
	line->addressing = ADDR_SIMPLE;
    line->memloc = 0;
}

/* hash (private): form hash value for string s */
unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for s in symtab */
nlist *lookup(char *s) {
    nlist *np;
    for (np = symtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
          return np; /* found */
    return NULL; /* not found */
}

/* install: put (name, loc) in symtab */
nlist *install(char *name, int loc) {
    nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* not found */
        np = (nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = symtab[hashval];
        symtab[hashval] = np;
        records_indir = &records_head;
        sym_record *new = (sym_record *)malloc(sizeof(sym_record));
        new->name = strdup(name), new->next = NULL;
        while (*records_indir) 
            records_indir = &((*records_indir)->next);
        *records_indir = new;
    } else /* already there */
        free((void *) np->loc); /* free previous loc */
    np->loc = loc;
    return np;
}

int process_line(LINE *line) {
    char buf[LEN_SYMBOL];
    int c, state, ret;
    Instruction *op;
	lines_tail = &(lines_head);

    c = ASM_token(buf);
	if(c == EOF)
		return LINE_EOF;
	else if((c == 1) && (buf[0] == '\n'))	/* blank line */
		return LINE_COMMENT;
	else if((c == 1) && (buf[0] == '.'))	/* a comment line */
	{
		do
		{
			c = ASM_token(buf);
		} while((c != EOF) && (buf[0] != '\n'));
		return LINE_COMMENT;
	}
	else
	{
		init_LINE(line);
		ret = LINE_ERROR;
		state = 0;
		while(state < 8)
		{
			switch(state)
			{
				case 0:
				case 1:
				case 2:
					op = is_opcode(buf);
					if((state < 2) && (buf[0] == '+'))	/* + */
					{
						line->fmt = FMT4;
						state = 2;
					}
					else	if(op != NULL)	/* INSTRUCTION */
					{
						strcpy(line->op, op->op);
						line->code = op->code;
						state = 3;
						if(line->fmt != FMT4)
						{
							line->fmt = op->fmt & (FMT1 | FMT2 | FMT3);
						}
						else if((line->fmt == FMT4) && ((op->fmt & FMT4) == 0)) /* INSTRUCTION is FMT1 or FMT 2*/
						{	/* ERROR 20210326 added */
							printf("ERROR at token %s, %s cannot use format 4 \n", buf, buf);
							ret = LINE_ERROR;
							state = 7;		/* skip following tokens in the line */
						}
					}				
					else	if(state == 0)	/* SYMBOL */
					{
						strcpy(line->symbol, buf);
						state = 1;
					}
					else		/* ERROR */
					{
						printf("ERROR at token %s\n", buf);
						ret = LINE_ERROR;
						state = 7;		/* skip following tokens in the line */
					}
					break;	
				case 3:
					if(line->fmt == FMT1 || line->code == 0x4C)	/* no operand needed */
					{
						if(c == EOF || buf[0] == '\n')
						{
							ret = LINE_CORRECT;
							state = 8;
						}
						else		/* COMMENT */
						{
							ret = LINE_CORRECT;
							state = 7;
						}
					}
					else
					{
						if(c == EOF || buf[0] == '\n')
						{
							ret = LINE_ERROR;
							state = 8;
						}
						else	if(buf[0] == '@' || buf[0] == '#')
						{
							line->addressing = (buf[0] == '#') ? ADDR_IMMEDIATE : ADDR_INDIRECT;
							state = 4;
						}
						else	/* get a symbol */
						{
							op = is_opcode(buf);
							if(op != NULL)
							{
								printf("Operand1 cannot be a reserved word\n");
								ret = LINE_ERROR;
								state = 7; 		/* skip following tokens in the line */
							}
							else
							{
								strcpy(line->operand1, buf);
								state = 5;
							}
						}
					}			
					break;		
				case 4:
					op = is_opcode(buf);
					if(op != NULL)
					{
						printf("Operand1 cannot be a reserved word\n");
						ret = LINE_ERROR;
						state = 7;		/* skip following tokens in the line */
					}
					else
					{
						strcpy(line->operand1, buf);
						state = 5;
					}
					break;
				case 5:
					if(c == EOF || buf[0] == '\n')
					{
						ret = LINE_CORRECT;
						state = 8;
					}
					else if(buf[0] == ',')
					{
						state = 6;
					}
					else	/* COMMENT */
					{
						ret = LINE_CORRECT;
						state = 7;		/* skip following tokens in the line */
					}
					break;
				case 6:
					if(c == EOF || buf[0] == '\n')
					{
						ret = LINE_ERROR;
						state = 8;
					}
					else	/* get a symbol */
					{
						op = is_opcode(buf);
						if(op != NULL)
						{
							printf("Operand2 cannot be a reserved word\n");
							ret = LINE_ERROR;
							state = 7;		/* skip following tokens in the line */
						}
						else
						{
							if(line->fmt == FMT2)
							{
								strcpy(line->operand2, buf);
								ret = LINE_CORRECT;
								state = 7;
							}
							else if((c == 1) && (buf[0] == 'x' || buf[0] == 'X'))
							{
								line->addressing = line->addressing | ADDR_INDEX;
								ret = LINE_CORRECT;
								state = 7;		/* skip following tokens in the line */
							}
							else
							{
								printf("Operand2 exists only if format 2 is used\n");
								ret = LINE_ERROR;
								state = 7;		/* skip following tokens in the line */
							}
						}
					}
					break;
				case 7:	/* skip tokens until '\n' || EOF */
					if(c == EOF || buf[0] =='\n')
						state = 8;
					break;										
			}
			if(state < 8)
				c = ASM_token(buf);  /* get the next token */
		}
        if (line->code == OP_START) {
            pc = saddr = atoi(line->operand1);
            line->memloc = pc;
        }
        if (line->fmt != 0 || (line->code >= OP_BYTE && line->code <= OP_RESW))
            line->memloc = pc;

        if (*(line->symbol) != '\0')
            install(line->symbol, pc);

        if (line->fmt != 0) 
            for (int i=line->fmt; i!=0; i>>=1)
                pc++;
        else if (line->code == OP_BYTE) {
			if 		(line->operand1[0] == 'C') 
				pc += (strlen(line->operand1)-3); 
			else if (line->operand1[0] == 'X')
				pc += (strlen(line->operand1)-2)/2;
		}
        else if (line->code == OP_WORD)
            pc += 3;
        else if (line->code == OP_RESB)
            pc += atoi(line->operand1);
        else if (line->code == OP_RESW)
            pc += atoi(line->operand1) * 3;
		
		// save line for pass 2
		*lines_tail = (LINE *)malloc(sizeof(LINE));
		memcpy(*lines_tail, &line, sizeof(LINE));
		*lines_tail = &((*lines_tail)->next);

		return ret;
	}

}