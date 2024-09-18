### Linien- und Farberkennungs Programm 

#### Lininenverfolgung
Das Programm liest die Werte von sechs Infrarotsensoren (IR), die an den Unterboden des AI-Starters angebracht sind, um die auf der Testmatte vorgegebenen schwarzen Linien zu verfolgen. Die Daten der IR-Sensoren werden bitweise in einer Variablen zusammengeführt, die den Zustand der Linie (ob erkannt oder nicht) für jeden Sensor speichert.

```cpp
int getIRState() {
    int irstate = 0;
    for (int i = 0; i < 6; i++) {
        irstate |= AIStarter_SmartBotGetIRModuleValue(i) << i;
    }
    return irstate;
}
```
Basierend auf dieser Information steuert das Programm die Bewegungen des AI-Starters, um die Linie präzise zu folgen. Unterschiedliche Bitmuster werden analysiert, um zu bestimmen, ob der Roboter nach links oder rechts ausweichen oder weiter geradeaus fahren muss.

Der folgende Codeblock zeigt die Hauptlogik der Linienverfolgung:
```cpp
// 0: Keine Schwarze Linie
// 1: Schwarze Linie
int speed = 150;

if (irstate == 0b001100) {  // Die mittleren Sensoren (IR3 & IR4) lesen die Schwarze Linie
    AIStarter_SmartBotSetMovment(FRONT, speed);  // geradeaus fahren
} else if (irstate == 0b000110) {  // Die rechten Sensoren (IR4 & IR5) lesen die Schwarze Linie
    AIStarter_SmartBotSetMovment(RIGHT, speed);  // rechts fahren
}
```
Hierbei handelt es sich um eine einfache Bedingung, bei der das IR-Modul erkennt, ob sich der Roboter exakt auf der Linie befindet (Muster: 0b001100), und ihn entsprechend steuert. Je nach Position wird die Richtung des Roboters angepasst.

#### Farberkennung
Um diese zu gewährleisten sind zwei Farbsensoren in den AI-Starter verbaut. Diese messen die Rot-, Grün-, Blauanteile anhand der Intensität des Lichts und vergleichen die gemessenen Werte mit gewissen Schwellwerten, wodurch das Programm erkennen kann, ob es sich um eine rote oder grüne Farbe handelt. Wenn eine der beiden Farben erkannt wird, gibt der Roboter ein akustisches Signal aus - zweimaliges Piepsen bei Rot, dreimaliges Piepsen bei Grün) - um das zu signalisieren.

Der folgende Code überprüft, ob die Farbe Rot erkannt wird:
```cpp
\begin{lstlisting}[language=ST]
int Threshold = 20;
redValue1: Der Farben Sensor 1 liest farbe "Rot"
redValue2: Der Farben Sensor 2 liest farbe "Rot"

greenValue1: Der Farben Sensor 1 liest farbe "Grün"
greenValue2: Der Farben Sensor 2 liest farbe "Grün"

blueValue1: Der Farben Sensor 1 liest farbe "Blau"
blueValue2: Der Farben Sensor 2 liest farbe "Blau"

 if ((redValue1 - greenValue1 > Threshold && redValue1 - blueValue1 > Threshold) &&
     (redValue2 - greenValue2 > Threshold && redValue2 - blueValue2 > Threshold)) {
    if (colorState != RED) {
        colorState = RED;
        Serial.println("Rot erkannt - Beep");
        // Tiefes Piepen als Signal
    }
}
\end{lstlisting}
```

Hierbei werden die Rot-, Grün- und Blauwerte der beiden Sensoren miteinander verglichen, um eine zuverlässige Farberkennung zu gewährleisten. Die Nutzung zweier Sensoren sorgt für eine erhöhte Genauigkeit und Stabilität bei der Farbdetektion.

#### Ausblick für Verbesserungen

**Verbesserungen bei der Linienverfolgung:** In der Praxis tritt das Problem auf, dass die Infrarotsensoren nicht immer konsistent reagieren. Selbst wenn sich das Fahrzeug vollständig auf einer weißen Fläche befindet, melden einige der Sensoren fälschlicherweise `1`, als ob sie eine schwarze Linie erkannt hätten. Dies führt zu Fehlfunktionen bei der Linienverfolgung, da der Roboter auf Basis dieser falschen Erkennung versucht zu korrigieren, obwohl keine Linie vorhanden ist. Ohne eine Möglichkeit, die Empfindlichkeit der Sensoren anzupassen, bleibt dieses Problem jedoch bestehen. (Oder man versucht die Sensoren manuel auszutauschen und befestigt neue.)

**Probleme bei der Farberkennung:** Auch die Farbsensoren des AI-Starters arbeiten nicht immer zuverlässig. Bei der Fahrt kann es passieren, dass die Sensoren die Farben, Rot oder Grün nicht richtig erkennen, bzw. es einfach nicht anzeigen. Da dieses Problem hauptsächlich während der Fahrt auftritt, könnte eine möglicherweise zu kurze Erfassungszeit der Sensoren die Ursache davon sein. Lösungsansätze dafür sind, die Sensordaten häufiger auszulesen und wenn möglich die Geschwindigkeit des Fahrzeugs weiter zu reduzieren. 
