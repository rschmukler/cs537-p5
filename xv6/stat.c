#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"


uint
toAddr(uint pointer, uint size)
{
  return ((pointer << 8) | size);
}

uint
getPtr(uint addr)
{
  printf(1, "Getting ptr\n");
  return ((addr & ~0xff) >> 8);
}

uint
getSize(uint addr)
{
  printf(1, "Getting size\n");
  return (addr & 0xff);
}


void printStat(struct stat *statastic)
{
	printf(1, "Type: %d\niNode Number: %d\nNumber of Links: %d\nSize: %d bytes\n", statastic->type, statastic->ino, statastic->nlink, statastic->size);
	if(statastic->type == T_EXTENT)
	{
		int n = 0;
		while(statastic->addrs[n] && n < 13)
		{
			printf(1, "\tAddress: %x\n\t\tSize: %d blocks\n", getPtr(statastic->addrs[n]), getSize(statastic->addrs[n]));
			++n;
		}
	}
}



int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf(1, "Error, please specify a file.\n");
		exit();
	}else {
		int fd = open(argv[1], O_RDONLY | O_EXTENT);
		struct stat statastic;
		fstat(fd, &statastic);
		printStat(&statastic);
		exit();
	}
}