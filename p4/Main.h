header Main

  uses Kernel
 
  functions
    main ()

  class ResourceMonitor
   superclass Object
   fields
     monitorMutex : MonitorMutex
     mutex        : Mutex
     hCondition   : HCondition
     mCondition   : Condition
     cvType       : int
     numResource  : int

   methods
     Init    (semantic: int)
     Request (numRequested, thId: int)
     Release (numReleased, thId: int)

     Lock   ()
     Unlock ()
     Wait   ()
     Signal ()

     Error  ()
  endClass

endHeader
