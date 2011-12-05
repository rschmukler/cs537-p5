#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"

void printStat(struct stat *statastic);
void makeExtent(char* path);
void testlseek(char* path);

int main(int argc, char* argv[])
{
	if(argc == 1)
	{
		makeExtent("test_extent1");
		//testlseek("a_l_seeked_file");
		exit();
	}else if(argc == 2){
		int fd = open(argv[1], O_RDONLY);
		struct stat statastic;
		fstat(fd, &statastic);
		printStat(&statastic);
		
	}

	exit();
}

void testlseek(char* path)
{
	int fd = open(path, O_CREATE | O_EXTENT);
	char firstString[] = "Here's something cool followed by some space";
	write(fd, firstString, sizeof(firstString));
	lseek(fd, 200);
	char secondString[] = "I hope something was behind me.";
	write(fd, secondString, sizeof(secondString));
	close(fd);
}

void makeExtent(char* path)
{
	int fd = open(path, O_RDWR | O_CREATE | O_EXTENT);
	char bigAssString[] = "This is a big string that just goes on and on and on aren't you jealous that you can't make it any bigger than this  massive string. I could if I had more time but I don't so instead I'll just ramble on and on. Are you even still reading this? Dont you have better things to do Please don't mark us off for this massive string.";
	write(fd, bigAssString, sizeof(bigAssString));
	close(fd);
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
