#include <stdio.h>

int addr_space = 24;
int block_size;
int num_sets;
int assoc;
int write_policy;
int cache_size;
int num_blocks;

/* Will process and output all flags */
void GetFlags(int argc, char *argv[]) 
{
	while ((argc > 1) && (argv[1][0] == '-'))
	{
		switch (argv[1][1])
		{
			case 'b':
				block_size = atoi(&argv[1][3]);
				printf("Block size = %d\n", block_size);
				break;
			case 's':
				num_sets = atoi(&argv[1][3]);
				printf("Number of sets = %d\n", num_sets);
				break;
			case 'a':
				assoc = atoi(&argv[1][3]);
				printf("Associativity = %d\n", assoc);
				break;
			case 'W':
				write_policy = atoi(&argv[1][3]);
				printf("Write policty = %d\n", write_policy);
				break;
			default:
				printf("Wrong Argument: %s\n", argv[1]);
		}
		argv += 2;
		argc -= 2;
	}
		
}

/* Prints header information for cache */
void PrintHeader()
{
	int offset = num_sets;
	int index = num_sets;
	int counter = 1;

	while (offset != 0)
	{
		++counter;
		offset = offset >> 2;
	}
	offset = counter++;
	counter = 1;
	
	while (index != 0)
	{
		++counter;
		index = index >> 2;
	}
	index = ++counter;

	int tag = addr_space - offset - index;

	cache_size = (num_sets * block_size * assoc) / 1024;
	num_blocks = num_sets * assoc;

	printf("%dKB %d-way associative cache:\n", cache_size, assoc);
	printf("\tBlock size = %d bytes\n", block_size);
	printf("\tNumber of [sets,blocks] = [%d,%d]\n", num_sets, num_blocks);
	printf("\tExtra space for tag storage = ?? bytes (1.95%)\n");
	printf("\tBits for [tag,index,offset] = [%d,%d,%d]\n", tag, index, offset);
}

void HexToBin(char hex[], int hexc, char *bin[6])
{
	int i = 0;
	while (i != hexc)
	{
		switch (hex[i])
		{
			case '0':
				bin[i] = "0000\0";
				break;
			case '1':
				bin[i] = "0001\0";
				break;
			case '2':
				bin[i] = "0010\0";
				break;
			case '3':
				bin[i] = "0011\0";
				break;
			case '4':
				bin[i] = "0100\0";
				break;
			case '5':
				bin[i] = "0101\0";
				break;
			case '6':
				bin[i] = "0110\0";
				break;
			case '7':
				bin[i] = "0111\0";
				break;
			case '8':
				bin[i] = "1000\0";
				break;
			case '9':
				bin[i] = "1001\0";
				break;
			case 'a':
				bin[i] = "1010\0";
				break;
			case 'b':
				bin[i] = "1011\0";
				break;
			case 'c':
				bin[i] = "1100\0";
				break;
			case 'd':
				bin[i] = "1101\0";
				break;
			case 'e':
				bin[i] = "1110\0";
				break;
			case 'f':
				bin[i] = "1111\0";
				break;
			default:
				break;
		}
		//printf("%s\n", bin[i]);
		i++;
	}
	bin[5] = "\0";
}

int main(int argc, char *argv[]) 
{
	GetFlags(argc, argv);	
	PrintHeader();
	
	char hex[6];
	char *bin[6];

	hex[0] = '0';
	hex[1] = 'c';
	hex[2] = '0';
	hex[3] = 'e';
	hex[4] = '7';
	hex[5] = '\0';
	
	int hexc = sizeof(hex);

	printf("%s -> ", hex);

	HexToBin(hex, hexc, bin);

	int i = 1;
	printf("%6s", bin[0]);
	for (i; i < hexc; i++)
		printf("%s", bin[i]);	
	printf("\n");
	return 0;
}
