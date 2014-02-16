// #include <string.h>
//  #include <ctype.h>
//  int ledPin = 13;                  // LED test pin
//  int rxPin = 0;                    // RX PIN 
//  int txPin = 1;                    // TX TX
//  int byteGPS=-1;
//  char linea[300] = "";
//  char comandoGPR[7] = "$GPRMC";
//  int cont=0;
//  int bien=0;
//  int conta=0;
//  int indices[13];
//  void setup() {
//    pinMode(ledPin, OUTPUT);       // Initialize LED pin
//    pinMode(rxPin, INPUT);
//    pinMode(txPin, OUTPUT);
//    Serial1.begin(9600);
//    for (int i=0;i<300;i++){       // Initialize a buffer for received data
//      linea[i]=' ';
//     Serial.begin(115200);
//    }   
//  }
//  void loop() {
//    digitalWrite(ledPin, HIGH);
//    byteGPS=Serial1.read();         // Read a byte of the serial port
//    if (byteGPS == -1) {           // See if the port is empty yet
//      delay(100); 
//    } else {
//      // note: there is a potential buffer overflow here!
//      linea[conta]=byteGPS;        // If there is serial port data, it is put in the buffer
//      conta++;                      
//      Serial.print(byteGPS); 
//      if (byteGPS==13){            // If the received byte is = to 13, end of transmission
//        // note: the actual end of transmission is <CR><LF> (i.e. 0x13 0x10)
//        digitalWrite(ledPin, LOW); 
//        cont=0;
//        bien=0;
//        // The following for loop starts at 1, because this code is clowny and the first byte is the <LF> (0x10) from the previous transmission.
//        for (int i=1;i<7;i++){     // Verifies if the received command starts with $GPR
//          if (linea[i]==comandoGPR[i-1]){
//            bien++;
//          }
//        }
//        if(bien==6){               // If yes, continue and process the data
//          for (int i=0;i<300;i++){
//            if (linea[i]==','){    // check for the position of the  "," separator
//              // note: again, there is a potential buffer overflow here!
//              indices[cont]=i;
//              cont++;
//            }
//            if (linea[i]=='*'){    // ... and the "*"
//              indices[12]=i;
//              cont++;
//            }
//          }
//          Serial.println("");      // ... and write to the serial port
//          Serial.println("");
//          Serial.println("---------------");
//          for (int i=0;i<12;i++){
//            switch(i){
//              case 0 :Serial.print("Time in UTC (HhMmSs): ");break;
//              case 1 :Serial.print("Status (A=OK,V=KO): ");break;
//              case 2 :Serial.print("Latitude: ");break;
//              case 3 :Serial.print("Direction (N/S): ");break;
//              case 4 :Serial.print("Longitude: ");break;
//              case 5 :Serial.print("Direction (E/W): ");break;
//              case 6 :Serial.print("Velocity in knots: ");break;
//              case 7 :Serial.print("Heading in degrees: ");break;
//              case 8 :Serial.print("Date UTC (DdMmAa): ");break;
//              case 9 :Serial.print("Magnetic degrees: ");break;
//              case 10 :Serial.print("(E/W): ");break;
//              case 11 :Serial.print("Mode: ");break;
//              case 12 :Serial.print("Checksum: ");break;
//            }
//            for (int j=indices[i];j<(indices[i+1]-1);j++){
//              Serial.print(linea[j+1]); 
//            }
//            Serial.println("");
//          }
//          Serial.println("---------------");
//        }
//        conta=0;                    // Reset the buffer
//        for (int i=0;i<300;i++){    //  
//          linea[i]=' ';             
//        }
//      }
//    }

//  }

// //  // #include <SoftwareSerial.h>


// SoftwareSerial mySerial(6,7);



// int inputVal;

// void setup(){

// Serial.begin(115200);
// Serial1.begin(9600);

// }
// void loop() {
// if (Serial1.available() > 0) {
//             // read the incoming byte:
//             inputVal = Serial1.read();
//                 //potVal = (int) inputVal;
                 
//             // say what you got:
//             Serial.print("I received: ");
//             Serial.print("dec = ");
//   Serial.println(inputVal, DEC);  // print as an ASCII-encoded decimal
  
//   Serial.print("hex = ");
//   Serial.println(inputVal, HEX);  // print as an ASCII-encoded hexadecimal
  
//   Serial.print("oct = ");
//   Serial.println(inputVal, OCT);  // print as an ASCII-encoded octal
  
//   Serial.print("bin = ");
//   Serial.println(inputVal, BIN);  // print as an ASCII-encoded binary
  
//   // Serial.print("byte = ");
//   // Serial.println(inputVal, BYTE); // print as a raw byte value

//   // delay 10 milliseconds before the next reading:
//   delay(10);
//       }

// }


unsigned char buffer[64];                   // buffer array for data recieve over serial port
int count=0;                                // counter for buffer array

void setup()
{
    Serial1.begin(9600);                 // the SoftSerial baud rate
    Serial.begin(115200);                     // the Serial port of Arduino baud rate.
}

void loop()
{
    if (Serial1.available())                     // if date is comming from softwareserial port ==> data is comming from Serial1 shield
    {
        while(Serial1.available())               // reading data into char array
        {
            buffer[count++]=Serial1.read();      // writing data into array
            if(count == 64)break;
        }
        Serial.write(buffer,count);                 // if no data transmission ends, write buffer to hardware serial port
        clearBufferArray();                         // call clearBufferArray function to clear the storaged data from the array
        count = 0;                                  // set counter of while loop to zero


    }
    if (Serial.available())                 // if data is available on hardwareserial port ==> data is comming from PC or notebook
    Serial1.write(Serial.read());        // write it to the SoftSerial shield
}

void clearBufferArray()                     // function to clear buffer array
{
    for (int i=0; i<count;i++)
    { buffer[i]=NULL;}                      // clear all index of array with command NULL
}














