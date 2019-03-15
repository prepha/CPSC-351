import java.io.*;
import java.util.*;

public class Factory {
    public static void main(String[] args) {
        String filename = " C:\\Users\\preph\\IdeaProjects\\Bankers\\src\\infile.txt";
        int nResources = args.length;
        int[] resources = new int[nResources];

        for (int i = 0; i < nResources; i++) { resources[i] = Integer.parseInt(args[i].trim()); }

        Bank theBank = new BankImpl(resources);
        int[] maxDemand = new int[nResources];
        int[] allocated = new int[nResources];
        Thread[] workers = new Thread[Customer.COUNT];      // the customers

        // read in values and initialize the matrices
        // to do
        // ...
        workers[Customer.COUNT] = new Thread(new Customer(Customer.COUNT, maxDemand, theBank));
        theBank.addCustomer(Customer.COUNT, allocated, maxDemand);

        ++nResources;        //theBank.getCustomer(threadNum);
        nResources = 0;
    }

}
