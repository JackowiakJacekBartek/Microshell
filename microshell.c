#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#define RED "\e[0;91m"
#define BLU "\e[0;94m"
#define COLOR_RESET "\e[0m"

int main()
{
    char polecenie[100];
    int gdzienull;
    char cwd[100];
    char oldcwd[100];

    char *user=getenv("USER");
    char *home=getenv("HOME");

    while(1)
    {
        char *arg[100]= {};
        char cdarg[100]= {};
        getcwd(cwd,sizeof(cwd));
        printf(BLU "[%s" RED ":%s]$ "COLOR_RESET,user,cwd);

        fgets(polecenie, 100, stdin);

        if(polecenie[0]=='\n' || polecenie[0]==' ')
            continue;

        for(int i=0; i<100; i++)
        {
            if(polecenie[i]=='\n')
            {
                polecenie[i]='\0';
                gdzienull=i;
                break;
            }
        }

        for(int i=0; i<gdzienull; i++)
        {
            if(polecenie[i]==' ')
            {
                i++;
                int j=0;
                while(i<gdzienull)
                {
                    cdarg[j]=polecenie[i];
                    i++;
                    j++;
                }
                cdarg[j]='\0';
                break;
            }
        }

        for(int i=0; i<gdzienull; i++)                        //Pętla kodu for kodu wzorowana na kodzie ze strony: https://cpp0x.pl/dokumentacja/standard-C/strtok/442
        {
            char korektor[] = " ";
            char * schowek;
            schowek = strtok(polecenie, korektor);
            for(int i=0; schowek!=NULL; i++)
            {
                arg[i]=schowek;
                schowek = strtok(NULL, korektor);
            }
        }

        if(strcmp(arg[0], "exit")=='\0')
            return 0;

        else if(strcmp(arg[0], "help")=='\0')
        {
            printf("\n*** MicroShell SOP ***\nAutor: Bartosz Jackowiak\n\n");
            printf("My implementation:\n");
            printf("'cd ~' || 'cd' - Home directory\n");
            printf("'cd -' - Previous directory\n");
            printf("'cd ..' - Parent directory\n");
            printf("'cd /etc' - Absolute path\n");
            printf("'cd Downloads' - Relative path\n\n");
            printf("'Fork & exec example:\n");
            printf("'ls -l -a' - 1 and more arguments\n\n");
            printf("'exit'\n\n");
        }

        else if(strcmp(arg[0], "cd")=='\0')
        {
            if(strcmp(cdarg, "-")=='\0')
            {
                chdir(oldcwd);
            }
            else if(strcmp(cdarg, "~")=='\0' || cdarg[0]=='\0')
            {
                getcwd(oldcwd,sizeof(oldcwd));
                chdir(home);
            }
            else
            {
                getcwd(oldcwd,sizeof(oldcwd));
                if(chdir(cdarg)!=0)
                    fprintf(stderr, "cd: %s: %s\n",cdarg, strerror(errno));
            }
        }
        else
        {
            int signal=0;
            if(fork()==0)
            {
                execvp(arg[0], arg);
                fprintf(stderr, "%s: command not found: Error code (%d)\n",arg[0], errno);
                return 0;
            }
            else
            {
                wait(&signal);
            }
        }
    }
}
