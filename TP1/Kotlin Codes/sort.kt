fun main() {
    // Crear una lista de ejemplo con 100000 elementos no ordenados
    val lista = mutableListOf<Int>()
    repeat(100000) {
        lista.add((0..999).random()) // Agregar números aleatorios
    }

    // Ordenar la lista
    lista.sort()

    // Imprimir la lista ordenada
    println("Lista ordenada:")
    lista.forEach { elemento ->
        print("$elemento ")
    }
}

