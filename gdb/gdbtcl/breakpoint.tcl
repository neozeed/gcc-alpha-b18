#
# GDB Callback:
#
#	gdbtk_tcl_breakpoint (action bpnum file line) - Notify the TK
#	interface of changes to breakpoints.
#
# Description:
#
#	GDB calls this to notify TK of changes to breakpoints.  ACTION is one
#	of:
#		create		- Notify of breakpoint creation
#		delete		- Notify of breakpoint deletion
#		modify		- Notify of breakpoint modification
#

# file line pc type enabled disposition silent ignore_count commands cond_string thread hit_count

proc gdbtk_tcl_breakpoint {action bpnum} {
	set bpinfo [gdb_get_breakpoint_info $bpnum]
	set file [lindex $bpinfo 0]
	set line [lindex $bpinfo 1]
	set pc [lindex $bpinfo 2]
	set enable [lindex $bpinfo 4]

	if {$action == "modify"} {
		if {$enable == "1"} {
			set action enable
		} else {
			set action disable
		}
	}

	${action}_breakpoint $bpnum $file $line $pc
}


proc create_breakpoints_window {} {
    global bpframe_lasty

    if {[winfo exists .breakpoints]} {raise .breakpoints ; return}

    build_framework .breakpoints "Breakpoints" ""

    # First, delete all the old view menu entries
    .breakpoints.menubar.view.menu delete 0 last

    # Get rid of label
    destroy .breakpoints.label

    # Replace text with a canvas and fix the scrollbars
    
    destroy .breakpoints.text
    canvas .breakpoints.c -relief sunken -bd 2 \
	-cursor hand2 \
	-yscrollcommand {.breakpoints.yscroll set} \
	-xscrollcommand {.breakpoints.xscroll set}
    .breakpoints.yscroll configure -command {.breakpoints.c yview}
    .breakpoints.xscroll configure -command {.breakpoints.c xview}
    
    pack .breakpoints.c -side left -expand yes -fill both \
	-in .breakpoints.info
    
    set bpframe_lasty 0
    
    # Create a frame for each breakpoint
    
    foreach bpnum [gdb_get_breakpoint_list] {
	add_breakpoint_frame $bpnum
    }
}

# Create a frame for bpnum in the .breakpoints canvas

proc add_breakpoint_frame {bpnum} {
  global bpframe_lasty
  global enabled
  global disposition

  if {![winfo exists .breakpoints]} return

  set bpinfo [gdb_get_breakpoint_info $bpnum]

  lassign $bpinfo file line pc type enabled($bpnum) disposition($bpnum) \
    silent ignore_count commands cond thread hit_count

  set f .breakpoints.c.$bpnum

  if {![winfo exists $f]} {
    frame $f -relief sunken -bd 2

    label $f.id -text "#$bpnum     $file:$line    ($pc)" \
      -relief flat -bd 2 -anchor w
    frame $f.hit_count
    label $f.hit_count.label -text "Hit count:" -relief flat \
      -bd 2 -anchor w -width 11
    label $f.hit_count.val -text $hit_count -relief flat \
      -bd 2 -anchor w
    checkbutton $f.hit_count.enabled -text Enabled \
      -variable enabled($bpnum) -anchor w -relief flat

    pack $f.hit_count.label $f.hit_count.val -side left
    pack $f.hit_count.enabled -side right

    frame $f.thread
    label $f.thread.label -text "Thread: " -relief flat -bd 2 \
      -width 11 -anchor w
    entry $f.thread.entry -bd 2 -relief sunken -width 10
    $f.thread.entry insert end $thread
    pack $f.thread.label -side left
    pack $f.thread.entry -side left -fill x

    frame $f.cond
    label $f.cond.label -text "Condition: " -relief flat -bd 2 \
      -width 11 -anchor w
    entry $f.cond.entry -bd 2 -relief sunken
    $f.cond.entry insert end $cond
    pack $f.cond.label -side left
    pack $f.cond.entry -side left -fill x -expand yes

    frame $f.ignore_count
    label $f.ignore_count.label -text "Ignore count: " \
      -relief flat -bd 2 -width 11 -anchor w
    entry $f.ignore_count.entry -bd 2 -relief sunken -width 10
    $f.ignore_count.entry insert end $ignore_count
    pack $f.ignore_count.label -side left
    pack $f.ignore_count.entry -side left -fill x

    frame $f.disps

    label $f.disps.label -text "Disposition: " -relief flat -bd 2 \
      -anchor w -width 11

    radiobutton $f.disps.delete -text Delete \
      -variable disposition($bpnum) -anchor w -relief flat \
      -command "gdb_cmd \"delete break $bpnum\"" \
      -value delete

    radiobutton $f.disps.disable -text Disable \
      -variable disposition($bpnum) -anchor w -relief flat \
      -command "gdb_cmd \"disable break $bpnum\"" \
      -value disable

    radiobutton $f.disps.donttouch -text "Leave alone" \
      -variable disposition($bpnum) -anchor w -relief flat \
      -command "gdb_cmd \"enable break $bpnum\"" \
      -value donttouch

    pack $f.disps.label $f.disps.delete $f.disps.disable \
      $f.disps.donttouch -side left -anchor w
    text $f.commands -relief sunken -bd 2 -setgrid true \
      -cursor hand2 -height 3 -width 30

    foreach line $commands {
      $f.commands insert end "${line}\n"
    }

    pack $f.id -side top -anchor nw -fill x
    pack $f.hit_count $f.cond $f.thread $f.ignore_count $f.disps \
      $f.commands -side top -fill x -anchor nw
  }

  set tag [.breakpoints.c create window 0 $bpframe_lasty -window $f -anchor nw]
  update
  set bbox [.breakpoints.c bbox $tag]

  set bpframe_lasty [lindex $bbox 3]

  .breakpoints.c configure -width [lindex $bbox 2]
}

# Delete a breakpoint frame

proc delete_breakpoint_frame {bpnum} {
    global bpframe_lasty

    if {![winfo exists .breakpoints]} return

    # First, clear the canvas
    .breakpoints.c delete all
    
    # Now, repopulate it with all but the doomed breakpoint
    set bpframe_lasty 0
    foreach bp [gdb_get_breakpoint_list] {
	if {$bp != $bpnum} {
	    add_breakpoint_frame $bp
	}
    }
}


#
# Local procedure:
#
#	create_breakpoint (bpnum file line pc) - Record breakpoint info in TK land
#
# Description:
#
#	GDB calls this indirectly (through gdbtk_tcl_breakpoint) to notify TK
#	land of breakpoint creation.  This consists of recording the file and
#	line number in the breakpoint_file and breakpoint_line arrays.  Also,
#	if there is already a window associated with FILE, it is updated with
#	a breakpoint tag.
#

proc create_breakpoint {bpnum file line pc} {
	global wins
	global breakpoint_file
	global breakpoint_line
	global pos_to_breakpoint
	global pos_to_bpcount
	global cfunc
	global pclist

# Record breakpoint locations

	set breakpoint_file($bpnum) $file
	set breakpoint_line($bpnum) $line
	set pos_to_breakpoint($file:$line) $bpnum
	if {![info exists pos_to_bpcount($file:$line)]} {
		set pos_to_bpcount($file:$line) 0
	}
	incr pos_to_bpcount($file:$line)
	set pos_to_breakpoint($pc) $bpnum
	if {![info exists pos_to_bpcount($pc)]} {
		set pos_to_bpcount($pc) 0
	}
	incr pos_to_bpcount($pc)
	
# If there's a window for this file, update it

	if {[info exists wins($file)]} {
		insert_breakpoint_tag $wins($file) $line $bpnum
	}

# If there's an assembly window, update that too

	set win [asm_win_name $cfunc]
	if {[winfo exists $win]} {
		insert_breakpoint_tag $win [pc_to_line $pclist($cfunc) $pc] $bpnum
	}

# Update the breakpoints window

	add_breakpoint_frame $bpnum
}

#
# Local procedure:
#
#	delete_breakpoint (bpnum file line pc) - Delete breakpoint info from TK land
#
# Description:
#
#	GDB calls this indirectly (through gdbtk_tcl_breakpoint) to notify TK
#	land of breakpoint destruction.  This consists of removing the file and
#	line number from the breakpoint_file and breakpoint_line arrays.  Also,
#	if there is already a window associated with FILE, the tags are removed
#	from it.
#

proc delete_breakpoint {bpnum file line pc} {
    global wins
    global breakpoint_file
    global breakpoint_line
    global pos_to_breakpoint
    global pos_to_bpcount
    global cfunc pclist


    # Save line number and file for later
    set line $breakpoint_line($bpnum)
    set file $breakpoint_file($bpnum)

    # Reset breakpoint annotation info

    if {$pos_to_bpcount($file:$line) > 0} {
	decr pos_to_bpcount($file:$line)

	if {$pos_to_bpcount($file:$line) == 0} {
	    catch "unset pos_to_breakpoint($file:$line)"

	    unset breakpoint_file($bpnum)
	    unset breakpoint_line($bpnum)

	    # If there's a window for this file, update it

	    if {[info exists wins($file)]} {
		delete_breakpoint_tag $wins($file) $line
	    }
	}
    }

    # If there's an assembly window, update that too

    if {$pos_to_bpcount($pc) > 0} {
	decr pos_to_bpcount($pc)

	if {$pos_to_bpcount($pc) == 0} {
	    catch "unset pos_to_breakpoint($pc)"
	    set win [asm_win_name $cfunc]
	    if {[winfo exists $win]} {
		delete_breakpoint_tag $win [pc_to_line $pclist($cfunc) $pc]
	    }
	}
    }
    delete_breakpoint_frame $bpnum
}

#
# Local procedure:
#
#	enable_breakpoint (bpnum file line pc) - Record breakpoint info in TK land
#
# Description:
#
#	GDB calls this indirectly (through gdbtk_tcl_breakpoint) to notify TK
#	land of a breakpoint being enabled.  This consists of unstippling the
#	specified breakpoint indicator.
#

proc enable_breakpoint {bpnum file line pc} {
	global wins
	global cfunc pclist
	global enabled

	if {[info exists wins($file)]} {
		$wins($file) tag configure $line -fgstipple {}
	}

# If there's an assembly window, update that too

	set win [asm_win_name $cfunc]
	if {[winfo exists $win]} {
		$win tag configure [pc_to_line $pclist($cfunc) $pc] -fgstipple {}
	}

# If there's a breakpoint window, update that too

	if {[winfo exists .breakpoints]} {
		set enabled($bpnum) 1
	}
}

#
# Local procedure:
#
#	disable_breakpoint (bpnum file line pc) - Record breakpoint info in TK land
#
# Description:
#
#	GDB calls this indirectly (through gdbtk_tcl_breakpoint) to notify TK
#	land of a breakpoint being disabled.  This consists of stippling the
#	specified breakpoint indicator.
#

proc disable_breakpoint {bpnum file line pc} {
	global wins
	global cfunc pclist
	global enabled

	if {[info exists wins($file)]} {
		$wins($file) tag configure $line -fgstipple gray50
	}

# If there's an assembly window, update that too

	set win [asm_win_name $cfunc]
	if {[winfo exists $win]} {
		$win tag configure [pc_to_line $pclist($cfunc) $pc] -fgstipple gray50
	}

# If there's a breakpoint window, update that too

	if {[winfo exists .breakpoints]} {
		set enabled($bpnum) 0
	}
}

#
# Local procedure:
#
#	insert_breakpoint_tag (win line) - Insert a breakpoint tag in WIN.
#
# Description:
#
#	GDB calls this indirectly (through gdbtk_tcl_breakpoint) to insert a
#	breakpoint tag into window WIN at line LINE.
#

proc insert_breakpoint_tag {win line bpnum} {
    global GDBTK_LIBRARY BreakImage
    $win configure -state normal
    $win delete $line.0 
    button $win.$line -relief flat -padx 0 -pady 0 -image $BreakImage \
	-command [list gdb_cmd "delete $bpnum"] 
    $win window create $line.0 -window $win.$line
    #	$win.$line select
    $win configure -state disabled
}

#
# Local procedure:
#
#	delete_breakpoint_tag (win line) - Remove a breakpoint tag from WIN.
#
# Description:
#
#	GDB calls this indirectly (through gdbtk_tcl_breakpoint) to remove a
#	breakpoint tag from window WIN at line LINE.
#

proc delete_breakpoint_tag {win line} {
	$win configure -state normal
	$win delete $line.0
	if {[string range $win 0 3] == ".src"} then {
		$win insert $line.0 "-"
	} else {
		$win insert $line.0 " "
	}
#	$win.$line deselect
	$win configure -state disabled
}


#
# Local procedure:
#
#	toggle_breakpoint (win x y xrel yrel) - Handle clicks on breakdots
#
# Description:
#
#	This procedure sets or clears breakpoints where the button clicked.
#

proc toggle_breakpoint {win x y xrel yrel} {
    global wins
    global win_to_file
    global file_to_debug_file
    global highlight
    global selected_line
    global selected_file
    global selected_win
    global pos_to_breakpoint

    # Map TK window name back to file name.

    set file $win_to_file($win)
    set pos [split [$win index @$xrel,$yrel] .]

    # Record selected file and line
    set selected_file $file_to_debug_file($file)
    set selected_line [lindex $pos 0]
    set selected_col [lindex $pos 1]
    set selected_win $win

    # If we're in the margin, then toggle the breakpoint

    if {$selected_col < 8} {  # this is alway true actually
	set pos_break $selected_file:$selected_line
	set pos $file:$selected_line
	set tmp pos_to_breakpoint($pos)
	if {[info exists $tmp]} {
	    set bpnum [set $tmp]
	    gdb_cmd "delete $bpnum"
	} else {
	    gdb_cmd "break $pos_break"
	}
	return
    }
}

