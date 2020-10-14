# QMK USB HID Bluepill AMILO PI2550.

WORK IN PROGRESS !!!

## Objetivo: Convertir teclado de AMILO PI 2550 en teclado USB HID con Bluepill(STM32F103C8).
A continuación detallo los pasos que he seguido utilizando el proyecto QMK(https://docs.qmk.fm/) para que un teclado de un ordenador portatil Fujitsu-Siemens AMILO PI2550 con distribución en español se pueda usar como teclado USB HID.
A pesar de existir un proyecto que ya cubre esta necesidad https://github.com/thedalles77/USB_Laptop_Keyboard_Controller se basa en la utilización de las placas Teensy.
En mi caso disponia de placas bluepill STM32F103C8 por lo que realice los ajustes necesarios basandome en `qmk_firmware\keyboards\handwired\bluepill\bluepill70`

La diferencia con el proyecto original es que en este caso utilizamos 8 filas y 15 columnas. Relamente el teclado del AMILO PI2250 monta un cable FPC de 28 pines, de los cuales solo tiene cableados los 26 primeros.
Sin embargo al hacer el escaneo de teclas se comprueba que solo son necesarios 23 hilos distribuidos en 8 filas y 15 columnas.
El proyecto original se basa en una distribución optima del teclado, por lo que practicamente todas las combinaciones de filas y columnas representan un tecla.
En el cado del AMILO PI2550 hay muchas combinaciones que no representan teclas lo cual se traslada a la matriz como KC_TRNS.

## Referencias:
Based on the [KC64 of Xydane](https://github.com/Xydane/qmk_firmware) and [FPazos](https://github.com/fpazos)

# Configuración del entorno para compilar teclados QMK
Seguir las instrucciones en https://docs.qmk.fm/#/getting_started_build_tools para configurar el entorno.


En mi caso en Windows he usado el MSYS2. Instalar MSYS: https://www.msys2.org/

Normalmente quedará instalado en `C:\msys64`
Cuidado al terminar la instalación se debe ejecutar MinGW 64-bit terminal. NOTE: This is not the same as the MSYS terminal that opens when installation is completed.

Then, run the following:
> pacman -Syu

> pacman -Su

> pacman --needed --noconfirm --disable-download-timeout -S git mingw-w64-x86_64-toolchain mingw-w64-x86_64-python3-pip

esto dejará el python instalado en c:/msys64/usr/bin/python3.exe y las toolchain de compilación

Finalmente instalamos el qmk environement 
> python3 -m pip install qmk

configurarlo con

> qmk setup
confirmar la ubicación de la carpeta `\qmk_firmware`

Reemplazar la carpeta qmk_firmware, generalmente creada en `c:\users\<usuario>\qmk_firmware` por la que obtenemos de la siguiente instruccion
> git clone --recursive https://github.com/qmk/qmk_firmware.git

Esto ultimo es necesario para que compile para chibiOS (instala los submodulos especificados en qmk_firmware/.gitmodules) De nuevo
>qmk setup
y confirmar una vez más la ubicación de la carpeta `\qmk_firmware`

# Al lio con bluepill
## Copiar teclado de referencia 
1. Creamos una copia del directorio `C:\Users\<usuario>\qmk_firmware\keyboards\handwired\bluepill` en el directorio p.ejemplo `C:\Users\<usuario>\qmk_firmware\keyboards\handwired\bluepill_emg`
2. Renombro la carpeta `C:\Users\Enrique\qmk_firmware\keyboards\handwired\bluepill\bluepill70` por `C:\Users\Enrique\qmk_firmware\keyboards\handwired\bluepill\bluepill2550`
3. Cambio nombre de bluepill70.h a bluepill2550.h y de bluepill70.c a bluepill2550.c
4. Copiamos la carpeta `C:\Users\Enrique\qmk_firmware\keyboards\handwired\bluepill_emg\keymaps\iso` en `C:\Users\Enrique\qmk_firmware\keyboards\handwired\bluepill_emg\keymaps\pilar`

## Establecer valores de trabajo para QMK
> qmk config user.keyboard=handwired/bluepill_emg/bluepill2550

> qmk config user.keymap=pilar

## Probar entorno
> qmk compile

Si todo ha ido bien nos genera los archivos .bin, .hex, .elf en la carpeta `C:\Users\<usuario>\qmk_firmware\.build` en este caso con el nombre `handwired_bluepill_emg_bluepill2550_pilar.hex`

Este fichero lo podremos grabar el STM32F103C8 con el STM32CubeProgrammer con el programador STLink, comprobar start address 0x8000000 conectar STlink y darle a download

## Ajustar al caso AMILO PI 2550
Las configuraciones realizadas consisten en editar los siguientes ficheros:
> C:\Users\Enrique\qmk_firmware\keyboards\handwired\bluepill_emg\bluepill.h

Redefinir la macro LAYOUT_seventy_iso para que tenga 15 columnas y 8 filas


> C:\Users\Enrique\qmk_firmware\keyboards\handwired\bluepill_emg\rules.mk

modificar el valor DEFAULT_FOLDER = handwired/bluepill/bluepill2550


> C:\Users\Enrique\qmk_firmware\keyboards\handwired\bluepill_emg\bluepill2550\bluepill2550.c

modificar el valor #include "bluepill2550.h"


> C:\Users\Enrique\qmk_firmware\keyboards\handwired\bluepill_emg\bluepill2550\config.h

```
#define PRODUCT "BluePillEMG"
#define MATRIX_ROWS 8
#define MATRIX_COLS 15
#define DIODE_DIRECTION COL2ROW

// Iso fix for Space Cadet, comment for ANSI layouts
#define LSPO_KEY KC_8 //tecla que se pulsa en combianacion con shift para obtener ( 
#define RSPC_KEY KC_9 //tecla que se pulsa en combianacion con shift para obtener )
```

> C:\Users\Enrique\qmk_firmware\keyboards\handwired\bluepill_emg\bluepill2550\matrix.c
```
//pongo GPIOA7, estaba uno incompatible con mi planteamiento
#ifdef BOARD_GENERIC_STM32_F103
// This could be removed, only used now in matrix_init()
#define LED_ON()    do { palClearPad(GPIOA, 7) ;} while (0)
#define LED_OFF()   do { palSetPad(GPIOA, 7); } while (0)
#endif

Definir como entradas las columnas:
static void  init_cols(void){
  palSetPadMode(GPIOB, 4, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOB, 5, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOB, 6, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOB, 7, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOB, 8, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOB, 9, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOC, 14, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOC, 15, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOA, 0, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOA, 1, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOA, 2, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOA, 3, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOA, 4, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOA, 5, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOA, 6, PAL_MODE_INPUT_PULLUP);
}
```
Leer las columnas, el orden es importante ya que debe mantener la correspondencia con el que pongamos en el fichero keymap.c. Ver fichero .xls para aclarar
```
/* Returns status of switches(1:on, 0:off) */
//  Modified by Xydane
static matrix_row_t read_cols(void){
  return ((palReadPad(GPIOB, 4)==PAL_HIGH) ? 0 : (1<<0))
    | ((palReadPad(GPIOB, 5)==PAL_HIGH) ? 0 : (1<<1))
    | ((palReadPad(GPIOB, 6)==PAL_HIGH) ? 0 : (1<<2))
    | ((palReadPad(GPIOB, 7)==PAL_HIGH) ? 0 : (1<<3))
    | ((palReadPad(GPIOB, 8)==PAL_HIGH) ? 0 : (1<<4))
    | ((palReadPad(GPIOB, 9)==PAL_HIGH) ? 0 : (1<<5))
    | ((palReadPad(GPIOC, 14)==PAL_HIGH) ? 0 : (1<<6))
    | ((palReadPad(GPIOC, 15)==PAL_HIGH) ? 0 : (1<<7))
    | ((palReadPad(GPIOA, 0)==PAL_HIGH) ? 0 : (1<<8))
    | ((palReadPad(GPIOA, 1)==PAL_HIGH) ? 0 : (1<<9))
    | ((palReadPad(GPIOA, 2)==PAL_HIGH) ? 0 : (1<<10))
    | ((palReadPad(GPIOA, 3)==PAL_HIGH) ? 0 : (1<<11))
    | ((palReadPad(GPIOA, 4)==PAL_HIGH) ? 0 : (1<<12))
    | ((palReadPad(GPIOA, 5)==PAL_HIGH) ? 0 : (1<<13))
    | ((palReadPad(GPIOA, 6)==PAL_HIGH) ? 0 : (1<<14));
}
```
Definir las filas como entradas (alta impedancia) cuando no se usen:
```
static void unselect_rows(void){
  palSetPadMode(GPIOB, 12, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 13, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 14, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 15, PAL_MODE_INPUT);
  palSetPadMode(GPIOA, 8, PAL_MODE_INPUT);
  palSetPadMode(GPIOA, 9, PAL_MODE_INPUT);
  palSetPadMode(GPIOA, 10, PAL_MODE_INPUT);
  palSetPadMode(GPIOB, 3, PAL_MODE_INPUT);  
}
```
Activar la fila seleccionada. El orden es importante ya que debe mantener la correspondencia con el que pongamos en el fichero keymap.c. Ver fichero .xls para aclarar
```
//  Modified by Xydane
static void select_row(uint8_t row){
  (void)row;
  switch (row) {
    case 0:
      palSetPadMode(GPIOB, 12, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 12);
      break;
    case 1:
      palSetPadMode(GPIOB, 13, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 13);
      break;
    case 2:
      palSetPadMode(GPIOB, 14, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 14);
      break;
    case 3:
      palSetPadMode(GPIOB, 15, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 15);
      break;
    case 4:
      palSetPadMode(GPIOA, 8, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOA, 8);
      break;
    case 5:
      palSetPadMode(GPIOA, 9, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOA, 9);
      break;
    case 6:
      palSetPadMode(GPIOA, 10, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOA, 10);
      break;
    case 7:
      palSetPadMode(GPIOB, 3, PAL_MODE_OUTPUT_PUSHPULL);
      palClearPad(GPIOB, 3);
      break;	  
  }
}
```


> C:\Users\Enrique\qmk_firmware\keyboards\handwired\bluepill_emg\keymaps\pilar\keymap.c

Mapa del teclado fisico asignado a las KC_ que representa cada posición

```
  [_NORMAL] = LAYOUT_seventy_iso(
	KC_END, KC_TRNS, KC_MINUS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSHIFT, KC_M, KC_V, KC_X, KC_C, KC_RALT, KC_TRNS, KC_TRNS, KC_TRNS, \
	KC_RIGHT, KC_ENTER, KC_UP, KC_NO, KC_TRNS, KC_INSERT, KC_LSHIFT, KC_N, KC_B, KC_Z, KC_SPACE, KC_LALT, KC_DOWN, KC_TRNS, KC_LGUI, \
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F8, KC_F7, KC_TRNS, KC_TRNS, KC_G, KC_F2, KC_F3, KC_TRNS, KC_TRNS, KC_LCTRL, KC_TRNS, \
	KC_PSCREEN, KC_NUMLOCK, KC_F12, KC_TRNS, KC_F9, KC_F6, KC_TRNS, KC_Y, KC_T, KC_F1, KC_F4, KC_TRNS, KC_F11, KC_TAB, KC_TRNS, \
	KC_DELETE, KC_TRNS, KC_0, KC_TRNS, KC_TRNS, KC_F5, KC_TRNS, KC_6, KC_5, KC_ESCAPE, KC_CAPSLOCK, KC_TRNS, KC_F10, KC_TRNS, KC_TRNS, \
	KC_HOME, KC_BSPACE, KC_P, KC_TRNS, KC_TRNS, KC_8, KC_TRNS, KC_7, KC_4, KC_2, KC_3, KC_TRNS, KC_9, KC_1, KC_TRNS, \
	KC_PGDOWN, KC_TRNS, KC_TRNS, KC_TRNS, KC_APP, KC_I, KC_TRNS, KC_U, KC_R, KC_W, KC_E, KC_TRNS, KC_O, KC_Q, KC_TRNS, \
	KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_K, KC_TRNS, KC_J, KC_F, KC_TRNS, KC_TRNS, KC_TRNS, KC_L, KC_A, KC_TRNS), 
```
Se trata de una lista de 15x8=120 valores.
Los indices de filas y columnas van de row=0...7 , col=0..15
De tal forma que si activo la fila 0 y veo un valor activo en col 0 querrá de cir que se ha presionado la tecla KC_END

Para determinar esta matriz ver .xls. Esta tabla se ha determinado con el programa arduino C:\Users\Enrique\qmk_firmware\keyboards\handwired\bluepill_emg\Utilidades EMG\Matrix_Decoder_STM32F103C8



