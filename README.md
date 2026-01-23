***Control de LEDs por DIP Switch - Protolink EX1.***

**1. Resumen Ejecutivo**

  Este proyecto permite el control de un arreglo de 4 LEDs mediante la lectura de un DIP Switch de 4 posiciones en la placa Protolink EX.
  El sistema traduce la entrada del switch en estados visuales y reporta en tiempo real el valor decimal y binario a través de una terminal serial.

  Features principales:
   - *Mapeo DIP a LED:* Los LEDs reflejan el valor binario ingresado por el switch.
   - *Log por UART:* Envío de logs (Valor decimal y arreglo binario).
   - *Detección de cambios:* Actualización de periféricos solo cuando cambia el estado de la entrada.
   - *Máscara de bits:* Implementación de filtrado por software para asegurar lecturas limpias en el puerto F.

**2. Diagrama de la placa**

    _______________________________________________________________
      |                                                         |
      |                   SISTEMA PROTOLINK EX                  |
      |_________________________________________________________|
      |                                                         |
      |   [ ENTRADAS ]      [ PROCESAMIENTO ]      [ SALIDAS ]  |
      |   DIP SWITCHES            MCU                 LEDS      |
      |                                                         |
      |                                                         |
      |   (Pines F)                (XCore)          (Pines B/E) |
      |    _______                _________          _______    |
      |   | [1] F0|------------->|         |------->| LED1  |   |
      |   | [2] F1|------------->|   PIC   |------->| LED2  |   |
      |   | [3] F2|------------->|         |------->| LED3  |   |
      |   | [4] F3|------------->|_________|------->| LED4  |   |
      |   |_______|                   |             |_______|   |
      |                               |                         |
      |   [ ENERGÍA ]                 |        [ COMUNICACIÓN]  |
      |    _________                  |             _________   |
      |   | VCC 5V  |-----------------|----------->| UART-USB|  |
      |   | GND     |                              | 115200  |  |
      |   |_________|                              |_________|  |
      |_________________________________________________________|


**3. Periféricos Usados**

 - DIP Switch (GPIO Inputs): 4 entradas digitales configuradas en el puerto F.
 - LEDs (GPIO Outputs): 4 salidas digitales para led's.
 - UART/Terminal: Baudrate: 115200.
 - Timer/Delay: Uso de delay_ms para el polling de lectura y estabilización de la transmisión serial.

**4. Pinout / Mapeo**

| Componente | Etiqueta | Pin MCU | Función |
|------------|----------|---------|-----------|
| DIP 0      | ADDR0    | PIN_F0  | Entrada Digital|
| DIP 1      | ADDR1    | PIN_F1  | Entrada Digital|
| DIP 2      | ADDR2    | PIN_F2  | Entrada Digital|
| DIP 3      | ADDR3    | PIN_F3  | Entrada Digital|
| LED 1      | GPIO_1   | PIN_B0  | Salida Digital|
| LED 2      | GPIO_2   | PIN_B1  | Salida Digital|
| LED 3      | GPIO_3   | PIN_E5  | Salida Digital|
| LED 4      | GPIO_4   | PIN_E4  | Salida Digital|
| UART TX    | TX_5     | PIN_E2  | Transmisión Serial|
| UART RX    | RX_5     | PIN_E3  | Recepción Serial|

**5. Cómo compilar y flashear**

Prerrequisitos

 - Compilador CCS C Compiler.
 - IDE MPLAB X.

*Pasos:*
 - Clonar este repositorio.
 - Abrir el proyecto en MPLAB X.
 - Compilar el archivo principal verificando que se incluya la librería excore.h y bootloader.h.
 - Conectar la placa mediante USB.
 - Flashear el archivo .hex resultante usando la herramienta de carga de Protolink.

*Visualización de Logs:*
 - Conectar la placa por USB-Serial.
 - Abrir una terminal.
 - Configurar a 115200 baudios.

**6. Evidencia**

   
<img width="279" height="315" alt="image" src="https://github.com/user-attachments/assets/63f6c7b6-2900-4bba-921c-22c123633f9d" />

*Captura de la terminal serial en Galio Flash Tool mostrando el flujo de datos: conversión de estados del DIP Switch a valores decimales y binarios.*

<img width="240" height="320" alt="image" src="https://github.com/user-attachments/assets/60c4b86e-2ac7-448c-98f4-0b7f0f4e42d9" />


*Vista superior del sistema: Interfaz de entrada (DIP Switch rojo) y respuesta visual en los LEDs de salida (LD4, LD5, LD6).*


<img width="240" height="405" alt="image" src="https://github.com/user-attachments/assets/09283d2c-1365-4ee2-9b91-819931075ec3" />

*Hardware Protolink EX en funcionamiento durante las pruebas de control de GPIO.*


**7. Notas Técnicas / Decisiones** 

*Polling vs Interrupciones:*

Se decidió utilizar polling con un delay de 250ms. Dado que el cambio de un switch manual es una acción humana lenta, el polling es suficiente y consume menos recursos de configuración que las interrupciones por cambio de estado.

*Máscara de bits (& 0x0F):*

Se aplicó para ignorar cualquier ruido o señal en los pines superiores del puerto F, garantizando que la variable dip solo represente los 4 switches deseados.

*Control de estado:*

Se implementó una variable lectura_ant para evitar saturar el puerto serial; el sistema solo imprime y actualiza los LEDs si detecta que el valor del DIP ha cambiado respecto al ciclo anterior.

