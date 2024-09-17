# Installation und Setup

## Hardwareanschlüsse

Im GitHub-Repository [Dobot AI-Starter](https://github.com/michi-bot/Dobot-Ai-Starter/raw/main/Installation_and_Setup/AI-Starter_User_Guide.pdf) ist eine detaillierte Anleitung zum Aufbau der Hardware zu finden.

## Benötigte Software

Für die Programmierung des Dobot AI-Starters wird die **Arduino IDE** verwendet. In diesem Projekt wurde die Version 1.8.19 eingesetzt, welche die Programmiersprache Arduino C unterstützt.

Um die Bibliothek für den AI-Starter zu installieren und das System korrekt zu konfigurieren, sind die folgenden Schritte zu befolgen:

- Installiere und öffne **Arduino IDE** und navigiere zu `Werkzeuge → Bibliotheken verwalten`.
- Suche im Bibliotheksverwalter über die Suchleiste nach `AIStarter` und installiere die entsprechende Bibliothek.
- Schließe den **AI-Starter** an den PC an.
- Gehe erneut zu `Werkzeuge → Board` und wähle `Arduino Mega or Mega2560` aus.
- Wähle im Menü `Werkzeuge → Prozessor` ebenfalls `Arduino Mega or Mega2560` aus.
- Gehe zu `Werkzeuge → Port` und wähle den entsprechenden COM-Port für `Arduino Mega or Mega2560`.
- Öffne den `seriellen Monitor` über `Werkzeuge → Serieller Monitor`, um Sensordaten auszulesen. Dies funktioniert nur, wenn der AI-Starter mit der Arduino IDE verbunden ist.

## Code Implementierung

Im GitHub-Repository [Dobot AI-Starter](https://github.com/michi-bot/Dobot-Ai-Starter/tree/main) sind die von uns beschriebenen Programme und die Beispielcodes zu finden.

- Kopiere oder lade den Code in die **Arduino IDE**.
- Klicke oben links auf das Symbol mit dem **grünen Haken**, um den Code zu **kompilieren** bzw. **überprüfen**.
- Wenn der Code erfolgreich kompiliert wurde, klicke auf das Symbol mit dem **grünen Pfeil**, um das Programm auf den **AI-Starter** **hochzuladen**.


## Testumgebung

Jetzt ist der AI-Starter fast einsatzbereit. Um eine geeignete Testumgebung herzustellen, wird die von Dobot bereitgestellte Umgebungsmatte verwendet. Dabei handelt es sich um ein Plakat, auf dem die Linien und Farbmarkierungen für den Dobot aufgedruckt sind.

Um das Objektvermeidungs-Programm zu testen, wird empfohlen, Wände um die Testmatte zu platzieren, um geeignete Hindernisse zu simulieren. Dabei sollten die Wände so gestaltet sein, dass sie von den Sensoren des Dobot zuverlässig erkannt werden.
