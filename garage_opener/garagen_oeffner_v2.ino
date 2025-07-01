/*
  SMS-gesteuerter Garagenöffner (Arduino MKR GSM)

  Dieses Projekt nutzt ein GSM-Modul, um per SMS einen elektrischen Garagenöffner zu steuern.
  Der Arduino ist mit einem Garagentor-Fernbedienungsmodul verbunden, das durch einen kurzen
  Stromimpuls (z. B. LOW für 2 Sekunden) ein Öffnungssignal an das Tor sendet – wie ein Knopfdruck.

  Der Öffnungsbefehl wird nur ausgeführt, wenn das per SMS empfangene Passwort in einer gespeicherten
  Passwortliste enthalten ist. Zusätzlich gibt es einen Testmodus ("Testegarage"), der den Öffnungsimpuls
  mehrfach sendet.

  Weitere Funktionen:
  - GSM-Verbindung wird überwacht und ggf. neu aufgebaut.
  - Automatischer Neustart nach ~23 Stunden.
*/


#include <MKRGSM.h>
#include "arduino_secrets.h"

// Zeitvariable für Debug-Ausgabe alle 5 Minuten
int zeit =0;

// Pin-Definitionen
// Reset-Pin für GSM-Modul
#define Reset 4           
// Ausgang zum Funksender (Garagenöffnung durch Impuls)
#define GARAGE 0          
// Immer eingeschalteter Pin (z. B. Stromversorgung)
#define ALWAYSON 6        

// GSM-PIN aus Geheimdaten-Datei
const char PINNUMBER[]= SECRET_PINNUMBER;

// Passworttabelle mit bis zu 20 gültigen SMS-Passwörtern
char passworttabelle[20][20]={"","zweitepasswort","sdfasds","danke4denkuchen","4da8fRFf","kjjhjj","kcuanld","ealivalE","xfenas","435GRSDR4",""};

// Für späteres Setzen eines neuen Passworts (wird aktuell nicht genutzt)
String neuespasswort = "setzeneu";


//initialisiere die library instanzen
GSM gsmAccess;
GSM_SMS sms;
GSMScanner scan;
//GSM gsm(1);

// Inhalt der empfangenen SMS
String message;


// Telefonnummer des Absenders
char senderNumber[20];



void setup() {
  // Serielle Verbindung starten
  Serial.begin(9600);

  // I/O-Pins initialisieren
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(GARAGE, OUTPUT);
  digitalWrite(GARAGE, HIGH);  // Relais aus (kein Impuls)
 
  pinMode(ALWAYSON, OUTPUT);
  digitalWrite(ALWAYSON, LOW); // Immer-an-Pin aktivieren
 


  digitalWrite(Reset, HIGH);
  delay(200);
  pinMode(Reset, OUTPUT);

  Serial.println("Garagenöffner startet...");

  Serial.println(ALWAYSON);
  Serial.print("pin ist an");

  
  // GSM-Verbindung aufbauen
  connectGSM();

  
  Serial.println("GSM initialisiert");
  Serial.println("Warte auf SMS-Nachrichten...");
  Serial.println();
  digitalWrite(LED_BUILTIN,LOW); // LED aus
}

void loop() {
  digitalWrite(ALWAYSON,LOW);  // Sicherstellen, dass Pin 6 dauerhaft aktiv bleibt

  
   int c;

  // Prüfen, ob eine neue SMS empfangen wurde
  if (sms.available()) {
    Serial.println("Nachricht empfangen von:");
    
    // Absendernummer lesen
    sms.remoteNumber(senderNumber,20);
    Serial.println(senderNumber);

     Serial.print("Nachricht: ");
    // SMS-Zeichenweise lesen und in message speichern
     while ((c=sms.read()) != -1) {
      Serial.print((char)c);
      message += (char)c;
     }

      //leere zeile ausgeben um verschiede nachrichten zu trennen
    Serial.println();

// Passwortvergleich: Nur bei gültigem Passwort öffnet sich die Garage
    for(int i=0;i<20;i++){
        if (message.equals(String(passworttabelle[i]))) {
          Serial.println("Garage wird geöffnet (gültiges Passwort)");
          digitalWrite(GARAGE, LOW);          // Stromimpuls senden (Relais einschalten)
          digitalWrite(LED_BUILTIN, HIGH);    // LED an als Feedback
          delay(2000);                        // 2 Sekunden senden
          digitalWrite(LED_BUILTIN, LOW);     // LED aus
          digitalWrite(GARAGE, HIGH);         // Relais aus, kein impuls mehr senden
        }
    }

    //testmodus: 4 mal taste druecken
    if(message.equals("Testegarage")){
        for(int i=0;i<3;i++){
          Serial.println("Test-Signal an Garagenöffner...");
          digitalWrite(GARAGE,LOW);
          digitalWrite(LED_BUILTIN,HIGH);
          delay(2000);
          digitalWrite(LED_BUILTIN,LOW);
          digitalWrite(GARAGE,HIGH);
          delay(1000);
        }
      }
    
    Serial.println("Ende der Nachricht\n");
    sms.flush();    // SMS löschen
    message = "";   // Nachricht zurücksetzen
  }
  if(gsmAccess.isAccessAlive()) {
  //Serial.println("verbindung aktiv!");   
  }
  else {
    Serial.println("Verbindung verloren – versuche Reconnect...");
    connectGSM();
  }
  delay(1000);
// Alle 5 Minuten Debug-Ausgabe
  if (millis() / 60000 > zeit) {
    Serial.print("Laufzeit (min): ");
    Serial.println(zeit);
    zeit += 5;
  }zeit=zeit+5;
}
  // Nach ca. 23h 20min Reset-Signal setzen
  if ((millis() / 1000) > 84000) {
    digitalWrite(Reset, LOW);
  }

// GSM verbinden (mit Wiederholversuchen)
void connectGSM() {
  boolean connected = false;

  while (!connected) {
    Serial.println("Verbinde mit GSM-Netz");
    if(gsmAccess.begin(PINNUMBER)==GSM_READY) {
      connected = true;
      Serial.println("GSM-Verbindung erfolgreich!");
      Serial.println("Netzbetreiber: " + scan.getCurrentCarrier());
    } else {
      Serial.println("Verbindung fehlgeschlagen – neuer Versuch in 1s");
      delay(1000);
    }
  }
}
