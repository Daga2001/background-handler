
<p align='center'>
  <img width='400' heigth='450' src='https://user-images.githubusercontent.com/62605744/171186764-43f7aae0-81a9-4b6e-b4ce-af963564eafb.png'>
</p>

# background-handler
A shell which allows to manage Linux background processes in C

# Descripcion
Esta shell tiene como proposito comprender la forma en que se gestionan los procesos en el background de Linux, mediante el uso del lenguaje **C**.
Con esta herramienta se pueden crear, eliminar y llevar al background cada proceso ejecutado por medio de comandos en la terminal simulada.

# Autores
- Diego Fernando Chaverra
- David Alberto Guzman
- Juan Camilo Santa

# Consideraciones a tener en cuenta
- El shell no acepta cadenas vacias, es decir, el usuario no debe presionar **ENTER** si no ha digitado previamente algun comando.
- Se asume que hay un proceso padre que gestiona todos los hijos y que estos ultimos ejecutaran los comandos.
- La interfaz del shell es simple puesto que su proposito es estudiar mejor los procesos en **background**.

# Insumos
Abajo se listan las funciones, estructuras y variables implementadas en la shell para su funcionamiento:

## Funciones implementadas
- delete_from_bg: remueve un proceso del array **background**.
- send_to_bg: inserta un proceso en el array **background**.
- read_cmd: lee cada comando que hay almacenado en el **background**.
- len_cmds: revela la longitud del un **vector de cadenas**, el cual contiene el comando digitado por el usuario en la terminal.
- init_shell: inicializa la interfaz de inicio del shell.

## Estructuras y variables
- procesos: es una forma de abstraer los procesos, asociando el **PID** y **comando** que los representa.
- nElemBg: sirve para contabilizar la cantidad de procesos en **background**.
- notIgnoreWait: permite que un proceso padre ignore el llamado a **wait()**.
- stat: determina como fue terminado un proceso hijo. Sirve para verificar si se digita un comando inexistente.

# Update 1.3
En esta actualizacion se incluyen las siguientes mejoras:
- Se pueden validar procesos que no existan mediante el uso de **stat**.
- **wait()** es remplazado por **waitpid()** para garantizar que el padre espera a los procesos hijos que se eliminan y no a los anteriores a estos.
Ya que anteriormente, el llamado **wait(NULL)** era ignorado despues que un proceso hijo terminaba su ejecucion pero el padre ignoraba el anterior 
llamado a **wait()** puesto que se mandaba al **background** dicho proceso hijo. Recordemos que **wait()** puede ser detenido mediante la terminacion
de un proceso hijo o una señal: https://www.geeksforgeeks.org/wait-system-call-c/.
