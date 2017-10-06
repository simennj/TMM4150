void setup() {
  Serial.begin(9600);
}

void loop() {
  int left_horisontal = analogRead(A1);
  int left_vertical = analogRead(A2);
  Serial.print(left_horisontal);
  Serial.print(' ');
  Serial.println(left_vertical);
}
