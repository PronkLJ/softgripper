const int pwm1 = 3;
const int pwm2 = 5;
const int pwm3 = 6;
const int pwm4 = 9;

String inputString = "";
float voltage = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(pwm3, OUTPUT);
  pinMode(pwm4, OUTPUT);
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      inputString.trim();

      if (inputString.startsWith("SET")) {
        inputString.remove(0, 3);         // Remove "SET"
        voltage = inputString.toFloat();  // Convert to float
        voltage = constrain(voltage, 0.0, 5.0);

        int pwmValue = map(voltage * 100, 0, 500, 0, 255);  // 0.00–5.00 mapped to 0–255
        
        analogWrite(pwm1, pwmValue);
        analogWrite(pwm2, pwmValue);
        analogWrite(pwm3, pwmValue);
        analogWrite(pwm4, pwmValue);
      }

      inputString = "";
    } else {
      inputString += c;
    }
  }
}
