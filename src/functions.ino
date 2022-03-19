

void updateCommands(String reply)
{
    //Serial.println(reply);
    if(reply.length() > 2)
    {
      char aux = reply.charAt(0);
      switch(aux)
      {
         case 'K':
            k = 1;
            break;
         case 'J':
            j = 1;
            break;
         default:
            break;
      }
      //Serial.print(aux);
      if(k)
      {
        beam = reply.substring(1).toInt();
        k = 0;
        //Serial.println(beam);
      }
      else if(j)
      {
        j = 0;
        num_j = reply.substring(1).toInt();
        //Serial.println(num_j);
        if(num_j == 0)
        {
            inDrive = 0;
            brake = 0;
            setMotorBrake();
        }
        else
        {
          inDrive = 1;
          max_speed = num_j;
          //Serial.print("last :"), Serial.println(last_direction);
          updateCommands(String(last_direction));
        }
        
      }
    }
    else
    {
      //Serial.println(reply.charAt(0));
    switch(reply.charAt(0))
    {
        case 'F':
          //merge in fata
          setMotorFront(max_speed*inDrive, max_speed*inDrive);
          setSteering(SteeringCenter);
          lastDirectionFront = 1;
          last_direction = 'F';
          break;
          
        case 'E':
          //merge in fata, coteste putin dreapta
          if(last_direction == 'R' && lastDirectionFront == 0)
          {
            updateCommands(String('R'));
          }
          else
          {
            if(!tank_mode)
            {
              setMotorFront(max_speed*inDrive, 0.75*max_speed*inDrive);
              setSteering((SteeringCenter+SteeringRight)/2);
            }
            else
            {
              setMotorRotateRight(max_speed, 0);
              setSteering(SteeringCenter); 
            }
            lastDirectionFront = 1;
            last_direction = 'E';
          }
          break;
        
        case 'Q':
          //merge in fata, coteste putin stanga
          if(last_direction == 'L' && lastDirectionFront == 0)
          {
            updateCommands(String('L'));
          }
          else
          {
            if(!tank_mode)
            {
              setMotorFront(0.75*max_speed*inDrive, max_speed*inDrive);
              setSteering((SteeringCenter+SteeringLeft)/2);
            }
            else
            {
              setMotorRotateLeft(0, max_speed);
              setSteering(SteeringCenter);
            }
            lastDirectionFront = 1;
            last_direction = 'Q';
          }
          break;
        
        case 'L':
           //verifica daca a fost ultima data fata/spate si coteste stanga
           if(!tank_mode)
           {
            if(lastDirectionFront)
            {
              setMotorFront(0.55 * max_speed * inDrive, max_speed * inDrive);
            }
            else
            {
              setMotorRear(0.55 * max_speed * inDrive, max_speed * inDrive);
            }
            setSteering(SteeringLeft);
           }
           else
           {
            setMotorRotateLeft(max_speed * inDrive, max_speed * inDrive);
            setSteering(SteeringCenter);
           }
            last_direction = 'L';
          break;
        
        case 'R':
          //verifica daca a fost ultima data fata/spate si coteste dreapta
          if(!tank_mode)
          {
            if(lastDirectionFront)
            {
              setMotorFront(max_speed*inDrive, 0.55*max_speed*inDrive);
            }
            else
            {
              setMotorRear(max_speed*inDrive, 0.55*max_speed*inDrive);
            }
            setSteering(SteeringRight);
          }
          else
          {
            setMotorRotateRight(max_speed * inDrive, max_speed * inDrive);
            setSteering(SteeringCenter);
          }
          last_direction = 'R';
          break;
        
        case 'Z':
          //spate si coteste putin stanga
          if(last_direction == 'L' && lastDirectionFront == 1)
          {
            updateCommands(String('L'));
          }
          else
          {
            if(!tank_mode)
            {
              setMotorRear(0.75*max_speed*inDrive, max_speed*inDrive);
              setSteering((SteeringCenter+SteeringLeft)/2);
            }
            else
            {
              setMotorRotateRight(0, max_speed * inDrive);
              setSteering(SteeringCenter);
            }
            lastDirectionFront = 0;
            last_direction = 'Z';
          }
          break;
        
        case 'C':
          //spate si coteste putin dreapta
          if(last_direction == 'R' && lastDirectionFront == 1)
          {
            updateCommands(String('R'));
          }
          else
          {
            if(!tank_mode)
            {
              setMotorRear(max_speed*inDrive, 0.75*max_speed*inDrive);
              setSteering((SteeringCenter+SteeringRight)/2);
            }
            else
            {
              setMotorRotateRight(max_speed * inDrive, 0);
              setSteering(SteeringCenter);
            }
            lastDirectionFront = 0;
            last_direction = 'C';
          }
          break;
        
        case 'G':
          setMotorRear(max_speed*inDrive, max_speed*inDrive);
          setSteering(SteeringCenter);
          lastDirectionFront = 0;
          last_direction = 'G';
          break;
  
        case 'S':
          setMotorBrake();
          setSteering(SteeringCenter);
          brake_time = millis();
          last_direction = ' ';
          break;
  
        case 'X':
          if(!winch_mode)
          {
            lt = !lt;
          }
          else
          {
            if(winch_position == -1 || winch_position == 1)
            {
              winch_position = 0;
            }
            else
            {
              winch_position = -1;
            }
            setWinch(winch_position);
          }
          //last_direction = ' ';
          break;    
          
        case 'Y':
          if(!winch_mode)
          {
            rt = !rt;
          }
          else
          {
            if(winch_position == -1 || winch_position == 1)
            {
              winch_position = 0;
            }
            else
            {
              winch_position = 1;
            }
            setWinch(winch_position);
          }
          //last_direction = ' ';
          break;
  
        case 'K':
          k = 1;
          //last_direction = ' ';
          break;
  
        case 'J':
          j = 1;
          num_j = 0;
          //last_direction = ' ';
          break;

        case 'M':
          if(rt && lt)
          {
            winch_mode = 1;
            winch.attach(WinchPin);
            lt = 0;
            rt = 0;
          }
          else
          {
            tank_mode = 1;
          }
          break;
          
        case 'm':
          tank_mode = 0;
          winch_mode = 0;
          if(winch.attached())
          {
            winch.detach();
          }
         
          break;
          
        case 'N':
          underglow = 1;
          break;
          
        case 'n':
          underglow = 0;
          break;
          
        default:
          //???
          break;
      }
    }
}

void updateLights()
{
  //rev lights
  if(rev == 0)
  {
    digitalWrite(RevLightPin, LOW);
  }
  else
  {
    digitalWrite(RevLightPin, HIGH);
  }

  //brake lights
  time_now = millis();
  brake_lights();
  
  beam_lights();

  turn_lights();

  underglow_f();
}

void unconnected()
{
  setMotorBrake();
  steering.write(SteeringCenter);
  if(winch_mode)
  {
    winch_position = 0;
    setWinch(winch_position);
  }
  //set all lights off except turning lights
  digitalWrite(UnderglowPin, LOW);
  digitalWrite(DRLPin, LOW);
  digitalWrite(RoofLightsPin, LOW);
  analogWrite(BeamPin, 0);
  analogWrite(BrakeLightPin, 0);
  digitalWrite(ThirdBrakePin, LOW);
  digitalWrite(RevLightPin, LOW);
  //hazard lights + 3rd brake light
  time_now = millis();
  if(time_now - time_old > TurningBPS*500)
  {
    time_old = time_now;
    aprins = !aprins;
  }
  if(aprins)
  {
    digitalWrite(LTPin, HIGH);
    digitalWrite(RTPin, HIGH);
  }
  else
  {
    digitalWrite(LTPin, LOW);
    digitalWrite(RTPin, LOW);
  }
}
