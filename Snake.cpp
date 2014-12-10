#include<windows.h>
#include<iostream>
#include<conio.h>

#define ARRIBA     72       //Numeros asociados a las flechas del teclado
#define IZQUIERDA  75
#define DERECHA    77
#define ABAJO      80
#define ESC        27

int cuerpo[200][2];
int n = 1;
int tam = 4;
int x = 10 , y = 12;
int dir = 3;
int xc = 30, yc = 15;
int speed = 100 , h = 1;
int score = 0;
int pos = 1;
int puntaje_total = 0;

char tecla;

void gotoxy(int x, int y) //Funcion que posiciona el cursor
{
     HANDLE hCon;
     COORD dwPos;
     
     dwPos.X = x;
     dwPos.Y = y;
     hCon = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleCursorPosition(hCon,dwPos);
}

public void pintar(){
     //Lineas horizontales
     for (int i = 2 ; i < 78 ; i++){
         gotoxy(i,3); printf("%c",205);
         gotoxy(i,23); printf("%c",205);
         
     }
     
     //Lineas verticales
     for (int i = 4 ; i < 23 ; i++){
         gotoxy(2,i); printf("%c",186);
         gotoxy(77,i); printf("%c",186);
    }
    
    //Esquinas
    gotoxy(2,3); printf("%c",201);
    gotoxy(2,23); printf("%c",200);
    gotoxy(77,3); printf("%c",187);
    gotoxy(77,23); printf("%c",188);
}

public void guardar_posicion(){
     
     cuerpo[n][0] = x;
     cuerpo[n][1] = y;
     n++;
     if(n == tam) n = 1;
     
}

public void dibujar_cuerpo(){
     for(int i = 1 ; i < tam ; i++){
             gotoxy(cuerpo[i][0] , cuerpo [i][1]); printf ("*");
     }
}

public void borrar_cuerpo(){
     gotoxy(cuerpo[n][0] , cuerpo [n][1]); printf (" ");
     
}

private void teclear(){
     if(kbhit()){
                     tecla = getch();
                     switch(tecla){
                                   case ARRIBA :
                                        if(dir != 2);
                                               dir = 1;
                                               break;
                                   case ABAJO :
                                        if (dir != 1);
                                           dir = 2;
                                           break;
                                   case DERECHA :
                                        if (dir != 4)
                                           dir = 3;
                                           break;
                                   case IZQUIERDA :
                                        if (dir != 3)
                                           dir = 4;
                                           break;
                     }
         }
}              

public void change_speed(){
     if(score == h*20){
              speed -= 10;
              h++;
     }
}

public void comida(){
     if(x == xc && y == yc){
          xc = (rand()%73)+4;
          yc = (rand()%19)+4;
          
          tam++;
          score += 10;
          gotoxy(xc,yc);printf("%c",4);
          
          change_speed();
     }
     
}

public bool game_over(){
     if (y == 3 || y == 23 || x == 2 || x == 77) return true;
     for( int j = tam -1 ; j > 0 ; j--){
          if(cuerpo[j][0] == x && cuerpo[j][1] == y)
             return true;
             
     }
     return false;
}

public void points(){
     gotoxy(3,1); printf("score %d",score);
}

int PTotal(){
     if (puntaje_total > puntaje_total){
        puntaje_total = (points);
        }
}

private int menu_final(void){
    
    if(kbhit()){
       tecla = getch();
       if(tecla == ARRIBA){
                gotoxy(30,12); printf("%c  JUGAR DE NUEVO/NEW GAME",16);
                gotoxy(30,15); printf("    SALIR DEL JUEGO/CLOSE GAME");
                pos = 1;
       }
       if (tecla == ABAJO){
                gotoxy(30,12); printf("%c  JUGAR DE NUEVO/NEW GAME");
                gotoxy(30,15); printf("    SALIR DEL JUEGO/CLOSE GAME",16);
                pos = 0;
       }
       return 0;
    }
}

private void interaccion_menu_final(){
     borrar_cuerpo();
     gotoxy(xc,yc); printf(" ");
     
     gotoxy(35,1); printf(" <PRESS ENTER>");
     gotoxy(30,12); printf("%c     JUGAR DE NUEVO",16);
     gotoxy(30,15); printf("       SALIR DEL JUEGO");
     do{
                    
                    menu_final();
     }
     while (!menu_final());
     gotoxy(35,1); printf("              ");
     gotoxy(30,12); printf("                      ");
     gotoxy(30,15); printf("                      ");
}

private void iniciar_datos(){
     for(int j = tam ; j > 0 ; j--){              //Borramos el cuerpo de la partida
             gotoxy(cuerpo[j][0],cuerpo[j][1]); printf(" ");
     }
     for(int j = 0 ; j <= tam ; j++){          //Reseteamos los espacios de la matriz cuerpo
             for(int i = 0 ; i < 2 ; i++){
                     cuerpo[j][i] = '\0';
             }
     }
     score = 0;
     x = 10 ; y = 12 ; tam = 3 ; dir=3 ; speed = 100 ; h = 1 ; n = 0;
}

public int main(){
    
    srand(time(NULL));
    pintar();
    do{ while(tecla != ESC && !game_over()){
                   pintar();
                   iniciar_datos();
                   do{
                                   points();
                                   comida();
                                   change_speed();
                                   
                                   borrar_cuerpo();
                                   guardar_posicion();
                                   dibujar_cuerpo();
                                   
                                   Sleep(speed);
                                   teclear();
                                   teclear();
                                   
                                    if(dir == 1) y--;
                                    if(dir == 2) y++;
                                    if(dir == 3) x++;
                                    if(dir == 4) x--;
                                   
                                   gotoxy(xc,yc); printf("%c",4);
                                   }
    
    } //      FIN DEL WHILE
    printf("Felicidades, tu puntaje total es de : %d",puntaje_total);       
    }while(pos);
    return 0;
}
