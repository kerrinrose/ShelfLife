/*
* Shelf Life is the thesis project of Kerrin McLaughlin, Spring 2016
*
*
*  Wifi and GET request code from
*  https://learn.adafruit.com/wifi-weather-station-arduino-cc3000/introduction
* and
*  https://learn.adafruit.com/adafruit-cc3000-wifi
*
*
* NDEF Library -  https://github.com/don/NDEF
*/

//NFC required libraries

#if 0
#include <SPI.h>
#include <PN532_SPI.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_SPI pn532spi(SPI, 10);
NfcAdapter nfc = NfcAdapter(pn532spi);
#else



#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
#endif


// Include required libraries
#include <Adafruit_CC3000.h>
#include <SPI.h>
//#include <SHT1x.h>
#include<stdlib.h>


// Define CC3000 chip pins
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

// WiFi network (change with your settings !)
#define WLAN_SSID       "kerrin"        // cannot be longer than 32 characters!
#define WLAN_PASS       "11111111"
#define WLAN_SECURITY   WLAN_SEC_WPA2 // This can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2




String productID;


// Create CC3000 & DHT instances

Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                         SPI_CLOCK_DIV2);



// Local server IP, port, and repository (change with your settings !)
uint32_t ip = cc3000.IP2U32(54,164,177,88); //your computers ip address
int port = 80;//your webserver port (8888 is the default for MAMP)
//String repository = "/arduinoTest/";//the folder on your webserver where the sensor.php file is located





// Function to send a TCP request and get the result as a string
void send_request (String request) {
     
    // Connect    
    Serial.println("Starting connection to server...");
    Adafruit_CC3000_Client client = cc3000.connectTCP(ip, port);
    
    // Send request
    if (client.connected()) {
      client.println(request);      
      client.println(F(""));
      Serial.println("Connected & Data sent");
       digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);
    } 
    else {
      Serial.println(F("Connection failed"));    
    }

    while (client.connected()) {
      while (client.available()) {

      // Read answer
      char c = client.read();
      }
    }
    Serial.println("Closing connection");
    Serial.println("");
    client.close();
    
}




void setup(void)
{

 pinMode(13, OUTPUT);

  Serial.begin(115200);
  
Serial.println(F("Hello, CC3000!\n")); 


  
  /* Initialise the module */
  Serial.println(F("\nInitializing..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while(1);
  }
  
  // Optional SSID scan
  // listSSIDResults();
  
  Serial.print(F("\nAttempting to connect to ")); Serial.println(WLAN_SSID);
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while(1);
  }
   
  Serial.println(F("Connected!"));
  
  /* Wait for DHCP to complete */
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }



  Serial.println("NDEF Reader");
  nfc.begin();
   digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);              // wait for a second
  digitalWrite(13, LOW);
  delay(200); 
   digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);              // wait for a second
  digitalWrite(13, LOW);
  delay(200); 
   digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);              // wait for a second
  digitalWrite(13, LOW);
}

void loop(void)
{
  Serial.println("\nScan a NFC tag\n");
  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();

    if (tag.hasNdefMessage()) // every tag won't have a message
    {

      NdefMessage message = tag.getNdefMessage();
      int recordCount = message.getRecordCount();
     
        NdefRecord record = message.getRecord(0);



        // The TNF and Type should be used to determine how your application processes the payload
        // There's no generic processing for the payload, it's returned as a byte[]
        int payloadLength = record.getPayloadLength();
        byte payload[payloadLength];
        record.getPayload(payload);

        // Force the data into a String (might work depending on the content)
        // Real code should use smarter processing
      String tag = "";
     for (int c = 0; c < payloadLength; c++) {
         tag += (int)payload[c];
      }
         // tag.toInt();
        Serial.println(tag);
        
      
        
      
       
       productID = tag;
       
    // Send request
    String request = "GET /Firebase/main.php?ID=" + productID + " HTTP/1.0";
    send_request(request);
    Serial.println("");
    Serial.print("request: ");
    Serial.println(request);
    Serial.println("");

      
    }

  }
  delay(500);

}




