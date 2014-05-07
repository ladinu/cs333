code Main

  -- OS Class: Project 3
  --
  -- <PUT YOUR NAME HERE>
  --

-----------------------------  Main  ---------------------------------

  function main ()
      InitializeScheduler ()
      --SleepingBarber ()
      GamingParlor ()
      --ThreadFinish ()
    endFunction

  const
    CHAIRS = 5
    CCOUNT = 20
  var
    customerThreads : array [CCOUNT] of Thread = new array of Thread { CCOUNT of new Thread }
    barberThread    : Thread                   = new Thread
    customers       : Semaphore                = new Semaphore
    barbers         : Semaphore                = new Semaphore
    mutex           : Mutex                    = new Mutex
    waiting         : int                      = 0

  function SleepingBarber ()

      customers.Init(0)
      barbers.Init(0)
      mutex.Init()

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
        mutex.Lock()
        waiting = waiting - 1
        barbers.Up()
        mutex.Unlock()
        CutHair()
      endWhile
    endFunction

  function CustomerRoutine (customerId: int)
      mutex.Lock()
      E(customerId)
      if waiting < CHAIRS
        waiting = waiting + 1
        customers.Up()
        mutex.Unlock()
        S(customerId)
        barbers.Down()
        B(customerId)
        GetHairCut()
        F(customerId)
        L(customerId)
      else
        L(customerId)
        mutex.Unlock()
      endIf
    endFunction

  function CutHair ()
      var
        i: int
      Start()
      for i = 1 to 100
         currentThread.Yield()
      endFor
      End()
    endFunction

  function GetHairCut ()
      var
        i: int
      for i = 1 to 100
         currentThread.Yield()
      endFor
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


----------------------------------------------------------------------------------
--------------------------------- Gaming Parlor ----------------------------------
----------------------------------------------------------------------------------
errors fatalError ()
const DICE_COUNT        = 8
      MAX_DICE_PER_GAME = 5
      MIN_DICE_PER_GAME = 1
var
   diceMonitor : DiceMonitor 
   players     : array [8] of Thread 

function GamingParlor()
   players     = new array of Thread { 8 of new Thread }
   diceMonitor = new DiceMonitor

   -- Initialize the dice monitor
   diceMonitor.Init()

   --------- Backgamon Group ----------
   players[0].Init("A-Backgammon")
   players[0].Fork(PlayGame, 4)
   players[1].Init("B-Backgammon")
   players[1].Fork(PlayGame, 4)

   --------- Risk Group ----------------
   players[2].Init("C-Risk")
   players[2].Fork(PlayGame, 5)
   players[3].Init("D-Risk")
   players[3].Fork(PlayGame, 5)

   --------- Monopoly Group ------------
   players[4].Init("E-Monopoly")
   players[4].Fork(PlayGame, 2)
   players[5].Init("F-Monopoly")
   players[5].Fork(PlayGame, 2)

   --------- Pictionary Group -----------
   players[6].Init("G-Pictionary")
   players[6].Fork(PlayGame, 1)
   players[7].Init("H-Pictionary")
   players[7].Fork(PlayGame, 1)

   ThreadFinish ()
endFunction

function PlayGame(numberOfDice: int)
   var i, j : int
   for i = 1 to 5
      diceMonitor.RequestDice(numberOfDice)
      for j = 1 to 100
         currentThread.Yield()
      endFor
      diceMonitor.ReturnDice(numberOfDice)
   endFor
endFunction

class DiceMonitor
 superclass Object
 fields
   monitorMutex        : Mutex
   numberDiceAvail     : int
   waitingList         : Condition
   diceList            : Condition
   peopleInWaitingList : int
 methods
   Init        ( )
   RequestDice (numberOfDice: int)
   ReturnDice  (numberOfDice: int)
   Print       (str: String, count: int)
endClass

behavior DiceMonitor

 method Init ()
   monitorMutex = new Mutex
   waitingList  = new Condition
   diceList     = new Condition

   monitorMutex .Init ()
   waitingList  .Init ()
   diceList     .Init ()

   numberDiceAvail     = DICE_COUNT
   peopleInWaitingList = 0
 endMethod

 method RequestDice (numberOfDice: int)
   var numNeeded: int = numberOfDice
   monitorMutex.Lock()
   self.Print("requests", numNeeded)
   -- Assert numberOfDice is between 1 and 5
   assert(numNeeded >= MIN_DICE_PER_GAME && numNeeded <= MAX_DICE_PER_GAME)


   if peopleInWaitingList > 0
      waitingList.Wait(&monitorMutex)
   endIf

   peopleInWaitingList = peopleInWaitingList + 1
   

   while numNeeded > numberDiceAvail
      diceList.Wait(&monitorMutex)
   endWhile

   peopleInWaitingList = peopleInWaitingList - 1

   assert(numberDiceAvail >= 0 && numberDiceAvail <= DICE_COUNT)
   numberDiceAvail = numberDiceAvail - numNeeded
   assert(numberDiceAvail >= 0 && numberDiceAvail <= DICE_COUNT)

   waitingList.Signal(&monitorMutex)

   self.Print("proceds with", numNeeded)
   monitorMutex.Unlock()
 endMethod

 method ReturnDice (numberOfDice: int)
   var numReturned: int = numberOfDice
   monitorMutex.Lock()

   assert(numReturned >= MIN_DICE_PER_GAME && numReturned <= MAX_DICE_PER_GAME)

   assert(numberDiceAvail >= 0 && numberDiceAvail <= DICE_COUNT)
   numberDiceAvail = numberDiceAvail + numReturned
   assert(numberDiceAvail >= 0 && numberDiceAvail <= DICE_COUNT)
  
   diceList.Signal(&monitorMutex)

   self.Print("releases and adds back", numReturned)
   monitorMutex.Unlock()
 endMethod

 method Print(str: String, count: int)
   print (currentThread.name)
   print (" ")
   print (str)
   print (" ")
   printInt (count)
   nl ()
   print ("------------------------------Number of dice now avail = ")
   printInt (numberDiceAvail)
   nl ()
 endMethod
endBehavior

function assert(condition: bool)
   if !condition
      print ("Assertion Failure")
      nl()
      throw fatalError()
   endIf
endFunction

endCode

