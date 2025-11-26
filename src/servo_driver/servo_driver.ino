#include <ESP32Servo.h>

#define VENT_SERVO_LEFT_PIN 26
#define VENT_SERVO_RIGHT_PIN 25
#define VENT_SERVO_MIN 0
#define VENT_SERVO_MAX 80

Servo vent_servo_left, vent_servo_right;
short vent_servo_pos = VENT_SERVO_MIN;

void move_servo(int pos){
  vent_servo_left.write(pos);
  vent_servo_right.write(pos);
}
short calc_move(float open_rate){
  if(open_rate <= 1){
    if(open_rate >= 0){
      return (short)(open_rate * VENT_SERVO_MAX);
    }

    return VENT_SERVO_MIN;
  }

  return VENT_SERVO_MAX;
}



/*
  - maximalni delka requestu 100 znaku + 0 (ukoncovaci)
  - command -> prvnich 10 znaku | pole: + 0 ukoncovaci 

  -> SETMOVE___ <FLOAT-NUMBER> <COMMAND-TERMINATOR>
    - command: prvnich 10 znaku v requestu
    - value:
*/

#define max_request_length 101
#define max_command_length 11
#define open_rate_length 5
#define request_terminator '\n'
#define request_padding '_'

char request[max_request_length];
char command[max_command_length];
int request_index = 0;



void print_buf(char *buf, int len){
  printf("%s\n", buf);
  
  for(int i = 0; i < len; i++){
    printf("%d ", (unsigned char)buf[i]);
  }

  printf("\n");
}


void get_value(char *value, char *request){
  for(int i = 0; i < open_rate_length; i++){
    if(i + 11 < max_request_length){
      value[i] = request[i + 11];
    }
    else{
      value[i] = 0;
    }

    printf("%c ", value[i]);
  }
}
void get_command(){
  int i = 0;
  memset(command, 0, sizeof(command));

  for(int j = 0; j < (max_command_length - 1); j++){
    if(request[j] != request_padding){
      command[i] = request[j];
      i++;
    }
  }

  command[max_command_length - 1] = 0;
}
void identify_request(){
  get_command();

  if(!strcmp(command, "SETMOVE")){
    char value[open_rate_length] = {0};
    get_value(value, request);

    printf("%s\n", value);
  }
}
void read_serial(){
  while(Serial.available()){
    char c = Serial.read();

    if(c == request_terminator){
      request[max_request_length - 1] = 0;

      identify_request();

      request_index = 0;
      memset(request, 0, sizeof(request));
    }
    else{
      if(request_index < max_request_length){
        request[request_index] = c;
        request_index++;
      }
    }
  }
}



/*

  -> servo is lagged in vent_servo_pos by executive unit (EU)
  -> by sensor unit (SU) is calculated open_rate and is send request to EU to move_servo
  -> EU catch request call calc_move, which set vent_servo_pos
  -> servo is lagged... and respond with OK status
  -> REPEAT

*/

void setup(){
  vent_servo_left.attach(VENT_SERVO_LEFT_PIN);
  vent_servo_right.attach(VENT_SERVO_RIGHT_PIN);

  Serial.begin(115200);
}

void loop(){
  move_servo(vent_servo_pos);
  read_serial();
}