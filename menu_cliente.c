#include <stdio.h>
#include "menu_cliente.h"

/*
 Funciones del menu del cliente

A)Perfil mostrar perfil del cliente y preguntarle si quiere modificar, llamar a modificar

B)Productos  mostrar un listado de los productos buscados por id o por categoría, preguntar cual quiere.


C) Descuentos  :

Funciones necesarias:
void consultar_descuentos(Cliente* cliente); para mostrar los códigos promocionales y cheques regalo asignados al cliente.

D) Pedidos:

Funciones necesarias:
-Realizar un pedido , Preguntar si quiere listar todos los productos o buscar alguno por id o por categoría. Deberá seleccionar el producto y el sistema debe comprobar que hay
stock suficiente , el sistema seguirá permitiendo añadir
productos al pedido hastvoid recoger_pedido(Cliente* cliente, Pedido* pedido, char* codigo_locker); para recoger un pedido depositado en un locker.a que el cliente decida parar.
Entonces el sistema deberá preguntar si el cliente quiere
que se le entregue a domicilio o en un locker , tras esto
el sistema deberá gestionar la petición. Por ultimo
el sistema deberá preguntar si el cliente desea aplicar algun codigo promocional o cheque regalo , si la respuesta es afirmativa
le permitirá seleccionar 1 y lo aplicará al importe total del pedido , al finalizar se le debe mostrar un desglose del pedido con su importe correspondiente y el importe tras haber aplicado el descuento.

Una vez confirmado el pedido se debe de restar la cantidad pedida por el cliente de cada stock de los productos correspondientes.


- Mostrar los datos del pedido de un cliente mediante el id del pedido

-  Otra opción para el cliente es la recogida de un pedido que haya sido depositado en
un ESILocker antes de la fecha de caducidad, para ello se le debe mostrar la opción
solicitándole el código locker asociado. Una vez introducido, el sistema mostrará un
mensaje en pantalla indicando el número de compartimentos que se ha abierto. El estado
de los productos recogidos, en consecuencia, se debe actualizar.



E) Devoluciones:

-Permitirá al cliente realizar Devoluciones de productos que se le hayan entregado(importante comprobar esto), se le
preguntará si quiere listar los productos de un pedido en concreto(por id) o si quiere listar todos sus
pedidos entregados(los cuales tengan productos cuya fecha de devolución no haya caducado), en el momento en el
 que el cliente selecciona un producto a devolver se crea una devolución con el estado de pendiente.

-El cliente puede consultar sus devoluciones.

F) Salir

 Realizaremos primero las distintas funciones necesarias antes de realizar el menu
 * Opciones:
 * 1. Perfil
 * 2. Productos
 * 3. Descuentos
 * 4. Pedidos
 * 5. Devoluciones
 * 6. Salir del sistema
 *
 * El menú deberá mostrarse mientras el usuario no elija la opción 6.
 */

void perfil_cliente()
{

}

//Menu que pregunta si se quiere listar los productos por id o categoria
void listado_productos()
{

}


void realizar_pedido()
{

}

//Gestionar la recogida de un pedido depositado en un locker antes de la fecha de caducidad
void gestionar_recogida()
{

}
//Mostrará las distintas opciones de realizar un pedido , gestionar la recogida de alguno de un locker o consultar
//el estado de cada uno de los productos de un pedido concreto
void gestionar_pedidos()
{

}

//Lista todos los descuentos del cliente diferenciando entre cheques regalo y codigos promocionales
void listar_descuentos()
{

}



/*Se preguntará que producto quiere devolver para
  mostrar su informacion, previamente hay que comprobar si el
  productó se puede devolver comprobando al fecha correspondiente.

  Se solicitará una confirmación de devolucion para despues actualizar los estados
  correspondientes
 */
void realizar_devolucion()
{

}

//Permite consultar el estado de las devoluciones realizadas por el cliente
void consultar_devoluciones()
{

}


void menu_cliente(VectorClientes* v_clientes, VectorProductos* v_productos, VectorPedidos* v_pedidos, VectorDescuentos* v_descuentos, VectorDevoluciones* v_devoluciones, VectorDescuentosClientes* v_descuentos_clientes, VectorProductosPedido* v_productos_pedido)
{

    /*
    * Opciones:
     * 1. Perfil
     * 2. Productos
     * 3. Descuentos
     * 4. Pedidos
     * 5. Devoluciones
     * 6. Salir del sistema
     *
     * El menú deberá mostrarse mientras el usuario no elija la opción 6.
     */

}