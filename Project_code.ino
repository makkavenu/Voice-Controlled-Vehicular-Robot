 String voice;

int lm1=5;
int lm2=6;
int rm1=9;
int rm2=10;

int left_sensor=A0;
int right_sensor=A1;

int trigpin=7;
int echopin=8;
//int trigpin2=A2;
//int echopin2=A3;

long duration, distance;

const int s0=2;
const int s1=3;
const int s2=12;
const int s3=13;
const int out=11;

int red = 0;
int green = 0;
int blue = 0; 
int flag=0;
int i=0;

void setup()
{
  // put your setup code here, to run once:
  pinMode(lm1, OUTPUT);
  pinMode(lm2, OUTPUT);
  pinMode(rm1, OUTPUT);
  pinMode(rm2, OUTPUT);

  pinMode(left_sensor, INPUT);
  pinMode(right_sensor, INPUT);

  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  //pinMode(trigpin2, OUTPUT);
//  pinMode(echopin2, INPUT);
  
  

  Serial.begin(9600);
  
  pinMode(s0,OUTPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);

  digitalWrite(s0,HIGH);
  digitalWrite(s1,HIGH);

}

void loop()
{
  // put your main code here, to run repeatedly:
  long forwdis;
  long forwdis2;
 while(Serial.available())
  {
    delay(10);
    char c = Serial.read();
    if(c=='#')
    {
      break;
    }
    voice += c;
  }
  //voice="go to hospital";
  if(voice=="hospital"|| voice=="Hospital" && !(Serial.available()))//hospital corresponds to blue building
  {
    //Serial.println("hospital");
    flag=1;
  }
  else if(voice=="school" || voice=="School"&& !(Serial.available()))//school corresponds to red building
  {
    flag=3;
  }
  else if(voice=="Office" || voice=="office" && !(Serial.available()))//office corresponds to green
  {
    flag=2;
  }

  else if(voice=="go to hospital" &&!(Serial.available()))
  {
    forward();
    delay(2000);
    left();
    delay(3000);
    forward();
    delay(1500);
    left();
    delay(3000);
    forward();
    delay(2000);
    wait();
  }
  else if(voice == "stop" )
    {
     while(voice=="stop" && !(Serial.available()))
      {
      wait();
      }
    }
  else if(voice == "forward")
   {
    while(voice == "forward" &&!( Serial.available()))
  {
  forwdis = ping();
  //forwdis2 = ping2(); // Runs Ping fucntion reurns distance saves as forward distance
  
   if (forwdis >= 10) //If the forward dis is greater than 12 cm keep going forward
  {
      forward();
         
  }

  else if (forwdis < 10 )  //If distance is less than 12 cm then
  {
    Serial.println("obstacle detected");
    backward();
    delay(500);
    right();
    delay(1000);
    forward();
    
  }     
 }
}
     else if(voice == "backward" && !(Serial.available()))
    {
       backward();
       
    }
    else if(voice=="right" || voice=="a")
    {
      
      right();
      delay(2000);
      forward();

       while(voice == "right" &&!( Serial.available()))
 {
  forwdis = ping();
//  forwdis2 = ping2();
  // Runs Ping fucntion reurns distance saves as forward distance
  
   if (forwdis >= 10 ) //If the forward dis is greater than 12 cm keep going forward
  {
      forward();
         
  }

  else if (forwdis < 10)  //If distance is less than 12 cm then
  {
    Serial.println("obstcle detected");
    backward();
    delay(1000);
    right();
    delay(2000);
    forward();
  }     
 }
    }
    else if(voice=="left")
    {
      
      left();
      delay(2000);
      forward();
       while(voice == "left" &&!( Serial.available()))
 {
  forwdis = ping();
//  forwdis2 = ping2();// Runs Ping fucntion reurns distance saves as forward distance
  
   if (forwdis >=10) //If the forward dis is greater than 12 cm keep going forward
  {
      forward();
         
  }

  else if (forwdis < 10)  //If distance is less than 12 cm then
  {
    Serial.println("obstacle detected");
    backward();
    delay(1000);
    right();
    delay(2000);
    forward();
  }     
 }
    }
    
    voice="";
  


 
  
  if(i==0 && flag!=0 && !(Serial.available()))
  {
    Serial.println("journey started");
    i=i+1;
  }

  
  
  int ls;
  int rs;

  ls = digitalRead(left_sensor);
  rs = digitalRead(right_sensor);

  forwdis = ping();
/*  forwdis2 = ping2();
 if(forwdis<=10 && flag!=0)
  { backward();
    delay(300);
    right();
    delay(1000);
  }*/
  if(ls==1 && rs==1 && forwdis>15 && flag!=0)
  {
    forward();
  }
  
  else if(ls==0 && rs==0 && flag!=0)
  {
    Serial.println("this is not correct path, try other path");
    uturn();
    delay(2000);
  }

  else if(ls==0 && rs==1 &&forwdis >15 && flag!=0)
  {
    right();
    delay(20);
  }

  else if(ls==1 && rs==0 && forwdis >15  && flag!=0)
  {
    left();
    delay(10);
  }
  else if(ls==1 && rs==1 && forwdis<=15 && flag!=0)
  {
    Serial.println("obstacle detected");
    backward();
    delay(500);
    right();
    delay(1000);
  }

  color();
  /*Serial.print("redinten:");
  Serial.print(red,DEC);
  Serial.print("greeninten:");
  Serial.print(green,DEC);
  Serial.print("blueinten:");
  Serial.print(blue,DEC);*/

  /*if(red<blue && red<green && red<100 && flag==2)
  {
   // Serial.println("Red");
    wait();
    delay(1500);
    Serial.println("destination reached");
  }
  else if(blue<red && blue<green&&blue>30 && flag==1)
  {
    //Serial.println("Blue");
    wait();
    delay(1000);
    Serial.println("destination reached");
    
  }
  else if(green<red && green<blue && flag==3)
  {
    //Serial.println("Green");
    wait();
    delay(1500);
    Serial.println("destination arrived");
  }
  else
  {
    //Serial.println("Nothing");
  }
  */

  if(blue<red && blue<green &&blue>30)
  {
   // Serial.println("Blue");
   wait();
   Serial.println("reached to hospital");
    delay(1000);
  }

  else if(red<blue && red>green && red<100)
  {
    //Serial.println("Red");
    wait();
    Serial.println("reached to office");
    delay(1000);
  }
  
  else if(green>red && green<blue)
  {
    //Serial.println("Green");
    wait();
    Serial.println("reached to school");
    delay(1000);
  }
  else
  {
    //Serial.println("Nothing");
    delay(1000);
  }
  

}

void forward()
{
  digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);
} 

void right()
{
  digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,LOW);
  digitalWrite(rm2,HIGH);
}

void left()
{
  digitalWrite(lm1,LOW);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,HIGH);
  digitalWrite(rm2,LOW);
}

void uturn()
{
  digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,LOW);
  digitalWrite(rm2,HIGH);
}

unsigned long ping()
{
 long duration, distance;
 digitalWrite(trigpin, HIGH);
 delay(1);
 digitalWrite(trigpin, LOW);
 duration = pulseIn(echopin, HIGH);
 distance = (duration/2)/29.1;
 delay(10);
 return (distance);
}

/*unsigned long ping2()
{
 long duration, distance;
 digitalWrite(trigpin2, HIGH);
 delay(1);
 digitalWrite(trigpin2, LOW);
 duration = pulseIn(echopin2, HIGH);
 distance = (duration/2)/29.1;
 delay(10);
 return (distance);
}*/

void color()
{
  digitalWrite(s2,LOW);
  digitalWrite(s3,LOW);

  red = pulseIn(out,digitalRead(out)==HIGH?LOW:HIGH);
  digitalWrite(s3,HIGH);
  blue = pulseIn(out, digitalRead(out)==HIGH?LOW:HIGH);
  digitalWrite(s2,HIGH);
  green = pulseIn(out,digitalRead(out)==HIGH?LOW:HIGH);
}

void wait()
{
  digitalWrite(lm1,LOW);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,LOW);
  digitalWrite(rm2,LOW);
}
void rotate()
{
  digitalWrite(lm1,HIGH);
  digitalWrite(lm2,LOW);
  digitalWrite(rm1,LOW);
  digitalWrite(rm2,HIGH);
 }

void backward()
{
  digitalWrite(lm1,LOW);
  digitalWrite(lm2,HIGH);
  digitalWrite(rm1,LOW);
  digitalWrite(rm2,HIGH);
 }
