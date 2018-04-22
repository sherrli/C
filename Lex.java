# Sort a string array lexicographically, by sorting a List of its indices in an Insertion Sort manner

import java.util.Scanner;
import java.io.*;

public class Lex{
        public static void main(String[] args) throws IOException{
                // check for two command line arguments
                if(args.length != 2){
                        System.err.println("Usage: Lex infile outfile");
                        System.exit(1);
                }
                File file = new File(args[0]);
                // count number of lines in input file
                Scanner scan1 = new Scanner(file);
                PrintWriter out = new PrintWriter(new FileWriter(args[1]));
                int n = 0;
                while(scan1.hasNextLine()){
                        n++;
                        scan1.nextLine();
                }
                scan1.close();
                // read in lines of input file
                Scanner scan2 = new Scanner(file);
                // System.out.println(n);
                String[] pre = new String[n];
                int i;
                for(i=0; i<n; i++){
                        // don't use while loop here
                        pre[i] = scan2.nextLine(); // or scan2.next();
                }
                scan2.close();

                // build the List of indices from array pre
                List list = new List();
                list.append(0);
                // practice case: array has 2 elements
                if(n==2){
                        if(pre[0].compareTo(pre[1])<0){
                                list.append(1);
                        }else{
                                list.prepend(1);
                        }
                }

                // model after insertion sort:
                for (int j=1; j<n; j++){
                        // compare strings in array
                        list.moveBack();
                        String temp = pre[j];
                        // int i = j-1;
                        i = list.get(); // current index stored in cursor 
                        while(list.index()>=0 && temp.compareTo(pre[i])<0){
                                // shift cursor left if array element smaller
                                // list.insertBefore(j);
                                // i = list.get();
                                list.movePrev();
                                // change the next array comparison index in list
                                if(list.index()>=0){
                                        i = list.get();
                                }
                        }
                        // pre[j] was smaller than all ints in the list and cursor fell off
                        if(list.index()==-1){
                                list.prepend(j);
                        }else{
                                list.insertAfter(j);
                        }
                }

                // print array in alphabetical order to output file
                list.moveFront();
                for(int ii=0; ii<n; ii++){
                        out.println(pre[list.get()]);
                        list.moveNext(); // shift cursor forward
                }
                // do not need: out.println();
                out.close();
        }
}
