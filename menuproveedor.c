#include "menuproveedor.h"
#include <stdio.h>
#include <string.h>
void gestion_perfil(AdminProv *prov)
{
    listar_adminprov(prov);

    // Preguntar si quiere modificar
    char respuesta;
    printf("¿Desea modificar su perfil? (s/n): ");
    leer_caracter("Introduce una opcion valida", &respuesta);
    if (respuesta == 's' || respuesta == 'S')
    {
        unsigned opcion;
        do
        {
            printf("\nMenu gestion perfil\n\n");
            printf("1. Modificar nombre\n");
            printf("2. Modificar email\n");
            printf("3. Modificar contrasena\n");
            printf("4. Salir del sistema\n");
            leer_unsigned("Seleccione una opcion: ", &opcion);
            switch (opcion)
            {
            case 1:
                modificarNombre(prov);
                break;
            case 2:
                modificarEmail(prov);
                break;
            case 3:
                modificarContrasena(prov);
                break;
            case 4:
                break;
            default:
                printf("\nOpción no valida\n");
            }
        } while (opcion != 4);
    }
}

void gestion_productos(AdminProv *proveedor)
{
    VectorProductos v_productos;
    VectorCategorias v_categorias;

    unsigned opcion;
    do
    {
        printf("\nMenu gestion productos\n\n");
        printf("1. Dar de alta un producto\n");
        printf("2. Dar de baja un producto\n");
        printf("3. Listar productos\n");
        printf("4. Modificar productos \n");
        printf("5. Salir del sistema\n");
        leer_unsigned("Seleccione una opcion: ", &opcion);
        switch (opcion)
        {

        case 1:
            cargar_productos(&v_productos);
            cargar_categorias(&v_categorias);
            alta_producto_proveedor(&v_productos, &v_categorias, proveedor->id_empresa);
            guardar_productos(&v_productos);
            guardar_categorias(&v_categorias);
            break;
        case 2:
            cargar_productos(&v_productos);
            char id_producto[8];
            leer_cadena("\nIntroduce el ID de un producto a dar de baja:", id_producto, 8);

            Producto *producto = buscar_producto_id(&v_productos, id_producto);
            if (producto == NULL)
            {
                printf("\n El producto no existe\n");
                return;
            }

            if (strcmp(producto->id_gestor, proveedor->id_empresa) != 0)
            {
                printf("El producto no pertenece a este gestor \n");
                return;
            }
            baja_producto(&v_productos, producto->id_producto);
            guardar_productos(&v_productos);
            break;
        case 3:
            cargar_productos(&v_productos);
            listar_productos_gestor(&v_productos, proveedor->id_empresa);
            guardar_productos(&v_productos);
            break;
        case 4:
            cargar_productos(&v_productos);
            cargar_categorias(&v_categorias);
            leer_cadena("Introduce el ID de un producto a dar de baja:", id_producto, 8);

            Producto *prod = buscar_producto_id(&v_productos, id_producto);

            if (prod == NULL)
            {
                printf("\nEl producto no existe\n");
                return;
            }

            if (strcmp(prod->id_gestor, proveedor->id_empresa) != 0)
            {
                printf("\nEl producto no pertenece a este gestor \n");
                return;
            }
            listar_producto(modificar_producto_prov(prod, &v_categorias));

            guardar_productos(&v_productos);
            guardar_categorias(&v_categorias);

            break;
        case 5:
            break;
        default:
            printf("\nOpcion no valida\n");
        }
    } while (opcion != 5);
}
/*
 Un usuario proveedor podrá acceder únicamente a la información de los pedidos de productos
que él mismo suministra. Lógicamente podrá gestionar el estado de dichos pedidos de
productos, asignar transportistas, lockers, etc.

 */

void gestion_pedidos(AdminProv *proveedor)
{
    VectorProductos v_productos;
    VectorPedidos v_pedidos;
    VectorProductosPedido v_productos_pedido;
    VectorTransportistas v_transportistas;
    unsigned opcion;

    do
    {
        printf("\nMenu gestion pedidos\n\n");
        printf("1. Listar pedidos de un producto\n");
        printf("2. Modificar pedidos\n");
        printf("3. Salir del sistema\n");
        leer_unsigned("Seleccione una opcion: ", &opcion);
        switch (opcion)
        {

        case 1:
            cargar_productos(&v_productos);
            cargar_pedidos(&v_pedidos);
            cargar_productos_pedido(&v_productos_pedido);
            char id_producto[8];
            leer_cadena("\nIntroduce el ID de un producto a listar pedidos:", id_producto, 8);

            Producto *producto = buscar_producto_id(&v_productos, id_producto);
            if (producto == NULL)
            {
                printf("\nEl producto no existe \n");
                return;
            }

            if (strcpy(producto->id_gestor, proveedor->id_empresa) != 0)
            {
                printf("\nEl producto no pertenece a este gestor \n");
                return;
            }

            unsigned numero = listar_productospedidos_proveedor(proveedor->id_empresa, &v_productos, &v_productos_pedido);
            if (numero == 0)
            {
                printf("\nNo hay pedidos para este producto\n");
            }

            guardar_productos_pedido(&v_productos_pedido);
            guardar_pedidos(&v_pedidos);
            guardar_productos(&v_productos);
            break;

        case 2:
            cargar_productos(&v_productos);
            cargar_pedidos(&v_pedidos);
            cargar_productos_pedido(&v_productos_pedido);
            cargar_transportistas(&v_transportistas);
            char id_pedido[8];

            // Buscar pedido
            leer_cadena("\nIntroduce el ID de un pedido: ", id_pedido, 8);
            Pedido *pedido = buscar_pedido_por_id(&v_pedidos, id_pedido);
            if (pedido == NULL)
            {
                printf("\nEl pedido no existe\n");
                return;
            }
            // Buscar producto
            leer_cadena("\nIntroduce el ID de un producto modificar en el pedido: ", id_producto, 8);
            Producto *prod = buscar_producto_id(&v_productos, id_producto);

            if (prod == NULL)
            {
                printf("\nEl producto no existe \n");
                return;
            }

            // Comprobar que existe un producto pedido en ese pedido con ese ID
            ProductoPedido *productoPedido = buscar_producto_pedido(&v_productos_pedido, id_pedido, id_producto);
            if (productoPedido == NULL)
            {
                printf("\nEl producto no existe en el pedido \n");
                return;
            }

            // Comprobar que el producto lo gestiona el proveedor
            if (strcmp(prod->id_gestor, proveedor->id_empresa) != 0)
            {
                printf("\nEl producto no pertenece a este proveedor \n");
                return;
            }

            enviar_producto_pedido(productoPedido, &v_transportistas);

            guardar_pedidos(&v_pedidos);
            guardar_productos(&v_productos);
            guardar_productos_pedido(&v_productos_pedido);
            guardar_transportistas(&v_transportistas);
            break;
        case 3:
            break;
        default:
            printf("\nOpcion no valida\n");
        }
    } while (opcion != 3);
}

void mostrar_menu_proveedor(AdminProv *proveedor)
{

    unsigned opcion;
    do
    {
        printf("\nMenu proveedor\n\n");
        printf("1. Perfil\n");
        printf("2. Productos\n");
        printf("3. Pedidos\n");
        printf("4. Salir del sistema\n");
        leer_unsigned("Seleccione una opcion: ", &opcion);
        switch (opcion)
        {

        case 1:
            gestion_perfil(proveedor);
            break;
        case 2:
            gestion_productos(proveedor);
            break;
        case 3:
            gestion_pedidos(proveedor);
            break;
        case 4:
            break;
        default:
            printf("\nOpcion no valida\n");
        }
    } while (opcion != 4);
}