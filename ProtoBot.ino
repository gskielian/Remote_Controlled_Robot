#include <Servo.h>

#define LEFT_WHEEL_PIN 9
#define RIGHT_WHEEL_PIN 10

#define READ_FORWARD 14
#define READ_BACKWARD 15
#define READ_RIGHT 16
#define READ_LEFT 17

#define RIGHT_LED 18
#define LEFT_LED 19

#define DOING_STUFF_LED 22
#define BUSY_LED 4

#define BUSY_MODE 1
#define CONTROL_OK 0

Servo left_wheel;  
Servo right_wheel;  


void setup()
{
  left_wheel.attach(LEFT_WHEEL_PIN);  
  right_wheel.attach(RIGHT_WHEEL_PIN); 

  pinMode(READ_FORWARD, INPUT);
  pinMode(READ_BACKWARD, INPUT);
  pinMode(READ_RIGHT, INPUT);
  pinMode(READ_LEFT, INPUT);

  pinMode(RIGHT_LED, OUTPUT);
  pinMode(LEFT_LED, OUTPUT);

  pinMode(DOING_STUFF_LED, OUTPUT);
  pinMode(BUSY_LED, OUTPUT);
}

void loop()
{

  //SPECIAL MOVE (in this case hold forward and back at the same time to
  //activate front lights
  if (digitalRead(READ_FORWARD) && digitalRead(READ_BACKWARD)) {
    indicate_busy();
    toggle_front_lights();
    delay(500);
    indicate_free();
  }
  else if (digitalRead(READ_FORWARD) == HIGH) {
    indicate_busy();
    attach_wheels();
    start_moving_forward();
    delay(1000);                       // moves forward for 1000ms, and then listens again
    indicate_free();
  } else if (digitalRead(READ_BACKWARD) == HIGH) {
    indicate_busy();
    attach_wheels();
    start_moving_backward();
    delay(1000);                       // moves backward for 1000ms, and then listens again
    indicate_free();
  } else if (digitalRead(READ_RIGHT) == HIGH) {
    indicate_busy();
    attach_wheels();
    start_turning_right();
    delay(200);                       // rotates right for 200ms, and then listens again
    indicate_free();
  } else if (digitalRead(READ_LEFT) == HIGH) {
    indicate_busy();
    attach_wheels();
    start_turning_left();
    delay(200);                       // rotates left for 200ms, and then listens again
    indicate_free();
  }
  detach_wheels(); 
}


//SPECIAL MOVES (hold specific combo of two or more buttons down simultaneously to activate)
void toggle_front_lights() {
  if (digitalRead(RIGHT_LED) == HIGH) {
    digitalWrite(RIGHT_LED, LOW);
    digitalWrite(LEFT_LED, LOW);
  } else {
    digitalWrite(RIGHT_LED, HIGH);
    digitalWrite(LEFT_LED, HIGH);
  }
}

//INDICATE WHETHER LISTENING OR BUSY
void indicate_busy() {
  digitalWrite(DOING_STUFF_LED, LOW);
  digitalWrite(BUSY_LED, HIGH);
}

void indicate_free() {
  digitalWrite(DOING_STUFF_LED, HIGH);
  digitalWrite(BUSY_LED, LOW);
}

//ATTACH/DETACH (continuous-rotation servos always moving slightly unless detached)

void attach_wheels() {
  left_wheel.attach(LEFT_WHEEL_PIN);
  right_wheel.attach(RIGHT_WHEEL_PIN);
}

void detach_wheels() {
  left_wheel.detach();
  right_wheel.detach();
}

//MOVEMENT Subroutines

void start_moving_forward() {
  left_wheel.write(180);
  right_wheel.write(0);
}

void start_moving_backward() {
  left_wheel.write(0);
  right_wheel.write(180);
}

void start_turning_left() {
  left_wheel.write(0);
  right_wheel.write(0);
}

void start_turning_right() {
  left_wheel.write(180);
  right_wheel.write(180);
}
