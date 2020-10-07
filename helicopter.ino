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
/* 1.21            Changed the basic support for MP3 to now use the RedMP3.h library          */
/* 1.22            Added a separate state machine to differentiate between the 2 motors.      */
/*--------------------------------------------------------------------------------------------*/

// Includes
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "RedMP3.h"

// Define the physical pinout
#define BLINKLED  10
#define BLINKLED2 9
#define MOTOR     5
#define RMOTOR    6
#define SOLIDLED  13
#define MP3_RX    8   //should connect to TX of the Serial MP3 Player module
#define MP3_TX    7   //connect to RX of the MP3 player module

// Setup serial comms to the MP3 hardware
MP3 mp3(MP3_RX, MP3_TX);

// Get some base counters in for the runtime in seconds.
byte            Hundreds=0;
unsigned int    RunTime=0;

// Global variables
byte           MainMotorSpeed = 0;  // Speed at which the motor turns. Used in the Motor state machine.
byte           RearMotorSpeed = 0;  // Speed at which the motor turns. Used in the Motor state machine.
unsigned int   BlinkTimer = 0;  // Timer to control the blinking led.

// State machine for the motor
#define MOTOROFF  0
#define MOTORREVV 1
#define MOTORRUN  2
byte    MainMotorState = MOTOROFF;
byte    RearMotorState = MOTOROFF;

// This runs only once when powering on
void setup()
{
        digitalWrite(BLINKLED, LOW);     // Blinking led group starts OFF
        digitalWrite(BLINKLED2,LOW);     // Blinking led group 2 starts OFF
        digitalWrite(MOTOR,    LOW);     // Motor is OFF
        digitalWrite(RMOTOR,   LOW);     // Rear Motor is OFF
        digitalWrite(SOLIDLED, HIGH);    // Solid leds are always ON

        pinMode (BLINKLED2, OUTPUT);
        pinMode (BLINKLED,  OUTPUT);
        pinMode (MOTOR,     OUTPUT);
        pinMode (RMOTOR,    OUTPUT);
        pinMode (SOLIDLED,  OUTPUT);
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
                // The code below runs once a second.
                if (RunTime == 1)  mp3.playWithVolume(1,26);  // Play the first mp3 on the card at volume 26 (max is 30)
                if (RunTime == 70) mp3.stopPlay(); // Stop playing after the show is over
        }

        // Here we check if any led should still be running; Stop a few seconds after the engine stops
        if (RunTime < 73)
        {
                // HANDLE BLINKTIMER. Currently on a 0.5s frequency and lights both groups for 0.1s, 0.2s apart.
                BlinkTimer++;
                if (BlinkTimer == 1  ) digitalWrite(BLINKLED,HIGH);
                if (BlinkTimer == 11 ) digitalWrite(BLINKLED,LOW);
                if (BlinkTimer == 31 ) digitalWrite(BLINKLED2,HIGH);
                if (BlinkTimer == 41 ) digitalWrite(BLINKLED2,LOW);
                if (BlinkTimer >  149) BlinkTimer = 0;
        }
        else    // After 73 seconds kill the blinkleds and kill the solid leds.
        {
                digitalWrite(BLINKLED, LOW);
                digitalWrite(BLINKLED2,LOW);
                digitalWrite(SOLIDLED, LOW);
        }

        // HANDLE THE MOTOR state machine
        switch (MainMotorState)
        {
                case MOTOROFF:
                        if (RunTime == 10)      // Start revving the main rotor after +-10 seconds
                        {
                                analogWrite(MOTOR,255); // Kick the motor at full speed to make sure it starts turning
                                MainMotorSpeed = 10;        // ... MotorRevv will slow down the motor again after 1/20th of a second.
                                MainMotorState = MOTORREVV;
                        }
                        break;
                case MOTORREVV:
                        if ((Hundreds % 10) == 0) // 1/20th of seconds so revving up will take 25 seconds
                        {
                                MainMotorSpeed++;
                                if (MainMotorSpeed == 255) MainMotorState = MOTORRUN;
                                analogWrite(MOTOR,MainMotorSpeed);
                        }
                        break;
                case MOTORRUN:
                        if (RunTime == 70)  // Should run 1:20
                        {
                                MainMotorState = MOTOROFF;
                                analogWrite(MOTOR,0);
                        }
                        break;
                default: // This should never occur as it represents an illegal state. If it occurs, reset the state machine.
                        MainMotorState = MOTOROFF;
        }
        switch (RearMotorState)
        {
                case MOTOROFF:
                        if (RunTime == 30)      // Start revving after 30 seconds
                        {
                                RearMotorSpeed = 10;        // ... MotorRevv will slow down the motor again after 1/20th of a second.
                                RearMotorState = MOTORREVV;
                        }
                        break;
                case MOTORREVV:
                        if ((Hundreds % 5) == 0) // 1/20th of seconds so revving up will take 12.25 seconds
                        {
                                RearMotorSpeed++;
                                if (RearMotorSpeed == 255) RearMotorState = MOTORRUN;
                                analogWrite(RMOTOR,RearMotorSpeed);
                        }
                        break;
                case MOTORRUN:
                        if (RunTime == 70)
                        {
                                RearMotorState = MOTOROFF;
                                analogWrite(RMOTOR,0);
                        }
                        break;
                default: // This should never occur as it represents an illegal state. If it occurs, reset the state machine.
                        RearMotorState = MOTOROFF;
        }

        // Reset after 15 minutes and start over
        if (RunTime == 15*60)
        {
                RunTime = 0;
                MainMotorState = MOTOROFF;
                RearMotorState = MOTOROFF;
                digitalWrite(SOLIDLED,HIGH); // Restart so we start the solid leds again; blink led should start itself
        }

        delay(1); // Added this dummy delay() to make sure the code takes more than 1 ms to execute.
}
