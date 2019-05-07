const int stepper_direction = 4;
const int stepper_step = 7;
volatile float init_angle = 804;
int x = 0;
float kd = 0.97;
volatile int present_angle = 0;
volatile int previous_angle = 0;
const int limit1 = 3;
const int limit2 = 5;
void setup() {
  
  Serial.begin (9600);
  pinMode(A0, INPUT);
  pinMode(4, OUTPUT); 
  pinMode(7, OUTPUT);
  pinMode(limit1, INPUT_PULLUP);
  pinMode(limit2, INPUT_PULLUP);
  
}
 
void loop(){ 
  
  int enc = analogRead(A0);
  present_angle = enc - init_angle;
  int error_diff = present_angle - previous_angle;
  if ((present_angle) >= 0)
  {
    digitalWrite(stepper_direction, LOW);
  }
  else
  {
    digitalWrite(stepper_direction, HIGH);
  }
  if((digitalRead(limit1)==0) && (digitalRead(limit2)==0))
  {
  if((abs(present_angle) <= 100)) 
  {
    float val = map(abs(present_angle), 0, 100, 50, 7);
    float ans = val - (kd*error_diff);
    digitalWrite(stepper_step, HIGH);
    delayMicroseconds((int)(ans));
    digitalWrite(stepper_step, LOW);
    delayMicroseconds((int)(ans));
  }
  previous_angle = present_angle;
}
}
