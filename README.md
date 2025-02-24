

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

## Redirecciones

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

			
Redirección de entrada estándar (stdin): <

Descripción: Toma la entrada desde un archivo en lugar de desde el teclado.
Sintaxis:
bash
Copy
comando < archivo.txt
Redirección de error estándar (stderr): 2>

Descripción: Redirige la salida de error (stderr) hacia un archivo. El número 2 hace referencia al descriptor de archivo para errores (stderr).
Sintaxis:
bash
Copy
comando 2> archivo_error.txt
Redirección de error estándar (stderr) en modo de anexado: 2>>

Descripción: Redirige la salida de error y anexa los errores al final de un archivo de log de errores.
Sintaxis:
bash
Copy
comando 2>> archivo_error.txt
Redirección de salida estándar (stdout) y error estándar (stderr) a un mismo archivo: &>

Descripción: Redirige tanto la salida estándar como la salida de error a un archivo, sobrescribiendo el archivo.
Sintaxis:
bash
Copy
comando &> archivo.txt
Redirección de salida estándar (stdout) y error estándar (stderr) a un mismo archivo en modo de anexado: &>>

Descripción: Redirige tanto la salida estándar como la salida de error a un archivo, pero anexa la salida al archivo si ya existe.
Sintaxis:
bash
Copy
comando &>> archivo.txt
Descarte de salida: > /dev/null o 2> /dev/null

Descripción: Redirige la salida estándar o la salida de error a /dev/null, que es un "agujero negro" que descarta cualquier dato enviado allí.
Sintaxis para salida estándar:
bash
Copy
comando > /dev/null
Sintaxis para error estándar:
bash
Copy
comando 2> /dev/null