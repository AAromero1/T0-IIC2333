# :mortar_board: Tarea 0 Sistemas Operativos y Redes :mortar_board: # 

## Alvaro Romero - Fabian Mendoza ##

### Informacion general :page_facing_up: ###   

* Para compilar la tarea se tiene que usar el comando ```make``` en el mismo directorio de T0-IIC2333.
* La estructura de la tarea corresponde a:

- / (T0-IIC2333)
  - src
    - input_manager
      - manager.c
      - manager.h
    - lrsh
      - main.c
    - process
      - process.c
      - process.h
  - Makefile
  - README.md

* Donde la carpeta lrsh contiene el codigo que atiende e interpreta las instrucciones recibidas por parte del usuario y la carpeta process contiene el codigo que define la estructura de un proceso para trabajar con ellos comodamente.

* En particular, se modelaron los procesos como una doble lista ligada, esto para poder ejectuar instrucciones como ```lrlist``` y ```lrexit``` con mayor comodidad, asi se puede tener un orden en el cual iterar por sobre los procesos.

* Se realizo un proceso de testeo, donde se reviso que la consola fuera capaz de funcionar correcta y continuamente para cualquier cantidad y orden de las intrucciones.

* Finalmente comentar que para dar inicio a la ejecucion de la consola se tiene que usar ```./lrsh```

### Descripcion de las funcionalidades implementadas :clipboard: ###

1. :white_check_mark: ```hello``` : Al escribir "hello" en la consola, esta genera un nuevo proceso con fork, el cual imprime fork, para despues guardarse en la lista ligada de procesos.

2. :white_check_mark: ```sum <num_1> <num_2>``` : Al escribir "sum" seguido de dos numeros, se separa el input del usuario en los dos numeros que se reciben como argumento, los cuales son pasados a una funcion que crea un nuevo proceso con fork, el cual ejecuta la suma con los parametros recibidos. Finalemnte se agrega en la lista ligada de procesos.

3. :white_check_mark: ```is_prime <num>``` : Al escribir "is_prime" seguido de un numero, se convierte el numero que acompaña a esa instruccion a un long long number, el cual es pasado a una funcion, esta funcion genera un nuevo proceso con fork para que despues este proceso hijo ejecute la verificacion del numero y ver si es primo o no. Finalmente, se agrega a la lista ligada de procesos.

4. :white_check_mark: ```lrexec <executable> <arg1> <arg2> ... <argn>``` : Al escribir "lrexec" seguido de un ejecutable y sus argumentos, se crea un proceso hijo con fork, el que junta los parametros y ejecutable entregados en un array, para despues entregarlos a ```execvp``` el cual recibe como parametro un array de la forma ```["ejecutable", "argumentos", NULL]```, despues se agrega el proceso a la lista ligada de procesos.

5. :white_check_mark: ```lrlist``` : Al escribir "lrlist" se ejecuta in ciclo que recorre la lista ligada imprimiendo los procesos y su informacion guardada al momento de ingresarlos a la lista.

6. :white_check_mark: ```lrexit``` : Al escribir "lrexit" o presionar ctrl + c, se ejecuta un ciclo que recorre la lista ligada de atras hacia adelante mandando la señal SIGINT a cada proceso con el metodo kill(), despues espera 10 segundos y repite el ciclo, recorriendo de atras hacia adelante, pero esta vez enviando SIGKILL con el metodo kill().