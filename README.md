# Recetario Digital

Aplicación de consola en C++ para gestionar un recetario de cocina. Permite registrar, buscar, ordenar, filtrar y editar recetas, cada una con su lista de ingredientes, y persistir la información en disco.

## Características

- **Nueva receta**: nombre, tiempo de preparación, procedimiento, categoría (Desayuno, Comida, Cena, Navideño), autor (nombre y apellido) y una lista de ingredientes con cantidad.
- **Eliminar receta** por nombre, o **eliminar todas** las recetas.
- **Buscar receta** por nombre o por categoría.
- **Ordenar recetas** por nombre o por tiempo de preparación (Quicksort), evitando reordenar si ya están ordenadas.
- **Editar ingredientes** de una receta existente: agregar, eliminar, eliminar todos o modificar la cantidad de un ingrediente.
- **Editar el procedimiento** de una receta.
- **Mostrar recetas**, con la opción de filtrar por categoría.
- **Guardar en disco / Leer del disco** (`recetas.txt`), para persistir el recetario entre ejecuciones.

## Estructura del proyecto

```
Codigos/
├── cpp/
│   ├── main.cpp          # Punto de entrada
│   ├── menu.cpp           # Lógica del menú principal e interacción con el usuario
│   ├── recipe.cpp         # Implementación de la clase Recipe
│   ├── ingredients.cpp    # Implementación de la clase Ingredients
│   └── name.cpp            # Implementación de la clase Name (autor)
├── hpp/
│   ├── menu.hpp
│   ├── recipe.hpp
│   ├── ingredients.hpp
│   ├── name.hpp
│   ├── listDoublyLinked.hpp   # Lista doblemente enlazada genérica (template)
│   ├── listSimpleLinked.hpp   # Lista simplemente enlazada genérica (template)
│   └── datos.txt
└── Proyecto final_Entrega Final_Aguilera Alexis.pdf   # Documento de entrega
```

## Estructuras de datos

- **`ListDoubly<T>`**: lista doblemente enlazada genérica usada para almacenar el recetario completo (`ListDoubly<Recipe>`). Incluye inserción, eliminación, búsqueda por nombre/categoría, ordenamiento (Quicksort) y lectura/escritura en disco.
- **`ListSimple<T>`**: lista simplemente enlazada genérica usada para la lista de ingredientes de cada receta (`ListSimple<Ingredients>`), con inserción ordenada.
- **`Recipe`**: nombre, tiempo de preparación, procedimiento, categoría, autor (`Name`) y su lista de ingredientes.
- **`Ingredients`**: nombre del ingrediente y cantidad.
- **`Name`**: nombre y apellido del autor/chef.

## Compilación

Requiere un compilador con soporte de C++11 o superior (g++, MinGW, etc.).

**Manual:**

```bash
g++ -std=c++11 -I hpp cpp/*.cpp -o recetario
```

**Con Makefile:**

```bash
make
```

<!-- TODO: pegar aquí el contenido/target real del Makefile subido a GitHub (make, make clean, make run, etc.) -->

## Uso

```bash
./recetario
```

Al ejecutar el programa se muestra un menú interactivo en consola; se elige una opción escribiendo su número. El comando `system("cls")` se usa para limpiar la pantalla, por lo que el programa está pensado para ejecutarse en **Windows**; en Linux/macOS puede reemplazarse por `system("clear")` si se desea limpiar la pantalla correctamente.

## Configuración de VS Code

El proyecto incluye una carpeta `.vscode/` con la configuración de compilación y depuración (`tasks.json`, `launch.json`).

### Extensiones recomendadas

Instálalas desde el panel de Extensiones de VS Code, o crea/edita `.vscode/extensions.json` con:

```jsonc
{
    "recommendations": [
        "ms-vscode.cpptools",              // IntelliSense, depuración y navegación de código para C/C++
        "jeff-hykin.better-cpp-syntax",    // Resaltado de sintaxis mejorado para C++
        "ms-vscode.cpp-devtools",          // Herramientas adicionales de desarrollo C++
        "ms-vscode.cpptools-themes",       // Temas a juego con C/C++ Tools
        "amiralizadeh9480.cpp-helper",     // Generación rápida de getters/setters, includes, etc.
        "twxs.cmake",                      // Resaltado de sintaxis para archivos CMake
        "ms-vscode.cmake-tools",           // Integración de CMake (configurar, compilar, depurar)
        "pkief.material-icon-theme",       // Iconos de archivos/carpetas
        "ms-vscode.makefile-tools",        // Integración de Makefiles con VS Code
        "fougas.msys2"                     // Soporte para el entorno/toolchain MSYS2 en Windows
    ]
}
```

## Autor

Aguilera Alexis
