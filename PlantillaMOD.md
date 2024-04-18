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
Documentación relacionadas con las funciones del sistema pero no se hace referencia a nada relativo a su implementación. Está orientado a las personas que van a usar el sistema no a los que lo van a mantener.  


<div id='funcional' />
## Descripción funcional

[comment]:<>* Debe describir de forma simple el propósito del sistema.
[comment]:<>* En esta sección se debe incluir una breve descripción funcional sobre lo que hace y no hace el sistema.
[comment]:<>* Se pueden incluir pequeños ejemplos para dar una visión general de las características del sistema.


<div id='tecnología' />
## Tecnología

Un listado con una breve descripción de las tecnologías usadas en el proyecto: aplicaciones, frameworks, librerías, arquitecturas,...
Por ejemplo, se puede añadir información sobre el tipo de programa, desarrollador, última versión estable y enlace a la página web oficial, entre otros detalles. 
Para añadir el enlace puede hacerlo de esta forma:

* [Code::Blocks](https://www.codeblocks.org/): Version 20.3 
* [Typora](https://typora.io/): Version 0.9.96 (beta)

También se pueden añadir los iconos representativos de las herramientas, para ello incluir la imagen como se ha descrito más arriba.  

Si se necesita hacer referencia a algunos documentos se incluyen las citas que sean necesarias [@Ejemplo1][@Ejemplo2][@Ejemplo3].


<div id='instalación' />
## Manual de instalación

Una breve descripción que explique como instalar el sistema y adecuarlo a las configuraciones particulares del _hardware_, indicando las características mínimas de _hardware_ requeridas para el funcionamiento del programa.  


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
