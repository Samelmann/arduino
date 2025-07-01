


#define schaltereins 2
#define schalterzwei 3
#define schalterdrei 4
#define schalterschlummer 5
#define schalteraus A0
#define ledeinsg 6
#define ledeinsr A1
#define ledzweig 7
#define ledzweir 8
#define leddreig 12
#define leddreir 13
#define ledrgbred 9
#define ledrgbgreen 10
#define ledrgbyellow 11
//1 ist rot
//2 ist minus
//3 ist grun
//4 ist blue
int vollezeit = 52*60*2; // hier muss die zeit angepasst werden in Sekunden!
int schlummerzeit=5*60*2; //hier muss die schlummerzeit angepasst werden
int schalterstellung =0;
int timer =vollezeit;
int zahler=3;
int schlummern = 0;
bool schaltertest = true;
int schlummerstellung = 0;
bool erstemalnull=true;
bool booleins=true;
bool boolzwei=true;
bool booldrei=true;

void setup() {
  if (false){//falls getestet wird hier true reinmachen
    vollezeit=5;
    schlummerzeit=4;
    timer=vollezeit;
  }
  // put your setup code here, to run once:
Serial.begin(9600);
//while(!Serial){ }
Serial.println(timer+" Timerzeit");
pinMode(ledeinsg,OUTPUT);
pinMode(ledeinsr,OUTPUT);
pinMode(ledzweig,OUTPUT);
pinMode(ledzweir,OUTPUT);
pinMode(leddreig,OUTPUT);
pinMode(leddreir,OUTPUT);
pinMode(ledrgbred,OUTPUT);
pinMode(ledrgbgreen,OUTPUT);
pinMode(ledrgbyellow,OUTPUT);
pinMode(schaltereins,INPUT_PULLUP);
pinMode(schalterzwei,INPUT_PULLUP);
pinMode(schalterdrei,INPUT_PULLUP);
pinMode(schalterschlummer,INPUT_PULLUP);
//schalter aus ist A0 also um alles auszumachen!
pinMode(A0,INPUT);
Serial.print("Die Timer zeit ist auf: ");
Serial.print(vollezeit/(60*2));
Serial.println(" Minuten");
if (digitalRead(A0)==HIGH){
  Serial.println("Das System ist aus! schalter A0 ist aus");
}
}

void loop() {
  // put your main code here, to run repeatedly:

if (timer == (vollezeit-1)) {
  Serial.println("Timer begint von vorne.");
  schalterstellung = digitalRead(schaltereins);
}
if (timer == 0) {
  delay(1000);
  schlummern=0;
  if (erstemalnull){
    //hier soll wenn der Timer auf 0 ist nur einmal reingegangen werden!
    Serial.println("Timer ist null!");
    schlummerstellung=digitalRead(schalterschlummer);
    erstemalnull=false;
    digitalWrite(ledrgbred,HIGH);
    Serial.println("ROT AN");
    if(booleins){
      digitalWrite(ledeinsr,HIGH);
    }else{
      digitalWrite(ledeinsg,HIGH);
    }
    if(boolzwei){
      digitalWrite(ledzweir,HIGH);
    }else{
      digitalWrite(ledzweig,HIGH);
    }
    if(booldrei){
      digitalWrite(leddreir,HIGH);
    }else{
      digitalWrite(leddreig,HIGH);
    }
  }
  if (schlummerstellung != digitalRead(schalterschlummer)){
    timer=schlummerzeit;
    lichteraus();
    if(!booleins){
      digitalWrite(ledeinsg,HIGH);}
      if(!boolzwei){
      digitalWrite(ledzweig,HIGH);}
       if(!booldrei){
      digitalWrite(leddreig,HIGH);}
    erstemalnull=true;
    schlummern=1;
    Serial.println("schlummern wurde gedrückt");
  } else {
    pruefeschalter();
  }
}
if(schlummern==1){
  analogWrite(ledrgbyellow,10);
  schlummern=2;
  pruefeschalter();
}else if(schlummern==2){
  digitalWrite(ledrgbyellow,LOW);
  schlummern=1;
  pruefeschalter();
}
if(timer !=0 && digitalRead(schalteraus)==LOW){
  delay(500);
  timer=timer-1;
  digitalWrite(ledrgbyellow,LOW);  
}else if(digitalRead(schalteraus)==HIGH) {
  analogWrite(ledrgbred,127);
  analogWrite(ledrgbgreen,0);
  analogWrite(ledrgbyellow,100);
  delay(1000);
}
if(digitalRead(schalteraus)==LOW && timer != 0){
  digitalWrite(ledrgbyellow,LOW);
  digitalWrite(ledrgbred,LOW);
  digitalWrite(ledrgbgreen,LOW);
}
Serial.println(timer);
}

void pruefeschalter(){
  if (digitalRead(schaltereins) != schalterstellung && booleins){
        Serial.println("schalter 1 wurde betätigt");
        digitalWrite(ledeinsr,LOW);
        digitalWrite(ledeinsg,HIGH);
        zahler=zahler-1;
        booleins=false;
      }
      if (digitalRead(schalterzwei) != schalterstellung && boolzwei){
        Serial.println("schalter 2 wurde betätigt");
        digitalWrite(ledzweir,LOW);
        digitalWrite(ledzweig,HIGH);
        zahler=zahler-1;
        boolzwei=false;
      }
      if (digitalRead(schalterdrei) != schalterstellung && booldrei){
        Serial.println("schalter 3 wurde betätigt");
        digitalWrite(leddreir,LOW);
        digitalWrite(leddreig,HIGH);
        zahler=zahler-1;
        booldrei=false;
      }
      if (zahler==0){
      Serial.println("alle knöpfe wurden gedrueckt");
      farbenspiel();
      booleins=true;
      boolzwei=true;
      booldrei=true;
      timer=vollezeit;
      zahler=3;
      erstemalnull=true;
      schlummern=0;
     }
}

void lichteraus(){
  digitalWrite(ledeinsg,LOW);
  digitalWrite(ledzweig,LOW);
  digitalWrite(leddreig,LOW);
  digitalWrite(ledeinsr,LOW);
  digitalWrite(ledzweir,LOW);
  digitalWrite(leddreir,LOW);
  digitalWrite(ledrgbred,LOW);
  digitalWrite(ledrgbgreen,LOW);
  digitalWrite(ledrgbyellow,LOW);
}
void lichterang(){
  digitalWrite(ledeinsg,HIGH);
  digitalWrite(ledzweig,HIGH);
  digitalWrite(leddreig,HIGH);
  digitalWrite(ledrgbgreen,HIGH);
}
void farbenspiel(){
   for(int i=0;i<3;i++){
        lichterang();
        delay(200);
        lichteraus();
        delay(200);
      }
    int red =255;
    int blue =0;
    int green =0;
   for(int i=0;i<255;i++){
    red -=1;
    green +=1;
    analogWrite(ledrgbred,red);
    analogWrite(ledrgbgreen,green);
    delay(5);
   }
   for(int i=0;i<255;i++){
    green -=1;
    blue +=1;
    analogWrite(ledrgbyellow,blue);
    analogWrite(ledrgbgreen,green);
    delay(5);
   }
   for(int i=0;i<255;i++){
    red +=1;
    blue -=1;
    analogWrite(ledrgbred,red);
    analogWrite(ledrgbyellow,blue);
    delay(5);
   }
   for(int i=0;i<255;i++){
    red -=1;
    green +=1;
    analogWrite(ledrgbred,red);
    analogWrite(ledrgbgreen,green);
    delay(5);
   }
   for(int i=0;i<255;i++){
    green -=1;
    blue +=1;
    analogWrite(ledrgbyellow,blue);
    analogWrite(ledrgbgreen,green);
    delay(5);
   }
   for(int i=0;i<255;i++){
    red +=1;
    blue -=1;
    analogWrite(ledrgbred,red);
    analogWrite(ledrgbyellow,blue);
    delay(5);
   }
   lichteraus();
}
