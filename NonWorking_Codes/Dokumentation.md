
### Nicht-funktionierende Ansätze und Herausforderungen

Im Rahmen unseres Projekts haben wir zunächst die offiziellen **Guideline- und Example Codes** des Dobot AI-Starters verwendet, um die grundlegenden Funktionen wie **Linienverfolgung**, **Farberkennung** und **Ultraschallsensoren** zu implementieren. Leider führten diese Ansätze nicht zu den gewünschten Ergebnissen.

#### 1. Überblick über die verwendeten Guideline-Codes

Die offiziellen Beispielcodes aus der **Dobot AI-Starter Guideline** sollten dem Roboter ermöglichen, Linien zu folgen, Farben zu erkennen und auf Hindernisse zu reagieren. Diese Codes waren der Ausgangspunkt unserer Entwicklung und halfen uns, die grundlegende Funktionsweise des Systems zu verstehen.

#### 2. Analyse der Herausforderungen

Bei der Implementierung stießen wir auf mehrere technische Schwierigkeiten, die dazu führten, dass diese Codes nicht wie vorgesehen funktionierten. Zu den größten Herausforderungen gehörten:

- **Geschwindigkeitskontrolle**: Die Anpassung der Geschwindigkeit funktionierte nicht zuverlässig, was dazu führte, dass der Roboter zu schnell fuhr und die Linie oft nicht richtig erkannte.
- **Farberkennung**: Die Sensoren konnten nicht zwischen den Farben Rot und Grün unterscheiden, was auf eine unzureichende Kalibrierung und falsche Schwellenwerte zurückzuführen war.
- **Ultraschallsensoren**: Die Reaktion auf Hindernisse war oft zu langsam, was dazu führte, dass der Roboter Objekte entweder zu spät oder gar nicht erkannte.

#### 3. Schlussfolgerung

Die Analyse dieser nicht-funktionierenden Ansätze zeigte uns, dass wir eigene Lösungen entwickeln mussten, um die gewünschten Funktionen stabil und zuverlässig zu implementieren. Auf dieser Grundlage haben wir unsere eigenen Algorithmen entwickelt, die im nächsten Abschnitt beschrieben werden.
