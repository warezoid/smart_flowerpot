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

void remove_newline(char *buf, int len){
    for(int i = 0; i < len; i++){
        if(buf[i] == 10){
            buf[i] = 0;
        }
    }
}
///DEBUGING AREA - WONT BE INCLUDED - END



void null_buffer(char *buf, short buf_len){
    for(int i = 0; i < buf_len; i++){
        buf[i] = 0;
    }
}
bool string_equal(char *str_1, char *str_2){
    int i = 0;

    while(str_1[i] != 0 || str_2[i] != 0){
        if(str_1[i] != str_2[i]){
            return false;
        }

        i++;
    }

    return true;
}

short get_command(char *request, char *command){
    short i = 0;
    
    while(request[i] != 0){
        if(request[i] == ' '){
            return ++i;
        }

        command[i] = request[i];
        i++;
    }

    return 0;
}
short get_command_id(char *command){
    if(string_equal(command, "SETMOVE")){
        return 0;
    }
    else{
        return -1;
    }
}


/*
    last char allways have to be 0
    all chars in request have to be numbers, or '.' or ' '
*/
bool validate_request(char *request){
    if(request[MAX_REQUEST_SIZE - 1] == 0){
        short i = 0;
        while(request[i] != 0){
            if(request[i] < 48 || request[i] > 57){
                if(request[i] != 32 && request[i] != 46){
                    return false;
                }
            }

            i++;
        }

        return true;
    }

    return false;
}

int parse_request(char *request){
    if(validate_request(request)){
        //good
        printf("GOOD\n");
        return 0;
    }

    printf("BAD\n");
    return 1;
}


/*
NOTES

in serial communication read only for MAX_BUF_SIZE chars. last char will be 0 and request will be sended.

*/


///DEBUGING AREA - WONT BE INCLUDED - START
int main(){
    char req[MAX_REQUEST_SIZE] = {0};

    while(1){
        fgets(req, sizeof(req), stdin);
        remove_newline(req, MAX_REQUEST_SIZE);
        print_buffer(req, MAX_REQUEST_SIZE);

        parse_request(req);

        null_buffer(req, MAX_REQUEST_SIZE);
    }
    



    return 0;
}
///DEBUGING AREA - WONT BE INCLUDED - END