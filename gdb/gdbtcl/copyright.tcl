#
# Create a copyright window and center it on the screen.  Arrange for
# it to disappear when the user clicks it, or after a suitable period
# of time.
#
proc create_copyright_window {} {
  toplevel .c
  message .c.m -text [gdb_cmd {show version}] -aspect 500 -relief raised
  pack .c.m

  bind .c.m <1> {destroy .c}
  bind .c <Leave> {destroy .c}
  # "suitable period" currently means "30 seconds".
  after 30000 {
    if {[winfo exists .c]} then {
      destroy .c
    }
  }

  wm transient .c .
  center_window .c
}
