PAV - P5: síntesis musical polifónica
=====================================

Obtenga su copia del repositorio de la práctica accediendo a [Práctica 5](https://github.com/albino-pav/P5) 
y pulsando sobre el botón `Fork` situado en la esquina superior derecha. A continuación, siga las
instrucciones de la [Práctica 2](https://github.com/albino-pav/P2) para crear una rama con el apellido de
los integrantes del grupo de prácticas, dar de alta al resto de integrantes como colaboradores del proyecto
y crear la copias locales del repositorio.

Como entrega deberá realizar un *pull request* con el contenido de su copia del repositorio. Recuerde que
los ficheros entregados deberán estar en condiciones de ser ejecutados con sólo ejecutar:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.sh
  make release
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A modo de memoria de la práctica, complete, en este mismo documento y usando el formato *markdown*, los
ejercicios indicados.

Ejercicios.
-----------

### Envolvente ADSR.

Tomando como modelo un instrumento sencillo (puede usar el InstrumentDumb), genere cuatro instrumentos que
permitan visualizar el funcionamiento de la curva ADSR.

* Un instrumento con una envolvente ADSR genérica, para el que se aprecie con claridad cada uno de sus
  parámetros: ataque (A), caída (D), mantenimiento (S) y liberación (R).
* Un instrumento *percusivo*, como una guitarra o un piano, en el que el sonido tenga un ataque rápido, no
  haya mantenimiemto y el sonido se apague lentamente.
  - Para un instrumento de este tipo, tenemos dos situaciones posibles:
    * El intérprete mantiene la nota *pulsada* hasta su completa extinción.
    * El intérprete da por finalizada la nota antes de su completa extinción, iniciándose una disminución
	  abrupta del sonido hasta su finalización.
  - Debera representar en esta memoria **ambos** posibles finales de la nota.
* Un instrumento *plano*, como los de cuerdas frotadas (violines y semejantes) o algunos de viento. En
  ellos, el ataque es relativamente rápido hasta alcanzar el nivel de mantenimiento (sin sobrecarga), y la
  liberación también es bastante rápida.

Para los cuatro casos, deberá incluir una gráfica en la que se visualice claramente la curva ADSR. Deberá
añadir la información necesaria para su correcta interpretación, aunque esa información puede reducirse a
colocar etiquetas y títulos adecuados en la propia gráfica (se valorará positivamente esta alternativa).

### Instrumentos Dumb y Seno.

Implemente el instrumento `Seno` tomando como modelo el `InstrumentDumb`. La señal **deberá** formarse
mediante búsqueda de los valores en una tabla.

- Incluya, a continuación, el código del fichero `seno.cpp` con los métodos de la clase Seno.
- Explique qué método se ha seguido para asignar un valor a la señal a partir de los contenidos en la tabla,
  e incluya una gráfica en la que se vean claramente (use pelotitas en lugar de líneas) los valores de la
  tabla y los de la señal generada.
- Si ha implementado la síntesis por tabla almacenada en fichero externo, incluya a continuación el código
  del método `command()`.

### Efectos sonoros.

- Incluya dos gráficas en las que se vean, claramente, el efecto del trémolo y el vibrato sobre una señal
  sinusoidal. Deberá explicar detalladamente cómo se manifiestan los parámetros del efecto (frecuencia e
  índice de modulación) en la señal generada (se valorará que la explicación esté contenida en las propias
  gráficas, sin necesidad de *literatura*).
- Si ha generado algún efecto por su cuenta, explique en qué consiste, cómo lo ha implementado y qué
  resultado ha producido. Incluya, en el directorio `work/ejemplos`, los ficheros necesarios para apreciar
  el efecto, e indique, a continuación, la orden necesaria para generar los ficheros de audio usando el
  programa `synth`.

### Síntesis FM.

Construya un instrumento de síntesis FM, según las explicaciones contenidas en el enunciado y el artículo
de [John M. Chowning](https://web.eecs.umich.edu/~fessler/course/100/misc/chowning-73-tso.pdf). El
instrumento usará como parámetros **básicos** los números `N1` y `N2`, y el índice de modulación `I`, que
deberá venir expresado en semitonos.

- Use el instrumento para generar un vibrato de *parámetros razonables* e incluya una gráfica en la que se
  vea, claramente, la correspondencia entre los valores `N1`, `N2` e `I` con la señal obtenida.
- Use el instrumento para generar un sonido tipo clarinete y otro tipo campana. Tome los parámetros del
  sonido (N1, N2 e I) y de la envolvente ADSR del citado artículo. Con estos sonidos, genere sendas escalas
  diatónicas (fichero `doremi.sco`) y ponga el resultado en los ficheros `work/doremi/clarinete.wav` y
  `work/doremi/campana.work`.
  * También puede colgar en el directorio work/doremi otras escalas usando sonidos *interesantes*. Por
    ejemplo, violines, pianos, percusiones, espadas láser de la
	[Guerra de las Galaxias](https://www.starwars.com/), etc.

### Orquestación usando el programa synth.

Use el programa `synth` para generar canciones a partir de su partitura MIDI. Como mínimo, deberá incluir la
*orquestación* de la canción *You've got a friend in me* (fichero `ToyStory_A_Friend_in_me.sco`) del genial
[Randy Newman](https://open.spotify.com/artist/3HQyFCFFfJO3KKBlUfZsyW/about).

- En este triste arreglo, la pista 1 corresponde al instrumento solista (puede ser un piano, flautas,
  violines, etc.), y la 2 al bajo (bajo eléctrico, contrabajo, tuba, etc.).
- Coloque el resultado, junto con los ficheros necesarios para generarlo, en el directorio `work/music`.
- Indique, a continuación, la orden necesaria para generar la señal (suponiendo que todos los archivos
  necesarios están en directorio indicado).

También puede orquestar otros temas más complejos, como la banda sonora de *Hawaii5-0* o el villacinco de
John Lennon *Happy Xmas (War Is Over)* (fichero `The_Christmas_Song_Lennon.sco`), o cualquier otra canción
de su agrado o composición. Se valorará la riqueza instrumental, su modelado y el resultado final.
- Coloque los ficheros generados, junto a sus ficheros `score`, `instruments` y `efffects`, en el directorio
  `work/music`.
- Indique, a continuación, la orden necesaria para generar cada una de las señales usando los distintos
  ficheros.

> NOTA:
>
> No olvide escuchar el resultado generado y comprobar que no se producen ruidos extraños o distorsiones.
> Sobre todo, tenga en cuenta la salud auditiva de quien será encargado de corregir su trabajo.

---

## Documentación del Sistema Modular de Tablas de Onda (Wavetable Instrument)

Se ha implementado un nuevo sistema modular que permite cargar y sintetizar sonidos a partir de ficheros de texto externos, sin necesidad de recompilar el código C++ para cada nuevo instrumento.

### 1. Arquitectura
El sistema consta de dos componentes principales:
*   **`WavetableLoader` (Singleton):** Gestiona la carga de ficheros `.wtb` en memoria. Implementa una caché para asegurar que, si múltiples instrumentos usan la misma tabla de ondas, esta solo se carga una vez en RAM.
*   **`InstrumentWavetable`:** Una clase de instrumento genérica que utiliza el *Loader* para obtener los datos y realiza la síntesis interpolada aplicando una envolvente ADSR.

### 2. Formato de Ficheros de Onda (.wtb)
Los ficheros de tabla de onda son simples archivos de texto que contienen muestras de **un ciclo** de la señal, separadas por espacios o saltos de línea. Los valores deben estar normalizados (preferiblemente entre -1.0 y 1.0).

**Ejemplo (`sine.wtb`):**
```text
0.0 0.707 1.0 0.707 0.0 -0.707 -1.0 -0.707
```

### 3. Configuración en la Orquesta (.orc)
Para usar este instrumento, regístrelo en su fichero `.orc` usando el nombre `InstrumentWavetable`. Debe proporcionar obligatoriamente el parámetro `file` con la ruta al fichero `.wtb`.

**Parámetros disponibles:**
*   `file`: Ruta al fichero de muestras (e.g., `work/sine.wtb`).
*   `ADSR_A`: Tiempo de ataque (segundos).
*   `ADSR_D`: Tiempo de caída (segundos).
*   `ADSR_S`: Nivel de sostenimiento (0.0 a 1.0).
*   `ADSR_R`: Tiempo de liberación (segundos).

**Ejemplo (`banda.orc`):**
```text
# Canal 1: Flauta (usando una onda senoidal suave)
1 InstrumentWavetable file=work/sine.wtb;ADSR_A=0.1;ADSR_D=0.1;ADSR_S=0.9;ADSR_R=0.2

# Canal 2: Bajo (usando una onda cuadrada o pulso)
2 InstrumentWavetable file=work/pulse.wtb;ADSR_A=0.01;ADSR_D=0.05;ADSR_S=0.8;ADSR_R=0.1
```

### 4. Partituras (.sco)
El formato de la partitura utiliza **Ticks** para el tiempo.
*   Por defecto: 120 BPM y 120 Ticks/Beat => **1 Segundo = 240 Ticks**.
*   La primera columna es el tiempo de espera (Delta Time) desde el evento anterior.

**Ejemplo (`cancion.sco`):**
```text
# Time  Cmd  Chan  Note  Vel
0       9    1     60    100   ; Empieza Nota C4 en Canal 1
0       9    2     36    80    ; Empieza Nota C2 en Canal 2 (Bajo) simultáneamente
240     8    1     60    0     ; Para Canal 1 tras 1 segundo
0       8    2     36    0     ; Para Canal 2 inmediatamente después
```

### 5. Compilación y Ejecución
Para compilar el proyecto con estas nuevas funcionalidades:
```bash
make release
```

Para ejecutar una prueba:
```bash
./bin/synth work/banda.orc work/cancion.sco work/salida.wav
```
