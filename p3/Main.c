code Main

  -- OS Class: Project 3
  --
  -- <PUT YOUR NAME HERE>
  --

-----------------------------  Main  ---------------------------------

  function main ()
      InitializeScheduler ()
      SleepingBarber ()
      ThreadFinish ()
    endFunction

  const
    CHAIRS = 5
    CCOUNT = 20
  var
    customerThreads : array [CCOUNT] of Thread = new array of Thread { CCOUNT of new Thread }
    barberThread    : Thread                   = new Thread
    customers       : Semaphore                = new Semaphore
    barbers         : Semaphore                = new Semaphore
    mutex           : Semaphore                = new Semaphore
    waiting         : int                      = 0

  function SleepingBarber ()

      customers.Init(0)
      barbers.Init(0)
      mutex.Init(1)

      print("         Barber  1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20\n")

      -- Init the barber and customer threads
      barberThread.Init("Barber")
      barberThread.Fork(BarberRoutine, 1)


      customerThreads[0].Init ("1")
      customerThreads[0].Fork (CustomerRoutine, 1)

      customerThreads[1].Init ("2")
      customerThreads[1].Fork (CustomerRoutine, 2)

      customerThreads[2].Init ("3")
      customerThreads[2].Fork (CustomerRoutine, 3)

      customerThreads[3].Init ("4")
      customerThreads[3].Fork (CustomerRoutine, 4)

      customerThreads[4].Init ("5")
      customerThreads[4].Fork (CustomerRoutine, 5)

      customerThreads[5].Init ("6")
      customerThreads[5].Fork (CustomerRoutine, 6)

      customerThreads[6].Init ("7")
      customerThreads[6].Fork (CustomerRoutine, 7)

      customerThreads[7].Init ("8")
      customerThreads[7].Fork (CustomerRoutine, 8)

      customerThreads[8].Init ("9")
      customerThreads[8].Fork (CustomerRoutine, 9)

      customerThreads[9].Init ("10")
      customerThreads[9].Fork (CustomerRoutine, 10)

      customerThreads[10].Init ("11")
      customerThreads[10].Fork (CustomerRoutine, 11)

      customerThreads[11].Init ("12")
      customerThreads[11].Fork (CustomerRoutine, 12)

      customerThreads[12].Init ("13")
      customerThreads[12].Fork (CustomerRoutine, 13)

      customerThreads[13].Init ("14")
      customerThreads[13].Fork (CustomerRoutine, 14)

      customerThreads[14].Init ("15")
      customerThreads[14].Fork (CustomerRoutine, 15)

      customerThreads[15].Init ("16")
      customerThreads[15].Fork (CustomerRoutine, 16)

      customerThreads[16].Init ("17")
      customerThreads[16].Fork (CustomerRoutine, 17)

      customerThreads[17].Init ("18")
      customerThreads[17].Fork (CustomerRoutine, 18)

      customerThreads[18].Init ("19")
      customerThreads[18].Fork (CustomerRoutine, 19)

      customerThreads[19].Init ("20")
      customerThreads[19].Fork (CustomerRoutine, 20)


      ThreadFinish ()
    endFunction

   

  function BarberRoutine (barberId: int)
      while true
        customers.Down()
        mutex.Down()
        waiting = waiting - 1
        barbers.Up()
        mutex.Up()
        CutHair()
      endWhile
    endFunction

  function CustomerRoutine (customerId: int)
      mutex.Down()
      E(customerId)
      if waiting < CHAIRS
        waiting = waiting + 1
        customers.Up()
        mutex.Up()
        S(customerId)
        barbers.Down()
        B(customerId)
        GetHairCut()
        F(customerId)
        L(customerId)
      else
        L(customerId)
        mutex.Up()
      endIf
    endFunction

  function CutHair ()
      var
        i: int
      for i = 1 to 100
         currentThread.Yield()
      endFor
      Start()
    endFunction

  function GetHairCut ()
      var
        i: int
      for i = 1 to 100
         currentThread.Yield()
      endFor
      End()
    endFunction

  function Start ()
      PrintChairs()
      print("  start\n")
    endFunction

  function End ()
      PrintChairs()
      print("  end\n")
    endFunction

  function E (cId: int)
      PrintChairs()
      PrintSpaceForThread(cId)
      print("E\n")
    endFunction

  function S (cId: int)
      PrintChairs()
      PrintSpaceForThread(cId)
      print("S\n")
    endFunction

  function L (cId: int)
      PrintChairs()
      PrintSpaceForThread(cId)
      print("L\n")
    endFunction

  function B (cId: int)
      PrintChairs()
      PrintSpaceForThread(cId)
      print("B\n")
    endFunction

  function F (cId: int)
      PrintChairs()
      PrintSpaceForThread(cId)
      print("F\n")
    endFunction
  
  function PrintChairs ()
      var
        i: int
      print("|")
      for i = 1 to waiting
        print ("X")
      endFor

      for i = 1 to CHAIRS - waiting
        print ("_")
      endFor
      print("|")
    endFunction

  function PrintSpaceForThread (spaces: int)
      var
        i: int
      print("          ")
      for i = 1 to (spaces - 1) * 4
        print("-")
      endFor
    endFunction

endCode

