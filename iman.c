#include "headers.h"

void iman(char **token_list, int token_count)
{
    
    char command[200];
    strcpy(command, token_list[1]);
    char *hostwebsite = "man.he.net";
    const int port = 80;

   
    int socket_file_des = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_des < 0)
    {
        printf("\033[1;31mSocket error\n\033[0;0m");
        return;
    }

   
    struct hostent *server = gethostbyname(hostwebsite);
    if (server == NULL)
    {
        printf("\033[1;31mHost error\n\033[0;0m");
        close(socket_file_des);
        return;
    }

    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);


    if (connect(socket_file_des, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("\033[1;31mConnection error\n\033[0;0m");
        close(socket_file_des);
        return;
    }


    char request[1000];
    snprintf(request, sizeof(request), "GET /?topic=%s&section=all HTTP/1.1\r\nHost: %s\r\n\r\n", command, hostwebsite);


    if (send(socket_file_des, request, strlen(request), 0) < 0)
    {
        printf("\033[1;31mRequest sending error\n\033[0;0m");
        close(socket_file_des);
        return;
    }


    char response[4096];
    ssize_t bytes_received;
    int flag = 0;

    while ((bytes_received = recv(socket_file_des, response, sizeof(response) - 1, 0)) > 0)
    {
        response[bytes_received] = '\0';

        if (flag == 0)
        {
            char *result = strstr(response, "NAME\n");
            if (result != NULL)
            {
                flag = 1;
                char *to_break = strstr(result, "AUTHOR");
                if (to_break != NULL)
                {
                    *to_break = '\0'; 
                    printf("%s", result);
                    break;
                }
                else
                {
                    printf("%s", result);
                }
            }
        }
        else
        {
            char *to_break = strstr(response, "AUTHOR");
            if (to_break != NULL)
            {
                *to_break = '\0'; 
                printf("%s", response);
                break;
            }
            else
            {
                printf("%s", response);
            }
        }
    }

    if (flag == 0)
    {
        printf("\033[1;31mERROR\n\tNo such command\n\033[0;0m");
    }

    close(socket_file_des);
}
