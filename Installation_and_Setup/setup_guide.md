# Installation und Setup

### 1. Benötigte Software

- **Arduino IDE**: Version 1.8.19 oder höher.
- **AIStarter Bibliothek**: Installiere die Bibliothek über den Arduino Library Manager.

### 2. Hardwareanschlüsse

- Schließe die **Motoren**, **IR-Sensoren**, **Farbsensoren** und **Ultraschallsensoren** gemäß den Angaben der Dobot AI-Starter-Dokumentation an.
- Stelle sicher, dass alle Verbindungen sicher sind und dass die Sensoren richtig ausgerichtet sind.

### 3. Code hochladen

1. Öffne die **Arduino IDE**.
2. Lade die benötigten Bibliotheken, falls sie noch nicht installiert sind.
3. Öffne die `.ino`-Dateien für die jeweiligen Funktionalitäten (z.B. **main_code.ino** für Linienverfolgung oder Ultraschallsensoren).
4. Verbinde den **Dobot AI-Starter** mit deinem Computer und wähle den richtigen Port in der Arduino IDE.
5. Klicke auf **Hochladen**, um den Code auf den Roboter zu übertragen.

### 4. Testumgebung

- **Linienverfolgung**: Bereite einen Boden mit klar erkennbaren schwarzen Linien vor, denen der Roboter folgen kann.
- **Farberkennung**: Platziere farbige Objekte (z.B. Rot und Grün) auf dem Testpfad, um die Farberkennung zu testen.
- **Ultraschallsensoren**: Stelle Hindernisse auf, um die Funktion der Sensoren zu überprüfen.
