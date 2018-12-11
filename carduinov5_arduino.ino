/*
* Carduino - School-project - 02/02-2018
* RC Car Controled with bluetooth app (Andriod)
* Made by Oskar Wahlqvist, Mattias Julin and Edvin Nordholm 
*/
 
// Motors - A1 and A2 for power and B1 and B2 for the wheels  
  const int motorA1  = 5; 
  const int motorA2  = 6;  
  const int motorB1  = 10; 
  const int motorB2  = 9;  
  
//Leds 
  const int FrontLights  = 12;		//Front lights 
  const int blights  = 13;		//Back lights 
  
  const int breakLights = 7;	//Break lights 
  const int lblink = 3;			//Left blinker 
  const int rblink = 4; 		//Right blinker 

  //Empty pin
  //const int a = 3;
  
//Bluetooth module (HC-06) 
  const int BTState = 2; //Connected to pin 2
  
//State the constant from app
  int state;
//Speed is the speed of the car
  int Speed=255;     // Speed between 0-255

  
void setup() {
    // OUTPUT pins
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    pinMode(FrontLights, OUTPUT);
    pinMode(blights, OUTPUT);
    pinMode(lblink, OUTPUT); 
    pinMode(breakLights, OUTPUT); 
    pinMode(lblink, OUTPUT);
    pinMode(rblink, OUTPUT);   
	
	//INPUT pins
	pinMode(BTState, INPUT);
	
    // Initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
}
 
void loop() {

 
  //Saves the commands from the app to "state"
    if(Serial.available() > 0){     
      state = Serial.read();   
    }
  
  
  //There are 4 diffrent speed values in the app. values can range from 0 - 255. 
    if (state == '0'){
      Speed=0;}
    else if (state == '1'){
      Speed=100;}
    else if (state == '2'){
      Speed=150;}
    else if (state == '3'){
      Speed=200;}
    else if (state == '4'){
      Speed=255;}
     
  /***********************F - Forward****************************/
  //If the app sends out the letter F, the car goes forward. 
    if (state == 'F') {
      analogWrite(motorA1, Speed); analogWrite(motorA2, 0);
        analogWrite(motorB1, 0);      analogWrite(motorB2, 0); 
    }
  /**********************G - Forward Left************************/
  //If the app sends out the letter G, the car goes forward and turn left
    else if (state == 'G') {
      analogWrite(motorA1, Speed); analogWrite(motorA2, 0);  
        analogWrite(motorB1, 255);    analogWrite(motorB2, 0); 
    }
  /**********************I - Forward Right************************/
  //If the app sends out the letter I, the car goes forward and turn right
    else if (state == 'I') {
        analogWrite(motorA1, Speed); analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);      analogWrite(motorB2, 255); 
    }
  /***********************B - Backward****************************/
  //If the app sends out the letter B, the car goes backwards
    else if (state == 'B') {
         digitalWrite(breakLights, HIGH);
      analogWrite(motorA1, 0);   analogWrite(motorA2, Speed); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, 0); 
      digitalWrite(breakLights, LOW);
    }
    
  /**********************H - Backward Left************************/
  //If the app sends out the letter H, the car goes backward and turn left 
    else if (state == 'H') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, Speed); 
        analogWrite(motorB1, 255); analogWrite(motorB2, 0); 
    }
  /**********************J - Backward Right************************/
  // If the app sends out the letter J, the car goes backwards and turn right
    else if (state == 'J') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, Speed); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, 255); 
    }
  /***************************L - Left*****************************/
  //If the app sends out the letter L, the wheels turn left 
    else if (state == 'L') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
        analogWrite(motorB1, 255); analogWrite(motorB2, 0); 
    }
  /***************************R - Right*****************************/
  //If the app sends out the letter R, the wheels turn right
    else if (state == 'R') {
      analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);   analogWrite(motorB2, 255);     
    }
  /************************W and w - FrontLights*****************************/
  //If the app sends out a capital W, the front leds will turn on.
  //and if the app sends out a small w, the front leds will turn off.
    else if (state == 'W') { 
         digitalWrite(FrontLights, HIGH); 
      }
      else if (state == 'w'){
         digitalWrite(FrontLights, LOW); 
      }
     /************************U and u - BackLights*****************************/
	 //If the app sends out a capital U, the leds in the back will turn on. 
	 //and if the app sends out a small u, the leds in the back will turn off.
    else if (state == 'U') {  
         digitalWrite(blights, HIGH); 
      }
      else if (state == 'u'){
         digitalWrite(blights, LOW); 
      }
         /************************LeftBlink*****************************/
  //If state is equal with letter 'G or L', led will blink
  
    else if (state == 'L') {  
         digitalWrite(lblink, HIGH);
         delay(250); 
         digitalWrite(lblink, LOW);
         delay(250);
      } 
/**********************left blink***************************/
  //If state is equal with letter 'V', turn on blinker
  
	else if (state == 'V') {
	      digitalWrite(lblink, HIGH);
       delay(500);
       digitalWrite(lblink, LOW);
       delay(500);
        digitalWrite(lblink, HIGH);
       delay(500);
       digitalWrite(lblink, LOW);
       delay(500);
        digitalWrite(lblink, HIGH);
       delay(500);
       digitalWrite(lblink, LOW);
       delay(500);
	}
  
    //If state is equal with letter 'v', turn off turnsignal
	else if (state == 'v') {
		digitalWrite(lblink, LOW);
	}
	
 /**********************right blink***************************/
  //If state is equal with letter 'X', turn on turnsignal
    else if (state == 'X'){
          digitalWrite(rblink, HIGH);
       delay(500);
       digitalWrite(rblink, LOW);
       delay(500);
        digitalWrite(rblink, HIGH);
       delay(500);
       digitalWrite(rblink, LOW);
       delay(500);
        digitalWrite(rblink, HIGH);
       delay(500);
       digitalWrite(rblink, LOW);
       delay(500);
    }
	  //If state is equal with letter 'x', turn off turnsignal
	else if (state == 'x'){
		digitalWrite(rblink, LOW);
	}
   /************************S - Stop*****************************/
  //If the app sends out the letter S, the car stops 
    else if (state == 'S'){
        analogWrite(motorA1, 0);  analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
    }
   
}
