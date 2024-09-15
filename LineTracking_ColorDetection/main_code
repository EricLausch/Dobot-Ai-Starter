#include <AIStarter.h>

#define BEEP_PIN 9  // Pin für den Buzzer
#define Threshold 20

enum ColorState {
    NONE,
    RED,
    GREEN
};

ColorState colorState = NONE;

void setup() {
    AIStarter_SmartBotInit();
    Serial.begin(9600);
}

int getIRState() {
    int irstate = 0;
    for (int i = 0; i < 6; i++) {
        irstate |= AIStarter_SmartBotGetIRModuleValue(i) << i;
    }
    return irstate;
}

void colorCheck() {
    // Farbwerte für beide Sensoren lesen
    int redValue1 = AIStarter_SmartBotGetColorSenor(COLORSENOR1, RCOLOR);
    int greenValue1 = AIStarter_SmartBotGetColorSenor(COLORSENOR1, GCOLOR);
    int blueValue1 = AIStarter_SmartBotGetColorSenor(COLORSENOR1, BCOLOR);

    int redValue2 = AIStarter_SmartBotGetColorSenor(COLORSENOR2, RCOLOR);
    int greenValue2 = AIStarter_SmartBotGetColorSenor(COLORSENOR2, GCOLOR);
    int blueValue2 = AIStarter_SmartBotGetColorSenor(COLORSENOR2, BCOLOR);

    // Rot-Erkennung mit beiden Sensoren und Schwellenwert
    if ((redValue1 - greenValue1 > Threshold && redValue1 - blueValue1 > Threshold) &&
        (redValue2 - greenValue2 > Threshold && redValue2 - blueValue2 > Threshold)) {
        if (colorState != RED) {
            colorState = RED;
            Serial.println("Rot erkannt - Beep");

            // Tiefer Ton (2-mal)
            for (int i = 0; i < 2; i++) {
                digitalWrite(BEEP, HIGH);
                delay(300);  // 300 ms Ton
                digitalWrite(BEEP, LOW);
                delay(300);  // Pause
            }
        }
    }
    // Grün-Erkennung mit beiden Sensoren und Schwellenwert
    else if ((greenValue1 - redValue1 > Threshold && greenValue1 - blueValue1 > Threshold) &&
             (greenValue2 - redValue2 > Threshold && greenValue2 - blueValue2 > Threshold)) {
        if (colorState != GREEN) {
            colorState = GREEN;
            Serial.println("Grün erkannt - Beep");

            // Hoher Ton (3-mal)
            for (int i = 0; i < 3; i++) {
                digitalWrite(BEEP, HIGH);
                delay(300);  // 300 ms Ton
                digitalWrite(BEEP, LOW);
                delay(300);  // Pause
            }
        }
    }
    else {
        colorState = NONE;
    }
}

void linieVerfolgung(int irstate) {
    int speed = 130;  

//Return 1: Black line detected
// Return 0: No black line detected, light on

    // Line tracking logic
    if (irstate == 0b001100) {
        AIStarter_SmartBotSetMovment(FRONT, speed);
    }
    else if (irstate == 0b000110) {
        AIStarter_SmartBotSetMovment(RIGHT, speed);
    }
    else if (irstate == 0b001110) {
        AIStarter_SmartBotSetMovment(RIGHT, speed); 
    }
    else if (irstate == 0b000111) {
        AIStarter_SmartBotSetMovment(RIGHT, speed);
    }
    else if (irstate == 0b011000) {
        AIStarter_SmartBotSetMovment(LEFT, speed);
    }
    else if (irstate == 0b111000) {
        AIStarter_SmartBotSetMovment(LEFT, speed);  
    }
    else if (irstate == 0b111100) {
        AIStarter_SmartBotSetMovment(LEFT, speed);
    }
    else if (irstate == 0b000011) {
        AIStarter_SmartBotSetMovment(RIGHT, speed);
    }
    else if (irstate == 0b110000) {
        AIStarter_SmartBotSetMovment(LEFT, speed);
    }
    else if (irstate == 0b000000) {
        AIStarter_SmartBotSetMovment(BACK, 90); 
        
   /* } else if (irstate == 0b000010) {
        AIStarter_SmartBotSetMovment(RIGHT, 120); 
        
    } else if (irstate == 0b010000) {
        AIStarter_SmartBotSetMovment(LEFT, 120); 
        
    } */ } else if (irstate == 0b000001) {
        AIStarter_SmartBotSetMovment(RIGHT, 100);   
        
    } else if (irstate == 0b100000) {
        AIStarter_SmartBotSetMovment(LEFT, 100);
        
    }/* else if (irstate == 0b100010) {
        AIStarter_SmartBotSetMovment(LEFT, 100);  
 
    } else if (irstate == 0b010001) {
        AIStarter_SmartBotSetMovment(RIGHT, 100);  
     } */
    else if (irstate == 0b111111) {
        AIStarter_SmartBotSetMovment(FRONT, 70);
    } else {
        AIStarter_SmartBotSetMovment(BACK, 70);  
    }
}

void loop() {
    // Get the current infrared sensor states
    int irstate = getIRState();

    // Use the infrared sensor data to track the line
    linieVerfolgung(irstate);

    // Check for color and trigger beep if necessary
    colorCheck();

    // Small delay to stabilize the loop
    delay(100);
}
