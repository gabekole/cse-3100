#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char ** argv)
{
    pid_t child_1, child_2;
    int exitStatus;

    // at least, there should be 3 arguments
    // 2 for the first command, and the rest for the second command
    
    if (argc < 4) {
        fprintf(stderr, "Usage: %s cmd1 cmd1_arg cmd2 [cmd2_args ..]\n", argv[0]);
        return 1;
    }


    child_1 = fork();
    if(child_1 < 0)
    {
        perror("fork()");
        exit(1);
    }
    else if(child_1 == 0)
    {
        execlp(argv[1], argv[1], argv[2], NULL);
        perror("execlp");
        exit(1);
    }
    else
    {
        waitpid(child_1, &exitStatus, 0);
        printf("exited=%d exitstatus=%d\n", WIFEXITED(exitStatus), WEXITSTATUS(exitStatus));
    }


    pid_t child_2 = fork();
    if(child_2 < 0)
    {
        perror("Failed to create child process");
        exit(1);
    }
    else if(child_2 == 0)
    {        
        execvp("ls", argv + 3);
        perror("execvp");
        exit(1);
    }
    else
    {
        waitpid(child_2, NULL, 0);
        printf("exited=%d exitstatus=%d\n", WIFEXITED(exitStatus), WEXITSTATUS(exitStatus));
    }


    // TODO
    return exitStatus;
}
