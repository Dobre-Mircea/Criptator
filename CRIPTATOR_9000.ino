
#include <LiquidCrystal_I2C.h>
#include <cstring>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);    //declaration
LiquidCrystal_I2C lcd2(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);   //of the lcd's

  int algorithm = 0;   //agorithm determins which alg this will run
   char input[] ={"                "};
  char output[] ={"                "};
  int letters = 0;


  long mod26(long a)
  {
    return (a%26+26)%26;
  }

  int li (char l)
  {
    return l - 'A';
  }

  int indexof (char* array, int find)
  {
    return strchr(array, find) - array;
  }

 char Keyboard()
 {
  char key;
  int n = 0, i;
  while(n == 0){
    for(i = 22; i <= 52; i = i + 2)
      if(digitalRead(i) == 1){        //Checks if any of the pins of the keyboard
        n = i;                        //are connected to 5V and if it find one
      }                               //makes n the adress of that pin
    if(n == 0)
      for(i = 23; i <= 41; i = i + 2)
        if(digitalRead(i) == 1){
          n = i;
        }
  }
    if(n != 0)        //Determins which letter is assigned to the pressed pin
    {
      switch(n)
      {
        case 23:
          key = 'Q';
          break;
        case 25:
          key = 'W';
          break;
        case 27:
          key = 'E';
          break;
        case 29:
          key = 'R';
          break;
        case 31:
          key = 'T';
          break;
        case 33:
          key = 'Y';
          break;
        case 35:
          key = 'U';
          break;
        case 37:
          key = 'I';
          break;
        case 39:
          key = 'O';
          break; 
        case 41:
          key = 'P';
          break;
          
          //////// 
          
        case 22:
          key = 'A';
          break;
        case 24:
          key = 'S';
          break;
        case 26:
          key = 'D';
          break;
        case 28:
          key = 'F';
          break;
        case 30:
          key = 'G';
          break;
        case 32:
          key = 'H';
          break;
        case 34:
          key = 'J';
          break;
        case 36:
          key = 'K';
          break;
        case 38:
          key = 'L';
          break;

          //////
          
        case 40:
          key = 'Z';
          break;
        case 42:
          key = 'X';
          break;        
        case 44:
          key = 'C';
          break;
        case 46:
          key = 'V';
          break;
        case 48:
          key = 'B';
          break;
        case 50:
          key = 'N';
          break;
        case 52:
          key = 'M';
          break;     
        }
      }
      return key;
  }


void AddPrint(char inpKey, char outKey)
{
  int i;
    if(letters < 16)
    {
      input[letters] = inpKey;
      output[letters] = outKey;
      letters++;  
    }
    else
    {
        for(i = 0; i < 15; i++)
          input[i] = input[i + 1];
        input[15] = inpKey; 
        for(i = 0; i < 15; i++)
          output[i] = output[i + 1];
        output[15] = outKey; 
    }
   lcd.clear();
   lcd2.clear();
   lcd.print("  -# Input #-  ");
   lcd.setCursor(0, 1);
   lcd.print(input);
   lcd2.print("  -@ Output @- ");
   lcd2.setCursor(0, 1);
   lcd2.print(output);
}



void setup() 
{
  int i;
  Serial.begin(9600);
  Serial.print("!!!!!!!!!!\n");
  for(i = 22; i <= 52; i = i + 2)   //Turns all of the pins 
    pinMode(i, INPUT);              //of the keyboard to input
  for(i = 23; i <= 41; i = i + 2)   //26 pins in total
    pinMode(i, INPUT);
    
  pinMode(2, INPUT);    //Option key 1
  pinMode(3, INPUT);    //Option key 2  //Turns the option keys into inputs
  pinMode(4, INPUT);    //Option key 3
  pinMode(5, OUTPUT);   //Option led 1
  pinMode(6, OUTPUT);   //Option led 2  //Turns the option leds into outputs
  pinMode(7, OUTPUT);   //Option led 3
  
   for(i = 7; i >= 5; i--)
  {
    digitalWrite(i, HIGH);
    delay(200);           //Flashing all the option leds on startup
    digitalWrite(i, LOW);
   }
  
  
  lcd.begin(16,2);
  lcd.backlight();    //Turns on both lcds and 'starts' them
  lcd2.begin(16,2);
  lcd2.backlight();

  

  char password[] = "ENIGMA";   //The password to start the machine
  int letter, correctPassword = 2;   //0 = wrong  1 = correct 2 = first try                
  char aux[] = {"      "};
  while(correctPassword != 1)           //while the password wasn't found
  {
    letter = 0;       //reset the number of letters introduced
    lcd.clear();     //clear both displays
    lcd2.clear();
    if(correctPassword == 0){   //if the last try resulted in a bad password
      lcd.print(" Criptator 9000");     ///display this
      lcd2.setCursor(0, 0);
      lcd2.print("! Bad password !");
      lcd2.setCursor(0, 1);
      lcd2.print("!!!!!!!!!!!!!!!!"); 
    }
    delay(2000);
    while(letter < 6)       //while I introduced less than 6 letters i read more 
    {                       //you can't introduce more or less than 6 caracters
      lcd.clear();          //for a password (it's a bit insecure)
      lcd2.clear(); //clear both displays
      lcd.print(" Criptator 9000");   //print some messages
      lcd.setCursor(0, 1);
      lcd.print("*Insert password");
      lcd2.print(aux);
      aux[letter] = Keyboard();     //construct a word with the keys pressed
      letter++;     //increments the number of letters introduced
      delay(500);
     }

     if(strcmp(aux, password) == 0)  //when the correct password 
     {                                //is typed do this
      lcd.clear();
      lcd2.clear();   //clear both screens
      lcd.print(" Criptator 9000");
      lcd.setCursor(0, 1);            //display a message on lcd 1
      lcd.print("Correct password");
      for(i = 0; i < 3; i++)
      {
        lcd2.print("*Acces granted*");  //display a flashing message
        delay(500);                    //on lcd 2
        lcd2.clear();
        delay(500);
       }
      lcd2.print("*Acces granted*");
      correctPassword = 1;  //this tells the main 'while' to stop
      }
      else 
      {
        correctPassword = 0;   //if the password intruced is wrong
        for(i = 0; i < 6; i++)    //it clears the aux vector and
          aux[i] = ' ';         //tells the main while to continue
      }
  } 
  for(i = 5; i <= 7; i++)
  {
    digitalWrite(i, HIGH);
    delay(200);           //Flashing all the option leds for style
    digitalWrite(i, LOW);
   }
  
  lcd.clear();
  lcd2.clear();
  lcd.print(" Criptator 9000");
  lcd.setCursor(0, 1);
  lcd.print("Select algorithm");  //display the algorithm options
  lcd2.print(" *Use the keys");
  lcd2.setCursor(0, 1);
  lcd2.print("next to the lcds");

  while(algorithm == 0)
  {
    for(i = 2; i <= 4; i++)
      if(digitalRead(i) == 1)   //waits for one of the option keys
        algorithm = i;          //to be pressed and notes which one
  }   
  lcd.clear();
  lcd2.clear();
  lcd.print(" Criptator 9000");     
  if(algorithm == 4)
  {
    lcd2.print("*You have chosen");
    lcd2.setCursor(0, 1);               //for each key pressed it displays
    lcd2.print(" *Caesar cipher*");     //proper messages on the lcd's and
    for(i = 1; i <= 3; i++)             //uses the algorithm variable to know
                                        //which algorithm it will run
    digitalWrite(7, HIGH);
  }
  else if(algorithm == 3)
  {
    lcd2.print("*You have chosen");
    lcd2.setCursor(0, 1);
    lcd2.print("Substitution cph");  
    
    digitalWrite(6, HIGH);
  }
  else if(algorithm == 2)
  {
    lcd2.print("*You have chosen");
    lcd2.setCursor(0, 1);
    lcd2.print(" !*ENIGMA M3*!");  
   
    digitalWrite(5, HIGH);
  }
  delay(2000);
}

  
 
void loop(){
  if(algorithm == 4)
  {
    int i;
    char crypt[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char cryptDecrypt; // C = crypt D decrypt
    lcd.clear();
    lcd2.clear();
    lcd.print(" *Caesar Cipher*");
    lcd.setCursor(0, 1);
    lcd.print("Give the setting");
    lcd2.print("Crypt or decrypt");
    lcd2.setCursor(0, 1);
    lcd2.print(" *C    or  *D "); 
    cryptDecrypt = Keyboard();
    while(cryptDecrypt != 'C' && cryptDecrypt != 'D')
    {
      lcd2.setCursor(0, 0);
      lcd2.print(" !!Wrong key !! ");
      delay(1000); 
      lcd2.setCursor(0, 0);
      lcd2.print("Crypt or decrypt");
      cryptDecrypt = Keyboard();
    }
    lcd2.setCursor(0, 1);
    if(cryptDecrypt == 'C')
       lcd2.print("You chose crypt");
    else lcd2.print("You chose decryp");
    delay(2000);
    lcd2.clear();
    lcd2.print(" *Give the key* ");
    lcd2.setCursor(0, 1);
    lcd2.print("*A = 0...Z = 25*");
    char shift = Keyboard();

    lcd2.clear();
    lcd2.print("  You chose ");
    lcd2.print(shift);
    lcd2.setCursor(0, 1);
    lcd2.print("!You can start!");
   
    int shiftNr;
    if(cryptDecrypt == 'C')
     shiftNr =  shift - 65;
    else  shiftNr = 26 - (shift - 65);
    
    char aux;
    for(i = 0; i < shiftNr; i++)
    {
      aux = crypt[0];
      for(int j = 0; j < 25; j++)
        crypt[j] = crypt[j + 1];  
      crypt[25] = aux;
    }
    delay(2000);
    char letter;
    while(1)
    {
      letter = Keyboard();
      AddPrint(letter, crypt[letter - 65]);
      delay(500);
    }
  }
  else if(algorithm == 3)
  {
    int i;
    char crypt[] = "                          ";
    lcd.clear();
    lcd2.clear();
    lcd.print(" *Substitution* ");
    lcd.setCursor(0, 1);
    lcd.print("    *Cipher*    ");
    int wrong;
    char aux, aux2;
    i = 0;
    while(i < 26)
    {
      wrong = 0;
      lcd2.clear();
      lcd2.print(" *Give the keys*");
      lcd2.setCursor(3, 1);
      aux = i + 65;
      lcd2.print(aux);
      lcd2.print(" = ");      
      crypt[i] = Keyboard();
      for(int j = 0; j < i; j++)
        if(crypt[j] == crypt[i])
          wrong++;
      if(wrong == 1)
      {
        Serial.print(crypt[i]);
        Serial.print(" - WRONG \n");
        lcd2.setCursor(0, 1);
        lcd2.print(" !! Key used !! ");
        delay(500);
      }
      else {
        lcd2.print(crypt[i]);
        i = i + 1;
      }
      delay(500);
    }
    lcd2.clear();
    lcd2.print(" !Settings done!");
    lcd2.setCursor(0, 1);
    lcd2.print("!You can start!");
    
    char letter;
    while(1)
    {
      letter = Keyboard();
      AddPrint(letter, crypt[letter - 65]);
      delay(500);
    }

  }
  else if(algorithm == 2)
  {
    char rotoare[5][27] = {"EKMFLGDQVZNTOWYHXUSPAIBRCJ",        
                 "AJDKSIRUXBLHWTMCQGZNPYFVOE",   
                 "BDFHJLCPRTXVZNYEIWGAKMUSQO",   
                 "ESOVPZJAYQUIRHXLNFTGKDCMWB",   
                 "VZBRGITYUPSDNHLXAWMJQOFECK"};             
  
     
    char reflector[3][27] = {"EJMZALYXVBWFCRQUONTSPIKHGD",   
                 "YRUHQSLDPXNGOKMIEBFZCWVJAT",                    
                 "FVPJIAOYEDRZXWGCTKUQSBNMHL"};       

    char notch[5][2] = {"U",   
              "I",    
              "U",    
              "U",   
              "V"};   
             
    
    char plugboard[27]={"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};    
    int plgset = 1000, i;    
    int rtr1 = 0, rtr2 = 0, rtr3 = 0, pozr1 = 0, pozr2 = 0, pozr3 = 0;
    char rflct = 1000, aux, inel = 1, pozrtr = 1, auxprint, letter;                      
    lcd.clear();
    lcd2.clear();
    delay(500);

    while(plgset == 1000)
    {
      lcd.clear();
      lcd2.clear();
      lcd.print(" -@#ENIGMA M3@- ");
      lcd.setCursor(0, 1);
      lcd.print("Plgbord settings");
      lcd2.print("*Nr of settings*");
      lcd2.setCursor(0, 1);
      lcd2.print("@A = 0; @M = 13");
      plgset = Keyboard();
      delay(500);
      if(plgset > 65 + 13)
      {
        lcd2.clear();
        lcd2.print("  !@WRONG KEY@! ");
        lcd2.setCursor(0, 1);
        lcd2.print("!!!!!!!!!!!!!!!!");
        plgset = 1000;
        delay(500);
      }
      else plgset = plgset - 65;
    }
    if(plgset != 0)
    {
      lcd.clear();
      lcd.print(" -@#ENIGMA M3@- ");
      lcd.setCursor(0,1);
      lcd.print("Plgbord settings");
      char ltr1 = 0, ltr2 = 0, aux;
      for(i = 0; i < plgset * 2; i++)
      {
        if(ltr1 != '?' && ltr2 != '?')
        {
          ltr1 = '?';
          ltr2 = '?';
        }
        aux = 0;
        lcd2.clear();
        lcd2.print(" -Pick letters- ");
        lcd.setCursor(0, 1);
        lcd.print("LTR1= ");
        lcd.print(ltr1);
        lcd.print(" LTR2= ");
        lcd.print(ltr2);
        lcd.print(" ");
        if(ltr1 == '?')
          ltr1 = Keyboard();
        else ltr2 = Keyboard();
        if(ltr1 != '?' && ltr2 != '?')
        {
          lcd.setCursor(0, 1);
          lcd.print("LTR1= ");
          lcd.print(ltr1);
          lcd.print(" LTR2= ");
          lcd.print(ltr2);
          lcd.print(" ");
          aux = plugboard[ltr1 - 65];
          plugboard[ltr1 - 65] = plugboard[ltr2 - 65];
          plugboard[ltr2 - 65] = aux;
        }
        delay(500);
      }
    } //Plgset End

    delay(500);
    lcd.clear();
    lcd.print(" -@#ENIGMA M3@- ");
    lcd.setCursor(0, 1);
    lcd.print("  *Reflector*");
    while(rflct == 1000)
    {
      lcd2.clear();
      lcd2.print("*What reflector*");
      lcd2.setCursor(0, 1);
      lcd2.print("-@ A / B / C @-");
      aux = Keyboard();
      if(aux == 'A' || aux == 'B' || aux == 'C')
      {
        lcd2.clear();
        lcd2.print("You have chosen:");
        lcd2.setCursor(0, 1);
        lcd2.print("       ");
        lcd2.print(rflct);
        rflct = aux - 65;
        delay(1000);
      }
      else
      {
        lcd2.clear();
        lcd2.print("  !@WRONG KEY@! ");
        lcd2.setCursor(0, 1);
        lcd2.print("!!!!!!!!!!!!!!!!");
      }
      delay(500);
    }

    // Rotors
    lcd.clear();
    lcd.print(" -@#ENIGMA M3@- ");
    lcd.setCursor(0, 1);
    lcd.print("-Rotor settings-");

    while(rtr1 == 0)    //Rotor 1
    {
      lcd2.clear();
      lcd2.print("*Set 1st rotor*");
      lcd2.setCursor(0, 1);
      lcd2.print("*A = 1...E = 5*");
      aux = Keyboard();
      if(aux != 'A' && aux != 'B' && aux != 'C' && aux != 'D' && aux != 'E')
      {
        lcd2.clear();
        lcd2.print("  !@WRONG KEY@! ");
        lcd2.setCursor(0, 1);
        lcd2.print("!!!!!!!!!!!!!!!!");
        delay(500);
      }
      else {
            rtr1 = aux - 65;
            delay(500);
           }
    }

    while(rtr2 == 0)    //Rotor 2
    {
      lcd2.clear();
      lcd2.print("*Set 2nd rotor*");
      lcd2.setCursor(0, 1);
      lcd2.print("*A = 1...E = 5*");
      aux = Keyboard();
      if(aux != 'A' && aux != 'B' && aux != 'C' && aux != 'D' && aux != 'E' && aux != rtr1)
      {
        lcd2.clear();
        lcd2.print("  !@WRONG KEY@! ");
        lcd2.setCursor(0, 1);
        lcd2.print("!!!!!!!!!!!!!!!!");
        delay(500);
      }
      else {
            rtr2 = aux - 65;
            delay(500);
           }
    }

    while(rtr3 == 0)    //Rotor 3
    {
      lcd2.clear();
      lcd2.print("*Set 3rd rotor*");
      lcd2.setCursor(0, 1);
      lcd2.print("*A = 1...E = 5*");
      aux = Keyboard();
      if(aux != 'A' && aux != 'B' && aux != 'C' && aux != 'D' && aux != 'E' && aux != rtr1 && aux != rtr2)
      {
        lcd2.clear();
        lcd2.print("  !@WRONG KEY@! ");
        lcd2.setCursor(0, 1);
        lcd2.print("!!!!!!!!!!!!!!!!");
        delay(500);
      }
      else {
            rtr3 = aux - 65;
            delay(500);
           }
    }

    lcd2.clear();
    lcd2.print("*You have chosen");
    lcd2.setCursor(0, 1);
    lcd2.print("R1=");
    lcd2.print(rtr1);
    lcd2.print(" R2=");
    lcd2.print(rtr2);
    lcd2.print(" R3=");
    lcd2.print(rtr3);
    delay(1000);

   
    delay(1000);

    lcd.clear();
    lcd.print(" -@#ENIGMA M3@- ");
    lcd.setCursor(0, 1);
    lcd.print("#Rotor pozition#");

    lcd2.clear();
    lcd2.print("Rotor 1 pozition");
    lcd.setCursor(0, 1);
    lcd2.print("*A = 0...Z = 25*");

    pozr1 = Keyboard();

    if(pozrtr != 'A')       
      for(i = 0; i < pozrtr-65; i++)         
      {
        char aux = rotoare[rtr1][0];
        memmove(rotoare[rtr1]+0 ,rotoare[rtr1]+1, 25);     
        rotoare[rtr1][25] = aux; 
        pozr1++; 
        if(pozr1 == 26)      
          pozr1 = 0;            
      }
    delay(1000);

    lcd2.clear();
    lcd2.print("Rotor 2 pozition");
    lcd.setCursor(0, 1);
    lcd2.print("*A = 0...Z = 25*");

    pozr2 = Keyboard();

    if(pozrtr != 'A')       
      for(i = 0; i < pozrtr-65; i++)         
      {
        char aux = rotoare[rtr2][0];
        memmove(rotoare[rtr2] + 0 ,rotoare[rtr2] + 1, 25);     
        rotoare[rtr2][25] = aux; 
        pozr2++; 
        if(pozr2 == 26)      
          pozr2 = 0;            
      }
    delay(1000);

    lcd2.clear();
    lcd2.print("Rotor 3 pozition");
    lcd.setCursor(0, 1);
    lcd2.print("*A = 0...Z = 25*");

    pozr3 = Keyboard();

    if(pozrtr != 'A')       
      for(i = 0; i < pozrtr-65; i++)         
      {
        char aux = rotoare[rtr3][0];
        memmove(rotoare[rtr3] + 0 ,rotoare[rtr3] + 1, 25);     
        rotoare[rtr3][25] = aux; 
        pozr3++; 
        if(pozr3 == 26)      
          pozr3 = 0;            
      }
    delay(1000);

    lcd.setCursor(0, 1);
    lcd.print("!You have chosen");

    lcd2.clear();
    lcd2.print("  I - II - III ");
    lcd2.setCursor(0, 1);
    lcd2.print("  ");
    lcd2.print(pozr1 + 65);;
    lcd2.print("  ");
    lcd2.print(pozr2 + 65);
    lcd2.print("  ");
    lcd2.print(pozr3 + 65);
    delay(500);

    lcd.setCursor(0, 1);
    lcd.print(" !You can start!");





  }   //Enigma end
  


}