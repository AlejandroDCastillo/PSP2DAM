package MultihiloIII;

public class Sala {
    private HiloCliente[] arrayClientes;
    private boolean ocupada = false;


    public Sala(int tamaño){
        this.arrayClientes=new HiloCliente[tamaño];
    }

    public synchronized void entradaSala(){

    }

}
