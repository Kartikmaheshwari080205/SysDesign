package Java.Carpooling;

import java.util.*;

class Drive {
    
    String drivername;
    int seats;
    double[] start = new double[2];
    double[] end = new double[2];

    Drive(String name, int s, double sx, double sy, double ex, double ey)
    {
        this.drivername = name;
        this.seats = s;
        this.start[0] = sx;
        this.start[1] = sy;
        this.end[0] = ex;
        this.end[1] = ey;
    }
}

class Rider {

    String ridername;
    double[] start = new double[2];
    double[] end = new double[2];

    Rider(String name, double sx, double sy, double ex, double ey)
    {
        this.ridername = name;
        this.start[0] = sx;
        this.start[1] = sy;
        this.end[0] = ex;
        this.end[1] = ey;
    }

    double distance(Drive d)
    {
        return Math.sqrt(Math.pow(d.start[0] - start[0], 2) + Math.pow(d.start[1] - start[1], 2)) * 111;
    }

    List<Integer> availablerides(List<Drive> rides)
    {
        List<Integer> result = new ArrayList<>();
        for(int i=0; i<rides.size(); i++)
        {
            if(rides.get(i).seats > 0 && distance(rides.get(i)) <= 5.00)
            {
                result.add(i);
            }
        }
        return result;
    }
}

public class Carpooling {
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        List<Drive> rides = new ArrayList<>();
        Map<String, Rider> riders = new HashMap<>();
        while(sc.hasNextLine())
        {
            String line = sc.nextLine();
            if(!line.isEmpty())
            {
                String[] parts = line.split("\\s+");
                String command = parts[0];
                if(command.equals("MAKERIDE"))
                {
                    String name = parts[1];
                    int seats = Integer.parseInt(parts[2]);
                    double startlat = Double.parseDouble(parts[3]);
                    double startlong = Double.parseDouble(parts[4]);
                    double endlat = Double.parseDouble(parts[5]);
                    double endlong = Double.parseDouble(parts[6]);
                    Drive d = new Drive(name, seats, startlat, startlong, endlat, endlong);
                    rides.add(d);
                    System.out.println("Ride " + rides.size() + " created");
                }
                else if(command.equals("GETRIDE"))
                {
                    String name = parts[1];
                    double startlat = Double.parseDouble(parts[2]);
                    double startlong = Double.parseDouble(parts[3]);
                    double endlat = Double.parseDouble(parts[4]);
                    double endlong = Double.parseDouble(parts[5]);
                    Rider r = new Rider(name, startlat, startlong, endlat, endlong);
                    riders.put(name, r);
                    List<Integer> available = r.availablerides(rides);
                    if(available.isEmpty())
                    {
                        System.out.println("No rides available");
                    }
                    else
                    {
                        System.out.println("Available rides:");
                        for(int idx : available)
                        {
                            System.out.println("Ride id: " + (idx + 1) + " Driver: " + rides.get(idx).drivername + " Seats: " + rides.get(idx).seats + " Distance: " + String.format("%.5f", r.distance(rides.get(idx))) + " km");
                        }
                    }
                }
                else if(command.equals("TAKERIDE"))
                {
                    String name = parts[1];
                    int rideid = Integer.parseInt(parts[2]) - 1;
                    Rider r = riders.get(name);
                    List<Integer> available = r.availablerides(rides);
                    if(available.contains(rideid))
                    {
                        rides.get(rideid).seats -= 1;
                        System.out.println("SUCCESS");
                        riders.remove(name);
                    }
                    else
                    {
                        System.out.println("FAILURE");
                    }
                }
            }
        }
        sc.close();
    }
}

/*
INPUT:

MAKERIDE John 2 12.90 77.50 12.95 77.60
MAKERIDE Mary 1 12.92 77.52 12.96 77.62
GETRIDE Alice 12.91 77.51 12.97 77.63
TAKERIDE Alice 1
GETRIDE Bob 12.905 77.505 12.97 77.61
TAKERIDE Bob 1
GETRIDE Charlie 12.91 77.52 12.97 77.65
TAKERIDE Charlie 1
TAKERIDE Charlie 2

OUTPUT:

Ride 1 created
Ride 2 created
Available rides:
Ride id: 1 Driver: John Seats: 2 Distance: 1.56978 km
Ride id: 2 Driver: Mary Seats: 1 Distance: 1.56978 km
SUCCESS
Available rides:
Ride id: 1 Driver: John Seats: 1 Distance: 0.78489 km
Ride id: 2 Driver: Mary Seats: 1 Distance: 2.35467 km
SUCCESS
Available rides:
Ride id: 2 Driver: Mary Seats: 1 Distance: 1.11000 km
FAILURE
SUCCESS
*/