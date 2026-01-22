***Control de LEDs por DIP Switch - Protolink EX1.***

**1. Resumen Ejecutivo**

  Este proyecto permite el control de un arreglo de 4 LEDs mediante la lectura de un DIP Switch de 4 posiciones en la placa Protolink EX.
  El sistema traduce la entrada del switch en estados visuales y reporta en tiempo real el valor decimal y binario a través de una terminal serial.

  Features principales:
   - *Mapeo DIP a LED:* Los LEDs reflejan el valor binario ingresado por el switch.
   - *Log por UART:* Envío de logs (Valor decimal y arreglo binario).
   - *Detección de cambios:* Actualización de periféricos solo cuando cambia el estado de la entrada.
   - *Máscara de bits:* Implementación de filtrado por software para asegurar lecturas limpias en el puerto F.

**3. Periféricos Usados**

DIP Switch (GPIO Inputs): 4 entradas digitales configuradas en el puerto F.
LEDs (GPIO Outputs): 4 salidas digitales para led's.
UART/Terminal: Baudrate: 115200 (estándar de Protolink).
Timer/Delay: Uso de delay_ms para el polling de lectura y estabilización de la transmisión serial.

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

