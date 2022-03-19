void brake_lights()
{
  if((brake == 0 || time_now - brake_time > 5000) && inDrive)
  {
    if(beam > 0)
    {
      //Serial.println("am setat brk pe 10");
      //analogWrite(BrakeLightPin, 10);
      analogWrite(BrakeLightPin, 48);
      digitalWrite(ThirdBrakePin, LOW);
    }
    else
    {
      //Serial.println("am setat brk pe 0");
      analogWrite(BrakeLightPin, 0);
      digitalWrite(ThirdBrakePin, LOW);
    }
  }
  else
  {
    analogWrite(BrakeLightPin, 255);
    digitalWrite(ThirdBrakePin, HIGH);
  }

}

void beam_lights()
{
  if(beam == 0)
  {
    digitalWrite(DRLPin, LOW);
    digitalWrite(RoofLightsPin, LOW); //e negat
    analogWrite(BeamPin, 0);
  }
  else if(beam == 1)
  {
    digitalWrite(DRLPin, HIGH);
    digitalWrite(RoofLightsPin, LOW);
    analogWrite(BeamPin, 0);
  }
  else if(beam == 2)
  {
    digitalWrite(DRLPin, HIGH);
    digitalWrite(RoofLightsPin, LOW);
    analogWrite(BeamPin, 32);
  }
  else if(beam == 3)
  {
    digitalWrite(DRLPin, HIGH);
    digitalWrite(RoofLightsPin, LOW);
    analogWrite(BeamPin, 255);
  }
  else if(beam >= 4)
  {
    digitalWrite(DRLPin, HIGH);
    digitalWrite(RoofLightsPin, HIGH);
    analogWrite(BeamPin, 255);
  }
}

void turn_lights()
{
    if(rt || lt)
  {
    time_now = millis();
    if(time_now - time_old > TurningBPS*1000)
    {
      time_old = time_now;
      aprins = !aprins;
    }
    if(aprins)
    {
      if(lt) 
      {
        digitalWrite(LTPin, HIGH);
      }
      if(rt)
      {
        digitalWrite(RTPin, HIGH);
      }
    }
    else
    {
      digitalWrite(LTPin, LOW);
      digitalWrite(RTPin, LOW);
    }
  }
  else
  {
    digitalWrite(LTPin, LOW);
    digitalWrite(RTPin, LOW);
  }
}

void underglow_f()
{
  if(underglow)
  {
    digitalWrite(UnderglowPin, HIGH);
  }
  else
  {
    digitalWrite(UnderglowPin, LOW);
  }
}
