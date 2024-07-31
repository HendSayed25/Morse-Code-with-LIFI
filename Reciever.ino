#define LDR 5
String MorseCode[] = {
".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", // A-I
".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R 
"...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." // S-Z
};
void setup() {
  pinMode(LDR,INPUT);
  Serial.begin(9600);

}//-. .- -.. .-
String Final_Output="",Output="";

void loop() {
 // int duration=analogRead(LDR);
  unsigned long duration=pulseIn(LDR,HIGH,2000000);
 // if(duration==0)return;
  
  //Serial.println(duration);
  if(duration>=500000&&duration<600000){//.
     Output+='-';
     //Serial.println(Output);
    
   }
   else if(duration>=200000&&duration<=400000){//-
    Output+='.';
   // Serial.println(Output);
   }
  
   else if(duration>=600000&&duration<=910000) {// one space
    for(int i=0;i<26;i++){
      if(Output==MorseCode[i]){
        Final_Output+=char('A'+i);
        Output="";
        break;
      }
    }
   // Serial.println(Final_Output);
    
  }
    
  else if(duration>920000){//two space
    for(int i=0;i<26;i++){
      if(Output==MorseCode[i]){
        Final_Output+=char('A'+i);
        Output="";
        break;
      }
    }
    Final_Output+=' '; 
        Serial.println(Final_Output);
 
  }
    if(duration==0){
      Serial.println(Final_Output);
    }
  }
