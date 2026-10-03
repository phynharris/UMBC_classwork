: do-abort
  3 1 > abort" true, abort with this message"
;

: don't-abort
  3 1 < abort" false, does not abort but uses the stack top"
;
