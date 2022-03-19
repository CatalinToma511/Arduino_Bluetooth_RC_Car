void setMotorFront(int value1, int value2)
{
  value1 = ((value1-1)*220/20 + 35) * (value1 > 0);
  value2 = ((value2-1)*220/20 + 35) * (value2 > 0);
  /*Serial.print(value1);
  Serial.print(" ");
  Serial.println(value2);*/
  analogWrite(EnA, value1* LeftMotorsCoef);
  analogWrite(EnB, value2);
  digitalWrite(IN1, LOW); //motor A
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); //motor B
  digitalWrite(IN4, HIGH);
  rev = 0;
  brake = 0;
}

void setMotorRear(int value1, int value2)
{
  value1 = ((value1-1)*220/20 + 35) * (value1 > 0);
  value2 = ((value2-1)*220/20 + 35) * (value2 > 0);
  /*Serial.print(value1);
  Serial.print(" ");
  Serial.println(value2);*/
  analogWrite(EnA, value1 *LeftMotorsCoef);
  analogWrite(EnB, value2);
  digitalWrite(IN1, HIGH); //motor A
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); //motor B
  digitalWrite(IN4, LOW);
  rev = 1;
  brake = 0;
}

void setMotorBrake()
{
  digitalWrite(EnA, LOW);
  digitalWrite(EnB, LOW);
  digitalWrite(IN1, LOW); //motor A
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); //motor B
  digitalWrite(IN4, LOW);
  rev = 0;
  brake = 1;
}

void setSteering(int angle)
{
  steering.write(angle);
}

void setWinch(int pos)
{
  switch (pos)
  {
    case -1:
      winch.write(0);//aici se roteste intr-un sens
      break;
    case 0:
      winch.write(92);//sta pe loc
      break;
    case 1:
      winch.write(180); //aici se roteste in alt sens
      break;
    default:
        break;
  }
  
}

void setMotorRotateLeft(int value1, int value2)
{
  value1 = ((value1-1)*220/20 + 35) * (value1 > 0);
  value2 = ((value2-1)*220/20 + 35) * (value2 > 0);
  analogWrite(EnA, value1 * LeftMotorsCoef);
  analogWrite(EnB, value2);
  digitalWrite(IN1, HIGH); //motor A
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); //motor B
  digitalWrite(IN4, HIGH);
}

void setMotorRotateRight(int value1, int value2)
{
  value1 = ((value1-1)*220/20 + 35) * (value1 > 0);
  value2 = ((value2-1)*220/20 + 35) * (value2 > 0);
  analogWrite(EnA, value1 * LeftMotorsCoef);
  analogWrite(EnB, value2);
  digitalWrite(IN1, LOW); //motor A
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); //motor B
  digitalWrite(IN4, LOW);
}
