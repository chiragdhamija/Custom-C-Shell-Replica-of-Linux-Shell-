#include "headers.h"

void die(const char *s)
{
    perror(s);
    exit(1);
}

struct termios orig_termios;

void disableRawMode()
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("tcsetattr");
}

void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

void neonatekar(char **token_list, int tok_count, char *homedir)
{
    char dabao = 'x';
    int tim = 0;
    for (int i = 0; i < strlen(token_list[2]); i++)
    {
        tim = tim * 10 + ((int)token_list[2][i] - 48);
    }
    setbuf(stdout, NULL);
    enableRawMode();
    int pid = fork();
    int l_pid;
    if (pid == 0)
    {
        while (1)
        {
            l_pid = 0;
            FILE *fid = fopen("/proc/loadavg", "r");
            if (fid == NULL)
            {   
                printf("\033[1;31mError opening loadavg file\n\033[0;0m");
                exit(EXIT_FAILURE);
            }
            char read_load_avg[500];
            while (fgets(read_load_avg, 500, fid))
            {
                char list[5][30];
                int to_count = 0;
                char del[] = " :\t\n\0";
                char *toke = strtok(read_load_avg, del);
                while (toke != NULL)
                {
                    strcpy(list[to_count++],toke);
                    toke = strtok(NULL, del);
                }
                l_pid = 0;
                for (int i = 0; i < strlen(list[4]); i++)
                {
                    l_pid = l_pid * 10 + ((int)list[4][i] - 48);
                }
            }
            fclose(fid);
            printf("%d\n", l_pid);
            sleep(tim);
        }
    }
    else if (pid > 0)
    {
        char inp_key;
        while (read(STDIN_FILENO, &inp_key, 1) == 1 && inp_key != dabao)
        {
            continue;
        }
        kill(pid, SIGKILL);
        disableRawMode();
    }
}