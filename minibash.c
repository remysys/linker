#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
  
  char buff[1024] = {0};
    
	pid_t pid;
	while (1) {
		printf("minibash$");
		scanf("%s", buff);

		pid = fork();
		if (pid == 0) {
			if (execlp(buff, buff, 0) < 0)
			  printf("execlp error\n");
		} else if (pid > 0) {
			int status;
			waitpid(pid, &status, 0);
		} else {
			printf("fork error %d\n", pid);
		}
	}
	return 0;
}