// SIT210
// Name: Om Tomar
// Roll No: 2210994882

#include <Arduino.h>                // Include the Arduino library for basic functions
#include <WiFiNINA.h>               // Include the WiFiNINA library for WiFi connectivity
#include <ArduinoJson.h>            // Include the ArduinoJson library for JSON parsing
#include <Firebase_Arduino_WiFiNINA.h> // Include the Firebase library for Firebase integration

#define FIREBASE_HOST "https://light-control-b6f12-default-rtdb.asia-southeast1.firebasedatabase.app/" // Define the Firebase database URL
#define FIREBASE_AUTH "XNDueWNW3BeBXtWPPCE93UCaohnyWn5OZMs0LCVZ"   // Define the Firebase authentication token

char ssid[] = "Om";               // Define the WiFi SSID
char pass[] = "7011448844";       // Define the WiFi password

FirebaseData object;              // Create a FirebaseData object to interact with Firebase
String path = "/status/status";    // Define the Firebase database path

void setup()
{
  Serial.begin(9600);             // Initialize the serial communication for debugging
  pinMode(2, OUTPUT);             // Set pin 2 as an output for a LED
  pinMode(3, OUTPUT);             // Set pin 3 as an output for a LED
  pinMode(4, OUTPUT);             // Set pin 4 as an output for a LED

  // Initialize FirebaseData object
  FirebaseData object = FirebaseData();

  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    // Attempt to connect to WiFi and retry if failed
    Serial.print(".");
    delay(5000);                  // Wait for 5 seconds before retrying
  }

  Serial.print("You're connected to the ");
  Serial.println(ssid);
  Serial.print("WiFi localIP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Initialize Firebase connection and set Firebase data to "OFF"
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, ssid, pass);
  Firebase.reconnectWiFi(true);

  if (Firebase.setString(object, path, "OFF"))
  {
    Serial.println("OK");          // Print "OK" if setting the Firebase data was successful
  }
  else
  {
    Serial.println("Error: " + object.errorReason()); // Print an error message if setting data failed
  }
}

void loop()
{
  if (Firebase.getString(object, path))
  {
    if (object.stringData() == "RED")
    {
      // Turn on the RED LED
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      Serial.println("RED LED ON");  
    }
    else if (object.stringData() == "YELLOW")
    {
      // Turn on the YELLOW LED
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      Serial.println("YELLOW LED on");
    }
    else if (object.stringData() == "GREEN")
    {
      // Turn on the GREEN LED
      digitalWrite(3, LOW);
      digitalWrite(2, LOW);
      digitalWrite(4, HIGH);
      Serial.println("Green LED on");
    }
    else if (object.stringData() == "OFF")
    {
      // Turn off all LEDs
      digitalWrite(3, LOW);
      digitalWrite(2, LOW);
      digitalWrite(4, LOW);
      Serial.println("OFF");
    }
  }
  else
  {
    Serial.println("Error"); // Print an error message if Firebase data retrieval fails
  }
}