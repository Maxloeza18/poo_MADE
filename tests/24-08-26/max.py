import json
import os

# Definimos una constante con el nombre del archivo donde se guardará la información
ARCHIVO_DATOS = "registro_personas.json"

def cargar_datos():
    """
    Verifica si el archivo de datos ya existe. 
    Si existe, lee su contenido y lo devuelve como una lista de diccionarios.
    Si no existe (es la primera vez que se ejecuta), devuelve una lista vacía.
    """
    if os.path.exists(ARCHIVO_DATOS):
        # Usamos 'with' para asegurarnos de que el archivo se cierre automáticamente tras leerlo
        with open(ARCHIVO_DATOS, "r", encoding="utf-8") as archivo:
            # json.load convierte el texto del archivo nuevamente en una lista de Python
            return json.load(archivo)
    else:
        return []

def guardar_datos(datos):
    """
    Toma la lista actual de datos y la sobrescribe en el archivo JSON.
    """
    with open(ARCHIVO_DATOS, "w", encoding="utf-8") as archivo:
        # json.dump convierte la lista de Python en texto formateado
        # indent=4 le da un formato bonito y legible con saltos de línea
        # ensure_ascii=False permite que se guarden correctamente acentos y la letra ñ
        json.dump(datos, archivo, indent=4, ensure_ascii=False)

def registrar_persona(datos):
    """
    Solicita al usuario el nombre y trabajo, los empaqueta en un diccionario,
    los agrega a la lista principal y guarda los cambios.
    """
    print("\n--- Registro de Nueva Persona ---")
    nombre = input("Ingresa el nombre: ")
    trabajo = input("Ingresa el trabajo: ")
    
    # Creamos un diccionario con la estructura de la información
    nueva_persona = {
        "nombre": nombre,
        "trabajo": trabajo
    }
    
    # Añadimos el nuevo registro a la lista que tenemos en memoria
    datos.append(nueva_persona)
    
    # Llamamos a la función que guarda la lista en el disco duro
    guardar_datos(datos)
    print("✅ ¡Datos guardados exitosamente!")

def consultar_datos(datos):
    """
    Muestra en consola todos los registros que se han guardado.
    """
    print("\n--- Consulta de Datos Guardados ---")
    
    # Verificamos si la lista está vacía
    if len(datos) == 0:
        print("⚠️ Aún no hay personas registradas.")
        return # Terminamos la función aquí si no hay datos

    # Recorremos la lista para imprimir cada persona
    # enumerate(..., start=1) nos sirve para poner un número de lista (1, 2, 3...)
    for indice, persona in enumerate(datos, start=1):
        print(f"{indice}. Nombre: {persona['nombre']} | Trabajo: {persona['trabajo']}")
    print("-----------------------------------")

def menu_principal():
    """
    Controla el flujo del programa mostrando un menú interactivo.
    Mantiene un bucle infinito hasta que el usuario decide salir.
    """
    # 1. Al iniciar, lo primero es cargar lo que ya estaba guardado
    lista_personas = cargar_datos()
    
    # 2. Iniciamos el bucle del menú
    while True:
        print("\n=== MENÚ PRINCIPAL ===")
        print("1. Registrar una nueva persona")
        print("2. Consultar personas guardadas")
        print("3. Salir del programa")
        
        opcion = input("Elige una opción (1, 2 o 3): ")
        
        if opcion == "1":
            registrar_persona(lista_personas)
        elif opcion == "2":
            consultar_datos(lista_personas)
        elif opcion == "3":
            print("Saliendo del programa... ¡Hasta luego!")
            break # Rompe el bucle 'while' y termina el programa
        else:
            print("❌ Opción no válida. Por favor, intenta de nuevo.")

# Este bloque asegura que el menú principal solo se ejecute si corres 
# este archivo directamente, y no si lo importas desde otro código.
if __name__ == "__main__":
    menu_principal()
