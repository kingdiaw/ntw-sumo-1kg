//CH1 - TH
const byte TH = 13;
//CH2 - ST
const byte ST = 2;
unsigned long duration;
unsigned long t_tick;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(TH, INPUT);
  pinMode(ST, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (t_tick < millis()) {
    t_tick = millis() + 500;
    duration = pulseIn(ST, HIGH, 1000 * 500);
    Serial.println(duration);
  }
}
