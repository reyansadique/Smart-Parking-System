#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// =====================================================
// SMART PARKING SYSTEM USING ULTRASONIC SENSORS
// ESP32 + 4 HC-SR04 + SSD1306 OLED + LEDs + Buzzer
// =====================================================

// ---------------- OLED ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1
);

// ---------------- Number of slots ----------------
#define TOTAL_SLOTS 4

// ---------------- Ultrasonic pins ----------------
// Slot 1
const int trigPins[TOTAL_SLOTS] = {
    5, 18, 19, 23
};

const int echoPins[TOTAL_SLOTS] = {
    17, 16, 27, 33
};

// ---------------- LED pins ----------------
const int greenLEDs[TOTAL_SLOTS] = {
    12, 13, 14, 25
};

const int redLEDs[TOTAL_SLOTS] = {
    26, 32, 2, 15
};

// ---------------- Buzzer ----------------
const int buzzerPin = 4;

// ---------------- Parking threshold ----------------
const float OCCUPIED_DISTANCE = 15.0;

// ---------------- Variables ----------------
float distances[TOTAL_SLOTS];

bool occupied[TOTAL_SLOTS];

int freeSlots = 0;
int occupiedSlots = 0;

// =====================================================
// SETUP
// =====================================================

void setup()
{
    Serial.begin(115200);

    // Initialize ultrasonic pins
    for (int i = 0; i < TOTAL_SLOTS; i++)
    {
        pinMode(trigPins[i], OUTPUT);
        pinMode(echoPins[i], INPUT);

        digitalWrite(trigPins[i], LOW);
    }

    // Initialize LEDs
    for (int i = 0; i < TOTAL_SLOTS; i++)
    {
        pinMode(greenLEDs[i], OUTPUT);
        pinMode(redLEDs[i], OUTPUT);

        digitalWrite(greenLEDs[i], LOW);
        digitalWrite(redLEDs[i], LOW);
    }

    // Initialize buzzer
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW);

    // Initialize I2C
    Wire.begin(21, 22);

    // Initialize OLED
    if (!display.begin(
            SSD1306_SWITCHCAPVCC,
            OLED_ADDRESS))
    {
        Serial.println("OLED initialization failed!");

        while (true)
        {
            delay(1000);
        }
    }

    // Initial OLED screen
    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(5, 10);
    display.println("SMART");

    display.setCursor(5, 35);
    display.println("PARKING");

    display.display();

    delay(2000);

    Serial.println();
    Serial.println("================================");
    Serial.println(" SMART PARKING SYSTEM");
    Serial.println(" ESP32 + 4 HC-SR04 Sensors");
    Serial.println("================================");
    Serial.println();
}

// =====================================================
// MEASURE DISTANCE
// =====================================================

float measureDistance(int trigPin, int echoPin)
{
    // Make sure trigger is LOW
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Send 10 microsecond trigger pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read echo pulse
    long duration = pulseIn(
        echoPin,
        HIGH,
        30000
    );

    // If no echo received
    if (duration == 0)
    {
        return 400.0;
    }

    // Convert microseconds to centimeters
    float distance = duration / 58.0;

    return distance;
}

// =====================================================
// READ ALL SENSORS
// =====================================================

void readSensors()
{
    freeSlots = 0;
    occupiedSlots = 0;

    for (int i = 0; i < TOTAL_SLOTS; i++)
    {
        distances[i] = measureDistance(
            trigPins[i],
            echoPins[i]
        );

        // Determine slot status
        if (distances[i] < OCCUPIED_DISTANCE)
        {
            occupied[i] = true;
            occupiedSlots++;
        }
        else
        {
            occupied[i] = false;
            freeSlots++;
        }

        // Small delay between sensors
        delay(30);
    }
}

// =====================================================
// CONTROL LEDs
// =====================================================

void updateLEDs()
{
    for (int i = 0; i < TOTAL_SLOTS; i++)
    {
        if (occupied[i])
        {
            // Occupied
            digitalWrite(redLEDs[i], HIGH);
            digitalWrite(greenLEDs[i], LOW);
        }
        else
        {
            // Available
            digitalWrite(redLEDs[i], LOW);
            digitalWrite(greenLEDs[i], HIGH);
        }
    }
}

// =====================================================
// BUZZER CONTROL
// =====================================================

void updateBuzzer()
{
    if (freeSlots == 0)
    {
        // Parking full
        tone(buzzerPin, 2000, 200);
    }
    else
    {
        noTone(buzzerPin);
    }
}

// =====================================================
// OLED DISPLAY
// =====================================================

void updateOLED()
{
    display.clearDisplay();

    // Title
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.println("SMART PARKING");

    // Slot 1
    display.setCursor(0, 15);
    display.print("S1: ");

    if (occupied[0])
        display.print("OCC");
    else
        display.print("FREE");

    // Slot 2
    display.setCursor(65, 15);
    display.print("S2: ");

    if (occupied[1])
        display.print("OCC");
    else
        display.print("FREE");

    // Slot 3
    display.setCursor(0, 30);
    display.print("S3: ");

    if (occupied[2])
        display.print("OCC");
    else
        display.print("FREE");

    // Slot 4
    display.setCursor(65, 30);
    display.print("S4: ");

    if (occupied[3])
        display.print("OCC");
    else
        display.print("FREE");

    // Free slots
    display.setCursor(0, 48);
    display.print("FREE: ");
    display.print(freeSlots);
    display.print("/");
    display.print(TOTAL_SLOTS);

    // Full indication
    if (freeSlots == 0)
    {
        display.setCursor(70, 48);
        display.print("FULL");
    }

    display.display();
}

// =====================================================
// SERIAL MONITOR
// =====================================================

void printStatus()
{
    Serial.println("--------------------------------");

    for (int i = 0; i < TOTAL_SLOTS; i++)
    {
        Serial.print("Slot ");
        Serial.print(i + 1);

        Serial.print(" | Distance: ");
        Serial.print(distances[i], 1);
        Serial.print(" cm");

        Serial.print(" | Status: ");

        if (occupied[i])
            Serial.println("OCCUPIED");
        else
            Serial.println("AVAILABLE");
    }

    Serial.print("Occupied Slots: ");
    Serial.println(occupiedSlots);

    Serial.print("Free Slots: ");
    Serial.println(freeSlots);

    Serial.println("--------------------------------");
}

// =====================================================
// MAIN LOOP
// =====================================================

void loop()
{
    // Read all ultrasonic sensors
    readSensors();

    // Update LEDs
    updateLEDs();

    // Update buzzer
    updateBuzzer();

    // Update OLED
    updateOLED();

    // Print information
    printStatus();

    delay(500);
}