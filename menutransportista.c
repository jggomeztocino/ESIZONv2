#include "menutransportista.h"

/* Menu transportista
 *
 * Realizaremos las funciones necesarias antes del menu
 * Menu transportista

 1. Perfil --> Permite consultar su perfil y pregunta si desea modificarlo
 2. Repartos --> Submenu : Consultar pedidos asignados , gestionar entrega de un producto pedido a domicilo o locker.
 3. Retorno --> Gestionar productospedidos no recogidos a tiempo
 4. Salir del sistema

Menu:

1. Perfil --> Permite consultar su perfil y pregunta si desea modificarlo

2. Repartos :

            -Permite consultar la lista de productos asignados y su fecha de entrega.

            -Tambien permite seleccionar un productopedido por su id para confirmar que ha sido entregado y modificar su estado , en caso de no haberlo podido entregar se deberá modificar su estado al correspondiente de no haber podido realizar la entrega.

            -Si la entrega se realiza en un locker el transportista debe asignar un codigo de locker a los productos asociando el compartimento locker al producto y actualizando el numero de compartimentos ocupados.

3 Retornos:
            -Mostrar los productos que no han sido recogidos en locker una vez pasada la fecha , permitiendo consultar esta informacion de los lockers por localidad y mostrando sus pedidos.

            -Permite seleccionar que productos han sido recogidos del locker actualizando el numero de compartimentos ocupados y eliminando el numero del locker asociado al producto, además del estado de los productos y su stock.

4. Salir del sistema
 */

/*Getion de repartos.

    Mostrará el perfil del transportista y preguntará si desea modificarlo
 */
void gestion_perfil()
{

}

/*Getion de repartos, al principio de la función cargará en memoria los vectores necesarios y al terminar los guardará

 Mostrará un submenu con las siguientes opciones:
    1. Listar productos asignados al transportista con su fecha de entrega
    2. Gestionar una entrega
    3. Salir
 */
void gestion_repartos()
{

}
/*Getion de retornos, al principio de la función cargará en memoria los vectores necesarios y al terminar los guardará

 Mostrará un submenu con las siguientes opciones:
    1. Consultar lockers por localidad y mostrando pedidos no recogidos en fecha
    2. Gestionar recogida de producto de un locker
    3. Salir
 */
void gestion_retornos()
{

}


//Mostrará las distintas opciones del menu de transportistas y seguirá mostrando el menu hasta que se seleccione salir
void mostrar_menu_transportista(VectorTransportistas *v_transportistas)
{
    /*
     Menu transportista

     1. Perfil --> Permite consultar su perfil y pregunta si desea modificarlo
     2. Repartos --> Submenu : Consultar pedidos asignados , gestionar entrega de un producto pedido a domicilo o locker.
     3. Retorno --> Gestionar productospedidos no recogidos a tiempo
     4. Salir del sistema
     */

}
