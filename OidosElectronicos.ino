#define NS 1 //definir NS (Segundos de grabacion del sonido patron)
#define Fs 44100 //definir Fs (Frecuencia de Muestreo)
#define Nbits 2 //definir Nbits (Numero de bit de las Muestras)
#define ON 1 //definir ON (encendido '1')
#define OFF 0 //definir OFF (apagado '0')
#define TOL 0.80 //definir TOL (Porcentaje de tolerancia de la comparacion de las señales)
#define LED_SILENCIO 2 //pin de LED_SILENCIO
#define LED_CAPTURADO 3 //pin de LED_CAPTURADO
#define LED_ENSEÑANDO 4 //pin de LED_ENSEÑANDO


void setup() {

  //Configuracion Entrada analogica del sonido.
  //Configuracion de los Leds de salida
pinMode(LED_SILENCIO,OUTPUT);    //configura Led SILENCIO
pinMode(LED_CAPTURADO,OUTPUT);   //Configura Led CAPTURADO
pinMode(LED_ENSEÑANDO,OUTPUT);   //configura Led ENSEÑANDO

    //Configuracion de los botones de entrada
    //COnfigurar Boton ENSEÑAR.
    //Configurar Boton OK.
    
  //Configuracion de la frecuencia de muestreo con interrupciones en uno de los timer, Configurar la rutina de interrupcion. 
  //Configuracion del convertidor analogico a digital.
  //configuracion de la memoria SD.
 }

void loop() {
//Modo de Enseñanza
    //Conseguir patron. Inicio de ciclo Conseguir patron
      //Espera que el Usuario pulse el Boton ENSEÑAR. 
      //Fin de la espera. (1) El boton de ENSEÑAR fue presionado
      //LEd ENSEÑANDO=ON
      //Se realiza una grabacion del sonido patron durante NS Segundos.
      //Se calcula la FFT del sonido patron.
      //Se espera que se presione el boton OK o el Boton ENSEÑAR. (1) Si se presiona OK el usuario esta deacuerdo con la grabacion.(2) Si se presiona ENSEÑAR el usuario desea volver a grabar el sonido. 
    //Fin de cliclo Conseguir patron. (1) Se presiono el boton OK. 
         
   //Medir nivel de Ruido. Inicio de ciclo medir nivel de ruido.
     //Espera que el Usuario pulse el Boton ENSEÑAR. 
          //Fin de la espera. (1) El boton de ENSEÑAR fue presionado
          //Se realiza una medicion del nivel de ruido durante NS Segundos. Se captura el Maximo valor de ruido.
          //Se espera que se presione el boton OK o el Boton ENSEÑAR. (1) Si se presiona OK el usuario esta deacuerdo con la grabacion.(2) Si se presiona ENSEÑAR el usuario desea volver a grabar el sonido.
    //fin de clico medir nivel de ruido. (1) Se presiono el boton OK
     //LEd ENSEÑANDO=OFF
//fin de Modo de enseñansa.

//(1)Se espera que el usuario presione el boton OK, para continuar a modo Escuchar. (2) El usuario presiona el boton ENSEÑAR para iniciar nuevamente el modo de Enseñanza.
//ciclo Escuchar - Recordar patron
  //Modo Escuchar
    // Bandera ESCUCHAR=0N;
    //Se graba una ventana de NS segundos. Se mide el maximo Valor de la Ventana.
      //Se verifica que la señal medida esta por encima del ruido. Condicional de ruido.
        //(1) La señal No es ruido
            //calcula la FFT de la ventana grabada.
            //Realiza la correlacion entre la señal grabada y la señal patron. Se graba en la variable COMPARACION.
            //coloca la bandera MEMORIA=ON;
        //(2) La señal es Ruido
            // Enciende Led SILENCIO.
            // Coloca la Bandera MEMORIA=OFF;
      //FIn de condicional de Ruido.
    //Se calcula la FFT de dicha Ventana
 // Verifica la Bandera MEMORIA. Condicional de memoria. (1) si MEMORIA=ON entra en modo recordar. (2) si MEMORIA=OFF regresa al Modo escuchar.
    //Modo Recorda patron.
    //Establece el reconocimiento del sonido. Condicional de roconocimeinto. (1) Si COMPARACION>TOL entonces el sonido fue reconocido. (2) Caso contrario no reconocido.
      //Sonido reconocido
           // Variable RECONOCIMIENTO=ON;
      //sonido desconocido
          // Variables RECONOCIMENTO=OFF;
   //fin de condicional de reconociento.

   //si el usuario desea cancelar el modo escucha se debera presionar los botones OK y ENSEÑAR al mismo tiempo hasta que se entre en el modo Enseñar
   //Se hace un condiciona de cancelacion. (1) Si los botones OK y ENSEÑAR estan presionados la bandera ESCUCHAR=OFF.

//FIn de ciclo. (1)El Patron fue reconocido. (2) EL Modo de Escucha fue Cancelado (ESCUCHAR = OFF).
  //Patron reconocido
    //led CAPTURADO=ON.
  //Modo escucha cancelado
   // Se envia a  Modo Enseñar 
 

}
