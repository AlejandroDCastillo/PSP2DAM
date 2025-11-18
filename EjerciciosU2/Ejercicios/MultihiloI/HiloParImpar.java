package MultihiloI;
class HiloParImpar implements Runnable {

    // Atributo que indica el tipo de hilo:
    // tipo = 1 → generará números pares
    // tipo = 2 → generará números impares
    private int tipo;

    // Constructor: recibe el tipo de hilo y lo guarda en el atributo
    public HiloParImpar(int tipo) {
        this.tipo = tipo;
    }

    // Método run(): contiene el código que ejecutará el hilo al iniciarse
    public void run() {

        // Según el valor de 'tipo', el hilo hace una tarea diferente
        switch (tipo) {

            case 1:
                Thread.currentThread().setName("Hilo xx");
                // Caso 1 → generar números pares del 1 al 100
                for (int i = 1; i <= 100; i++) {
                    if (i % 2 == 0) // si es par
                        System.out.println("HILO " + Thread.currentThread().getName() +
                                           " generando número par " + i);
                }
                break;

            case 2:
                            Thread.currentThread().setName("Hilo yy");

                // Caso 2 → generar números impares del 101 al 200
                for (int i = 101; i <= 200; i++) {
                    if (i % 2 != 0) // si es impar
                        System.out.println("HILO " + Thread.currentThread().getName() +
                                           " generando número impar " + i);
                }
                break;
        }
    }

    // Método principal
    public static void main(String[] args) throws Exception {

        // Se crean dos hilos:
        // t1 → generará números pares (tipo = 1)
        // t2 → generará números impares (tipo = 2)
        Thread t1 = new Thread(new HiloParImpar(1));
        Thread t2 = new Thread(new HiloParImpar(2));

        // Se inicia el primer hilo (pares)
        t1.start();

        // Se usa join() para esperar a que el hilo t1 termine
        // antes de empezar el segundo hilo
        t1.join();

        // Una vez terminado t1, se inicia el hilo t2 (impares)
        t2.start();
    }
}
