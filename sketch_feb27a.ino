const boolean useSeparatePWMPin = true;

const int in1Pin = 10;
int in1PinState = LOW;
const int in2Pin = 9;
int in2PinState = LOW;
const int pwmPin = 11;
const int pumPin = 12;
int pumPinState = LOW;

unsigned long previousMillis1 = 0;
long ForwardTime = 200;
long DespinTime = 300;


unsigned long previousMillis2 = 0;
long OnTime = 300;
long OffTime = 600;

void forward(int value, int in1pinState, int in2PinState){
  if(useSeparatePWMPin){
    digitalWrite(in1Pin, in1PinState);//HIGH
    digitalWrite(in2Pin, in2PinState);//LOW
    analogWrite(pwmPin, value);
  }else{
    analogWrite(in1Pin, value);
    analogWrite(in2Pin, 0);
  }
}

void reverse(int value, int in1pinState, int in2PinState){
  if(useSeparatePWMPin){
    digitalWrite(in1Pin, in1PinState);//LOW
    digitalWrite(in2Pin, in2PinState);//HIGH
    analogWrite(pwmPin, value);
  }else{
    analogWrite(in1Pin, 0);
    analogWrite(in2Pin, value);
  }
}

void despin(boolean useBrake, int in1PinState, int in2PinState){
  if(useBrake){
    digitalWrite(in1Pin, in1PinState);//HIGH
    digitalWrite(in2Pin, in2PinState);//HIGH
    if(useSeparatePWMPin){
      analogWrite(pwmPin, 255);
    }
  }else{
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    if(useSeparatePWMPin){
      analogWrite(pwmPin, 0);
    }
  }
}

void pump(int state){
  digitalWrite(pumPin, state);
}

int num = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(pumPin, OUTPUT);
  Serial.begin(9600);
}



void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    byte data = Serial.read();
    num = (int)data;
  }
  unsigned long currentMillis = millis();
  Serial.println(currentMillis);
  if(num == 48){
    Serial.println(num);
    pump(LOW);
    despin(255, HIGH, HIGH);
  }else if(num==49){
    //ここで時間の代入
    pump(LOW);
    ForwardTime = 1000;
    DespinTime = 300;
    
    if((in1PinState == LOW) && (in2PinState == LOW) && (currentMillis - previousMillis1 >= ForwardTime)){
      in1PinState = HIGH;
      previousMillis1 = currentMillis;
      forward(255, in1PinState, in2PinState);
    }else if((in1PinState == HIGH) && (in2PinState == LOW) && (currentMillis - previousMillis1 >= DespinTime)){
      in2PinState = HIGH;
      previousMillis1 = currentMillis;
      despin(true, in1PinState, in2PinState);
      in1PinState = LOW;
      in2PinState = LOW;
    }
    
  }else if(num==50){
    pump(LOW);
    ForwardTime = 600;
    DespinTime = 300;


    if((in1PinState == LOW) && (in2PinState == LOW) && (currentMillis - previousMillis1 >= ForwardTime)){
      in1PinState = HIGH;
      previousMillis1 = currentMillis;
      forward(255, in1PinState, in2PinState);
    }else if((in1PinState == HIGH) && (in2PinState == LOW) && (currentMillis - previousMillis1 >= DespinTime)){
      in2PinState = HIGH;
      previousMillis1 = currentMillis;
      despin(true, in1PinState, in2PinState);
      in1PinState = LOW;
      in2PinState = LOW;
    }
  }else if(num==51){
    ForwardTime = 600;
    DespinTime = 300;
    OnTime = 2000;
    OffTime = 200;
    
    if((pumPinState == HIGH) && (currentMillis - previousMillis2 >= OnTime)){
      pumPinState = LOW;
      previousMillis2 = currentMillis;
      pump(pumPinState);
    }else if((pumPinState == LOW) && (currentMillis - previousMillis2 >= OffTime)){
      pumPinState = HIGH;
      previousMillis2 = currentMillis;
      pump(pumPinState);
    }

    if((in1PinState == LOW) && (in2PinState == LOW) && (currentMillis - previousMillis1 >= ForwardTime)){
      in1PinState = HIGH;
      previousMillis1 = currentMillis;
      forward(200, in1PinState, in2PinState);
    }else if((in1PinState == HIGH) && (in2PinState == LOW) && (currentMillis - previousMillis1 >= DespinTime)){
      in2PinState = HIGH;
      previousMillis1 = currentMillis;
      despin(true, in1PinState, in2PinState);
      in1PinState = LOW;
      in2PinState = LOW;
    }  
    
    
  }else if(num==52){
    ForwardTime = 200;
    DespinTime = 300;
    OnTime = 2000;
    OffTime = 50;

    if((pumPinState == HIGH) && (currentMillis - previousMillis2 >= OnTime)){
      pumPinState = LOW;
      previousMillis2 = currentMillis;
      pump(pumPinState);
    }else if((pumPinState == LOW) && (currentMillis - previousMillis2 >= OffTime)){
      pumPinState = HIGH;
      previousMillis2 = currentMillis;
      pump(pumPinState);
    }
    
    if((in1PinState == LOW) && (in2PinState == LOW) && (currentMillis - previousMillis1 >= ForwardTime)){
        in1PinState = HIGH;
        previousMillis1 = currentMillis;
        forward(255, in1PinState, in2PinState);
      }else if((in1PinState == HIGH) && (in2PinState == LOW) && (currentMillis - previousMillis1 >= DespinTime)){
        in2PinState = HIGH;
        previousMillis1 = currentMillis;
        despin(true, in1PinState, in2PinState);
        in1PinState = LOW;
      in2PinState = LOW;
      }
    }

}
