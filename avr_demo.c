#define dRegB *((volatile unsigned char*) 0x25)

int main(void)
{
	while (1)
	{
	  dRegB = 1;
	  for (long i = 0; i < 10000; i++) dRegB = 1;

	  dRegB = 0;
	  for (long i = 0; i < 10000; i++) dRegB = 0;

	}
}
