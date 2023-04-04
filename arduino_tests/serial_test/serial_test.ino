#define leftMotorForward 3
#define leftMotorBack 5
#define rightMotorForward 6
#define rightMotorBack 9

void setup()
{
  Serial.begin(115200);
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBack, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(rightMotorBack, OUTPUT);
}

void loop()
{
  if (Serial.available() > 0)
  {
    String rec = Serial.readStringUntil('\n');
    if (rec == "heartbeat") Serial.println("heartbeat");

    if (rec == "f"){
      analogWrite(leftMotorForward, 150);
      analogWrite(rightMotorForward, 150);
    }
    else if (rec == "b"){
      analogWrite(leftMotorBack, 150);
      analogWrite(rightMotorBack, 150);
    }
    else if (rec == "l"){
      analogWrite(leftMotorBack, 150);
      analogWrite(rightMotorForward, 150);
    }
    else if (rec == "r"){
      analogWrite(leftMotorForward, 150);
      analogWrite(rightMotorBack, 150);
    }
    else if (rec == "s") {
      analogWrite(leftMotorForward, 0);
      analogWrite(rightMotorForward, 0);
      analogWrite(leftMotorBack, 0);
      analogWrite(rightMotorBack, 0);
    }
  }
}
