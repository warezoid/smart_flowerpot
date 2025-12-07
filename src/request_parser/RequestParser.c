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
#include <time.h>

#define MAX_REQUEST_SIZE 21
#define MAX_COMMAND_SIZE 3
#define SEPARATOR_CHAR ' '


///DEBUGING AREA - WONT BE INCLUDED - START
void print_buffer(char *buf, int len){
    for(int i = 0; i < len; i++){
        printf("%d ", buf[i]);
    }

    printf("\t\t");
}

void remove_newline(char *buf, int len){
    for(int i = 0; i < len; i++){
        if(buf[i] == 10){
            buf[i] = 0;
        }
    }
}
///DEBUGING AREA - WONT BE INCLUDED - END



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



void null_buffer(char *buf, short buf_len){
    for(int i = 0; i < buf_len; i++){
        buf[i] = 0;
    }
}
int get_length(char *str){
    int i = 0;
    while(str[i] != 0){
        if(i > (MAX_REQUEST_SIZE - 1)){
            return -1;
        }
        i++;
    }
    
    return i;
}

int get_number(char *str){
    int i = 0;
    int res = 0;

    while(str[i] != 0){
        res = res * 10 + (str[i] - 48);
        i++;
    }

    return res;
}
int get_command(char *request, int *start_index){
    char command[MAX_REQUEST_SIZE] = {0};

    int i = 0;
    while(request[i] != 0 && request[i] != 32){
        if(i > (MAX_COMMAND_SIZE - 1)){
            return 0;
        }

        command[i] = request[i];
        i++;
    }

    *start_index = 0;
    if(request[i + 1] >= 48 && request[i + 1] <= 57){
        *start_index = i + 1;
    }

    return get_number(command);
}


/*
    request must be not null buffer (full of 0) or start with ' ' or '.'
    last char allways have to be 0
    all chars in request have to be numbers, or '.' or ' '

    multiple '.' or ' ' cant be direct next to eachother
    command have to start with command id (number)
    ' ' and '.' (and vice versa) cant be directly behind each other
    number can have only 1 or 0 dots 
*/
bool validate_request_format(char *request){
    int i = 0;
    while(request[i] != 32 && request[i] != 0){
        if(request[i] == 46){
            return false;
        }
        
        i++;
    }
    i = 0;

    int special_streak = 0;
    int dot_streak = 0;
    while(request[i] != 0){
        if(request[i] == 32 || request[i] == 46){
            if(++special_streak > 1){
                return false;
            }
            
            if(request[i] == 46){
                if(++dot_streak > 1){
                    return false;
                }
            }
            else{
                dot_streak = 0;
            }
        }
        else{
            special_streak = 0;
        }

        i++;
    }

    if(request[i - 1] == 32 || request[i - 1] == 46){
        return false;
    }

    return true;
}
bool validate_request(char *request){
    request[MAX_REQUEST_SIZE - 1] = 0;

    if(request[0] != 32 && request[0] != 0){
        int i = 0;
        while(request[i] != 0){
            if(request[i] < 48 || request[i] > 57){
                if(request[i] != 32 && request[i] != 46){
                    return false;
                }
            }

            i++;
        }

        return validate_request_format(request);
    }

    return false;
}



int parse_request(char *request){
    int params_start_index = 0;

    if(validate_request(request)){
        switch(get_command(request, &params_start_index)){
            case 1:
                //SETMOVE
                break;
            default:
                return 1;
        }

        return 0;
    }

    return 1;
}


/*

NOTES:
    In serial communication read only for MAX_BUF_SIZE chars. last char will be 0 and request will be sended.

*/


///DEBUGING AREA - WONT BE INCLUDED - START
int main(){
    clock_t start_clk = clock();

    char req[MAX_REQUEST_SIZE] = {0};

    while(fgets(req, sizeof(req), stdin)){
        remove_newline(req, MAX_REQUEST_SIZE);

        parse_request(req);

        null_buffer(req, MAX_REQUEST_SIZE);
    }

    printf("Processor time used by program: %Lg sec.\n", \
    (clock() - start_clk) / (long double) CLOCKS_PER_SEC);

    /*
        runtime:
            15147 lines of stdin -> 0.03 sec
    */

    return 0;
}
///DEBUGING AREA - WONT BE INCLUDED - END