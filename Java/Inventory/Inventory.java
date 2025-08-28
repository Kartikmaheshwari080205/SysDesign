package Java.Inventory;

import java.util.*;

class Product {

    String id;
    int price, count;

    Product(String id, int price, int count)
    {
        this.id = id;
        this.price = price;
        this.count = count;
    }
}

class Seller {

    String id;
    HashSet<String> paymentmethods = new HashSet<>();
    HashMap<String, Product> products = new HashMap<>();
    HashSet<String> pincodes = new HashSet<>();

    Seller() {}

    Seller(String id, String[] pm, String[] pc)
    {
        this.id = id;
        this.paymentmethods = new HashSet<>(Arrays.asList(pm));
        this.pincodes = new HashSet<>(Arrays.asList(pc));
    }
}

class Inventory {

    HashMap<String, Seller> sellers = new HashMap<>();

    Inventory() {}

    void createseller(String id, String[] pc, String[] pm)
    {
        sellers.put(id, new Seller(id, pm, pc));
        System.out.println("Seller " + id + " created");
    }

    void addinventory(String pid, String sid, int count)
    {
        sellers.get(sid).products.get(pid).count += count;
        System.out.println("Added " + count + " products " + pid + " to seller " + sid);
    }

    void getinventory(String pid, String sid)
    {
        if(!sellers.containsKey(sid))
        {
            System.out.println("Seller does not exist");
            return;
        }
        if(!sellers.get(sid).products.containsKey(pid))
        {
            System.out.println("Product does not exist");
            return;
        }
        System.out.println(sellers.get(sid).products.get(pid).count);
    }

    void order(String destination, String sid, String pid, int count, String method)
    {
        if(!sellers.containsKey(sid))
        {
            System.out.println("Seller does not exist");
            return;
        }
        if(!sellers.get(sid).pincodes.contains(destination))
        {
            System.out.println("Seller does not sell at destination " + destination);
            return;
        }
        if(!sellers.get(sid).products.containsKey(pid))
        {
            System.out.println("Seller does not sell product " + pid);
            return;
        }
        if(!sellers.get(sid).paymentmethods.contains(method))
        {
            System.out.println("Seller does not accept " + method);
            return;
        }
        if(sellers.get(sid).products.get(pid).count < count)
        {
            System.out.println("Seller does not have " + count + " product " + pid);
            return;
        }
        sellers.get(sid).products.get(pid).count -= count;
        System.out.println("Order placed of " + count + " " + pid + " from " + sid + " to " + destination);
    }

    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        Inventory inventory = new Inventory();
        while(sc.hasNextLine())
        {
            String line = sc.nextLine();
            if(!line.isEmpty())
            {
                String[] parts = line.split("\\s+");
                String command = parts[0];
                if(command.equals("CREATESELLER"))
                {
                    String id = parts[1];
                    int n = Integer.parseInt(parts[2]);
                    String[] pc = new String[n];
                    for(int i=0; i<n; i++)
                    {
                        pc[i] = parts[3+i];
                    }
                    int m = Integer.parseInt(parts[3+n]);
                    String[] pm = new String[m];
                    for(int i=0; i<m; i++)
                    {
                        pm[i] = parts[4+n+i];
                    }
                    inventory.createseller(id, pc, pm);
                }
                else if(command.equals("ADDINVENTORY"))
                {
                    String pid = parts[1];
                    String sid = parts[2];
                    int count = Integer.parseInt(parts[3]);
                    int price = Integer.parseInt(parts[4]);
                    if(!inventory.sellers.containsKey(sid))
                    {
                        System.out.println("Seller " + sid + " does not exist");
                        continue;
                    }
                    if(!inventory.sellers.get(sid).products.containsKey(pid))
                    {
                        Product p = new Product(pid, price, count);
                        inventory.sellers.get(sid).products.put(pid, p);
                        System.out.println("Addeed " + count + " products " + pid + " to seller " + sid);
                    }
                    else
                    {
                        inventory.addinventory(pid, sid, count);
                    }
                }
                else if(command.equals("GETINVENTORY"))
                {
                    String pid = parts[1];
                    String sid = parts[2];
                    inventory.getinventory(pid, sid);
                }
                else if(command.equals("ORDER"))
                {
                    String destination = parts[1];
                    String sid = parts[2];
                    String pid = parts[3];
                    int count = Integer.parseInt(parts[4]);
                    String method = parts[5];
                    inventory.order(destination, sid, pid, count, method);
                }
            }
        }
        sc.close();
    }
}

/*
INPUT:

CREATESELLER S1 3 110001 110002 110003 2 COD CARD
CREATESELLER S2 2 560001 560002 1 UPI
ADDINVENTORY P1 S1 10
ADDINVENTORY P2 S1 5
ADDINVENTORY P3 S2 20
GETINVENTORY P1 S1
GETINVENTORY P2 S1
GETINVENTORY P3 S2
GETINVENTORY P4 S1
GETINVENTORY P1 S3
ORDER 110001 S1 P1 3 COD
ORDER 110004 S1 P1 2 CARD
ORDER 110001 S1 P4 1 COD
ORDER 560001 S2 P3 25 UPI
ORDER 560002 S2 P3 5 CARD
ORDER 560001 S2 P3 10 UPI

OUTPUT:

Seller S1 created
Seller S2 created
Added 10 products P1 to seller S1
Added 5 products P2 to seller S1
Added 20 products P3 to seller S2
10
5
20
Product does not exist
Seller does not exist
Order placed of 3 P1 from S1 to 110001
Seller does not sell at destination 110004
Seller does not sell product P4
Seller does not have 25 product P3
Seller does not accept CARD
Order placed of 10 P3 from S2 to 560001
*/