### Entwürfe für die Objektvermeidung

Nach der erfolgreichen Implementierung der Linien- und Farberkennung wandten wir uns der Entwicklung eines Programms zur Hindernisvermeidung für den AI-Starter zu. Hierbei nutzen wir die Ultraschallsensoren des Roboters, um Hindernisse zu erkennen und angemessen darauf zu reagieren.

**Objektvermeidung:** Mithilfe von drei Ultraschallsensoren (links, rechts und vorne) werden die Abstände zu potenziellen Hindernissen gemessen. Überschreitet der gemessene Abstand einen vordefinierten Schwellenwert (`DIS`), entscheidet das Programm automatisch, ob der Roboter nach links, rechts oder zurückfahren muss. Falls keine Hindernisse erkannt werden, setzt der Roboter seine Fahrt nach vorne fort. Die Funktion `avoidObstacles()` bildet das Herzstück dieser Entscheidungslogik.

Der folgende Codeblock zeigt die Logik der Hindernisvermeidung:

```cpp
#define DIS 10
void avoidObstacles() {
    float distanceLeft = AIStarter_SmartBotGetSonar(SONAR3);
    float distanceRight = AIStarter_SmartBotGetSonar(SONAR1);
    float distanceFront = AIStarter_SmartBotGetSonar(SONAR2);

    if (distanceFront < DIS) {
        AIStarter_SmartBotSetMovment(BACK, 100);
        delay(1000);
    } else if (distanceLeft < DIS) {
        AIStarter_SmartBotSetMovment(RIGHT, 100);
        delay(1000);
    } else if (distanceRight < DIS) {
        AIStarter_SmartBotSetMovment(LEFT, 100);
        delay(1000);
    } else {
        AIStarter_SmartBotSetMovment(FRONT, 100);
    }
}
```
Durch diese Bedingungen stellt das Programm sicher, dass der Roboter in Situationen mit nahegelegenen Hindernissen flexibel reagiert. Es wird stets überprüft, ob links oder rechts mehr Platz zum Ausweichen vorhanden ist, und daraufhin die Fahrtrichtung angepasst. Falls keine Hindernisse vorliegen, setzt der Roboter seine Vorwärtsbewegung fort.
