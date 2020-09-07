//Demo for Serial MP3 Player A module
//by Open-Smart Team and Catalex Team
//catalex_inc@163.com
//Board:  Arduino UNO R3
//IDE:	  Arduino-1.6.4
//Store: http://www.aliexpress.com/store/1199788
//      http://dx.com
//Function:  In the process that the Rotation Angle Sensor is rotated from
//               the 'Min' side to the 'Max' side, the volume is gradually greater.
//               If you touch the Touch Sensor,it will play or pause.

/* Wiring Guide */
//Serial MP3 Player A     |  Arduino UNO R3//
//              RX              |   7
//              TX              |   8
//              VCC            |   5V
//              GND            |   GND
//-------------------------------------
//     Touch Sensor         |  Arduino UNO R3//
//              SIG             |   2
//              VCC            |   5V
//              GND            |   GND
//-------------------------------------
// Rotary Angle Sensor   |  Arduino UNO R3//
//              SIG             |   A0
//              VCC            |   5V
//              GND            |   GND


#include <SoftwareSerial.h>

#define ARDUINO_RX 8//should connect to TX of the Serial MP3 Player module
#define ARDUINO_TX 7//connect to RX of the module
SoftwareSerial myMP3(ARDUINO_RX, ARDUINO_TX);

unsigned char playmode = 1; 
  #define PLAY  1
  #define PAUSE 0
  static int8_t Send_buf[6] = {0} ;
/************Command byte**************************/
/*basic commands*/
#define CMD_PLAY  0X01
#define CMD_PAUSE 0X02
#define CMD_NEXT_SONG 0X03
#define CMD_PREV_SONG 0X04
#define CMD_VOLUME_UP   0X05
#define CMD_VOLUME_DOWN 0X06
#define CMD_FORWARD 0X0A // >>
#define CMD_REWIND  0X0B // <<
#define CMD_STOP 0X0E
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
  
#define CMD_PLAY_COMBINE 0X45//can play combination up to 15 songs

/*********************************************************************/
/*macro definitions of Rotary angle sensor and LED pin*/
#define ROTARY_ANGLE_SENSOR A0

#define ADC_REF 5//reference voltage of ADC is 5v
#define VCC     5    //the default value of VCC of the control interface is 5v
#define FULL_ANGLE 280//full value of the rotary angle is 280 degrees

#define TOUCH_SENSOR 2

void sendCommand(int8_t command, int16_t dat = 0);

void setup() 
{
	Serial.begin(9600);
	myMP3.begin(9600);
	delay(500);
	pinMode(TOUCH_SENSOR, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(TOUCH_SENSOR), playOrPause, RISING);
    sendCommand(CMD_SEL_DEV, DEV_TF);  
	delay(200);
	playWithVolume(0X0F01);//play the first song with volume 15(0x0F) class
}
static int8_t pre_vol = 0x0f; 
void loop() 
{
  int degrees;
  degrees = getDegree();
  	
  int8_t volume;
	/*The degrees is 0~280, should be converted to be 0~255 to control the*/
	/*brightness of LED */
  volume = map(degrees, 0, 280, 0, 30); 
  if(volume != pre_vol)
  {
    setVolume(volume);
    pre_vol = volume;
  }
  if(playmode == PLAY) sendCommand(CMD_PLAY);
  else sendCommand(CMD_PAUSE);
  delay(50);
}


/********************************************************************************/
/*Function: Get the angle between the mark on the potentiometer cap and the starting position	*/
/*Parameter:-void                                                                                                          */
/*Return:     -int,the range of degrees is 0~280                                                                 */
int getDegree()
{
	int sensor_value = analogRead(ROTARY_ANGLE_SENSOR);
	float voltage;
	voltage = (float)sensor_value*ADC_REF/1023;
	float degrees = (voltage*FULL_ANGLE)/VCC;
	return degrees;
}

/*Interrupt service routine*/
void playOrPause()
{
  playmode = !playmode;
}

void setVolume(int8_t vol)
{
  mp3_5bytes(CMD_SET_VOLUME, vol);
}
void playWithVolume(int16_t dat)
{
  mp3_6bytes(CMD_PLAY_W_VOL, dat);
}

/*cycle play with an index*/
void cyclePlay(int16_t index)
{
  mp3_6bytes(CMD_SET_PLAY_MODE,index);
}

void setCyleMode(int8_t AllSingle)
{
  mp3_5bytes(CMD_SET_PLAY_MODE,AllSingle);
}


void playCombine(int8_t song[][2], int8_t number)
{
  if(number > 15) return;//number of songs combined can not be more than 15
  uint8_t nbytes;//the number of bytes of the command with starting byte and ending byte
  nbytes = 2*number + 4;
  int8_t Send_buf[nbytes];
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = nbytes - 2; //the number of bytes of the command without starting byte and ending byte
  Send_buf[2] = CMD_PLAY_COMBINE; 
  for(uint8_t i=0; i < number; i++)//
  {
    Send_buf[i*2+3] = song[i][0];
	Send_buf[i*2+4] = song[i][1];
  }
  Send_buf[nbytes - 1] = 0xef;
  sendBytes(nbytes);
}


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

void mp3Basic(int8_t command)
{
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0x02; //the number of bytes of the command without starting byte and ending byte
  Send_buf[2] = command; 
  Send_buf[3] = 0xef; //
  sendBytes(4);
}
void mp3_5bytes(int8_t command, uint8_t dat)
{
  Send_buf[0] = 0x7e; //starting byte
  Send_buf[1] = 0x03; //the number of bytes of the command without starting byte and ending byte
  Send_buf[2] = command; 
  Send_buf[3] = dat; //
  Send_buf[4] = 0xef; //
  sendBytes(5);
}
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
void sendBytes(uint8_t nbytes)
{
  for(uint8_t i=0; i < nbytes; i++)//
  {
    myMP3.write(Send_buf[i]) ;
  }
}

