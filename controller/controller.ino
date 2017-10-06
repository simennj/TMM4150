int left_horisontal_neutral;
int left_vertical_neutral;

void setup() {
  Serial.begin(9600);
  left_horisontal_neutral = analogRead(A1);
  left_vertical_neutral = analogRead(A2);
}

void loop() {
  int left_horisontal = analogRead(A1);
  int left_vertical = analogRead(A2);
  Serial.print(left_horisontal - left_horisontal_neutral);
  Serial.print(' ');
  Serial.println(left_vertical - left_vertical_neutral);
}
