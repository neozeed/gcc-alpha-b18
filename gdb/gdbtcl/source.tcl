proc create_source_window {} {
    global wins
    global cfile
    
    if {[winfo exists .src]} {raise .src ; return}
    
    build_framework .src Source "* No file *"
    
    # First, delete all the old view menu entries
    
    .src.menubar.view.menu delete 0 last
    
    # Source file selection
    .src.menubar.view.menu add command -label "Select source file" \
	-command files_command
    
    # Line numbers enable/disable menu item
    .src.menubar.view.menu add checkbutton -variable line_numbers \
	-label "Line numbers" -onvalue 1 -offvalue 0 -command {
	    foreach source [array names wins] {
		if {$source == "Blank"} continue
		destroy $wins($source)
		unset wins($source)
	    }
	    set cfile Blank
	    update_listing [gdb_loc]
	}
    
    frame .src.row1
    frame .src.row2
    
    button .src.start -width 6 -text Start -command \
	{interactive_cmd {break main}
	    interactive_cmd {enable delete $bpnum}
	    interactive_cmd run }
    button .src.stop -width 6 -text Stop -fg red -activeforeground red \
	-state disabled -command gdb_stop
    button .src.step -width 6 -text Step \
	-command {interactive_cmd step}
    button .src.next -width 6 -text Next \
	-command {interactive_cmd next}
    button .src.continue -width 6 -text Cont \
	-command {interactive_cmd continue}
    button .src.finish -width 6 -text Finish \
	-command {interactive_cmd finish}
    button .src.up -width 6 -text Up \
	-command {interactive_cmd up}
    button .src.down -width 6 -text Down \
	-command {interactive_cmd down}
    button .src.bottom -width 6 -text Bottom \
	-command {interactive_cmd {frame 0}}
    
    pack .src.start .src.step .src.continue .src.up .src.bottom \
	-side left -padx 3 -pady 5 -in .src.row1
    pack .src.stop .src.next .src.finish .src.down -side left -padx 3 \
	-pady 5 -in .src.row2
    
    pack .src.row2 .src.row1 -side bottom -anchor w -before .src.info

    $wins($cfile) insert 0.0 "  This page intentionally left blank."
    $wins($cfile) configure -width 88 -state disabled \
	-yscrollcommand [list .src.yscroll set]\
	-xscrollcommand [list .src.xscroll set]
}


#
# Local procedure:
#
#	update_listing (linespec) - Update the listing window according to
#				    LINESPEC.
#
# Description:
#
#	This procedure is called from various places to update the listing
#	window based on LINESPEC.  It is usually invoked with the result of
#	gdb_loc.
#
#	It will move the cursor, and scroll the text widget if necessary.
#	Also, it will switch to another text widget if necessary, and update
#	the label widget too.
#
#	LINESPEC is a list of the form:
#
#	{ DEBUG_FILE FUNCNAME FILENAME LINE }, where:
#
#	DEBUG_FILE - is the abbreviated form of the file name.  This is usually
#		     the file name string given to the cc command.  This is
#		     primarily needed for breakpoint commands, and when an
#		     abbreviated for of the filename is desired.
#	FUNCNAME - is the name of the function.
#	FILENAME - is the fully qualified (absolute) file name.  It is usually
#		   the same as $PWD/$DEBUG_FILE, where PWD is the working dir
#		   at the time the cc command was given.  This is used to
#		   actually locate the file to be displayed.
#	LINE - The line number to be displayed.
#
#	Usually, this procedure will just move the cursor one line down to the
#	next line to be executed.  However, if the cursor moves out of range
#	or into another file, it will scroll the text widget so that the line
#	of interest is in the middle of the viewable portion of the widget.
#

proc update_listing {linespec} {
    global pointers
    global wins cfile
    global current_label
    global win_to_file
    global file_to_debug_file
    global line_numbers

    # Rip the linespec apart
    
    lassign $linespec debug_file funcname filename line
    
    # Sometimes there's no source file for this location
    
    if {$filename == ""} {set filename Blank}
    
    # If we want to switch files, we need to unpack the current text widget, and
    # stick in the new one.
    
    if {$filename != $cfile} then {
	pack forget $wins($cfile)
	set cfile $filename
	
	# Create a text widget for this file if necessary
	
	if {![info exists wins($cfile)]} then {
	    set wins($cfile) [create_file_win $cfile $debug_file]
	    if {$wins($cfile) != ".src.nofile"} {
		set win_to_file($wins($cfile)) $cfile
		set file_to_debug_file($cfile) $debug_file
		set pointers($cfile) 1.1
	    }
	}
	
	# Pack the text widget into the listing widget, and scroll to the right place
	
	pack $wins($cfile) -side left -expand true -in .src.info \
	    -fill both -after .src.yscroll
	
	# Make the scrollbar point at the new text widget
	
	.src.yscroll configure -command [list $wins($cfile) yview]
	.src.xscroll configure -command [list $wins($cfile) xview]
	
	# $wins($cfile) see "${line}.0 linestart"
	ensure_line_visible $wins($cfile) $line
    }
    
    # Update the label widget in case the filename or function name has changed
    
    if {$current_label != "$filename.$funcname"} then {
	set tail [expr [string last / $filename] + 1]
	wm title .src "[string range $filename $tail end] : ${funcname}()"
	set current_label $filename.$funcname
    }
    
    # Update the pointer, scrolling the text widget if necessary to keep the
    # pointer in an acceptable part of the screen.
    
    if {[info exists pointers($cfile)]} then {
	$wins($cfile) tag configure current_source -background green
	$wins($cfile) tag configure source -background [$wins($cfile) cget -bg]
	$wins($cfile) configure -state normal
	set pointer_pos $pointers($cfile)
	$wins($cfile) configure -state normal
	set cline [lindex [split $pointer_pos .] 0]
	if {$line_numbers} {
	    $wins($cfile) tag remove current_source $cline.8 $cline.end
	} else {
	    $wins($cfile) tag remove current_source $cline.2 $cline.end
	}

	set pointer_pos [$wins($cfile) index $line.1]
	set pointers($cfile) $pointer_pos
	set cline [lindex [split $pointer_pos .] 0]
	if {$line_numbers} {
	    $wins($cfile) tag add current_source $cline.8 $cline.end
	} else {
	    $wins($cfile) tag add current_source $cline.2 $cline.end
	}

	ensure_line_visible $wins($cfile) $line
	$wins($cfile) configure -state disabled
    }
}

#
# Local procedure:
#
#	update_ptr - Update the listing window.
#
# Description:
#
#	This routine will update the listing window using the result of
#	gdb_loc.
#

proc update_ptr {} {
    update_listing [gdb_loc]
    if {[winfo exists .asm]} {
	update_assembly [gdb_loc]
    }
    if {[winfo exists .reg]} {
	update_registers changed
    }
    if {[winfo exists .expr]} {
	update_exprs
    }
    if {[winfo exists .autocmd]} {
	update_autocmd
    }
}

#
# Make sure line number $LINE is visible in the text widget.  But be
# more clever than the "see" command: if LINE is not currently
# displayed, arrange for LINE to be centered.  There are cases in
# which this does not work, so as a last resort we revert to "see".
#
# This is inefficient, but probably not slow enough to actually
# notice.
#
proc ensure_line_visible {text line} {
    set pixHeight [winfo height $text]
    # Compute height of widget in lines.  This fails if a line is wider
    # than the screen.  FIXME.
    set topLine [lindex [split [$text index @0,0] .] 0]
    set botLine [lindex [split [$text index @0,${pixHeight}] .] 0]
    
    if {$line > $topLine && $line < $botLine} then {
	# Onscreen, and not on the very edge.
	return
    }
    
    set newTop [expr {$line - ($botLine - $topLine)}]
    if {$newTop < 0} then {
	set newTop 0
    }
    $text yview moveto $newTop
    
    # In case the above failed.
    $text see ${line}.0
}

#
# Local procedure:
#
#	listing_window_popup (win x y xrel yrel) - Handle popups for listing window
#
# Description:
#
#	This procedure is invoked by holding down button 2 (usually) in the
#	listing window.  The action taken depends upon where the button was
#	pressed.  If it was in the left margin (the breakpoint column), it
#	sets or clears a breakpoint.  In the main text area, it will pop up a
#	menu.
#

proc listing_window_popup {win x y xrel yrel} {
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
    
# Record selected file and line for menu button actions

    set selected_file $file_to_debug_file($file)
    set selected_line [lindex $pos 0]
    set selected_col [lindex $pos 1]
    set selected_win $win

# Post the menu near the pointer, (and grab it)

    .file_popup entryconfigure 0 -label "$selected_file:$selected_line"
    
    tk_popup .file_popup $x $y
}

