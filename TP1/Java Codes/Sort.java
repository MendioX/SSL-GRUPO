import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Sort {
    public static void main(String[] args) {
        // Crear una lista de ejemplo con 100000 elementos no ordenados
        List<Integer> lista = new ArrayList<>();
        for (int i = 0; i < 100000; i++) {
            lista.add((int) (Math.random() * 1000)); // Agregar números aleatorios
        }

        // Ordenar la lista
        Collections.sort(lista);

        // Imprimir la lista ordenada
        System.out.println("Lista ordenada:");
        for (Integer elemento : lista) {
            System.out.print(elemento + " ");
        }
    }
}
