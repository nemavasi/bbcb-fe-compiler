MODULE TWith;
  IMPORT CPmain;
  TYPE Base = EXTENSIBLE RECORD END;
       Ext = RECORD (Base) END;
       Other = RECORD END;
  VAR o: Other;

  PROCEDURE P(VAR x: ANYREC);
  BEGIN
    WITH x: Ext DO ASSERT(TRUE) END
  END P;

BEGIN
  P(o)
END TWith.
