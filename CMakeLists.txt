cmake_minimum_required(VERSION 3.22.1)
project(ESIZON C)

# Establece el estándar del lenguaje C al estándar ANSI C (C89/C90)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED True)
#set(CMAKE_C_EXTENSIONS OFF)

include_directories(.)

add_executable(
        ESIZON
        adminprov.h
        categoria.h
        cliente.c
        cliente.h
        compartimentolocker.h
        descuentos.h
        descuentos.c
        devoluciones.c
        devoluciones.h
        fecha.c
        fecha.h
        locker.h
        menu_administrador.c
        menu_administrador.h
        menu_cliente.c
        menu_cliente.h
        pedido.h
        pedido.c
        productos.h
        productos.c
        transportista.h
        transportista.c
        utilidades.c
        utilidades.h
        locker.c
        categoria.c
        adminprov.c
        menutransportista.c
        menutransportista.h
        menuproveedor.c
        menuproveedor.h
)
