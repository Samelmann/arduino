# Bewegungs-Reminder mit LED-Feedback (Frühes Arduino-Projekt)

> ⚠ Hinweis: Dieses Projekt stammt aus meiner Anfangszeit mit Arduino (Winter 2021/22 Lockdown).
> Der Code ist nicht optimal strukturiert und verwendet einfache, zum Teil naive Lösungen.
> Ich habe es trotzdem dokumentiert, weil es ein wichtiges persönliches Lernprojekt war und mein Interesse an Elektronik und eingebetteter Programmierung geweckt hat.

##  Idee

Ein kleines Gerät, das mich regelmäßig daran erinnert, aufzustehen oder mich zu bewegen.  
Sobald der Timer abgelaufen ist, aktivieren sich LEDs, und ich kann über Taster bestätigen, dass ich aktiv war.  
Das Ziel war, Sitzzeiten am Schreibtisch zu reduzieren und Bewegung spielerisch einzubauen.

##  Funktionen

- Drei Taster zur Bewegungsbestätigung (z. B. Kniebeuge, Hampelmann, Dehnung)
- Schlummerschalter zur zeitweisen Deaktivierung (z. B. bei Terminen)
- Jeder Taster hat eine zugeordnete LED (grün/rot) als visuelle Rückmeldung
- RGB-LED zur Statusanzeige (rot = Erinnerung aktiv, gelb = Schlummer)
- Belohnung durch Farbspiel nach erfolgreicher Bewegung
- Timer-Reset nach vollständiger Aktivitätsbestätigung

## Verwendete Hardware

- Arduino (z. B. Uno oder Nano)
- 3 Taster + 1 Schlummerschalter
- 3 grüne LEDs + 3 rote LEDs (jeweils für die Bewegungstaster)
- 1 RGB-LED für Statusanzeige
- Widerstände für LEDs und Taster (Pullup intern genutzt)
- ggf. kleines Gehäuse mit Steckbrett oder Lötboard

##  Was ich dabei gelernt habe

- Grundlegender Umgang mit digitalen Ein- und Ausgängen
- Verwendung von `INPUT_PULLUP` für Taster
- LED-Steuerung mit `digitalWrite()` und `analogWrite()`
- Erste Versuche mit Ablaufsteuerung über Timer
- Wie schwer es ist, "guten" Code zu schreiben – und wie wichtig Klarheit, Struktur und Wiederverwendbarkeit sind

## Mögliche Verbesserungen (heute)

- Statt `delay()` besser `millis()` verwenden für reaktionsfähigeren Code
- Debouncing der Taster (Hardware oder Software)
- Strukturierung des Codes in Funktionen oder Klassen
- Konfigurierbare Zeiten über EEPROM oder serielle Schnittstelle
- Logging der Aktivität (z. B. über SD-Karte oder Bluetooth)

##  Projektstruktur

```text
bewegungsreminder/
├── bewegungsreminder.ino     ← Hauptsketch
├── README.md                  ← Diese Datei
