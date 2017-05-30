#define NS 1 //definir NS (Segundos de grabacion del sonido patron)
#define Fs 44100 //definir Fs (Frecuencia de Muestreo)
#define Nbits 2 //definir Nbits (Numero de bit de las Muestras)
#define ON 1 //definir ON (encendido '1')
#define OFF 0 //definir OFF (apagado '0')
#define TOL 0.80 //definir TOL (Porcentaje de tolerancia de la comparacion de las señales)
#define LED_SILENCIO 2 //pin de LED_SILENCIO
#define LED_CAPTURADO 3 //pin de LED_CAPTURADO
#define LED_ENSEÑANDO 4 //pin de LED_ENSEÑANDO
#define BOTON_ENSEÑAR 5 //pin de BOTON_ENSEÑAR
#define BOTON_OK 6 //pin de BOTON_OK
#define PIN_SONIDO 7 // Pin de sonido analogico
#define F_SEGURIDAD 2  // Factor de seguridad para discriminar el ruido.

void setup() {

  //Configuracion Entrada analogica del sonido.
  //Configuracion de los Leds de salida
pinMode(LED_SILENCIO,OUTPUT);    //configura Led SILENCIO
pinMode(LED_CAPTURADO,OUTPUT);   //Configura Led CAPTURADO
pinMode(LED_ENSEÑANDO,OUTPUT);   //configura Led ENSEÑANDO

 //Configuracion de los botones de entrada
pinMode(BOTON_ENSEÑAR,INPUT);   //COnfigurar Boton ENSEÑAR.
pinMode(BOTON_OK,INPUT);     //Configurar Boton OK.

  //Configuracion de la frecuencia de muestreo con interrupciones en uno de los timer, Configurar la rutina de interrupcion.
  //configuracion de la memoria SD.

  //Inicializaciones

 }

//definicion de Variables
int ESCUCHAR;
int MEMORIA;
int   RECONOCIMIENTO;
double URuido;
int band0,band1,band2;
double COMPARACION;

void loop() {

Enseñar_label: //Modo de Enseñanza
band2=ON;
do{
band0=OFF;
  do{  //Conseguir patron. Inicio de ciclo Conseguir patron
      //Espera que el Usuario pulse el Boton ENSEÑAR.
      int band1=ON;
      while(band1==ON){
          if (digitalRead(BOTON_ENSEÑAR)==HIGH){
            band1=OFF;
          }
        } //Fin de la espera. (1) El boton de ENSEÑAR fue presionado
digitalWrite(LED_ENSEÑANDO, HIGH);      //LEd ENSEÑANDO=ON
GrabaPatron();      //Se realiza una grabacion del sonido patron durante NS Segundos.
FFT()   ;   //Se calcula la FFT del sonido patron.
band1=ON;    //Se espera que se presione el boton OK o el Boton ENSEÑAR. (1) Si se presiona OK el usuario esta deacuerdo con la grabacion.(2) Si se presiona ENSEÑAR el usuario desea volver a grabar el sonido.
    while(band1==ON){
        if (digitalRead(BOTON_ENSEÑAR)==HIGH){
          //Colocar delay para el rebote del boton
          band1=OFF;
          band0=OFF;
        }
        else if (digitalRead(BOTON_OK)==HIGH){
          //Colocar delay para el rebote del boton
          band1=OFF;
          band0=ON;
        }
      }
   }while(band0==OFF); //Fin de cliclo Conseguir patron. (1) Se presiono el boton OK.

band0=OFF;
do{//Medir nivel de Ruido. Inicio de ciclo medir nivel de ruido.
     //Espera que el Usuario pulse el Boton ENSEÑAR.
     int band1=ON;
     while(band1==ON){
         if (digitalRead(BOTON_ENSEÑAR)==HIGH){
           band1=OFF;
         }
       }  //Fin de la espera. (1) El boton de ENSEÑAR fue presionado
URuido=F_SEGURIDAD*ValorMax();        //Se realiza una medicion del nivel de ruido maximo durante NS Segundos. Se captura el Maximo valor de ruido.
        band1=ON;     //Se espera que se presione el boton OK o el Boton ENSEÑAR. (1) Si se presiona OK el usuario esta deacuerdo con la grabacion.(2) Si se presiona ENSEÑAR el usuario desea volver a grabar el sonido.

              while(band1==ON){
                  if (digitalRead(BOTON_ENSEÑAR)==HIGH){
                    //Colocar delay para el rebote del boton
                    band1=OFF;
                    band0=OFF;
                  }
                  else if (digitalRead(BOTON_OK)==HIGH){
                    //Colocar delay para el rebote del boton
                    band1=OFF;
                    band0=ON;
                  }
                }
    }while(band0==OFF);//fin de clico medir nivel de ruido. (1) Se presiono el boton OK
digitalWrite(LED_ENSEÑANDO, LOW);         //LEd ENSEÑANDO=OFF.Fin de Modo de enseñanza.
band1=ON; //(1)Se espera que el usuario presione el boton OK, para continuar a modo Escuchar. (2) El usuario presiona el boton ENSEÑAR para iniciar nuevamente el modo de Enseñanza.
while(band1==ON){
        if (digitalRead(BOTON_ENSEÑAR)==HIGH){
          //Colocar delay para el rebote del boton
          band1=OFF;
          band2=OFF;
        }
        else if (digitalRead(BOTON_OK)==HIGH){
          //Colocar delay para el rebote del boton
          band1=OFF;
          band2=ON;
        }
    }
} while(band2==ON)

//ciclo Escuchar - Recordar patron

MEMORIA=OFF;
COMPARACION=0.0;
  //Modo Escuchar
ESCUCHAR =ON; // Bandera ESCUCHAR=0N;
do{
Grabacion();    //Se graba una ventana de NS segundos.
int Amplitud_Max=ValorMax()  // Se mide el maximo Valor de la Ventana.
      if (Amplitud_Max>URuido){//Se verifica que la señal medida esta por encima del ruido. Condicional de ruido.
        //(1) La señal No es ruido
          FFT();  //calcula la FFT de la ventana grabada.
        COMPARACION =   Correlacion();//Realiza la correlacion entre la señal grabada y la señal patron. Se graba en la variable COMPARACION.
        MEMORIA=ON;//coloca la bandera MEMORIA=ON;
        }else{//(2) La señal es Ruido
          LED_SILENCIO=ON;  // Enciende Led SILENCIO.
          MEMORIA=OFF;  // Coloca la Bandera MEMORIA=OFF;
        }//FIn de condicional de Ruido.

     if(MEMORIA==ON){// Verifica la Bandera MEMORIA. Condicional de memoria. (1) si MEMORIA=ON entra en modo recordar. (2) si MEMORIA=OFF regresa al Modo escuchar.
        //Modo Recorda patron.
    //Establece el reconocimiento del sonido. Condicional de roconocimeinto. (1) Si COMPARACION>TOL entonces el sonido fue reconocido. (2) Caso contrario no reconocido.
          if(COMPARACION>TOL) {   //Sonido reconocido
            RECONOCIMIENTO=ON;   // Variable RECONOCIMIENTO=ON;
          }else{    //sonido desconocido
            RECONOCIMIENTO=OFF;  // Variables RECONOCIMENTO=OFF;
            }//fin de condicional de reconociento.
          }

   //si el usuario desea cancelar el modo escucha se debera presionar los botones OK y ENSEÑAR al mismo tiempo hasta que se entre en el modo Enseñar
   //Se hace un condiciona de cancelacion. (1) Si los botones OK y ENSEÑAR estan presionados la bandera ESCUCHAR=OFF.
   if (digitalRead(BOTON_OK)==HIGH and digitalRead(BOTON_ENSEÑAR)==HIGH ){
     //Colocar delay para el rebote del boton
     ESCUCHAR=OFF;// se cancela el modo Escuchar.
   }

}while (ESCUCHAR==ON or RECONOCIMIENTO==OFF );//FIn de ciclo. (1)El Patron fue reconocido. (2) EL Modo de Escucha fue Cancelado (ESCUCHAR = OFF).

      if (RECONOCIMIENTO==ON){  //Patron reconocido
      LED_CAPTURADO=ON;//led CAPTURADO=ON.
      }else {//Modo escucha cancelado
      goto Enseñar_label;// Se envia a  Modo Enseñar
      }

}

//define GrabaPatron
int GrabaPatron (){
//Realiza la grabacion de la señal patron
return 1;
}

// define Grabacion
int Grabacion (){
// Graba una cierta catidad de segundo
  return 1;
}

// define FFT
int FFT(){
// realiza la FFT de un vector de un cierto numero de muestras.
  return 1;
}
// define RuidoMax
int ValorMax(){
//realiza la medicion del valor maximo. Es usado para medir el maximo valor del ruido del ambiente.
return 1;
}

int Correlacion(){
//realiza la Correlacion de dos señales
return 1;

}
