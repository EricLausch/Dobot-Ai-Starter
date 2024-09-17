# Analyse der Dobot-Beispiele

Im Folgenden analysieren wir die Motorsteuerung und die auftretenden Probleme bei der Implementierung.

## Ursprünglicher Code zur Funktion der Motorsteuerung

Die Funktion `SET_MOTOR_SPEED()` steuert die Anpassung der Geschwindigkeit der beiden Motoren, `MOTORR` und `MOTORL`. Diese Funktion soll die Geschwindigkeit schrittweise erhöhen oder verringern, um abrupte Bewegungen zu verhindern.

Zu Beginn prüft die Funktion, ob die Zielgeschwindigkeit der Motoren bereits mit der letzten Zielgeschwindigkeit übereinstimmt.

- Wenn dies der Fall ist, wird keine Änderung vorgenommen. Andernfalls wird der aktuelle Zustand der Motoren gespeichert und eine lineare Beschleunigung durchgeführt.
- Dieser Prozess erfolgt über eine Schleife, in der die Geschwindigkeit in zehn Schritten angepasst wird, um eine sanfte Beschleunigung oder Verzögerung zu simulieren.
- Am Ende der Schleife werden die neuen Zielgeschwindigkeiten gespeichert, um sie für den nächsten Vergleich bereitzuhalten.

Der folgende Code zeigt diese Logik:

```cpp
void SET_MOTOR_SPEED(int MOTORR_tar_speed, int MOTORL_tar_speed)
{
    static int num = 0;
    static int MOTORL_last_tar_speed = 0;
    static int MOTORL_last_speed = 0;
    static int MOTORL_now_speed = 0;

    static int MOTORR_last_tar_speed = 0;
    static int MOTORR_last_speed = 0;
    static int MOTORR_now_speed = 0;

    if(MOTORR_tar_speed == MOTORR_last_tar_speed && MOTORL_tar_speed == MOTORL_last_tar_speed) {
        // Keine Anpassung notwendig
    }
    else {
        num = 0;
        MOTORL_last_speed = MOTORL_now_speed;
        MOTORR_last_speed = MOTORR_now_speed;
        while(num <= 10) {
            num++;
            MOTORL_now_speed += (MOTORL_tar_speed - MOTORL_last_speed) / 10;
            MOTORR_now_speed += (MOTORR_tar_speed - MOTORR_last_speed) / 10;
            AIStarter_SmartBotSetMotor(MOTORR, MOTORR_now_speed);
            AIStarter_SmartBotSetMotor(MOTORL, MOTORL_now_speed);
            delay(50);
        }
        MOTORR_last_tar_speed = MOTORR_tar_speed;
        MOTORL_last_tar_speed = MOTORL_tar_speed;
    }
}
```
## Probleme mit der Funktion `AIStarter_SmartBotSetMotor`

Die Funktion `AIStarter_SmartBotSetMotor(int port, int speed)` wird in den Beispielcodes von Dobot, wie `LineControl`, `ObstacleAvoid` und `ColorRecognition`, verwendet. Der serielle Monitor zeigte zwar die korrekten Werte für die Sensoren und die berechneten Geschwindigkeiten der Räder an, dennoch bewegte sich das Fahrzeug nicht wie vorgesehen.

| **Irstate**         | **speedLeftWheel [rpm]** | **speedRightWheel [rpm]** |
|---------------------|--------------------------|---------------------------|
| 63 = 0b111111        | 50                       | 50                        |
| 55 = 0b001100        | 47                       | 53                        |
| 54 = 0b110000        | 78                       | 22                        |
| 53 =  0b000011       | 22                       | 78                        |
| 52 =  0b100000       | 95                       | 05                        |
| 51 =  0b000001       | 05                       | 95                        |

*Table: Serial Monitor Ausgänge*

Der Zweck dieser Funktion besteht darin, die Geschwindigkeit der Motoren individuell anzupassen. Dabei sollte es möglich sein, unterschiedliche Geschwindigkeiten für `MOTORR` und `MOTORL` festzulegen, um eine präzise Steuerung des Roboters zu ermöglichen. In der Praxis zeigte sich jedoch, dass die Fahrzeuge immer mit einer konstanten Geschwindigkeit fuhren, unabhängig von den übergebenen Werten.

Dieses Verhalten deutet darauf hin, dass die interne Implementierung der Funktion entweder fehlerhaft ist oder dass die Motorsteuerung des AI-Starters nicht korrekt mit den übergebenen Geschwindigkeiten arbeitet. Da dies in mehreren Beispielcodes vorkam, haben wir alternative Ansätze zur Geschwindigkeitssteuerung entwickelt, um dieses Problem zu umgehen.

## Analyse der Funktion `getCurrentPos`

Die Funktion `getCurrentPos()` berechnet die aktuelle Position des Fahrzeugs relativ zur Linie, indem sie die Daten der sechs Infrarotsensoren (IR-Sensoren) auswertet.

Der Algorithmus summiert die Positionen der aktiven Sensoren, also der Sensoren, die eine Linie detektieren, und berechnet daraus die Abweichung des Fahrzeugs von der Mittellinie. Ein wichtiger Aspekt der Funktion ist die Verwendung eines Filters, um abrupte Änderungen zu vermeiden. Wenn kein Sensor eine Linie erkennt, wird die letzte bekannte Position des Fahrzeugs beibehalten, um ein plötzliches Abdriften zu verhindern. Dieser gleitende Durchschnitt sollte dazu beitragen, eine gleichmäßige Bewegung zu gewährleisten.

Die Funktion liefert einen Wert zurück, der die Position des Fahrzeugs relativ zur Linie darstellt und von der Steuerlogik verwendet wird, um die Richtung und Geschwindigkeit anzupassen.

```cpp
float getCurrentPos(const int irstate) {
    const float coeff = 0.7; 
    const int irPos[] = {-30, -18, -6, 6, 18, 30}; 
    static float lastPos;
    float curPos;
    float readPos;
    int total = 0;
    int irOffCnt = 0;

    for (int i = 0; i < IR_NUM; i++) {
        if (irstate & (1 << i)) {
            total += irPos[i]; 
            irOffCnt++;
        }
    }

    readPos = irOffCnt ? total / irOffCnt : lastPos;
    curPos = (1 - coeff) * lastPos + coeff * readPos;
    lastPos = curPos;

    return curPos;
}
```

## Analyse der Funktion `setCarSpeed`

Die Funktion `setCarSpeed()` passt die Geschwindigkeit der Räder des Fahrzeugs auf Basis der Abweichung von der Linie an. Diese Anpassung erfolgt mithilfe eines PID-Reglers, der für eine präzise Steuerung sorgt. Der Regler berechnet einen Korrekturwert, der die Geschwindigkeiten der Räder so beeinflusst, dass das Fahrzeug der Linie stabil folgen kann. Der PID-Regler trägt dazu bei, dass der Roboter sowohl kleine als auch größere Abweichungen effektiv ausgleicht und die Bewegung gleichmäßig bleibt.

```cpp
void setCarSpeed(const float curPos) {
    const int baseSpeed = 50; 
    const float kp = 1; 
    const float ki = 0.06; 
    const float kd = 0.0;
    const float errorsumLimit = 50;
    float error = curPos;
    static float lastError;
    static float errorsum;
    float errorChange;
    int speedLeftWheel;
    int speedRightWheel;
    int speedOffset;

    errorsum += error; 
    if (errorsum > errorsumLimit) errorsum = errorsumLimit;
    else if (errorsum < -errorsumLimit) errorsum = -errorsumLimit;

    errorChange = error - lastError;
    speedOffset = kp * error + ki * errorsum + kd * errorChange;
    lastError = error;

    speedLeftWheel = baseSpeed + speedOffset;
    speedRightWheel = baseSpeed - speedOffset;

    AIStarter_SmartBotSetMotor(MOTORL, speedLeftWheel);
    AIStarter_SmartBotSetMotor(MOTORR, speedRightWheel);
}
```
Der PID-Regler sorgt für eine dynamische Anpassung der Geschwindigkeit, indem er den Fehler, die Fehlerhistorie (integraler Anteil) und die Änderungsrate des Fehlers (differentieller Anteil) berücksichtigt.
