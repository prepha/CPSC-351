import java.io.*;
import java.util.*;

public class BankImpl implements Bank {
    private int n;			// the number of threads in the system
    private int m;			// the number of resources

    private int[] available; 	// the amount available of each resource
    private int[][] maximum; 	// the maximum demand of each thread
    private int[][] allocation;	// the amount currently allocated to each thread
    private int[][] need;		// the remaining needs of each thread

    private void showAllMatrices(int[][] alloc, int[][] max, int[][] need, String msg)
    {
        // todo
        //alloc[n][m]
        for(int i=0;i<alloc.length ; i++) //row
        {
         for (int p=0;p<alloc.length; p++) //height
         {
             System.out.print(alloc[i][p]);

         }
        }

        //max[n][m]

        for(int i=0;i<max.length ; i++) //row
        {
            for (int p=0;p<max.length; p++) //height
            {
                System.out.print(max[i][p]);

            }
        }


        //need[n][m]
        for(int i=0;i<need.length ; i++)
        {
            for (int p=0;p<need.length; p++)
            {
                need[i][p]=max[i][p]-alloc[i][p];
                System.out.print(need[i][p]);
            }
        }



    }

    private void showMatrix(int[][] matrix, String title, String rowTitle)
    {
        // todo

        for(int i=0;i<matrix.length ; i++) //row
        {
            for (int p=0;p<matrix.length; p++) //height
            {
                System.out.print(matrix[i][p]);

            }
        }

    }

    private void showVector(int[] vect, String msg) {
        // todo
        //available[m];
        for(int i =0; i<vect.length;i++)
        {
            System.out.print(vect[i]);
        }
    }

    public BankImpl(int[] resources)
    {      // create a new bank (with resources)
        // todo
        resources.equals(m);
       need = new int[m][];
       maximum = new int[m][];
       allocation = new int[m][];
       available = new int[m];


    }
    // invoked by a thread when it enters the system;  also records max demand
    public void addCustomer(int threadNum, int[] allocated, int[] maxDemand) {
        // todo



    }

    public void getState() {        // output state for each thread
        // todo
    }

    private boolean isSafeState (int threadNum, int[] request)

    {
        // todo -- actual banker's algorithm
        return true;
    }
    // make request for resources. will block until request is satisfied safely
    public synchronized boolean requestResources(int threadNum, int[] request) {
        // todo
        if (isSafeState(threadNum, request))
        {
            for (int i = 0; i < m; ++i)
            {
                request[i] -= available[i];
                allocation[m][i] +=request[i];
                need[m][i] = maximum[m][i]-allocation[m][i];

            }
        }

        if(!isSafeState(threadNum,request))
        {
            return false;
        }
        return true;
    }


    public synchronized void releaseResources(int threadNum, int[] release)
    {
        // todo
        for(int i=0; i<m; ++i)
        {
            System.out.print(release[i]);
        }
    }

