// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //

// // // // // // //
//  HELP LIBRARY: //
// // // // // // //

#include "help.h"

void main_help()
{
    printf("\e[1m\e[96mIntegrantes:\e[97m Arnel Sanchez Rodriguez\n");
    printf("             Samuel Efrain Pupo Wong\n");
    printf("\e[1m\e[96mGrupo:\e[97m C-212\n");
    printf("\e[1m\e[96mCurso:\e[97m 2019-2020\n");
    printf("\n\e[1m\e[95mFuncionalidades Implementadas:\n");
    printf("\e[1m\e[92m[1-8] basic: funcionalidades basicas\e[0m                                         (3.0 puntos)\n");
    printf("\e[1m\e[92m[9]   multi-pipe: multiples tuberias en una sola linea\e[0m                       (1.0 punto)\n");
    printf("\e[1m\e[92m[10]  background: procesos en segundo plano\e[0m                                  (0.5 puntos)\n");
    printf("\e[1m\e[92m[11]  spaces: cualquier cantidad de espacios entre los comandos y parametros\e[0m (0.5 puntos)\n");
    printf("\e[1m\e[92m[12]  history: historial de comandos\e[0m                                         (0.5 puntos)\n");
    printf("\e[1m\e[92m[13]  ctrl+c: capturar y enviar señales a procesos\e[0m                           (0.5 puntos)\n");
    printf("\e[1m\e[92m[14]  chain: comandos encadenados\e[0m                                            (0.5 puntos)\n");
    printf("\e[1m\e[92m[15]  if: expresiones condicionales\e[0m                                          (1.0 punto)\n");
    printf("\e[1m\e[92m[16]  multi-if: multiples condicionales en una sola linea \e[0m                   (0.5 puntos)\n");
    printf("\e[1m\e[92m[17]  help: ayuda\e[0m                                                            (1.0 punto)\n");
    printf("\e[1m\e[92m[18]  variables: variables y comillas invertidas\e[0m                             (1.0 punto)\n");
    printf("\e[1m\e[92m[19]  extras: control de teclas especiales y editor de texto\e[0m                 (-.- punto)\n");
    printf("\n\e[1m\e[95mComandos built-in:\n");
    printf("\e[1m\e[92m[2]  cd: cambia de directorio\n");
    printf("\e[1m\e[92m[8]  exit: cierra el shell\n");
    printf("\e[1m\e[92m[10] jobs: lista todos los procesos que estan en el background\n");
    printf("\e[1m\e[92m     fg: envia un proceso del background hacia el foreground\n");
    printf("\e[1m\e[92m[12] history: lista los ultimos comandos ejecutados\n");
    printf("\e[1m\e[92m     again: vuelve a ejecutar un comando del history\n");
    printf("\e[1m\e[92m[14] true: retorna (exit status) 0\n");
    printf("\e[1m\e[92m     false: retorna (exit status) 1\n");
    printf("\e[1m\e[92m[15] if: marca el inicio de una expresion condicional\n");
    printf("\e[1m\e[92m[17] help: muestra la ayuda\n");
    printf("\e[1m\e[92m[18] set: declara e imprime variables\n");
    printf("\e[1m\e[92m     get: imprime una variable declarada\n");
    printf("\e[1m\e[92m     unset: elimina una variable declarada\n");
    printf("\e[1m\e[92m[19] editext: abre un editor de texto\n");
    printf("\n\e[1m\e[92mTotal:\e[0m 10 puntos\n");
}

void basic_help()
{
    printf("\e[1m\e[96mBasic:\n");
    printf("\e[1m\e[95m[1] Al ejecutar el programa imprimir el prompt.\n");
    printf("\e[0mNuestro Shell presenta un Prompt, el cuál quisimos hacer lo más parecido posible a bash, para eso obtenemos el directorio sobre el cual el usuario ejecuta el software con la función getenv(HOME) truncada con el resultado de ejecutar la función getcwd(), capturamos el nombre del usuario con la función getenv(USER), generando así un char* que une la información obtenida anteriormente, modificamos el texto, en negrita y el color de letra, dicho char* se lo enviamos a readline() que es el encargado de mostrarlo a través de la consola.\n");
    printf("\e[1m\e[95m[2] Ejecutar comandos e imprimir la salida de estos.\n");
    printf("\e[0mPara la ejecución de los comandos creamos una estructura command que contiene char** args, en la que se almacena el comando y sus argumentos, y char** redir en la que se almacenan los caracteres de redireccionamiento y su redirección. Lugo que el comando se encuentra almacenado; se dirige a la sección de ejecución, llega a la función execute en la que se distingue si es un comando built-in o si es un comando del sistema. En caso de ser un comando built-in se ejecuta la función creada para ese comando expecíficamente, de lo contrario se le hace fork() al proceso actual, a través de los pid ejecutamos mediante execvp() en el processo hijo y después con waitpaid() esperamos a que termine de procesarse, si no es un proceso de bg.\n");
    printf("\e[1m\e[95m[3] Ejecutar el comando CD.\n");
    printf("\e[0mPara la ejecución del comando cd distinguimos a través de la información almacenada en command->args[1], de ser null se cambiará el directorio actual a getenv(HOME), de lo contrario se cambiará el directorio al directorio almacenado en command->args[1] con la función chdir().\n");
    printf("\e[1m\e[95m[4] Redirigir entrada y salida estándar.\n");
    printf("\e[0mPara los redireccionamientos utilizamos la estructura que creamos para almacenar los comandos, distinguimos el tipo de direccionamiento que se tiene que procesar, y en dependencia de cuál sea son los flags que se le pasan a la función open() (O_RDONLY,O_WRONLY, O_CREAT, O_TRUNC, O_APPEND), es la operación qu ese realizará, además le pasamos 00700 a la función open() para darle permisos de administrador a las operaciones, esta función devuelve un FileDescriptor, con la función dup2() hacemos una copia del FileDescriptor y le cambiamos la entrada y la salida estándar respectivamente.\n");
    printf("\e[1m\e[95m[5] Usar una tubería.\n");
    printf("\e[0mPara la ejecución de los PIPES, utilizamos la estructura command, almacenamos pipe(|) como un comando, creamos un array bidimensional con tamaño igual a 2x2,en la fila 0 estaría el comando que se encuentra ubicado a la izquierda del pipe y el la 1 estaría el comando que se encuentra ubicado a la derecha del pipe, a la función pipe() le pasamos cada fila del array para crear los pipes, en la columna 0 tenemos el FileDescriptor en que puede leer y en la columna 1 el FileDescriptor en el que puede escribir, mandamos a ejecutar y cerramos los pipes con la función close().\n");
    printf("\e[1m\e[95m[6] Una vez terminado el comando previo, se muestra el prompt nuevamente.\n");
    printf("\e[0mPara que se ejecute el Prompt después de procesar cada línea, hicimos un while utilizando la función control que devuelve 1 siempre y cuando no se inserte el comando exit y en el do hacemos la llamada a readline() que imprime el Prompt.\n");
    printf("\e[1m\e[95m[7] Sólo hay un espacio entre los tokens de la entrada.\n");
    printf("\e[0mCuando se garantiza que existe un solo espacio entre los tokens, después de capturar la línea, el parser la divide en argumentos y redirecciones,esta separación la hace cortando cada vez que se encuentra un espacio.\n");
    printf("\e[1m\e[95m[8] Además.\n");
    printf("\e[0mEn el caso de que la línea contenga un #, nuestro Shell procesa la línea hasta encontrarlo, al detectarlo termina de procesar la línea e ignora lo que está a continuación.\n");
    printf("Para la ejecución del comando exit se busca que no pertenezca al backgrund, se envía una señal de terminación al programa y devuelve 0 la función execute() y la función control() que terminan el while, se libera la memoria y se termina el programa, de pertenecer se ignora su función.\n");
}

void multi_pipe_help()
{
    printf("\e[1m\e[96mMulti-pipe:\n");
    printf("\e[1m\e[95m[9] Multiples tuberías en una sola línea.\n");
    printf("\e[0mPara la ejecución de múltiple PIPES, utilizamos la estructura command, almacenamos pipe(|) como un comando, creamos un array bidimensional con tamaño igual a 2 por la cantidad de pipes de la línea y 2(pipes[2 * count.pipes][2]),en la fila i estaría el comando que se encuentra ubicado a la izquierda del pipe y el la i+1 estaría el comando que se encuentra ubicado a la derecha del pipe. A la función pipe(), pasamos cada fila del array para crear los pipes, en la columna 0 tenemos el FileDescriptor en que puede leer y en la columna 1 el FileDescriptor en el que puede escribir, mandamos a ejecutar y cerramos los pipes con la función close().\n");
}

void background_help()
{
    printf("\e[1m\e[96mBackground:\n");
    printf("\e[1m\e[95m[10] Procesos en segundo plano.\n");
    printf("\e[0mEl bg funciona utilizando una lista enlazada de jobs. Cuando la línea termina en &, se toma la línea y el pid de la lista de comandos resultantes y se guardan en jobs. No se hace waitpaid a esas ejecuciones.\n");
    printf("El comando fg{numero} devuelve a fg la ejecución en bg cuyo id coincida con el número deseado\n");
    printf("Hay unos casitos en los que no funciona bien, por ejemplo, Ctrl+C mata a los procesos en bg, además de que existen casos donde el bg corrompe el Shell, por ejemplo cuando ejecutas con el Shell el propio Shell en bg.\n" );
}

void spaces_help()
{
    printf("\e[1m\e[96mSpaces:\n");
    printf("\e[1m\e[95m[11] Cualquier cantidad de espacios entre los comandos y parametros.\n");
    printf("\e[0mCuando no se garantiza que existe un solo espacio entre los tokens, definimos ciertos caracteres como comandos separadores(definidos en el enum character) de manera que nuestro Shell divida por estos comandos en caso de que no haya espacios y si hay más de uno, nuestro Shell los ignora hasta que se encuentra con un caracter distinto.\n");
}

void history_help()
{
    printf("\e[1m\e[96mHistory:\n");
    printf("\e[1m\e[95m[12] Historial de comandos.\n");
    printf("\e[0mPara la ejecución del history, hicimos uso de un array circular de tamañno 100, con dos punteros(first y last), este se actualiza con cada línea entrada al Shell. Cuando se utiliza el comando again se sobreescribe lo recibido por la linea del historial deseada, en caso de ser correcta.\n");
}

void ctrl_c_help()
{
    printf("\e[1m\e[96mCtrl+C:\n");
    printf("\e[1m\e[95m[13] Implementar la posibilidad de dar Ctrl+C en el prompt.\n");
    printf("\e[0mNuestro Shell permite que cuando un comando se está ejecutando se le pueda interrumpir presionando Cntrl+C, captura la señal, a través de un manejador de señales(sig_handler) que se encarga de enviar la señal SIGINT y si el proceso decide ignorarla y seguir ejecutándose, a la segunda presión del Ctrl+C se le envía la señal SIGKILL que termina el proceso completamente.\n");
}

void chain_help()
{
    printf("\e[1m\e[96mChain:\n");
    printf("\e[1m\e[95m[14] Operadores para encadenar comandos.\n");
    printf("\e[0mLos operadores para encadenar comandos son tratados con las misma estructura que los comandos en general. Su análisis se hace a manera de cortocircuito, en dependencia del enlace utilizado.\n");
}

void if_help()
{
    printf("\e[1m\e[96mIf-Then-Else:\n");
    printf("\e[1m\e[95m[15] Expresiones Condicionales.\n");
    printf("\e[0mLas expresiones condicionales se reciben de manera similar a las cadenas de comandos. Al recibir un if, ser ejecuta todo lo que antecede al then. Luego, se analiza si termina directamente en end o si existe una expresion else antes. En el primer caso, se ejecuta la expresion posterior al then si fue 0 el valor recibido de la ejecucion del if, sino se ejecuta la expresion posterior al else.\n");
}

void multi_if_help()
{
    printf("\e[1m\e[96mMulti-If-Then-Else:\n");
    printf("\e[1m\e[95m[16] Múltiples condicionales en una sola línea.\n");
    printf("\e[0mSe analiza de igual manera que las condicionales simples, pero se controla la cantidad de if-end anidados con un contador(a manera de parentesis balanceados).\n");
}

void help_help()
{
    printf("\e[1m\e[96mHelp:\n");
    printf("\e[1m\e[95m[17] Muestra las funcionalidades del shell y algunos detalles de su implementacion.\n");
    printf("\e[0mNuestro Shell tiene un help que le brinda al usuario una explicación de todo lo implementado por nosotros.\n");
}

void variables_help()
{
    printf("\e[1m\e[96mVariables:\n");
    printf("\e[1m\e[95m[18] Variables y comillas invertidas.\n");
    printf("\e[0mPara la manipulación de las variables creamos una estructura variables que cuenta con un char**var en la que se almacenan los nombres de las variables y un char**value en el que almacenamos el valor de la variable, si el usuario inserta la variable directamente se inserta directo en la estructura pero si la inserta con una expresión evaluable, tokenizamos y ejecutamos los parámetros redireccionando a un archivo temporal del que leemos el resultado de la evaluación, asignamos y eliminamos el archivo y si se inserta el comando de get solamente se retorna la estructura completa para la impresión. En el caso de get recorremos la estructura y si el parámetro coincide con el nombre de la variable retornamos el valor. En el caso de unset recorremos la estructura y si el parámetro coincide con el nombre de la variable eliminamos dicha variable de la estructura. La expresion interior a las comillas invertidas se ejecuta usando como salida un archivo temporal. Luego, el contenido de dicho archivo se guarda en la variable deseada.\n");
}

void extras_help()
{
    printf("\e[1m\e[96mExtras:\n");
    printf("\e[1m\e[95mOperaciones con readline:\n");
    printf("\e[0mPara que nuestro Shell fuera lo más precido posible a bash, nos propusimos capturar ciertas teclas para darle distintas fucionalidades, para implementar lo dicho anteriormente tuvimos que hacer uso de la librería de GNU readline, la cual nos permite movernos por la línea que estamos escribiendo, autocompletar en caso de que estemos trabajando con ficheros, y navegar por el historial de comandos. Utilizamos la función readline() para interactuar con la consola, y la función add_history() para interactuar con el historial de comandos que habíamos creado nosotros. De la existencia de esta librería nos enteramos después de haber tenido un historial hecho por nosotros, así que para mantener nuestro historial y vincularlo con esta función agregamos, cada vez que se inicia el software, los 100 comandos de nuestro historial, y durante la ejecución se van insertando según el usuario va ejecutando.\n\n");
    printf("Cuando se escribes hasta el final de la línea esta regresa al principio y se sobreescribe, por lo tanto después cuando se navegue por el history con las teclas de dirección mostrará problemas.\n");
    printf("\e[1m\e[95mComando editext<value>:\n");
    printf("\e[0mCreamos un comando nuevo, editext <value>, que abre el editor de texto Kilo Editor v=0.0.1, el cuál esta implementado por Salvatore Sanfilippo. Durante la investigación que realizamos sobre la terminal en modo Raw, nos encontramos con un tutorial en Internet donde dicho colega explica exhaustivamente como desarrollar un proyecto, específicamente un editor de texto, cambiando la terminal a modo Raw, después de haber estudiado el tutorial, decidimos insertar el editor en nuestro Shell.\n\n");
    printf("Originalmente no teníamos pensado la librería readline() e implementar nosotros las funcionalidades anteriormente mencionadas, pero debido a un desperfecto técnico casi de última hora(muerte de disco duro) perdimos todo lo avanzado durante en el desarrollo de nuestra biblioteca y con falta de tiempo no pudimos comenzar desde el principio, por tanto decidimos incluir readline().\n\n");
    printf("\n");
}

void select_help(char **tokens, int *status)
{
    *status = 0;
    if (tokens[1] == NULL)
        main_help();
    else if (!strcmp(tokens[1], "basic"))
        basic_help();
    else if (!strcmp(tokens[1], "multi-pipe"))
        multi_pipe_help();
    else if (!strcmp(tokens[1], "background"))
        background_help();
    else if (!strcmp(tokens[1], "spaces"))
        spaces_help();
    else if (!strcmp(tokens[1], "history"))
        history_help();
    else if (!strcmp(tokens[1], "ctrl+c"))
        ctrl_c_help();
    else if (!strcmp(tokens[1], "chain"))
        chain_help();
    else if (!strcmp(tokens[1], "if"))
        if_help();
    else if (!strcmp(tokens[1], "multi-if"))
        multi_if_help();
    else if (!strcmp(tokens[1], "help"))
        help_help();
    else if (!strcmp(tokens[1], "variables"))
        variables_help();
        else if (!strcmp(tokens[1], "extras"))
        extras_help();
    else
    {
        *status = 1;
        printf("help: no help topics match '%s'.  Try 'help help'.\n", tokens[1]);
    }
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //