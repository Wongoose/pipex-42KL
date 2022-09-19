#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
    pid_t   pid1;
    pid_t   pid2;
    pid_t   result;
    int     status;

    printf("Fork here!\n");
    pid1 = fork();
    if (pid1 == -1)
        return (-1);
    // Splitting point is here (same program counter)
    printf("Fork 1 SUCCESS!\n");
    if (pid1 == 0)
    {
        // fork successful child has it's own pid
        printf("\tFORK: I AM THE 1ST CHILD, my internal pid is %d.\n", pid1);
        return (1);
    }
    else if (pid1 > 0)
    {
        pid2 = fork();
        if (pid2 == -1)
            return (-2);
        printf("Fork 2 SUCCESS!\n");
        if (pid2 == 0)
        {
            // fork successful child has it's own pid
            printf("\tFORK: I AM THE 2ND CHILD, my internal pid is %d.\n", pid1);
            return (2);
        }
        else if (pid2 > 0)
        {
            // at this point, pid1 and pid2 are the children's PID
            printf("\tFORK: I AM THE PARENT OF 2 CHILDREN!\n");
            result = waitpid(pid1, &status, 0);
            printf("\tPARENT: I received my FIRST child %d\n", result);
            if (WIFEXITED(status))
                printf("\tPARENT: 1ST CHILD exited successfully, exit code %d\n", WEXITSTATUS(status));
            else
                printf("\tPARENT: 1ST CHILD was interrupted...\n");

            result = waitpid(pid2, &status, 0);
            printf("\tPARENT: I received my SECOND child %d\n", result);
            if (WIFEXITED(status))
                printf("\tPARENT: 2ND CHILD exited uccessfully, exit code %d\n", WEXITSTATUS(status));
            else
                printf("\tPARENT: 2ND CHILD was interrupted...\n");
        }
    }
    return (0);
}