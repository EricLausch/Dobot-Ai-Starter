#include <AIStarter.h>

#define DIS 15

void setup() {
    Serial.begin(115200);
    AIStarter_SmartBotInit();
}

void avoidObstacles() {
    float distanceLeft = AIStarter_SmartBotGetSonar(SONAR3);
    float distanceRight = AIStarter_SmartBotGetSonar(SONAR1);
    float distanceFront = AIStarter_SmartBotGetSonar(SONAR2);

    if (distanceFront < DIS) { // der vordere Sensor lest ein Abstand mehr als DIS
        AIStarter_SmartBotSetMovment(BACK, 100);
        delay(1000);
    } else if (distanceLeft < DIS) { // der linke Sensor lest ein Abstand mehr als DIS
        AIStarter_SmartBotSetMovment(RIGHT, 100);
        delay(1000);
    } else if (distanceRight < DIS) {
        AIStarter_SmartBotSetMovment(LEFT, 100); // der rechte Sensor lest ein Abstand mehr als DIS
        delay(1000);
    } else if (distanceLeft < distanceRight) {
        AIStarter_SmartBotSetMovment(RIGHT, 100);
    } else {
        AIStarter_SmartBotSetMovment(LEFT, 100);
    }

    // Keine Obstacles
    if (distanceFront >= DIS && distanceLeft >= DIS && distanceRight >= DIS) {
        AIStarter_SmartBotSetMovment(FRONT, 100);
    }
}

void loop() {
    avoidObstacles();
    delay(500);
}
