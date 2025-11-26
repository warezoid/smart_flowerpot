/*
    - get request string (from master unit by UART communication) and params array [param param1 param2 param3]
    - get command id and fill params
    - return command id

    - assuming that request is in right format -> right length, not empty, correct spaces, ... 

    - MAX request size -> 60 chars + ending char

    - -1 -> Error | params are empty
    - SETMOVE (open_rate - float number - x.xx) -> 0
*/

#include <stdio.h>
#include <stdbool.h>

#define MAX_REQUEST_SIZE 21
#define SEPARATOR_CHAR ' '


///DEBUGING AREA - WONT BE INCLUDED - START
void print_buffer(char *buf, int len){
    for(int i = 0; i < len; i++){
        printf("%d ", buf[i]);
    }

    printf("\n");
}
///DEBUGING AREA - WONT BE INCLUDED - END



void null_buffer(char *buf, short buf_len){
    for(int i = 0; i < buf_len; i++){
        buf[i] = 0;
    }
}

short get_command(char *request, char *command){
    short i = 0;
    
    while(request[i] != 0)
    {
        if(request[i] == ' '){
            return ++i;
        }

        command[i] = request[i];
        i++;
    }

    return 0;
}

short parse_request(char *request, char *parameters){
    char command[MAX_REQUEST_SIZE] = {0};
    null_buffer(parameters, MAX_REQUEST_SIZE);

    request[MAX_REQUEST_SIZE - 1] = 0;

    short parameters_start_index = get_command(request, command);

    printf("index: %c | cmd: %s\n", request[parameters_start_index], command);

    return -1;
}



///DEBUGING AREA - WONT BE INCLUDED - START
int main(){
    char req[MAX_REQUEST_SIZE] = "SETMOVE 1.85 1.5";
    char params[MAX_REQUEST_SIZE] = {0};

    print_buffer(req, MAX_REQUEST_SIZE);
    print_buffer(params, MAX_REQUEST_SIZE);

    printf("get_command: %d\n", parse_request(req, params));

    return 0;
}
///DEBUGING AREA - WONT BE INCLUDED - END