---
bibliography: ../Referencias.bib
biblio-style: "apalike"
link-citations: true

title: 'Metodología de la Programación'
author: 
- Esther-Lydia Silva-Ramírez  (<esther.silva@uca.es>)

---
# <span style='color:blue'> **Nombre del proyecto** </span> 

***

[comment]:<> "Los tres asteriscos añaden una línea horizontal"

## Índice 
1. [Introducción](#introducción)

2. [Documentación de usuario](#usuario)
   - [Descripción funcional](#funcional)
   - [Tecnologías](#tecnología)
   - [Instalación](#instalación)
   - [Acceso al sistema](#acceso)
   - [Manual de referencia](#referencia)
   - [Guía del operador](#operador)
   
3. [Documentación del sistema](#sistema)
   - [Especificación del sistema](#requisitos)
   - [Módulos](#módulos)
   - [Plan de pruebas](#pruebas)  

***

<div id='introducción' />
## Introducción

Este es un ejemplo de plantilla para la generación de la documentación asociada al desarrollo de un programa. Se puede usar como guía, pero puede sufrir todas las modificaciones que considere oportunas para mejorar su documento.

Es necesario incluir una portada, elemento que no se ha considerado imprescindible para este ejemplo.

Se debe añadir un índice. En Markdown, el índice de contenidos se puede estructurar con una lista ordenada. Fíjese, en el código fuente, que en cada sección se ha incorporado un identificador con una etiqueta HTML. Es muy útil porque permite la navegación.

A lo largo del documento también puede surgir la necesidad de añadir una imagen, por ejemplo:

![ImagenUCA](uca-transp1.png){:height="10px" width="10px"}

Observe en el código fuente cómo ha sido incorporada esta imagen.  



Markdown también le permite incluir código. Fíjese en el código fuente cómo está delimitado. El resultado para el típico ejemplo _Hola mundo_ en C es el siguiente:

```c
/* Programa: Hola mundo */

#include <stdio.h>

int main()
{
    printf( "Hola mundo." );
    system("PAUSE"); 
    return 0;
}
```
También puede necesitar destacar algún tema o citar o dar instrucciones. Puede resaltar añadiendo el símbolo ">" al principio de la línea, convirtiéndolo así en una cita.

> Si quiere escribir una cita 
> esto es un 
> pequeño ejemplo.

Puede consultar tutoriales, libros o blogs para profundizar más en el aprendizaje de Markdown. Es un lenguaje de marcado ligero con una sintaxis sencilla, fácil de leer y escribir con cualquier editor de texto plano. Para    



Las siguientes secciones indican cada una de las partes que se debe incluir en la documentación del programa. Hay que tener en cuenta que se trata de una tarea tediosa pero muy necesaria para realizar un buen mantenimiento del programa. Para cualquier modificación del código hay que entender el mismo, siendo de gran ayuda la documentación.

Recuerde que en la documentación del programa se distinguen dos partes claramente diferenciadas:

* Documentación interna. Documentación contenida en las líneas de comentarios del programa.
* Documentación externa. Documentación que incluye el análisis, diagramas de flujos y/o pseudocódigos, manuales de usuario con instrucciones para ejecutar el programa e interpretar los resultados. Dentro de esta se distingue a su vez:
  * Documentación del usuario
  * Documentación del sistema

En las siguientes secciones se describirá el contenido a incluir en cada uno de estos tipos de documentación. El objetivo que se debe marcar en la redacción de las mismas debe ser el de conseguir un texto claro, completo y conciso, utilizando para ello construcciones gramaticales y ortográficas correctas.  



<div id='usuario' />
# Documentación de usuario



<div id='funcional' />
## Descripción funcional

###Proposito del sistema

El objetivo de esta aplicación es implementar una versión simplificada de una plataforma de comercio electrónico online. La plataforma permitirá la adquisición de productos clasificados en diferentes categorías, así como el control de los pedidos de los clientes. Además, los clientes podrán aplicar códigos promocionales y cheques de descuento en el momento de realizar un pedido, y elegir entre la entrega a domicilio o en un punto de recogida ESILocker.

ESIZON será proveedor de los productos vendidos en la plataforma y también gestionará productos suministrados por proveedores externos, quienes se encargarán del control de sus propios productos y stock.

El sistema contará con cuatro perfiles de usuarios: cliente, administrador, proveedor y transportista. Los clientes podrán realizar búsquedas de productos, gestionar pedidos y devoluciones, y añadir dinero a la cartera, entre otras funciones. Los administradores realizarán tareas de configuración de la plataforma, como el tratamiento de clientes, productos, pedidos, devoluciones, stock, ESILockers y proveedores. Los proveedores gestionarán sus propios productos, stock y devoluciones, además de acceder a sus datos de perfil. Los transportistas actualizarán su perfil y se encargarán del reparto de pedidos asignados.

Para conservar la información entre sesiones, todos los datos de ESIZON estarán almacenados en ficheros. Al iniciar el sistema, esta información se cargará en las estructuras de datos correspondientes en memoria, y al cerrar el programa, se actualizarán los datos en los ficheros. De esta manera, el sistema funcionará en memoria principal.

##Funcionamiento


El sistema divide a los usuarios en cuatro perfiles: Usuario, Administrador, Proveedor y Transportista, cada uno con acceso a diferentes funciones.

Usuario: Al iniciar sesión, el usuario tiene acceso a las siguientes opciones:
```c
1.Perfil: Permite al usuario ver y editar su perfil.

2.Productos: Permite al usuario buscar y explorar los productos disponibles.

3.Descuentos: Permite al usuario visualizar sus códigos promocionales y cheques de descuento.

4.Pedidos: Permite al realizar pedidos y ver el historial de los mismos.

5.Devoluciones: Permite al usuario gestionar sus devoluciones.

6.Salir del sistema: Finaliza la sesión del usuario.
```

Administrador: Al iniciar sesión, el administrador tiene acceso a las siguientes opciones:
```c
1.Perfil: Permite al administrador ver y editar su perfil.

2.Clientes: Permite al administrador gestionar clientes, incluyendo alta, baja, modificación y listado.

3.Proveedores: Permite al administrador gestionar proveedores, incluyendo alta, baja, modificación y listado.

4.Productos: Permite al administrador gestionar productos, incluyendo alta, baja, modificación y listado.

5.Categorías: Permite al administrador gestionar categorías de productos.

6.Pedidos: Permite al administrador gestionar pedidos de clientes.

7.Transportista: Permite al administrador gestionar información sobre transportistas.

8.Descuentos: Permite al administrador gestionar códigos promocionales y cheques de descuento.

9.Devoluciones: Permite al administrador gestionar devoluciones.

10.Salir del sistema: Finaliza la sesión del administrador.
```
Proveedor: Al iniciar sesión, la empresa tiene acceso a las siguientes opciones:

```c
1.Perfil: Permite al proveedor ver y editar su perfil.

2.Productos: Permite a la proveedor gestionar sus productos, incluyendo alta, baja, modificación y listado.

3.Pedidos: Permite a la proveedor visualizar información y modificar el estado de los pedidos y productos que suministra.

4.Salir del sistema: Finaliza la sesión del proveedor.
```

Transportista: Al iniciar sesión, el transportista tiene acceso a las siguientes opciones:
```c
1.Perfil: Permite al transportista ver y editar su perfil.

2.Repartos: Permite al transportista gestionar la entrega de pedidos asignados.

3.Retornos: Permite al transportista gestionar devoluciones de productos.

4.Salir del sistema: Finaliza la sesión del transportista.
```
El sistema solicita al usuario que introduzca su nombre de usuario y contraseña. Una vez iniciada la sesión, se mostrará un menú correspondiente al perfil del usuario. Cada opción del menú permite realizar diferentes acciones según el perfil del usuario. Al seleccionar una opción, el usuario podrá realizar las operaciones correspondientes, y luego podrá optar por continuar utilizando el sistema o salir del mismo.


<div id='tecnología' />
## Tecnología

##Programas utilizados
* [Clion](https://www.jetbrains.com/es-es/clion/): Version 2024.1
* [Visual Studio Code](https://code.visualstudio.com/): Version 1.88


##Librerias utilizadas

* stdio.h
* string.h
* locale.h
* stdlib.h

##Librerias propias

* Utilidades.h
* Fecha.h

##Requisitos del sistema para el uso de la aplicación

**Requisitos Mínimos:**
- **Sistema Operativo:** Microsoft Windows 95, 98, NT 4
- **RAM:** 8 MB con un archivo de intercambio grande
- **Procesador:** Compatible Intel a 100 Mhz
- **Espacio en Disco Duro:** 30 MB libres

**Requisitos Recomendados:**
- **Sistema Operativo:** Microsoft Windows 2000, XP
- **RAM:** 32 MB
- **Procesador:** Compatible Intel a 400 Mhz
- **Espacio en Disco Duro:** 200 MB libres



<div id='instalación' />

## Manual de Instalación de ESIZON

### Requisitos Previos:
- **Sistema Operativo:** Windows
- **MinGW (GCC):** Instalado siguiendo los pasos del manual anterior.
- **Carpeta ESIZON:** Contiene todos los archivos necesarios para la compilación.
- **Datos:** Los ficheros de texto se encuentran en el subdirectorio "data" dentro de la carpeta ESIZON.

### Pasos para Compilar ESIZON:

1. **Descargar ESIZON:**
    - Descarga la carpeta ESIZON que contiene todos los archivos necesarios para la compilación desde la fuente correspondiente.

2. **Preparar los Datos:**
    - Asegúrate de que los ficheros de texto con los datos se encuentran en el subdirectorio "data" dentro de la carpeta ESIZON.

3. **Abrir la Consola de Comandos:**
    - Abre el Símbolo del Sistema o la Consola de Comandos de Windows.

4. **Navegar a la Carpeta ESIZON:**
    - Utiliza el comando `cd` para navegar a la carpeta ESIZON donde se encuentran los archivos del proyecto.
      ```bash
      cd ruta_a_ESIZON
      ```

5. **Compilar el Código:**
    - Utiliza el compilador GCC para compilar el código fuente de ESIZON. Asegúrate de incluir todos los archivos necesarios en el comando de compilación.
      ```bash
      gcc *.c -o esizon
      ```

6. **Ejecutar ESIZON:**
    - Una vez compilado correctamente, ejecuta el archivo ejecutable generado.
      ```bash
      esizon
      ```



<div id='acceso' />
## Acceso al sistema

Debe contener una explicación sencilla de cómo iniciarse en el sistema y cómo salir del mismo. Así como la forma de salir de los problemas más habituales.  


<div id='referencia' />
## Manual de referencia

En esta sección se describe con detalle las ventajas que ofrece el sistema a los usuarios y cómo se pueden obtener mediante su uso. Debe describir de una manera más completa y formal el uso del sistema, así como las situaciones de error y los informes generados.  


<div id='operador' />
## Guía del operador

Si el programa requiere de operador entonces se incluiría esta sección. Debe describir cómo se debe de reaccionar antes determinadas situaciones que pueden darse durante el uso del sistema.  



<div id='sistema' />
# Documentación del sistema
Documentación referida a los aspectos del análisis, diseño, implementación y prueba del _software_, así como la implantación del mismo. En general debe hacer referencia al sistema, ya que está orientada a los programadores que van a realizar el mantenimiento. Debe estar muy bien estructurada, desde lo más general a los más interno.   


<div id='requisitos' />
## Especificación del sistema

Esta sección debe describir el análisis y la especificación de requisitos. Cómo se descompone el problema en distintos subproblemas y los módulos asociados a cada uno de ellos, acompañados de su especificación. También debe incluir el plan de desarrollo del _software_.  


<div id='módulos' />
## Módulos

Debe contener una descripción de cada módulo, su funcionalidad y la interfaz. También se podría añadir código fuente.  


<div id='pruebas' />
## Plan de prueba


Debe describir todo el plan de pueba que se ha llevado a cabo. Se distinguen las realizadas a cada módulo, a la integración de los distintos módulos probándolo como un todo. Y por último la descripción del plan de pruebas de aceptación.  

### Prueba de los módulos
Incluir toda la batería de pruebas realizadas. Pruebas de caja blanca y pruebas de caja negra.  

### Prueba de integración
Incluir toda la batería de pruebas realizadas. Pruebas de caja blanca y pruebas de caja negra.  

### Plan de pruebas de aceptación
Estas pruebas deben diseñarse con el usuario del sistema. Deben describir las pruebas que son necesarias pasar para que el sistema sea aceptado por el usuario final.  



<div id='sistema' />
# Documentación del código fuente

En este punto se puede incluir toda la documentación interna que puede ser generada con [Doxygen](https://www.doxygen.nl/index.html).

La documentación interna del programa, como se ha comentado anteriormente, comprende los comentarios del programa. Durante la fase de implementación es necesario comentar adecuadamente cada una de las partes del programa. Estos comentarios se incluyen en el código fuente con el objetivo de aclarar qué es lo que hace el fragmento de código, para explicar sus elementos. 

Esta documentación ayuda a hacer más comprensible el código fuente a los programadores que deban trabajar en él, facilitando las tareas de mantenimiento. No sólo proporciona una mayor legibilidad en la actualización y modificación del código, sino también en la depuración del mismo.

<div id='referencias' />
# Referencias {-}

---
nocite: |
  @*
...
