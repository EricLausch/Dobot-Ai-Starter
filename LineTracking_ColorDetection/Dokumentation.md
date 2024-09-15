### Linien- und Farberkennungs Programm 

Zuerst widmetetn wir uns dem Problem der Linien und Farberkennung. Dafür haben wir nach ausgiebiger Recherche, unter anderem inspiriert durch das Arduino-Projekt „Line Following Robot“ (siehe https://projecthub.arduino.cc/lightthedreams/line-following-robot-34b1d3) ein Programm entwickelt, dass auf den Funktionen der von Dobot bereitgestellten Bibliothek aufbaut. Dieses Programm kombiniert die Erkennung von Linien mittels Infrarotsensoren mit der Detektion von Farben, um eine Navigation zu ermöglichen.

**Linienverfolgung:** Das Programm liest die Werte von sechs Infrarotsensoren (IR), die an den Unterboden des AI-Starters angebracht sind, um die auf der Testmatte vorgegebenen schwarzen Linien zu verfolgen. Die Daten der IR-Sensoren werden bitweise in einer Variablen zusammengeführt, die den Zustand der Linie (ob erkannt oder nicht) für jeden Sensor speichert. Basierend auf dieser Information steuert das Programm die Bewegungen des AI-Starters, um die Linie präzise zu folgen. Unterschiedliche Bitmuster werden analysiert, um zu bestimmen, ob der Roboter nach links oder rechts ausweichen oder weiter geradeaus fahren muss.

Der folgende Codeblock zeigt die Hauptlogik der Linienverfolgung:

```cpp
if (irstate == 0b001100) {
    AIStarter_SmartBotSetMovment(FRONT, speed);
} else if (irstate == 0b000110) {
    AIStarter_SmartBotSetMovment(RIGHT, speed);
}
```

Hierbei handelt es sich um eine einfache Bedingung, bei der das IR-Modul erkennt, ob sich der Roboter exakt auf der Linie befindet (Muster: '0b001100'), und ihn entsprechend steuert. Je nach Position wird die Richtung des Roboters angepasst.

**Farberkennung:** Zur Farberkennung verwendet der AI-Starter zwei Farbsensoren. Diese sind in der Lage, die Intensität der Rot-, Grün- und Blauanteile des erfassten Lichts zu messen. Durch Vergleich der Farbsensorwerte mit definierten Schwellenwerten kann das Programm erkennen, ob eine rote oder grüne Farbe vorliegt. Wird eine Farbe erkannt, gibt der Roboter akustische Signale aus (z.B. zweimaliges Piepen bei Rot, dreimaliges Piepen bei Grün), um den Benutzer über die erkannte Farbe zu informieren.

Der folgende Code überprüft, ob die Farbe Rot erkannt wird:

```cpp
if ((redValue1 - greenValue1 > Threshold && redValue1 - blueValue1 > Threshold) &&
    (redValue2 - greenValue2 > Threshold && redValue2 - blueValue2 > Threshold)) {
    if (colorState != RED) {
        colorState = RED;
        Serial.println("Rot erkannt - Beep");
        // Tiefes Piepen als Signal
    }
}

Hierbei werden die Rot-, Grün- und Blauwerte der beiden Sensoren miteinander verglichen, um eine zuverlässige Farberkennung zu gewährleisten. Die Nutzung zweier Sensoren sorgt für eine erhöhte Genauigkeit und Stabilität bei der Farbdetektion.

