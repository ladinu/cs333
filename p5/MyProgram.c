code MyProgram

-----------------------------  main  ---------------------------------

  function main ()
    --
    -- This is a generic User-Level program.  Feel free to modify it and
    -- use it during debugging.
    --
      var rv : int
      print ("\nMy user-level program is running!!!\n")
      rv = Sys_Exec("FOO bar")
      Sys_Shutdown ()

    endFunction

endCode
