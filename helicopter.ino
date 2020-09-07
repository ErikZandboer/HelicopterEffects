/*--------------------------------------------------------------------------------------------*/
/* Helicopter led & motor simulation.                                                         */
/*                                                                                            */
/* Controls two leds and a motor to simulate starting up of a model helicopter                */
/*                                                                                            */
/* Versioning:                                                                                */
/* 1.00            Creation. First go at timing the leds and motor. No audio included yet     */
/* 1.10            Added a second blinking group and a second motor control (main and rear)   */
/* 1.11            Bugfix around BlinkTimer: Checked for zero were lowest indent is 1.Fixed.  */
/* 1.20            Added basic support for mp3 player                                         */
/*--------------------------------------------------------------------------------------------*/

// Includes
#include <Arduino.h>
#include <SoftwareSerial.h>

// Define the physical pinout
#define BLINKLED  10
#define BLINKLED2 9
#define MOTOR     5
#define RMOTOR    6
#define SOLIDLED  13
#define MP3_RX    8   //should connect to TX of the Serial MP3 Player module
#define MP3_TX    7   //connect to RX of the MP3 player module

// Setup serial comms to the MP3 hardware
SoftwareSerial myMP3(MP3_RX, MP3_TX);

// MP3 hardware commands
#define CMD_SEL_DEV     0X35
#define DEV_TF          0X01

/*basic MP3 commands*/
#define CMD_PLAY        0X01
#define CMD_PAUSE       0X02
#define CMD_NEXT_SONG   0X03
#define CMD_PREV_SONG   0X04
#define CMD_VOLUME_UP   0X05
#define CMD_VOLUME_DOWN 0X06
#define CMD_FORWARD     0X0A // >>
#define CMD_REWIND      0X0B // <<
#define CMD_STOP        0X0E
#define CMD_STOP_INJECT 0X0F//stop interruptting with a song, just stop the interlude

/*5 bytes commands*/
#define CMD_SEL_DEV 0X35
  #define DEV_TF 0X01
#define CMD_IC_MODE 0X35
  #define CMD_SLEEP   0X03
  #define CMD_WAKE_UP 0X02
  #define CMD_RESET   0X05

/*6 bytes commands*/  
#define CMD_PLAY_W_INDEX   0X41
#define CMD_PLAY_FILE_NAME 0X42
#define CMD_INJECT_W_INDEX 0X43

/*Special commands*/
#define CMD_SET_VOLUME 0X31
#define CMD_PLAY_W_VOL 0X31

#define CMD_SET_PLAY_MODE 0X33
  #define ALL_CYCLE 0X00
  #define SINGLE_CYCLE 0X01
#define MAX_VOLUME      15

// Get some base counters in for the runtime in seconds.
byte            Hundreds=0;
unsigned int    RunTime=0;

// Global variables
byte           MotorSpeed = 0;  // Speed at which the motor turns. Used in the Motor state machine.
unsigned int   BlinkTimer = 0;  // Timer to control the blinking led.
static int8_t Send_buf[6] = {0} ; // Send buffer for the MP3 unit

// State machine for the motor
#define MOTOROFF  0
#define MOTORREVV 1
#define MOTORRUN  2
byte    MotorState = MOTOROFF;

// MP3 function sendBytes. This function sends a command to the mp3 hardware
void sendBytes(uint8_t nbytes)
{
  for(uint8_t i=0; i < nbytes; i++)//
  {
    myMP3.write(Send_buf[i]) ;
  }
}

// mp3_5bytes sends a five byte, low level command to the MP3 hardware 
void mp3_5bytes(int8_t command, uint8_t dat)
{
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0x03; //the number of bytes of the command without starting byte and ending byte
  Send_buf[2] = command; 
  Send_buf[3] = dat; //
  Send_buf[4] = 0xef; //
  sendBytes(5);
}

// mp3_6bytes sends a six byte, low level command to the MP3 hardware 
void mp3_6bytes(int8_t command, int16_t dat)
{
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0x04; //the number of bytes of the command without starting byte and ending byte
  Send_buf[2] = command; 
  Send_buf[3] = (int8_t)(dat >> 8);//datah
  Send_buf[4] = (int8_t)(dat); //datal
  Send_buf[5] = 0xef; //
  sendBytes(6);
}

// send a command 
void sendCommand(int8_t command, int16_t dat)
{
  delay(20);
  if((command == CMD_PLAY_W_VOL)||(command == CMD_SET_PLAY_MODE)||(command == CMD_PLAY_COMBINE))
  	return;
  else if(command < 0x10) 
  {
	mp3Basic(command);
  }
  else if(command < 0x40)
  { 
	mp3_5bytes(command, dat);
  }
  else if(command < 0x50)
  { 
	mp3_6bytes(command, dat);
  }
  else return;
 
}


// This runs only once when powering on
void setup()
{
        digitalWrite(BLINKLED,LOW);  // Blinking led group starts OFF
        digitalWrite(BLINKLED2,LOW); // Blinking led group 2 starts OFF
        digitalWrite(MOTOR,LOW);     // Motor is OFF
        digitalWrite(RMOTOR,LOW);    // Rear Motor is OFF
        digitalWrite(SOLIDLED,HIGH); // Solid leds are always ON

        pinMode (BLINKLED2, OUTPUT);
        pinMode (BLINKLED,  OUTPUT);
        pinMode (MOTOR,     OUTPUT);
        pinMode (RMOTOR,    OUTPUT);
        pinMode (SOLIDLED,  OUTPUT);
        
        // Init the MP3 module
        myMP3.begin(9600);                 // Start serial comms to the MP3 hardware
	delay(500);                        //Wait chip initialization is complete
        sendCommand(CMD_SEL_DEV, DEV_TF);  //select the TF card as a source 
}

// This loops forever.
void loop()
{
        while ( (millis() % 10) != 0L ) //Just do nothing until millis()/10 has no remainder --> Run at 100Hz
        {
                asm("nop \n"); // Just do NOP to make sure the compiler doesn't optimize the while() away
        }

        // This code executes 100 times a second
        Hundreds++;
        if (Hundreds > 99)
        {
                Hundreds = 0;   // Counts up to a single second, then increase the RunTime
                RunTime++;
        }

        // Here we check if any led should still be running; Stop a few seconds after the engine stops
        if (RunTime < 73)
        {
                // HANDLE BLINKTIMER. Currently on a 0.5s frequency and lights both groups for 0.1s, 0.2s apart.
                BlinkTimer++;
                if (BlinkTimer == 1 ) digitalWrite(BLINKLED,HIGH);
                if (BlinkTimer == 11) digitalWrite(BLINKLED,LOW);
                if (BlinkTimer == 21) digitalWrite(BLINKLED2,HIGH);
                if (BlinkTimer == 31) digitalWrite(BLINKLED2,LOW);
                if (BlinkTimer >  49)
                {
                        BlinkTimer = 0;
                }
        }
        else    // After 73 seconds kill the blinkleds and kill the solid leds.
        {
                digitalWrite(BLINKLED,LOW);
                digitalWrite(BLINKLED2,LOW);
                digitalWrite(SOLIDLED, LOW);
        }

        // HANDLE THE MOTOR state machine
        switch (MotorState)
        {
                case MOTOROFF:
                        if (RunTime == 30)      // Start revving after 30 seconds
                        {
                                analogWrite(MOTOR,255); // Kick the motor at full speed to make sure it starts turning
                                analogWrite(RMOTOR,255);        // Kick the motor at full speed to make sure it starts turning
                                MotorSpeed = 10;        // ... MotorRevv will slow down the motor again after 1/20th of a second.
                                MotorState = MOTORREVV;
                                mp3_6bytes(CMD_PLAY_W_VOL, (MAX_VOLUME<<8) + CMD_PLAY ); // Play the first mp3!
                        }
                        break;
                case MOTORREVV:
                        if ((Hundreds % 5) == 0) // 1/20th of seconds so revving up will take 12.25 seconds
                        {
                                MotorSpeed++;
                                if (MotorSpeed == 255)
                                {
                                        MotorState = MOTORRUN;
                                }
                                analogWrite(MOTOR,MotorSpeed);
                                analogWrite(RMOTOR,MotorSpeed);
                        }
                        break;
                case MOTORRUN:
                        if (RunTime == 70)
                        {
                                MotorState = MOTOROFF;
                                analogWrite(MOTOR,0);
                                analogWrite(RMOTOR,0);
                                sendCommand(CMD_STOP); // Stop playing the MP3

                        }
                        break;
                default: // This should never occur as it represents an illegal state. If it occurs, reset the state machine.
                        MotorState = MOTOROFF;
        }

        // Reset after 15 minutes and start over
        if (RunTime == 15*60)
        {
                RunTime = 0;
                MotorState = MOTOROFF;
                digitalWrite(SOLIDLED,HIGH); // Restart so we start the solid leds again; blink led should start itself
        }

        delay(1); // Added this dummy delay() to make sure the code takes more than 1 ms to execute.
}
