// Do not modify this file. It will be replaced by the grading scripts
// when checking your project.

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define assert(x) if (x) { /* pass */ } else { \
   printf(1, "assert failed %s %s %d\n", #x , __FILE__, __LINE__); \
   exit(); \
   }

char * testname = "extent";

char buf[512];

int
main(int argc, char *argv[])
{
   int status;

   memset(buf, 0, 512);

   int fd;

   unlink("testout");
   fd = open("testout", O_WRONLY | O_CREATE | O_EXTENT);
   assert(fd != -1);

   int i;
   for (i = 0; i < 10; i++) {
      buf[0] = i;
      status = write(fd, buf, 512);
         assert(status != -1);
   }
   status = close(fd);
   assert(status != -1);


   int pid = fork();
   if (pid == 0) {
      printf(1, "Output from stat:\n");
      char * args[] = {"stat", "testout", NULL};
      exec(args[0], args);
      exit();
   } else {
      wait();
      printf(1, "\n");
   }

   fd = open("testout", O_RDONLY);
   assert(fd != -1);

   for (i = 0; i < 10; i++) {
      status = read(fd, buf, 512);
      assert(status != -1);
      printf(1, "Wanted Buffer: %d\n", i);
      printf(1, "Actual Buffer: %d\n", buf[0]);
      assert(buf[0] == i);
   }
   status = close(fd);
   assert(status != -1);

   printf(1, "%s TEST PASSED\n", testname);
   exit();
}
