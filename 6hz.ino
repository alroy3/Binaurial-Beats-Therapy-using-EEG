/*

  Project Name:   Binaural Beats Therapy using EEG
  Author List:    Alroy Pereira, Raj Lad, Maitreya Shelke, Prashant Rawat
  Filename:       6hz.uno
  Functions:   setup() , CheckState(), loop()
  Global Variables: MedValue, AtValue

*/

#include<SoftwareSerial.h>
#include <Brain.h>

// Set up the brain parser, pass it the hardware serial object you want to listen on.
Brain brain(Serial);

// Create object named bt of the class SoftwareSerial
SoftwareSerial bt(2, 3); // (Rx,Tx)

//veriables
int MedValue;
int AtValue;

/*
*Function Name:  setup
*Input:          None
*Output:         hardware def
*Logic:          Its use for set the hardware that is used from the controller  
*                it loops only onces and is called by controller automatically
*Example Call:   Called automatically    
*/

void setup() {
  // Start the hardware serial.
  Serial.begin(9600);

  // Define baud rate for software serial communication
  bt.begin(9600);

}
/*
*Function Name:  CheckState
*Input:          The input to the function given from the MedVal and Atvalue
*Output:         The function send the value to the bluetooth 
*Logic:          The function sends the data to the app using bluetooth using  
*                the values recived from MedVal and AtVale
*Example Call:   CheckState();     
*/
void CheckState() {
  /*as the users meditation and attwnction valuse is close to 1
    that means the user is meditating the valuse close to 1 are good*/
  if (MedValue > 50 && Atvalue > 50)
    bt.write("0"); //sends data to bluetooth

  else if (MedValue < 50 && Atvalue > 50)
    bt.write("1"); //sends data to bluetooth

  else if (MedValue < 50 && Atvalue < 50)
    bt.write("2"); //sends data to bluetooth
}

/*
*Function Name:  setup
*Input:          None
*Output:         int to inform the caller that the program exited correctly or incorrectly
*Logic:          it calls the function  CheckState() 
*Example Call:   Called automatically;     
*/

void loop() {
  // Expect packets about once per second.
  // The .readCSV() function returns a string (well, char*) listing the most recent brain data, in the following format:
  // "signal strength, attention, meditation, delta, theta, low alpha, high alpha, low beta, high beta, low gamma, high gamma"
  Serial.println(brain.readCSV());
  MedValue = brain.readMeditation(); //returs 8 bytes values
  AtValue = brain.readAttention(); //returs 8 bytes values

  /*Checks the state of the user and sends the data to the app
    which plays the beats */
  CheckState();
}
