#!/bin/bash

# Definir colores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
ROSA='\033[0;35m'
NC='\033[0m' # Sin color (restablece el color al valor predeterminado)

# Dibujo en ASCII de un gato "cute"
gato="
 /\_/\   
( o.o ) 
 > ^ <  
"
original_pwd=$(pwd)

loading_spinner() {
    spin='/-\|'
    i=0
    while true; do
        echo -ne "${spin:i%4:1}\r"   # Mostrar el spinner y sobrescribir el carácter anterior
        ((i++))                       # Incrementar el índice para el spinner
        sleep 0.1                      # Retardo para la animación
    done
}

# Función para ejecutar un comando y verificar si se ejecuta correctamente
run_test()
{

    # Ejecutar el comando en Bash y redirigir stderr a /dev/null
    bash_output=$(bash -c "$1" 2>/dev/null)
    bash_exit_code=$?

    # Ejecutar el comando en minishell y redirigir stderr a /dev/null
    minishell_output=$($1 2>/dev/null)
    minishell_exit_code=$?

    # Comparar las salidas y los códigos de salida
    if [ "$bash_exit_code" -eq "$minishell_exit_code" ] && [ "$bash_output" == "$minishell_output" ]; then
        echo -e "${GREEN}[PASSED]${NC} '$1'"
    else
            echo -e "${RED}[FAILED]${NC} '$1' "
    fi
    
    echo "Bash exit code: $bash_exit_code VS Minishell exit code: $minishell_exit_code"


}


# Imprimir la cabecera con el gato
clear
echo -e "${YELLOW}$gato${NC}"
echo -e "${YELLOW}Iniciando las pruebas en minishell...${NC}"
echo -e "${YELLOW}no compruebo leaks en este tester...${NC}"
echo -e "${YELLOW}$gato${NC}"

    loading_spinner &   # Inicia el spinner en un segundo plano
    spinner_pid=$!      # Captura el PID del spinner para poder detenerlo más tarde

# Prueba de comandos comunes
# Sección para el comando 'ls'

echo -e "${ROSA}\n---------------------------------------------${NC}"
echo -e "${ROSA}             Pruebas comunes           ${NC}"
echo -e "${ROSA}---------------------------------------------${NC}"
run_test ""
run_test " "
run_test "comando_que_no_existe"


echo -e "${ROSA}\n---------------------------------------------${NC}"
echo -e "${ROSA}             ls            ${NC}" #//13 espacios
echo -e "${ROSA}---------------------------------------------${NC}"
run_test "ls"
run_test "ls -l"
run_test "ls -llllllll"
run_test "ls -lllllla"
run_test "ls ------l"

echo -e "${ROSA}\n---------------------------------------------${NC}"
echo -e "${ROSA}             comandos aleatorios           ${NC}" #//13 espacios
echo -e "${ROSA}---------------------------------------------${NC}"
echo -e "${ROSA}   Creo una carpeta   ${NC}"
mkdir mi_carpeta
run_test "ls"
echo -e "${ROSA}   Elimino una carpeta   ${NC}"
rm -rf mi_carpeta
run_test "ls"

# Sección para el comando 'pwd'
echo -e "${ROSA}\n---------------------------------------------${NC}"
echo -e "${ROSA}             pwd            ${NC}"
echo -e "${ROSA}---------------------------------------------${NC}"
echo -e "${ROSA}   Prueba con PWD no válido   ${NC}"
export PWD="/ruta/no/existe"
run_test "pwd"     
echo -e "${ROSA}   Prueba con PWD borrado   ${NC}"
unset PWD
run_test "pwd" 
echo -e "${ROSA}   Prueba con PWD normal   ${NC}"
export PWD="$original_pwd"
run_test "pwd" 

# Sección para el comando 'echo'
echo -e "${ROSA}\n---------------------------------------------${NC}"
echo -e "${ROSA}             echo               ${NC}"
echo -e "${ROSA}---------------------------------------------${NC}"
echo -e "${ROSA}   Prueba con echo normal   ${NC}"
run_test "echo Hola Mundo" 
echo -e "${ROSA}   Prueba con echo con comillas   ${NC}"
run_test "echo "Hola Mundo" "
run_test "echo Hola Mundo "patata" patata "
echo -e "${ROSA}   Pruebas con echo y variables de entorno  ${NC}"
echo -e "${ROSA}   No existe  ${NC}"
run_test "echo $Hola "
echo -e "${ROSA}   Si existe  ${NC}"
run_test "echo $PWD"
echo -e "${ROSA}   varias  ${NC}"
run_test "echo $PWD $OLDPWD"
echo -e "${ROSA}   mix ${NC}"
run_test "echo "Hola" $PWD $DADASDA"
run_test "echo "Hola" $PWD $DADASDA HOLA"


# Sección para el comando 'cd'
echo -e "${ROSA}\n---------------------------------------------${NC}"
echo -e "${ROSA}             cd             ${NC}"
echo -e "${ROSA}---------------------------------------------${NC}"
run_test "cd /"            # Verifica si el comando 'cd' funciona (el cambio de directorio)
run_test "cd .."           # Verifica si 'cd ..' sube un nivel de directorio
run_test "cd"              # Verifica si 'cd' sin argumentos va al directorio home

echo -e "${ROSA}\n---------------------------------------------${NC}"
echo -e "${ROSA}             export     (no funciona muy bien el tester)        ${NC}"
echo -e "${ROSA}---------------------------------------------${NC}"
run_test "export"
run_test "A=patata"

echo -e "${ROSA}\n---------------------------------------------${NC}"
echo -e "${ROSA}             unset             ${NC}"
echo -e "${ROSA}---------------------------------------------${NC}"

echo -e "${ROSA}\n---------------------------------------------${NC}"
echo -e "${ROSA}             env             ${NC}"
echo -e "${ROSA}---------------------------------------------${NC}"

echo -e "${ROSA}\n---------------------------------------------${NC}"
echo -e "${ROSA}             Redirecciones           ${NC}"
echo -e "${ROSA}---------------------------------------------${NC}"
echo -e "${ROSA}   Creando archivo con env  ${NC}"
env > prueba.txt
run_test "cat prueba"
run_test "grep e prueba"
echo -e "${ROSA}   Prueba de varias creaciones  ${NC}"
ls > prueba2.txt > prueba3.txt
run_test "ls"
run_test "echo prueba2.txt prueba3.txt"
echo -e "${ROSA}   borrando pruebas   ${NC}"
rm prueba.txt prueba2.txt prueba3.txt
echo -e "${ROSA}   Prueba de no creacion  ${NC}"
env < archivo_no_exite >to
run_test "echo to"


echo -e "${YELLOW}\nFin de las pruebas.${NC}"


# Detener el spinner
kill $spinner_pid