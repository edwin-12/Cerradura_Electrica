//**********************************************************//
//  Universidad del Cauca                                   //
//  Tecnologia en Telematica                                //
//  ESTUDIANTES:                                            //
//  Edwin Alexis Montenegro                                 //
//  Adrian Antonio Morales                                  //
//**********************************************************// 
//               DESCRIPCION DEL CODIGO                     //
//                                                          //
// este codigo corresponde al de una cerradura electronica  //
// con codigo de seguridad de 4 digitos, el cual se podra   //
// cambiar mediante el boton select que se encuantra en el  //
// LCD Keypad Shield.                                       //
//                                                          //
//**********************************************************//

// *****************************
//      LIBRERIAS A UTILIZAR
//******************************
#include <LiquidCrystal.h>  //incluye libreria del Dislpay 
#include <Keypad.h>         // incluye libreria del teclado matricial

//******************************
//      CONFIGURACION TECLADO MATRICIAL
//******************************
const byte ROWS = 4; // numero de filas del teclado matricial
const byte COLS = 4; // numero de columnas del teclado matricial
char keys[ROWS][COLS] = { // definir la distribucion de las teclas 
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {22, 24, 26, 28}; // pines correspondientes a las filas
byte colPins[COLS] = {30, 32, 34, 36}; // pines correspondientes a las columnas

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); // se crea el objeto teclado

//**********************************************
//        CONFIGURACION DEL LCD KEYPAD SHIELD
//**********************************************
// pines de conexion del display rs, en, d4, d5, d6, d7
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 


//***************************************
//   DECLARACION DE  VARIABLES GLOBALES
//***************************************

char TECLA;                       // almacena la tecla presionada
char CLAVE[5];                    // almacena en un array de 4 digitos ingresados
char MAESTRA [5] = "0000";        // almacena en un array la contraseña inicial
byte INDICE = 0;                  // indice del array
int errores = 0;
int boton =0;
int valor = analogRead(boton);
const int redPin = 38; // Pata R del modulo y pin digital donde se conecta
const int greenPin = 39; // Pata G del modulo y pin digital donde se conecta
const int bluePin = 40; // Pata B del modulo y pin digital donde se conecta

//*******************************************************//
//                        COLOR                          //
//*******************************************************//
void color (unsigned char red, unsigned char green, unsigned char blue) // the color generating function
{
analogWrite(redPin, red);
analogWrite(bluePin, blue);
analogWrite(greenPin, green);
}

//***********************************************//
//      MENSAJE DE BIENVENIDA                    //
//***********************************************//
void Bienvenida (){
  lcd.print("CERRADURA");
      lcd.setCursor(5,1);
      lcd.print("ELECTRICA");
      delay (2000);
}
// **********************************************//
//                     ERROR DE CLAVE            //
//***********************************************//
void error (){
  lcd.clear();
  lcd.setCursor (0, 1);
  lcd.print(" ERROR DE CLAVE "); 
  Led_rojo(); 
  lcd.clear();      
  INDICE = 0;  
}
//***********************************************//
//            BLOQUEO CERRADURA                  //
//***********************************************//
void Bloqueo(){
  lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CERRADURA");
      lcd.setCursor(7, 1);
      lcd.print("BLOQUEADA");
      Led_multiple();
      lcd.clear();      
      INDICE = 0;
      errores = 0;      
      Bienvenida();
      lcd.clear();
}
// *********************************************//
//         APERTURA DE PUERTA                   //
//**********************************************//
void abierto (){
  lcd.clear();
  lcd.setCursor (0, 1);
  lcd.print("BIENVENIDO");
  Led_verde();
  lcd.clear();
  INDICE = 0;
  Bienvenida();
}
//************************************************//
//                 CAMBIAR CLAVE                  //
//************************************************//
void Clave_Nueva (){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Cambio de Clave ");
  lcd.setCursor(0,1);
  lcd.print("Nueva :");
  lcd.setCursor(8,1);
  INDICE =0;
  while (INDICE <= 3){
    TECLA =  keypad.getKey();
    if (TECLA){
      MAESTRA[INDICE] = TECLA;
      CLAVE[INDICE]=TECLA;
      INDICE++;
      lcd.print(TECLA);
    }
  }
  lcd.setCursor(0,1);
  lcd.print("CLAVE CAMBIADA");
  delay(2000);
  lcd.clear();
  INDICE = 0;
}
//***********************************************//
//              COLORES LED                      //
//***********************************************//
void Led_verde (){
  color(0,255, 0); // turn the RGB LED green
  delay(1000); // delay for 1 second
  color(0,0,0); 
}

void Led_rojo (){
  color(255, 0, 0); // turn the RGB LED red
  delay(1000); // delay for 1 second
  color(0,0,0);
}

void Led_multiple(){
  color(255, 0, 0); // turn the RGB LED red
      delay(500); // delay for 1 second
      color(0,255, 0); // turn the RGB LED green
      delay(500); // delay for 1 second
      color(0, 0, 255); // turn the RGB LED blue
      delay(500); // delay for 1 second
      // Example blended colors:
      color(255,0,0); // turn the RGB LED red
      delay(500); // delay for 1 second
      color(237,109,0); // turn the RGB LED orange
      delay(500); // delay for 1 second
      color(255,215,0); // turn the RGB LED yellow
      delay(500); // delay for 1 second
      color(0,0,0);

}
//***************************************//
//                CODIGO                 //
//***************************************//

void setup() {  
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT); // se establece la variable redPin como una salida
  pinMode(greenPin, OUTPUT); // se establece la variable greenPin como una salida
  pinMode(bluePin, OUTPUT); // se establece la variable bluePin como una salida

  lcd.begin(16, 2);   
  lcd.clear(); 
  lcd.setCursor(0,0);
  Bienvenida();  
  lcd.clear();
}

void loop() { 
  
  int valor = analogRead(boton);
    if(valor > 722 && valor <= 725){
      Clave_Nueva();
    }
    if (errores == 3 ){
      Bloqueo();            
    }
    else{      
      lcd.setCursor(0, 0); 
      lcd.print("Introduce Clave");    
    } 


  TECLA = keypad.getKey();  
  
  if (TECLA){    
    CLAVE[INDICE] = TECLA;
    INDICE++;    
    lcd.setCursor(INDICE, 1);
    lcd.print ("*");
  }
  if (INDICE == 4)
  {
    if(!strcmp(CLAVE, MAESTRA)){
      abierto();
      lcd.clear();
    }
    else{
      error();
      INDICE = 0;
      errores++;
      lcd.clear();            
    }
  }
}
