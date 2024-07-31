#define led 6
String MorseCode[] = {
".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", // A-I
".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R 
"...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.." // S-Z
};
String output="";
void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(9600);
} 

void loop() {
  if(Serial.available()>0){
     String input=Serial.readStringUntil('\n');
     input.toUpperCase();
     Serial.println(input);

     for (int i = 0; i < input.length(); i++) {
      if (input[i] >= 'A' && input[i] <= 'Z') {
        output+= MorseCode[input[i] - 'A'];
        output+=' ';
      }
      else{//space
        output+=' ';
      }
    }
    // Serial.println(output);
    delay(2500);
    Transsimation();
    output="";
    
  }

}
void Transsimation(){
  for(int i=0;i<output.length();i++){
     if(output[i]=='.'){
      digitalWrite(led,HIGH);
      delay(200);
      digitalWrite(led,LOW);
      delay(400);
     }
     else if(output[i]=='-'){
      digitalWrite(led,HIGH);
      delay(500);
      digitalWrite(led,LOW);
      delay(400);
     }
      else if((i==output.length()-1&&output[i]==' ')||(output[i]==' '&&output[i+1]!=' ' )){
      digitalWrite(led,HIGH);
      delay(900);
      digitalWrite(led,LOW);
      delay(1000);
     }
      else if(output[i]==' '&&output[i+1]==' '){
      digitalWrite(led,HIGH);
      delay(1000);
      digitalWrite(led,LOW);
      delay(1200);
     }
    
       
   }
}
