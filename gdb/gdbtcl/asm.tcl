#
# Local procedure:
#
#	create_asm_window - Open up the assembly window.
#
# Description:
#
#	Create an assembly window if it doesn't exist.
#

proc create_asm_window {} {
    global cfunc
    
    if {[winfo exists .asm]} {raise .asm ; return}
    
    set cfunc *None*
    set win [asm_win_name $cfunc]
    
    build_framework .asm Assembly "*NIL*"
    
    # First, delete all the old menu entries
    
    .asm.menubar.view.menu delete 0 last
    
    .asm.text configure -yscrollcommand ".asm.yscroll set" \
	-xscrollcommand ".asm.xscroll set" -wrap none -tabs { 1c }
    
    frame .asm.row1
    frame .asm.row2
    
    button .asm.stepi -width 6 -text Stepi \
	-command {interactive_cmd stepi}
    button .asm.nexti -width 6 -text Nexti \
	-command {interactive_cmd nexti}
    button .asm.continue -width 6 -text Cont \
	-command {interactive_cmd continue}
    button .asm.finish -width 6 -text Finish \
	-command {interactive_cmd finish}
    button .asm.up -width 6 -text Up -command {interactive_cmd up}
    button .asm.down -width 6 -text Down \
	-command {interactive_cmd down}
    button .asm.bottom -width 6 -text Bottom \
	-command {interactive_cmd {frame 0}}
    
    pack .asm.stepi .asm.continue .asm.up .asm.bottom -side left -padx 3 -pady 5 -in .asm.row1
    pack .asm.nexti .asm.finish .asm.down -side left -padx 3 -pady 5 -in .asm.row2
    
    pack .asm.row2 .asm.row1 -side bottom -anchor w -before .asm.info
    
    update
    update_assembly [gdb_loc]
    
    # We do this update_assembly to get the proper value of disassemble-from-exec.
    # exec file menu item
    .asm.menubar.view.menu add radiobutton -label "Exec file" \
	-variable disassemble-from-exec -value 1
    # target memory menu item
    .asm.menubar.view.menu add radiobutton -label "Target memory" \
	-variable disassemble-from-exec -value 0
    
    # Disassemble with source
    .asm.menubar.view.menu add checkbutton -label "Source" \
	-variable disassemble_with_source -onvalue source \
	-offvalue nosource -command {
	    foreach asm [info command .asm.func_*] {
		destroy $asm
	    }
	    set cfunc NIL
	    update_assembly [gdb_loc]
	}
}

#
# Local procedure:
#
#	create_asm_win (funcname pc) - Create an assembly win for FUNCNAME.
#
# Return value:
#
#	The new text widget.
#
# Description:
#
#	This procedure creates a text widget for FUNCNAME.  It returns the
#	newly created widget.  First, a text widget is created, and given basic
#	configuration info.  Second, all the bindings are setup.  Third, the
#	function FUNCNAME is read into the text widget.
#

proc create_asm_win {funcname pc} {
    global breakpoint_file
    global breakpoint_line
    global pclist
    global disassemble_with_source
    
    # Replace all the dirty characters in $filename with clean ones, 
    # and generate a unique name for the text widget.
    
    set win [asm_win_name $funcname]
    
    # Actually create and do basic configuration on the text widget.

    text $win -height 25 -width 80 -relief sunken -borderwidth 2 \
	-setgrid true -cursor hand2 -yscrollcommand ".asm.yscroll set" \
	-xscrollcommand ".asm.xscroll set" -wrap none -tabs { 1c }

    # Setup all the bindings

    bind $win <Enter> {focus %W}
    bind $win <1> {asm_window_button_1 %W %X %Y %x %y; break}
    bind $win <B1-Motion> break
    bind $win <Double-Button-1> break
    
    bind $win <Key-Alt_R> do_nothing
    bind $win <Key-Alt_L> do_nothing
    
    bind $win n {interactive_cmd nexti}
    bind $win s {interactive_cmd stepi}
    bind $win c {interactive_cmd continue}
    bind $win f {interactive_cmd finish}
    bind $win u {interactive_cmd up}
    bind $win d {interactive_cmd down}

    # Disassemble the code, and read it into the new text widget
    
    $win insert end [gdb_disassemble $disassemble_with_source $pc]
    
    set numlines [$win index end]
    set numlines [lindex [split $numlines .] 0]
    decr numlines

    # Delete the first and last lines, cuz these contain useless info
    
    #	$win delete 1.0 2.0
    #	$win delete {end - 1 lines} end
    #	decr numlines 2
    
    # Add margins (for annotations) and note the PC for each line

    catch "unset pclist($funcname)"
    lappend pclist($funcname) Unused
    for {set i 1} {$i <= $numlines} {incr i} {
	scan [$win get $i.0 "$i.0 lineend"] "%s " pc
	lappend pclist($funcname) $pc
	$win insert $i.0 " \t"
    }
    
    # Scan though the breakpoint data base and install any destined for this file
    
    #foreach bpnum [array names breakpoint_file] {
    #	if {$breakpoint_file($bpnum) == $filename} {
    #	    insert_breakpoint_tag $win $breakpoint_line($bpnum)
    #	}
    #    }
    
    # Disable the text widget to prevent user modifications
    
    $win configure -state disabled
    return $win
}

#
# Local procedure:
#
#	update_assembly - Update the assembly window.
#
# Description:
#
#	This procedure updates the assembly window.
#

proc update_assembly {linespec} {
    global asm_pointers
    global wins cfunc
    global current_label
    global win_to_file
    global file_to_debug_file
    global current_asm_label
    global pclist
    
    # Rip the linespec apart
    
    lassign $linespec debug_file funcname filename line pc
    
    set win [asm_win_name $cfunc]
    
    # Sometimes there's no source file for this location
    
    if {$filename == ""} {set filename Blank}
    
    # If we want to switch funcs, we need to unpack the current text widget, 
    # and stick in the new one.

    if {$funcname != $cfunc } {
	set oldwin $win
	set cfunc $funcname
	
	set win [asm_win_name $cfunc]
	
	# Create a text widget for this func if necessary
	
	if {![winfo exists $win]} {
	    create_asm_win $cfunc $pc
	    set asm_pointers($cfunc) 1.1
	    set current_asm_label NIL
	}
	
	# Pack the text widget, and scroll to the right place
	
	pack forget $oldwin
	pack $win -side left -expand yes -fill both \
	    -after .asm.yscroll
	.asm.yscroll configure -command "$win yview"
	set line [pc_to_line $pclist($cfunc) $pc]
	ensure_line_visible $win $line
	update
    }
    
    # Update the label widget in case the filename or function name has changed
    
    if {$current_asm_label != "$pc $funcname"} then {
	wm title .asm "$pc $funcname"
	set current_asm_label "$pc $funcname"
    }
    
    # Update the pointer, scrolling the text widget if necessary to keep the
    # pointer in an acceptable part of the screen.
    
    if {[info exists asm_pointers($cfunc)]} then {
	$win configure -state normal
	set pointer_pos $asm_pointers($cfunc)
	$win tag configure current_source -background green
	$win tag configure source -background [$win cget -bg]
	$win configure -state normal
	set cline [lindex [split $pointer_pos .] 0]
	$win tag remove current_source $cline.6 $cline.end
	
	# Map the PC back to a line in the window		

	set line [pc_to_line $pclist($cfunc) $pc]

	if {$line == -1} {
	    echo "Can't find PC $pc"
	    return
	}
	
	set pointer_pos [$win index $line.1]
	set asm_pointers($cfunc) $pointer_pos
	
	set cline [lindex [split $pointer_pos .] 0]
	$win tag add current_source $cline.6 $cline.end
	ensure_line_visible $win $line
	$win configure -state disabled
    }
}

#
# Local procedure:
#
#	asm_window_button_1 (win x y xrel yrel) - Handle button 1 in asm window
#
# Description:
#
#	This procedure is invoked as a result of holding down button 1 in the
#	assembly window.  The action taken depends upon where the button was
#	pressed.  If it was in the left margin (the breakpoint column), it
#	sets or clears a breakpoint.  In the main text area, it will pop up a
#	menu.
#

proc asm_window_button_1 {win x y xrel yrel} {
	global wins
	global win_to_file
	global file_to_debug_file
	global highlight
	global selected_line
	global selected_file
	global selected_win
	global pos_to_breakpoint
	global pclist
	global cfunc

	set pos [split [$win index @$xrel,$yrel] .]

# Record selected file and line for menu button actions

	set selected_line [lindex $pos 0]
	set selected_col [lindex $pos 1]
	set selected_win $win

# Figure out the PC

	set pc [lindex $pclist($cfunc) $selected_line]

# If we're in the margin, then toggle the breakpoint

	if {$selected_col < 11} {
		set tmp pos_to_breakpoint($pc)
		if {[info exists $tmp]} {
			set bpnum [set $tmp]
			gdb_cmd "delete	$bpnum"
		} else {
			gdb_cmd "break *$pc"
		}
		return
	}

# Post the menu near the pointer, (and grab it)

#	.file_popup entryconfigure 0 -label "$selected_file:$selected_line"
#	.file_popup post [expr $x-[winfo width .file_popup]/2] [expr $y-10]
#	grab .file_popup
}


proc asm_win_name {funcname} {
	if {$funcname == "*None*"} {return .asm.text}

	regsub -all {\.} $funcname _ temp

	return .asm.func_${temp}
}

