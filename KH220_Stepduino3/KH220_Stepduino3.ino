// Each driver board will have pins labeled "IN1", "IN2", "IN3", & "IN4"
// These are the pins that need to be connected to digital out pins on your Arduino.
// The variables below give you an easy way to assign which pins on the driver board are
// connected to corresponding pins on the Arduino.

// These are for stepper #1 (the pan)
int S1_IN1 = 4;    
int S1_IN2 = 5;
int S1_IN3 = 6;
int S1_IN4 = 7;

//These are for stepper #2 (the tilt)
int S2_IN1 = 8;    
int S2_IN2 = 9;
int S2_IN3 = 10;
int S2_IN4 = 11;


int Speed = 1;        // This controls how long we wait between pulses (In seconds)
int Distance = 0;        // Creating an integer variable named "Distance" that counts the number of steps we've made
int FullRotation = 4096; // How many steps are in a full revolution of the motor shaft?
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};
                          // This array contains bimary values that will be pushed to the outpur pins to properly pulse the stepper

void setup() {
  
// Set mode on the pins for stepper #1  
  pinMode(S1_IN1, OUTPUT);
  pinMode(S1_IN2, OUTPUT);
  pinMode(S1_IN3, OUTPUT);
  pinMode(S1_IN4, OUTPUT);

// And now lets do the same for stepper #2
  pinMode(S2_IN1, OUTPUT);
  pinMode(S2_IN2, OUTPUT);
  pinMode(S2_IN3, OUTPUT);
  pinMode(S2_IN4, OUTPUT);

// And open up a serial port so we can debug our program
  Serial.begin(9600);

}

void loop()
{
        // We only want to do something when we receive data
        // This if statement puts us into pause until the arduino receives data from the serial port
        
        if (Serial.available() > 0) 
          {
                int incomingByte = Serial.read(); // Read the incoming data

                Serial.print("I received: ");
                Serial.println(incomingByte);

                // IF the arduino has received data, then evaluate the following four IF statements

                // If the arduino has recieved ASCII "97" - ("a")
                if (incomingByte == 97)
                {
                  for (int x=0; x < 3; x++)
                  {
                    CCW();
                  }
                }
                
                // If the arduino has received ASCII "100" - ("d")
                if (incomingByte == 100)
                {
                  for (int x=0; x < 3; x++)
                  {
                    CW();
                  }
                }

                // If the arduino has received ASCII "119" - ("w")
                if (incomingByte == 119)
                {
                  for (int x=0; x < 3; x++)
                  {
                    UP();
                  }
                }
        

                // If the arduino has received ASCII "115" - ("s")
                if (incomingByte == 115)
                {
                  for (int x=0; x < 3; x++)
                  {
                    DOWN();
                  }
                }

        
        }


}


void CW()
{
  for(int stepper = 7; stepper >= 0; stepper--)
  {
    MoveStep1(stepper);
    delay(Speed);
  }
}

void CCW()
{
  for(int stepper = 0; stepper < 8; stepper++)
  {
    MoveStep1(stepper);
    delay(Speed);
  }
}

void UP()
{
  for(int stepper = 7; stepper >= 0; stepper--)
  {
    MoveStep2(stepper);
    delay(Speed);
  }  
}

void DOWN()
{
  for(int stepper = 0; stepper < 8; stepper++)
  {
    MoveStep2(stepper);
    delay(Speed);
  }  
}

// This function will move stepper #1 one step in either direction (depending on which function called this function)
void MoveStep1(int eighth)
{
  digitalWrite(S1_IN1, bitRead(lookup[eighth], 0));
  digitalWrite(S1_IN2, bitRead(lookup[eighth], 1));
  digitalWrite(S1_IN3, bitRead(lookup[eighth], 2));
  digitalWrite(S1_IN4, bitRead(lookup[eighth], 3));
}

// This function will move stepper #2 one step in either direction (depending on which function called this function)
void MoveStep2(int eighth)
{
  digitalWrite(S2_IN1, bitRead(lookup[eighth], 0));
  digitalWrite(S2_IN2, bitRead(lookup[eighth], 1));
  digitalWrite(S2_IN3, bitRead(lookup[eighth], 2));
  digitalWrite(S2_IN4, bitRead(lookup[eighth], 3));
}
