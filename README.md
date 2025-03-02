

De Lucas para Sergi:

--> en seleccionadores o como lo llamemos necesito
			-comands
			-cosas que no se ejecuten?
			-pipex
			-redirecciones





TO DO LUCAS empezados

-pipex para las redirecciones que esta medio hecho
-redirecciones


-borrar comentarios que no he borrado por pena de use_echo

TO DO de cosas sin empezar 

-señales
-here docks

- TO DO DUDA sobre crear

- funciones de sistema creadas a partir de export sin iguales que ademas se tienen que ver 
	cuando haces export sin nada mas ....



# minishell

## Redirecciones del proyecto

# >
	1: Redirección de salida estándar (stdout): >
	
		Descripción: Redirige la salida de un comando hacia un archivo. Si el archivo no existe, se crea. Si el archivo ya existe, se sobrescribe.

		Sintaxis:
			comando > archivo.txt

# >>
	2: Redirección de salida estándar (stdout) en modo de anexado: >>

		Descripción: Redirige la salida de un comando hacia un archivo, pero anexa la salida al final del archivo si ya existe (no sobrescribe).

		Sintaxis:
			comando >> archivo.txt

# <
	3: Redirección de entrada estándar (stdin): <

	Descripción: Toma la entrada desde un archivo en lugar de desde el teclado.

	Sintaxis:
		comando < archivo.txt

# <<
	4: Here dock: <<

	Descripcion: Permite redirigir múltiples líneas de texto directamente como entrada estándar a un comando, sin tener que escribirlas manualmente o desde un archivo.

	Sintaxis:
		comando >> archivo.txt

Hay mas redirecciones de las cuales no hay que hacer caso para este proyecto

Redirección de error estándar (stderr): 2>
Redirección de error estándar (stderr) en modo de anexado: 2>>
Redirección de salida estándar (stdout) y error estándar (stderr) a un mismo archivo: &>
Redirección de salida estándar (stdout) y error estándar (stderr) a un mismo archivo en modo de anexado: &>>
Descarte de salida: > /dev/null o 2> /dev/null


TODO

----> union de gran pipex con redirecciones

----> dejar las redirecciones bien del todo...
			---> si haces ls < archivo que no existe. da leaks
			
			---> en caasos como cat << aaa   . este ultimo aaa se queda como parte de lo que tiene que repetir, eso esta mal. pues no tendria que aparecer
			---> cuando se hace << aaa tiene que salir por pantalla normal no por archivo aleatorio

			---> tecnicamente en << pa se tiene que añadir todo el comando al historial pero no se como hacerlo 


