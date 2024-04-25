#include <stdio.h>
#include <string.h>
#include "adminprov.h"
#include "cliente.h"
#include "transportista.h"
#include "menu_administrador.h"
#include "menu_cliente.h"
#include "menutransportista.h"
#include "menuproveedor.h"

#ifdef _WIN32
#include <Windows.h>
#endif

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // establece la página de códigos de salida de la consola en UTF-8
#endif

    // Cargar los vectores de AdminProv, Clientes y Transportistas
    VectorAdminProv v_adminprovs;
    cargar_adminprov(&v_adminprovs);

    VectorClientes v_clientes;
    cargar_clientes(&v_clientes);

    VectorTransportistas v_transportistas;
    cargar_transportistas(&v_transportistas);

    AdminProv *adminProv;
    Cliente *cliente;
    Transportista *transportista;

    char email[31];
    char password[16];

    unsigned opcion = 0;
    do
    {
        printf("\n¡BIENVENIDO A ESIZON!\n");
        printf("1. Iniciar sesión como administrador/proveedor\n");
        printf("2. Iniciar sesión como cliente\n");
        printf("3. Iniciar sesión como transportista\n");
        printf("4. Salir\n");
        leer_unsigned("Introduce el número de la opción que deseas", &opcion);

        if(opcion >= 1 && opcion <= 3) {
            leer_cadena("Introduce tu email: ", email, 30);
            leer_cadena("Introduce tu contraseña: ", password, 15);
        }

        switch (opcion)
        {
        case 1:
            adminProv = buscar_adminprov_email(&v_adminprovs, email);
            if (adminProv == NULL || strcmp(password, adminProv->contrasena) != 0)
            {
                printf("Email o contraseña incorrectos\n");
            }
            else
            {
                if (strcmp(adminProv->perfil_usuario, "proveedor") == 0)
                {
                    AdminProv *proveedor = buscar_proveedor_email(&v_adminprovs, email);
                    mostrar_menu_proveedor(proveedor);
                }
                else
                {
                    mostrarMenuAdministrador(adminProv);
                }
            }
            break;
        case 2:
            cliente = buscar_cliente_por_email(&v_clientes, email);
            if (cliente == NULL || strcmp(password, cliente->contrasena) != 0)
            {
                printf("Email o contraseña incorrectos\n");
            }
            else
            {
                menu_cliente(cliente);
            }
            break;
        case 3:
            transportista = buscar_transportista_email(&v_transportistas, email);
            if (transportista == NULL || strcmp(password, transportista->contrasena) != 0)
            {
                printf("Email o contraseña incorrectos\n");
            }
            else
            {
                mostrar_menu_transportista(transportista);
            }
            break;
        case 4:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opción no válida\n");
        }
    } while (opcion != 4);

    // Guardar los vectores de AdminProv, Clientes y Transportistas
    guardar_adminprov(&v_adminprovs);
    guardar_clientes(&v_clientes);
    guardar_transportistas(&v_transportistas);
}
