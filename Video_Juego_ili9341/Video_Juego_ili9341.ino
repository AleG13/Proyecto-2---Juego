
//***************************************************************************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include "pitches.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include "bitmaps.h"
#include "font.h"
#include "lcd_registers.h"

#define LCD_RST PD_0
#define LCD_CS PD_1
#define LCD_RS PD_2
#define LCD_WR PD_3
#define LCD_RD PE_1
#define NOTE_C4_1 260
int DPINS[] = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7};  


//***************************************************************************************************************************************
// Functions Prototypes
//***************************************************************************************************************************************
void LCD_Init(void);
void LCD_CMD(uint8_t cmd);
void LCD_DATA(uint8_t data);
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_Clear(unsigned int c);
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void LCD_Print(String text, int x, int y, int fontSize, int color, int background);

void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
void LCD_Bitmap2(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);

void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset);


extern uint8_t perropatos[];
extern uint8_t fondo[];
extern uint8_t fondo01[];
extern uint8_t fondonegro[];
extern uint8_t vidapatos[];
extern uint8_t mira[];
void fmira(void);
//***************************************************************************************************************************************
// Inicialización
//***************************************************************************************************************************************
void setup() {
 
  SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
  Serial.begin(115200);
  Serial2.begin(115200);
  GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
  //Serial.println("Inicio");
  LCD_Init();
  LCD_Clear(0x00);
 
 
  LCD_Bitmap(70, 50, 191, 97, fondonegro);
  for(int x = 70; x <265; x++){
    delay(15);
    V_line(x, 97, 2, 0xA120);
  }
  String text1 = "ALEJANDRO GONZALEZ - 21398";
  LCD_Print(text1, 60, 180, 1, 0xffff, 0);
  delay(3000);
  Serial2.println(1);
  LCD_Bitmap(0, 0, 320, 240, fondo01);
  for(int x = 0; x <261; x++){
    delay(15);
    int anim1 = (x/5)%2;
    LCD_Sprite(x,189,59,51,perro,2,anim1,0,0);
  }
    FillRect(261, 189,59,51, 0x72E1);
    
    String text2 = "READY?";
    LCD_Print(text2, 140, 50, 2, 0, 0x4E3F);
    delay(1500);
    String text3 = "GO!";
    FillRect(140, 50,100,25, 0x4E3F);
    LCD_Print(text3, 160, 75, 2, 0, 0x4E3F);
    LCD_Bitmap(76, 200, 167, 20, vidapatos);
    delay(1500);
    FillRect(140, 75,100,25, 0x4E3F);
    
}
//***************************************************************************************************************************************
// Loop Infinito
//***************************************************************************************************************************************
int posymira= 40;
int posxmira= 153;
int m = 0;
byte index2 = 0;  // Índice para seguir la posición en el buffer
int valor1;
int valor2;
int puntaje = 0;
int level = 1;
byte digitCount = 0; // Contador de dígitos recibidos
int total = 0;
void fmira(void){
 while (Serial2.available() > 0) {
  
    if(posxmira<107 and posxmira>27){ 
      posxmira = 0;
      posymira= 0;
    }
    else{
     FillRect(posxmira, posymira, 18,18, 0x4E3F);
    }
    char receivedChar = Serial2.read();
    
   if (isdigit(receivedChar)) {
      if (digitCount < 3) {
        valor1 = valor1 * 10 + (receivedChar - '0');
      } else if (digitCount >= 3 && digitCount < 6) {
        valor2 = valor2 * 10 + (receivedChar - '0');
      }
      digitCount++;
    } else if (receivedChar == ' ') {
      // Cambio a recibir el segundo valor
      digitCount = 3;
    } else if (receivedChar == '\n') {
      // Se recibieron ambos valores, imprimirlos
      Serial.print("Valor X ");
      Serial.print(valor1);
      Serial.print(" Valor Y ");
      Serial.println(valor2);
      posymira = map(valor2,0,255,0,112);
      posxmira = map(valor1,0,255,0,300);
      digitCount = 0;
      valor1 = 0;
      valor2 = 0;
    }
  }
  if(posxmira<107 and posxmira>27){
    
  }
  else{
    LCD_Bitmap(posxmira, posymira, 18, 18, mira);
  }
  
  
}

void loop() {
  int pato = random(1, 7);
  int randNumber;
  int posxpato = 0;
  int posypato = 0;
  int shot = 0;
  
  switch(pato){
    case 1:
        randNumber = random(106, 196);
        for(int y = 130; y > 0; y=y-1){
        int anim2 = (y/20)%3;  
        LCD_Sprite(randNumber,y,29,25,pato2,3,anim2,0,1);
        fmira();
        Rect(randNumber, y, 29,26, 0x4E3F);
        if(posxmira-5<= randNumber and posymira<=y){
          if(randNumber+29<= posxmira+34 and y+25<=posymira+25){
            shot=1;
            puntaje++;
            posxpato = randNumber;
            posypato = y;
            y = 0;
          }
        }
        }
        FillRect(randNumber, 0, 29,26, 0x4E3F);
        

        m++;
    break;

    case 2:
        randNumber = random(258, 290);
        for(int y = 130; y > 0; y=y-1){
        int anim2 = (y/20)%3;  
        LCD_Sprite(randNumber,y,29,25,pato2,3,anim2,0,1);
        fmira();
        Rect(randNumber, y, 29,26, 0x4E3F);
       if(posxmira-5<= randNumber and posymira<=y){
          if(randNumber+29<= posxmira+34 and y+25<=posymira+25){
            shot=1;
            puntaje++;
            posxpato = randNumber;
            posypato = y;
            y = 0;
          }
        }
        }
        FillRect(randNumber, 0, 29,26, 0x4E3F);
        
        m++;
        break;
        
    case 3:
        randNumber = random(2, 8);
        for(int y = 130; y > 0; y=y-1){
        int anim2 = (y/20)%3;  
        LCD_Sprite(randNumber,y,29,25,pato2,3,anim2,0,1);
        fmira();
        Rect(randNumber, y, 29,26, 0x4E3F);
        if(posxmira-5<= randNumber and posymira<=y){
          if(randNumber+29<= posxmira+34 and y+25<=posymira+25){
            shot=1; 
            puntaje++;
            posxpato = randNumber;
            posypato = y;
            y = 0;
          }
        }
        }
        FillRect(randNumber, 0, 29,26, 0x4E3F);
        
        m++;
    break;
    
   case 4:
        randNumber = random(0, 99);
        for(int x = 0; x < 290; x=x+1){
          if(x>7 and x<74 and randNumber > 9){
           FillRect(7, randNumber, 30,31, 0x4E3F);
           delay(500);
           x = 105;
          }   
        int anim2 = (x/20)%3;  
        LCD_Sprite(x,randNumber,30,31,pato3,3,anim2,0,1);
        fmira();
        Rect(x, randNumber, 30,35, 0x4E3F);
        if(posxmira<= x and posymira-5<=randNumber){
          if(x+30<= posxmira+32 and randNumber+31<=posymira+36){
            shot=1;
            posxpato = x;
            posypato = randNumber;
            x = 290;
             puntaje++;
          }
        }
        }
        FillRect(290, randNumber, 30,31, 0x4E3F);
        
        m++;
    break;
    
   case 5:
        randNumber = random(0, 99);
        for(int x = 290; x > 0; x=x-1){
          if(x<104 and x>6 and randNumber > 9){
           FillRect(104, randNumber, 30,31, 0x4E3F);
           delay(500);
           x = 7;
          }   
        int anim2 = (x/20)%3;  
        LCD_Sprite(x,randNumber,30,31,pato3,3,anim2,1,0);
        fmira();
        Rect(x, randNumber, 30,35, 0x4E3F);
        if(posxmira<= x and posymira-5<=randNumber){
          if(x+30<= posxmira+32 and randNumber+31<=posymira+36){
            shot=1;
            posxpato = x;
            puntaje++;
            posypato = randNumber;
            x = 0;
          }
        }
        }
        delay(25);
        FillRect(0, randNumber, 30,31, 0x4E3F);
        
        m++;
    break;
  case 6:
        randNumber = random(0, 99);
        for(int x = 0; x < 290; x=x+1){
          if(x>7 and x<74 and randNumber > 9){
           FillRect(7, randNumber, 30,31, 0x4E3F);
           delay(500);
           x = 105;
          }   
        int anim2 = (x/20)%3;  
        LCD_Sprite(x,randNumber,30,31,pato3,3,anim2,0,1);
        fmira();
        Rect(x, randNumber, 30,35, 0x4E3F);
        if(posxmira<= x and posymira-5<=randNumber){
          if(x+30<= posxmira+32 and randNumber+31<=posymira+36){
            shot=1;
            posxpato = x;
            puntaje++;
            posypato = randNumber;
            x = 290;
          }
        }
        }
        FillRect(290, randNumber, 30,31, 0x4E3F);
       
        m++;
    break;

    case 7:
        randNumber = random(0, 99);

        for(int x = 290; x > 0; x=x-1){
          if(x<104 and x>6 and randNumber > 9){
           FillRect(104, randNumber, 30,31, 0x4E3F);
           delay(500);
           x = 7;
           
          }   
        int anim2 = (x/20)%3;  
        LCD_Sprite(x,randNumber,30,31,pato3,3,anim2,1,0);
        fmira();
        Rect(x, randNumber, 30,35, 0x4E3F);
        if(posxmira<= x and posymira-5<=randNumber){
          if(x+30<= posxmira+32 and randNumber+31<=posymira+36){
            shot=1;
            puntaje++;
            posxpato = x;
            posypato = randNumber;
            x = 0; 
          }
        }
        }
        delay(25);
        FillRect(0, randNumber, 30,31, 0x4E3F);
        
        m++;
    break;

    
  }
  if(shot == 1){
    Serial2.println(3);
    LCD_Bitmap(posxpato-1, posypato, 30, 26, patomuerto);
    delay(500);
    FillRect(posxpato-1, posypato, 30,26, 0x4E3F); 
    for(int y = posypato; y < 128; y++){
    int anim2 = (y/20)%3;  
    LCD_Sprite(posxpato-1,y,24,28,patomuerto2,3,anim2,0,0);
    Rect(posxpato, y, 24,2, 0x4E3F);
    }
    FillRect(posxpato, 128, 24,28, 0x4E3F);  
    delay(20);
    if(posxpato>273){
      posxpato=271;
    }
    LCD_Bitmap(posxpato, 113, 47, 44, perropatos);
    delay(500);
    FillRect(posxpato, 113, 47,44, 0x4E3F); 
    LCD_Bitmap(81+(m*13), 205, 13, 12, patoverde);
   
    delay(500);
  }
  else if(shot == 0){
    LCD_Bitmap(81+(m*13), 205, 13, 12, patorojo);
  }
  
  if (m == 10){
    Serial2.println(4);
    level++;
    String text4 = "PUNTAJE:";
    LCD_Print(text4, 130, 60, 2, 0, 0x4E3F);
    String cadena = String(puntaje);
    total = total + puntaje;
    String text5 = "10/10";
    LCD_Print(text5, 130, 80, 2, 0, 0x4E3F);
    delay(5500);
    FillRect(130, 60,180,80, 0x4E3F);
    m=0;
    shot = 0;
    int s=0;
    while( s == 0){
      fmira();
      String text7 = "DESEA CONTINUAR? ";
      LCD_Print(text7, 130, 60, 1, 0, 0x4E3F);
      String text8 = "SI ";
      LCD_Print(text8, 130, 80, 2, 0x7861, 0x4E3F);
      String text9 = "NO";
      LCD_Print(text9, 130, 110, 2,0x7861, 0x4E3F);
      
      if (posymira > 60 and posxmira > 110 and posymira+18< 105 and posxmira+18 < 155){
        Serial2.println(2);
        s = 1;
          FillRect(130, 60,180,80, 0x4E3F);
          FillRect(130, 80,180,80, 0x4E3F);
           String cadena2 = String(level);
          String text6 = "NIVEL: "+cadena2;
          LCD_Print(text6, 130, 60, 2, 0, 0x4E3F);
          delay(2000);
          FillRect(130, 60,180,80, 0x4E3F);
          LCD_Bitmap(76, 200, 167, 20, vidapatos);
        
      }
      else if (posymira > 95 and posxmira > 110 and posymira+18< 135 and posxmira+18 < 155){
        Serial2.println(2);
        FillRect(130, 60,180,80, 0x4E3F);
        FillRect(130, 80,180,80, 0x4E3F);
        String cadena3 = String(total);
        String text10 = "PUNTAJE TOTAL:";
        LCD_Print(text10, 90, 60, 2, 0, 0x4E3F);
        LCD_Print(cadena3, 170, 90, 2, 0x7861, 0x4E3F);
        s = 1;
        while(1);
        
      }    
    }
    puntaje= 0;
  }
  
   
   FillRect(posxmira, posymira, 18,18, 0x4E3F);
}



//***************************************************************************************************************************************
// Función para inicializar LCD
//***************************************************************************************************************************************
void LCD_Init(void) {
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_WR, OUTPUT);
  pinMode(LCD_RD, OUTPUT);
  for (uint8_t i = 0; i < 8; i++){
    pinMode(DPINS[i], OUTPUT);
  }
  //****************************************
  // Secuencia de Inicialización
  //****************************************
  digitalWrite(LCD_CS, HIGH);
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, HIGH);
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_RST, HIGH);
  delay(5);
  digitalWrite(LCD_RST, LOW);
  delay(20);
  digitalWrite(LCD_RST, HIGH);
  delay(150);
  digitalWrite(LCD_CS, LOW);
  //****************************************
  LCD_CMD(0xE9);  // SETPANELRELATED
  LCD_DATA(0x20);
  //****************************************
  LCD_CMD(0x11); // Exit Sleep SLEEP OUT (SLPOUT)
  delay(100);
  //****************************************
  LCD_CMD(0xD1);    // (SETVCOM)
  LCD_DATA(0x00);
  LCD_DATA(0x71);
  LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0xD0);   // (SETPOWER) 
  LCD_DATA(0x07);
  LCD_DATA(0x01);
  LCD_DATA(0x08);
  //****************************************
  LCD_CMD(0x36);  // (MEMORYACCESS)
  LCD_DATA(0x40|0x80|0x20|0x08); // LCD_DATA(0x19);
  //****************************************
  LCD_CMD(0x3A); // Set_pixel_format (PIXELFORMAT)
  LCD_DATA(0x05); // color setings, 05h - 16bit pixel, 11h - 3bit pixel
  //****************************************
  LCD_CMD(0xC1);    // (POWERCONTROL2)
  LCD_DATA(0x10);
  LCD_DATA(0x10);
  LCD_DATA(0x02);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC0); // Set Default Gamma (POWERCONTROL1)
  LCD_DATA(0x00);
  LCD_DATA(0x35);
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x02);
  //****************************************
  LCD_CMD(0xC5); // Set Frame Rate (VCOMCONTROL1)
  LCD_DATA(0x04); // 72Hz
  //****************************************
  LCD_CMD(0xD2); // Power Settings  (SETPWRNORMAL)
  LCD_DATA(0x01);
  LCD_DATA(0x44);
  //****************************************
  LCD_CMD(0xC8); //Set Gamma  (GAMMASET)
  LCD_DATA(0x04);
  LCD_DATA(0x67);
  LCD_DATA(0x35);
  LCD_DATA(0x04);
  LCD_DATA(0x08);
  LCD_DATA(0x06);
  LCD_DATA(0x24);
  LCD_DATA(0x01);
  LCD_DATA(0x37);
  LCD_DATA(0x40);
  LCD_DATA(0x03);
  LCD_DATA(0x10);
  LCD_DATA(0x08);
  LCD_DATA(0x80);
  LCD_DATA(0x00);
  //****************************************
  LCD_CMD(0x2A); // Set_column_address 320px (CASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x3F);
  //****************************************
  LCD_CMD(0x2B); // Set_page_address 480px (PASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0xE0);
//  LCD_DATA(0x8F);
  LCD_CMD(0x29); //display on 
  LCD_CMD(0x2C); //display on

  LCD_CMD(ILI9341_INVOFF); //Invert Off
  delay(120);
  LCD_CMD(ILI9341_SLPOUT);    //Exit Sleep
  delay(120);
  LCD_CMD(ILI9341_DISPON);    //Display on
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar comandos a la LCD - parámetro (comando)
//***************************************************************************************************************************************
void LCD_CMD(uint8_t cmd) {
  digitalWrite(LCD_RS, LOW);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = cmd;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para enviar datos a la LCD - parámetro (dato)
//***************************************************************************************************************************************
void LCD_DATA(uint8_t data) {
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = data;
  digitalWrite(LCD_WR, HIGH);
}
//***************************************************************************************************************************************
// Función para definir rango de direcciones de memoria con las cuales se trabajara (se define una ventana)
//***************************************************************************************************************************************
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
  LCD_CMD(0x2a); // Set_column_address 4 parameters
  LCD_DATA(x1 >> 8);
  LCD_DATA(x1);   
  LCD_DATA(x2 >> 8);
  LCD_DATA(x2);   
  LCD_CMD(0x2b); // Set_page_address 4 parameters
  LCD_DATA(y1 >> 8);
  LCD_DATA(y1);   
  LCD_DATA(y2 >> 8);
  LCD_DATA(y2);   
  LCD_CMD(0x2c); // Write_memory_start
}
//***************************************************************************************************************************************
// Función para borrar la pantalla - parámetros (color)
//***************************************************************************************************************************************
void LCD_Clear(unsigned int c){  
  unsigned int x, y;
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);   
  SetWindows(0, 0, 319, 239); // 479, 319);
  for (x = 0; x < 320; x++)
    for (y = 0; y < 240; y++) {
      LCD_DATA(c >> 8); 
      LCD_DATA(c); 
    }
  digitalWrite(LCD_CS, HIGH);
} 
//***************************************************************************************************************************************
// Función para dibujar una línea horizontal - parámetros ( coordenada x, cordenada y, longitud, color)
//*************************************************************************************************************************************** 
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {  
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + x;
  SetWindows(x, y, l, y);
  j = l;// * 2;
  for (i = 0; i < l; i++) {
      LCD_DATA(c >> 8); 
      LCD_DATA(c); 
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una línea vertical - parámetros ( coordenada x, cordenada y, longitud, color)
//*************************************************************************************************************************************** 
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {  
  unsigned int i,j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + y;
  SetWindows(x, y, x, l);
  j = l; //* 2;
  for (i = 1; i <= j; i++) {
    LCD_DATA(c >> 8); 
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);  
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  H_line(x  , y  , w, c);
  H_line(x  , y+h, w, c);
  V_line(x  , y  , h, c);
  V_line(x+w, y  , h, c);
}
//***************************************************************************************************************************************
// Función para dibujar un rectángulo relleno - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//***************************************************************************************************************************************
/*
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  unsigned int i;
  for (i = 0; i < h; i++) {
    H_line(x  , y  , w, c);
    H_line(x  , y+i, w, c);
  }
}*/


void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 
  
  unsigned int x2, y2;
  x2 = x+w;
  y2 = y+h;
  SetWindows(x, y, x2-1, y2-1);
  unsigned int k = w*h*2-1;
  unsigned int i, j;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      LCD_DATA(c >> 8);
      LCD_DATA(c);
      
      //LCD_DATA(bitmap[k]);    
      k = k - 2;
     } 
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar texto - parámetros ( texto, coordenada x, cordenada y, color, background) 
//***************************************************************************************************************************************
void LCD_Print(String text, int x, int y, int fontSize, int color, int background) {
  int fontXSize ;
  int fontYSize ;
  
  if(fontSize == 1){
    fontXSize = fontXSizeSmal ;
    fontYSize = fontYSizeSmal ;
  }
  if(fontSize == 2){
    fontXSize = fontXSizeBig ;
    fontYSize = fontYSizeBig ;
  }
  
  char charInput ;
  int cLength = text.length();
  //Serial.println(cLength,DEC);
  int charDec ;
  int c ;
  int charHex ;
  char char_array[cLength+1];
  text.toCharArray(char_array, cLength+1) ;
  for (int i = 0; i < cLength ; i++) {
    charInput = char_array[i];
    //Serial.println(char_array[i]);
    charDec = int(charInput);
    digitalWrite(LCD_CS, LOW);
    SetWindows(x + (i * fontXSize), y, x + (i * fontXSize) + fontXSize - 1, y + fontYSize );
    long charHex1 ;
    for ( int n = 0 ; n < fontYSize ; n++ ) {
      if (fontSize == 1){
        charHex1 = pgm_read_word_near(smallFont + ((charDec - 32) * fontYSize) + n);
      }
      if (fontSize == 2){
        charHex1 = pgm_read_word_near(bigFont + ((charDec - 32) * fontYSize) + n);
      }
      for (int t = 1; t < fontXSize + 1 ; t++) {
        if (( charHex1 & (1 << (fontXSize - t))) > 0 ) {
          c = color ;
        } else {
          c = background ;
        }
        LCD_DATA(c >> 8);
        LCD_DATA(c);
      }
    }
    digitalWrite(LCD_CS, HIGH);
  }
}
//***************************************************************************************************************************************
// Función para dibujar una imagen a partir de un arreglo de colores (Bitmap) Formato (Color 16bit R 5bits G 6bits B 5bits)
//***************************************************************************************************************************************
void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]){  
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 
  
  unsigned int x2, y2;
  x2 = x+width;
  y2 = y+height;
  SetWindows(x, y, x2-1, y2-1);
  unsigned int k = 0;
  unsigned int i, j;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      //LCD_DATA(bitmap[k]);    
      k = k + 2;
     } 
  }
  digitalWrite(LCD_CS, HIGH);
}
void LCD_Bitmap2(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]){  
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 
  
  unsigned int x2, y2;
  x2 = x+width;
  y2 = y+height;
  SetWindows(x, y, x2-1, y2-1);
  unsigned int k = 0;
  unsigned int i, j;

  for (int i = 0; i < width; i++) {  
      if (j >= 0){
        if(j < 239){
         LCD_DATA(bitmap[k]);
         LCD_DATA(bitmap[k+1]);
        }
      }
    for (int j = 0; j < height; j++) {
      k = k + 2;
      // LCD_DATA(bitmap[0]);
     
     } 
      
  }
  digitalWrite(LCD_CS, HIGH);
}
//***************************************************************************************************************************************
// Función para dibujar una imagen sprite - los parámetros columns = número de imagenes en el sprite, index = cual desplegar, flip = darle vuelta
//***************************************************************************************************************************************
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset){
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 

  unsigned int x2, y2;
  x2 =   x+width;
  y2=    y+height;
  SetWindows(x, y, x2-1, y2-1);
  int k = 0;
  int ancho = ((width*columns));
  if(flip){
  for (int j = 0; j < height; j++){
      k = (j*(ancho) + index*width -1 - offset)*2;
      k = k+width*2;
     for (int i = 0; i < width; i++){
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      k = k - 2;
     } 
  }
  }else{
     for (int j = 0; j < height; j++){
      k = (j*(ancho) + index*width + 1 + offset)*2;
     for (int i = 0; i < width; i++){
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      k = k + 2;
     } 
  }
    
    
    }
  digitalWrite(LCD_CS, HIGH);
}
