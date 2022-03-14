# Proceso de selección cátedra ISDEFE
## Datos personales
|      Nombre       | Apellidos |              Grado              | Curso |
| :---------------: | :-------: | :-----------------------------: | :---: |
| Nicolae-Alexandru |  Molnar   | Grado en Ingeniería informática |  3º   |

## Retos CTF (Capture The Flag)
|   Nombre    |                                                             Descripción                                                             |   Categoría   |               Flag               |
| :---------: | :---------------------------------------------------------------------------------------------------------------------------------: | :-----------: | :------------------------------: |
|   cuckoo    | Hemos desarrollado un programa completamente resistente a cualquier tipo de ataque de desbordamiento de buffers ¡jaque mate jaquer! |  Exploiting   |                -                 |
|     ??      |                                                                  -                                                                  |     OSINT     |                -                 |
|    nope     |                                                      Chuck Testa loves Stego!                                                       | Cryptography  |                -                 |
|  pdf_leaks  |                                           La cátedra ISDEFE ha llegado a nuevos tratos...                                           |   Forensics   |    flag{fbiredacteddocument}     |
| reto_isdefe |                                           Obtención de varios flags hasta llegar al final                                           | Multi-purpose | flag{este_es_el_verdadero_final} |
 
## Documentación
La documentación del ejercicio se ha realizado utilizando el programa [Cherry Tree](https://www.giuspen.com/cherrytree/). Este programa almacena sus documentos en una estructura de directorios y nodos, todos dentro del archivo `isdefe.ctb`.

Para acceder a la documentación del ejercicio, se debe abrir el archivo `isdefe.ctb` en Cherry Tree. Sin embargo, se han subido archivos de documentación en formato pdf, almacenada de forma independiente en la carpeta de cada reto siguiendo el patrón `nombreReto/nombreReto.pdf`.

Además, accediendo al archivo `documentación_isdefe.lnk` se puede acceder a una versión web de la documentación con el mismo formato utilizado en Cherry Tree, evitando tener que instalarlo en caso de no tenerlo.

## Herramientas utilizadas
|      Herramienta       |                                     Repositorio                                      |              Referencia              |
| :--------------------: | :----------------------------------------------------------------------------------: | :----------------------------------: |
|      **strings**       |                                      Linux Apt                                       | https://linux.die.net/man/1/strings  |
|      **hexedit**       |                                      Linux Apt                                       | https://linux.die.net/man/1/hexedit  |
|      **steghide**      |                                      Linux Apt                                       |   http://steghide.sourceforge.net/   |
|     **steg-snow**      |                                      Linux Apt                                       | https://www.kali.org/tools/stegsnow/ |
|       **elftoc**       |       [Elfkickers](https://github.com/zardus/ctf-tools/tree/master/elfkickers)       |                  -                   |
| **overload_script.py** |                                        Local                                         |                  -                   |
|   **dic_creator.py**   | [python-wordlist-generator](https://github.com/agusmakmun/python-wordlist-generator) |                  -                   |
|  **snow_decrypt.py**   |                                        Local                                         |                  -                   |

## Páginas de interés
 - [Ctf-toolkit by Zardus](https://github.com/zardus/ctf-tools)
 - [Cherry Tree](https://www.giuspen.com/cherrytree/)