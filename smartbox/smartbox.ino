#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// Pins for Ultrasonic Sensors
const int trigPin1 = 9;
const int echoPin1 = 10;
const int trigPin2 = 11;
const int echoPin2 = 12;
const int trigPin3 = A0;
const int echoPin3 = A1;
const int trigPin4 = A2;
const int echoPin4 = A3;

// MP3 Player
SoftwareSerial mySerial(5, 6); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

// Flags to track if each sensor has already triggered
bool triggered1 = false;
bool triggered2 = false;
bool triggered3 = false;
bool triggered4 = false;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  // Initialize the DFPlayer
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1. Please recheck the connection!"));
    Serial.println(F("2. Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(30);  // Set volume value (0~30).

  // Initialize sensor pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
}

long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

void stopAllSounds() {
  myDFPlayer.stop();  // Stop any currently playing sound
  delay(100);  // Delay to allow the DFPlayer to stop properly
}

void loop() {
  long distance1 = getDistance(trigPin1, echoPin1);
  long distance2 = getDistance(trigPin2, echoPin2);
  long distance3 = getDistance(trigPin3, echoPin3);
  long distance4 = getDistance(trigPin4, echoPin4);

  // Check which sensor detects an object within 2 cm and play sound
  if (distance1 <= 2 && !triggered1) {
    stopAllSounds();  // Stop any currently playing sound
    myDFPlayer.play(1);  // Play the first track
    triggered1 = true;  // Set the flag to true to indicate it has triggered
  } else if (distance2 <= 2 && !triggered2) {
    stopAllSounds();  // Stop any currently playing sound
    myDFPlayer.play(2);  // Play the second track
    triggered2 = true;  // Set the flag to true to indicate it has triggered
  } else if (distance3 <= 2 && !triggered3) {
    stopAllSounds();  // Stop any currently playing sound
    myDFPlayer.play(3);  // Play the third track
    triggered3 = true;  // Set the flag to true to indicate it has triggered
  } else if (distance4 <= 2 && !triggered4) {
    stopAllSounds();  // Stop any currently playing sound
    myDFPlayer.play(4);  // Play the fourth track
    triggered4 = true;  // Set the flag to true to indicate it has triggered
  }

  // Check if no hand is detected near any sensor
  if (distance1 > 2) {
    triggered1 = false;  // Reset triggered flag
  }
  if (distance2 > 2) {
    triggered2 = false;  // Reset triggered flag
  }
  if (distance3 > 2) {
    triggered3 = false;  // Reset triggered flag
  }
  if (distance4 > 2) {
    triggered4 = false;  // Reset triggered flag
  }

  delay(50); // Adjust the delay as needed for the main loop
}
