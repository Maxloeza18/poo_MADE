import json
import os

# Nombre del archivo donde se guardarán los datos.
# El archivo se creará automáticamente en la misma carpeta
# donde se ejecute este programa.
ARCHIVO = "datos.json"


# ---------------------------------------------------------
# FUNCIÓN PARA CARGAR LOS DATOS GUARDADOS
# ---------------------------------------------------------
def cargar_datos():
    """
    Lee el archivo datos.json y devuelve los registros guardados.
    Si el archivo todavía no existe, devuelve una lista vacía.
    """

    # Verificamos si existe el archivo.
    if os.path.exists(ARCHIVO):

        # Abrimos el archivo en modo lectura ("r").
        with open(ARCHIVO, "r", encoding="utf-8") as archivo:

            # Convertimos el contenido JSON en una lista de Python.
            return json.load(archivo)

    # Si no existe el archivo, comenzamos con una lista vacía.
    return []


# ---------------------------------------------------------
# FUNCIÓN PARA GUARDAR LOS DATOS
# ---------------------------------------------------------
def guardar_datos(datos):
    """
    Guarda todos los registros dentro del archivo datos.json.
    """

    # Abrimos el archivo en modo escritura ("w").
    with open(ARCHIVO, "w", encoding="utf-8") as archivo:

        # json.dump convierte la lista de Python a formato JSON.
        json.dump(
            datos,
            archivo,
            ensure_ascii=False,
            indent=4
        )


# ---------------------------------------------------------
# FUNCIÓN PARA AGREGAR UN NUEVO REGISTRO
# ---------------------------------------------------------
def agregar_registro(datos):

    print("\n--- NUEVO REGISTRO ---")

    # Capturamos los datos introducidos por el usuario.
    nombre = input("Ingrese el nombre: ")
    domicilio = input("Ingrese el domicilio: ")

    # Creamos un diccionario con los datos.
    registro = {
        "nombre": nombre,
        "domicilio": domicilio
    }

    # Agregamos el registro a la lista.
    datos.append(registro)

    # Guardamos la lista actualizada en el archivo.
    guardar_datos(datos)

    print("\nDatos guardados correctamente.")


# ---------------------------------------------------------
# FUNCIÓN PARA CONSULTAR UN REGISTRO
# ---------------------------------------------------------
def consultar_registro(datos):

    print("\n--- CONSULTAR REGISTRO ---")

    # Solicitamos el nombre que queremos buscar.
    nombre_buscar = input("Ingrese el nombre que desea buscar: ")

    encontrado = False

    # Recorremos todos los registros guardados.
    for registro in datos:

        # Comparamos los nombres.
        # lower() permite ignorar mayúsculas y minúsculas.
        if registro["nombre"].lower() == nombre_buscar.lower():

            print("\nRegistro encontrado:")
            print("Nombre:", registro["nombre"])
            print("Domicilio:", registro["domicilio"])

            encontrado = True

    # Si terminamos de revisar y no encontramos coincidencias.
    if not encontrado:
        print("\nNo se encontró ningún registro con ese nombre.")


# ---------------------------------------------------------
# FUNCIÓN PARA MOSTRAR TODOS LOS REGISTROS
# ---------------------------------------------------------
def mostrar_registros(datos):

    print("\n--- REGISTROS GUARDADOS ---")

    # Verificamos que existan registros.
    if len(datos) == 0:
        print("No existen registros guardados.")
        return

    # enumerate permite numerar los registros comenzando desde 1.
    for numero, registro in enumerate(datos, start=1):

        print("\nRegistro", numero)
        print("Nombre:", registro["nombre"])
        print("Domicilio:", registro["domicilio"])


# ---------------------------------------------------------
# PROGRAMA PRINCIPAL
# ---------------------------------------------------------

# Al iniciar el programa cargamos los datos que ya existan.
datos = cargar_datos()

# Ciclo principal del programa.
# Se repetirá hasta que el usuario seleccione "Salir".
while True:

    print("\n==============================")
    print("   SISTEMA DE REGISTROS")
    print("==============================")
    print("1. Agregar registro")
    print("2. Consultar registro")
    print("3. Mostrar todos")
    print("4. Salir")

    opcion = input("\nSeleccione una opción: ")

    # Si selecciona 1, agregamos un nuevo registro.
    if opcion == "1":
        agregar_registro(datos)

    # Si selecciona 2, buscamos un registro.
    elif opcion == "2":
        consultar_registro(datos)

    # Si selecciona 3, mostramos todos los registros.
    elif opcion == "3":
        mostrar_registros(datos)

    # Si selecciona 4, termina el programa.
    elif opcion == "4":
        print("\nPrograma finalizado.")
        break

    # Si escribe una opción diferente.
    else:
        print("\nOpción no válida. Intente nuevamente.")