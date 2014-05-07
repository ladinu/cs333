code Main

  -- OS Class: Project 3
  --
  -- <Ladinu Chandrasinghe>
  --

-----------------------------  Main  ---------------------------------

  function main ()
      InitializeScheduler ()
      SleepingBarber ()
      --GamingParlor ()
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
    mutex           : Mutex                    = new Mutex
    printLock       : Mutex                    = new Mutex
    waiting         : int                      = 0

  function SleepingBarber ()

      customers.Init(0)
      barbers.Init(0)
      mutex.Init()
      printLock.Init()

      print("         Barber  1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20\n")

      -- Init the barber and customer threads
      barberThread.Init("Barber")
      barberThread.Fork(BarberRoutine, 1)


      customerThreads[0].Init ("1")
      customerThreads[0].Fork (HairCutLoop, 1)

      customerThreads[1].Init ("2")
      customerThreads[1].Fork (HairCutLoop, 2)

      customerThreads[2].Init ("3")
      customerThreads[2].Fork (HairCutLoop, 3)

      customerThreads[3].Init ("4")
      customerThreads[3].Fork (HairCutLoop, 4)

      customerThreads[4].Init ("5")
      customerThreads[4].Fork (HairCutLoop, 5)

      customerThreads[5].Init ("6")
      customerThreads[5].Fork (HairCutLoop, 6)

      customerThreads[6].Init ("7")
      customerThreads[6].Fork (HairCutLoop, 7)

      customerThreads[7].Init ("8")
      customerThreads[7].Fork (HairCutLoop, 8)

      customerThreads[8].Init ("9")
      customerThreads[8].Fork (HairCutLoop, 9)

      customerThreads[9].Init ("10")
      customerThreads[9].Fork (HairCutLoop, 10)

      customerThreads[10].Init ("11")
      customerThreads[10].Fork (HairCutLoop, 11)

      customerThreads[11].Init ("12")
      customerThreads[11].Fork (HairCutLoop, 12)

      customerThreads[12].Init ("13")
      customerThreads[12].Fork (HairCutLoop, 13)

      customerThreads[13].Init ("14")
      customerThreads[13].Fork (HairCutLoop, 14)

      customerThreads[14].Init ("15")
      customerThreads[14].Fork (HairCutLoop, 15)

      customerThreads[15].Init ("16")
      customerThreads[15].Fork (HairCutLoop, 16)

      customerThreads[16].Init ("17")
      customerThreads[16].Fork (HairCutLoop, 17)

      customerThreads[17].Init ("18")
      customerThreads[17].Fork (HairCutLoop, 18)

      customerThreads[18].Init ("19")
      customerThreads[18].Fork (HairCutLoop, 19)

      customerThreads[19].Init ("20")
      customerThreads[19].Fork (HairCutLoop, 20)


      ThreadFinish ()
    endFunction

   function HairCutLoop(customerId: int)
      var i: int
      for i = 0 to 10
         CustomerRoutine(customerId)
      endFor
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
        S(customerId)
        customers.Up()
        mutex.Unlock()
        barbers.Down()
        GetHairCut(customerId)
        L(customerId)
      else
        L(customerId)
        mutex.Unlock()
      endIf
   endFunction

   function CutHair ()
      var
        i: int
      mutex.Lock()
      Start()
      for i = 1 to 100
         currentThread.Yield()
      endFor
      End()
      mutex.Unlock()
   endFunction

   function GetHairCut (customerId: int)
      var
        i: int
      mutex.Lock()
      B(customerId)
      for i = 1 to 100
         currentThread.Yield()
      endFor
      F(customerId)
      mutex.Unlock()
   endFunction

-------------------------------------------------------------------
-------------------- Helper Print function ------------------------
-------------------------------------------------------------------
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

 -- This was a tricky method to implement. I was originally thinking
 -- this monitor should at least have 5 dice before waking any customers
 -- from the waiting list. This would avoid starvation but its not very
 -- concurrent. I implemented the RequestDice method using 2
 -- waitingLists. The second list named "diceList" at any given time
 -- should only have 1 customer waiting. "peopleWaitingList" should have
 -- all the other customers waiting.
 --
 -- Initially, the "waitingList" is empty. The first customer
 -- increment "peopleInWaitingList" counter and tries to obtain some
 -- dice. If there are not enough dice available, the customer put him/her
 -- in the "diceList". The "ReturnDice" method wake up customers from the
 -- "diceList". When a customer wake up from the "diceList", she/he wakes
 -- up another customer from the "waitingList" before leaving the method.
 -- This ensure that only 1 customer is in contention for dice at a given
 -- time. This avoids starvation.
 method RequestDice (numberOfDice: int)
   var numNeeded: int = numberOfDice
   monitorMutex.Lock()
   self.Print("requests", numNeeded)
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

