#include "asm_pass2.c"

int main(int argc, char *argv[])
{
	int			i, c, line_count;
	char		buf[LEN_SYMBOL];
	LINE		line;

	if(argc < 2)
	{
		printf("Usage: %s fname.asm\n", argv[0]);
	}
	else
	{
		if(ASM_open(argv[1]) == NULL)
			printf("File not found!!\n");
		else
		{
			if (argc >= 3)
				ASM_out(argv[3]);
			else
				ASM_out("asm_out");
			printf("LC  : MEMLOC | %12s %12s %12s \n", "SYMBOL", "INSTRUCTION", "OPERAND");
			printf("-----------------------------------------------------\n");
			for(line_count = 1 ; (c = process_line(&line)) != LINE_EOF; line_count++)
			{
                char line_memloc[LEN_SYMBOL], line_op[LEN_SYMBOL], line_operand1[LEN_SYMBOL], line_operand2[LEN_SYMBOL];
                sprintf(line_memloc, "%06X", line.memloc);
                sprintf(line_op, "%s%s", (line.fmt==FMT4)?"+":" ", line.op);
                sprintf(line_operand1, "%s%s", (line.addressing==ADDR_IMMEDIATE)?"#":(line.addressing==ADDR_INDIRECT?"@":""), line.operand1);
                sprintf(line_operand2, "%s%5s", (*line.operand2) ? "," : "", line.operand2);

				if(c == LINE_ERROR)
					printf("%03d : Error\n", line_count);
				else if(c == LINE_COMMENT)
					printf("%03d : ------ | . Comment line \n", line_count);
				else
					printf("%03d : %6s | %12s %12s %12s %s\n",
                            line_count, (line.memloc || line.fmt) ? line_memloc : "------", 
                            line.symbol, line_op,
                            line_operand1, line_operand2
                    );
            }
            printf(".\n.\n");
            printf("Program length = %06X\n.\n.\n", pc);
			printf("----SYM_NAME|----MEMLOC----\n\n");
            records_indir = &records_head;
            while(*records_indir) {
                printf("%12s:\t %06X\n", (*records_indir)->name, lookup((*records_indir)->name)->loc);
                records_indir = &((*records_indir)->next);
			}
			ASM_close();
		}
	}
}