// this .ino is for arduino
// set port here
const int led  = 13;
const int tem  = 14;
const int lit1 = 15;
const int lit2 = 16;
const int wat  = 18;
const int pup  = 3;
// map bottom && top value
const int bot = 99;
const int top = 10;
// command and return string
String command = "";  // string for command
String data    = "";     // string for return value
// water state, two semaphores
boolean state = false;  // water now or not
int stt = 0;
// this part is used for timming, never mind
static int interval = 1000;  // interval time(1000 milliseconds in here)
int currentCP = millis();  // get nowtime millisecond
int lastCP = currentCP;    // fresh checkpoint
// value to contain data
int temp,tempB;
int light,lightB;
int water,waterB;
// int LightTime,watering=0; 

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  analogWrite(led, 255);

  //pinMode(tem, INPUT);
  //pinMode(lit1, INPUT);
  //pinMode(lit2, INPUT);
  //pinMode(wat, INPUT);
  pinMode(pup, OUTPUT);

  lightB = (analogRead(lit1) + analogRead(lit2)) / 2;
  tempB = analogRead(tem);
  waterB = analogRead(wat);
}

void loop()
{
  currentCP = millis();
  if (currentCP - lastCP > interval) {
    light = (analogRead(lit1) + analogRead(lit2)) / 2;
    lightB = lightB * 0.8 + light * 0.2;

    temp = analogRead(tem);
    tempB = tempB * 0.8 + temp * 0.2;
    
    //water
    water = analogRead(wat);
    waterB = waterB * 0.8 + water * 0.2;
    
    //Serial.println(lightB);
    /*
    Serial.print("\t");
    Serial.print(tempB);
    Serial.print("\t");
    *///Serial.println(waterB);

    lightB = 4500 / lightB;
    tempB = map(tempB, 0, 1023, bot, top)/3;
    waterB = 5625/waterB;

    if (waterB < 30 || state)
    {
      stt = 1;
      digitalWrite(pup, stt);
      //Serial.println("watering");
    }
    else
    {
      stt = 0;
      digitalWrite(pup, stt);
    }
    //total output
    
    //Serial.print(lightB);
    //Serial.print("\t");
    //Serial.print(tempB);
    //Serial.print("\t");
    //Serial.println(waterB);
    
    //Serial.println("50 milliseconds just passed");
    lastCP = currentCP;
  }

  // serial command detact
  while(Serial.available() > 0)
  {
    command += char(Serial.read());
    
    delay(2);
  }
  if (command.length() > 0)
  {
    action(command);
  }
  command = "";
  delay(10);
}

void action(String cmd)
{
  char type = cmd[0];
  //int port = cmd.substring(2, 4).toInt();
  //int value = cmd.substring(5).toInt();
  
  switch (type)
  {
    case 'p': { // pump now!
      state = true;
      returndata();
      break;
    }
    case 's': { // pump now!
      state = false;
      returndata();
      break;
    }
    case 'r': {
      returndata();
      break;
    }
  }
}
void returndata()
{
  data += tempB;
      data += "/";
      data += waterB;
      data += "/";
      data += lightB;
      data += "/";
      data += stt;
      Serial.print(data);
      data = "";
}


