int left_horisontal_neutral;
int left_vertical_neutral;

void setup() {
  Serial.begin(9600);
  left_horisontal_neutral = analogRead(A1);
  left_vertical_neutral = analogRead(A2);
}

void loop() {
  int left_horisontal = analogRead(A1) - left_horisontal_neutral;
  int left_vertical = analogRead(A2) - left_vertical_neutral;
  
  int left_belt = -left_vertical + left_horisontal;
  int right_belt = -left_vertical - left_horisontal;
  
  Serial.print(left_belt);
  Serial.print(' ');
  Serial.println(right_belt);
}
