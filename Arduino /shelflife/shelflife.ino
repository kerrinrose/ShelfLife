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
#define WLAN_PASS       ""
#define WLAN_SECURITY   WLAN_SEC_WPA2 // This can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2

// Specify data and clock connections and instantiate SHT1x object
#define dataPin  9
#define clockPin 8





// Create CC3000 & DHT instances

Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIV2);
                                         
                                         
                                         
// Local server IP, port, and repository (change with your settings !)
uint32_t ip = cc3000.IP2U32(52,24,159,58);//your computers ip address
int port = 80;//your webserver port (8888 is the default for MAMP)
//String repository = "/arduinoTest/";//the folder on your webserver where the sensor.php file is located










void setup(void)
{
 

  
  Serial.begin(115200);
    
//  // Initialise the CC3000 module
//  if (!cc3000.begin())
//  {
//    while(1);
//  }
//
//  // Connect to  WiFi network
//  cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY);
//  Serial.println("Connected to WiFi network!");
//    
//  // Check DHCP
//  Serial.println(F("Request DHCP"));
//  while (!cc3000.checkDHCP())
//  {
//    delay(100);
//    
//  
//  }


Serial.println("NDEF Reader");
 nfc.begin();  
  
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
      
      int payloadLength = record.getPayloadLength();
        byte payload[payloadLength];
       record.getPayload(payload);
       
      // force payload to string
      
          String tag = "";
        for (int c = 0; c < payloadLength; c++) {
          tag += (char)payload[c];
        }
        Serial.print("  Payload (as String): ");
        Serial.println(tag);
        
        //parse string
        
        String UUID = "";
        String foodName = "";
        String expire = "";
        String cats = "i likecats";
        Serial.println(tag.indexOf('Begin'));
   
        
        // UUID = tag.substring(tag.indexOf("BeginUUID")+9, tag.indexOf("EndUUID"));
       // Serial.println("the id is: " + UUID);
//        foodName = tag.substring(tag.lastIndexOf("BeginFood")+9, tag.lastIndexOf("EndFood"));
//        Serial.println(foodName);
//        expire = tag.substring(tag.lastIndexOf("BeginExpires")+12, tag.lastIndexOf("EndExpires"));
//        Serial.println(expire);
     
     
      
    }
        

        
        
        
    }
    delay(5000);
 
}


