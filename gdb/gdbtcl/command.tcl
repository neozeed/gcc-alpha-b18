#
# Command window for GdbTk.
#

proc create_command_window {} {
    global command_line
    global command_stack
    global command_stack_top
    global command_stack_ptr
    global saw_tab
    global gdb_prompt
    
    set saw_tab 0
    set command_stack_top 0
    set command_stack_ptr 0
    set command_line {}

    if {[winfo exists .cmd]} {raise .cmd ; return}
    
    build_framework .cmd Command "* Command Buffer *"

    # Put focus on command area.
    focus .cmd.text
    
    gdb_cmd {set language c}
    gdb_cmd {set height 0}
    gdb_cmd {set width 0}
    
    bind .cmd.text <Control-c> gdb_stop
    
    # Tk uses the Motifism that Delete means delete forward.  I
    # hate this, and I'm not gonna take it any more.
    set bsBinding [bind Text <BackSpace>]
    bind .cmd.text <Delete> "delete_char %W ; $bsBinding; break"
    bind .cmd.text <BackSpace> {
	if {([%W cget -state] == "disabled")} { break }
	delete_char %W
    }
    bind .cmd.text <Control-u> {
	if {([%W cget -state] == "disabled")} { break }
	delete_line %W
	break
    }
    bind .cmd.text <Control-p> {
	if {([%W cget -state] == "disabled")} { break }
	command_prev %W
	break
    }
    bind .cmd.text <Up> {
	if {([%W cget -state] == "disabled")} { break }
	command_prev %W
	break
    }
    bind .cmd.text <Control-n> {
	if {([%W cget -state] == "disabled")} { break }
	command_next %W
	break
    }
    bind .cmd.text <Down> {
	if {([%W cget -state] == "disabled")} { break }
	command_next %W
	break
    }
    bind .cmd.text <Meta-less> {
	if {([%W cget -state] == "disabled")} { break }
	command_first %W
	break
    }
    bind .cmd.text <Meta-greater> {
	if {([%W cget -state] == "disabled")} { break }
	command_last %W
	break
    }
    bind .cmd.text <Any-Key> {
	if {([%W cget -state] == "disabled")} { break }
	set saw_tab 0
	%W insert end %A
	%W see end
	append command_line %A
	break
    }
    bind .cmd.text <Key-Return> {
	if {([%W cget -state] == "disabled")} { break }
	set saw_tab 0
	%W insert end \n
	command_push
	interactive_cmd $command_line
	set command_line {}
	%W insert end "$gdb_prompt"
	%W see end
	break
	}
    bind .cmd.text <Button-2> {
	%W insert end [selection get]
	%W see end
	append command_line [selection get]
	break
    }
    bind .cmd.text <B2-Motion> break
    bind .cmd.text <ButtonRelease-2> break
    bind .cmd.text <Key-Tab> {
	if {([%W cget -state] == "disabled")} { break }
	set choices [gdb_cmd "complete $command_line"]
	set choices [string trimright $choices \n]
	set choices [split $choices \n]
	
	# Just do completion if this is the first tab
	if {!$saw_tab} {
	    set saw_tab 1
	    set completion [find_completion $command_line $choices]
	    append command_line $completion
	    # Here is where the completion is actually done.  If there
	    # is one match, complete the command and print a space.
	    # If two or more matches, complete the command and beep.
	    # If no match, just beep.
	    switch [llength $choices] {
		0	{}
		1	{
		    %W insert end "$completion "
		    append command_line " "
		    return
		}
		
		default {
		    %W insert end $completion
		}
	    }
	    bell
	    %W see end
	} else {
	    # User hit another consecutive tab.  List the choices.
	    # Note that at this point, choices may contain commands
	    # with spaces.  We have to lop off everything before (and
	    # including) the last space so that the completion list
	    # only shows the possibilities for the last token.
	    set choices [lsort $choices]
	    if {[regexp ".* " $command_line prefix]} {
		regsub -all $prefix $choices {} choices
	    }
	    %W insert end "\n[join $choices { }]\n$gdb_prompt$command_line"
	    %W see end
	}
	break
    }
}

# Trim one character off the command line.  The argument is ignored.

proc delete_char {win} {
    global command_line gdb_prompt

    set tmp [expr [string length $command_line] - 2]
    if {$tmp < 0} { 
	set command_line {}
	$win delete "insert linestart" "insert lineend" 
	$win insert end "$gdb_prompt "	
    } else {
	set command_line [string range $command_line 0 $tmp]
    }
}

# FIXME: This should actually check that the first characters of the current
# line  match the gdb prompt, since the user can move the insertion point
# anywhere.  It should also check that the insertion point is in the last
# line of the text widget.

proc delete_line {win} {
    global command_line
    global gdb_prompt

    set tmp [string length $gdb_prompt]
    $win delete "insert linestart + $tmp chars" "insert lineend"
    $win see insert
    set command_line {}
}


#
# GDB Callback:
#
#	gdbtk_tcl_readline_begin (message) - Notify Tk to open an interaction
#	window and start gathering user input
#
# Description:
#
#	GDB calls this to notify TK that it needs to open an interaction
#	window, displaying the given message, and be prepared to accept
#	calls to gdbtk_tcl_readline to gather user input.

proc gdbtk_tcl_readline_begin {message} {
    global readline_text

    # If another readline window already exists, just bring it to the front.
    if {[winfo exists .rl]} {raise .rl ; return}

    # Create top level frame with scrollbar and text widget.
    toplevel .rl
    wm title .rl "Interaction Window"
    wm iconname .rl "Input"
    message .rl.msg -text $message -aspect 7500 -justify left
    text .rl.text -width 80 -height 20 -setgrid true -cursor hand2 \
	    -yscrollcommand {.rl.scroll set}
    scrollbar .rl.scroll -command {.rl.text yview}
    pack .rl.msg -side top -fill x
    pack .rl.scroll -side right -fill y
    pack .rl.text -side left -fill both -expand true

    # When the user presses return, get the text from the command start mark to the
    # current insert point, stash it in the readline text variable, and update the
    # command start mark to the current insert point
    bind .rl.text <Return> {
	set readline_text [.rl.text get cmdstart {end - 1 char}]
	.rl.text mark set cmdstart insert
    }
    bind .rl.text <BackSpace> {
	if [%W compare insert > cmdstart] {
	    %W delete {insert - 1 char} insert
	} else {
	    bell
	}
	break
    }
    bind .rl.text <Any-Key> {
	if [%W compare insert < cmdstart] {
	    %W mark set insert end
	}
    }
    bind .rl.text <Control-u> {
	%W delete cmdstart "insert lineend"
	%W see insert
    }
    bindtags .rl.text {.rl.text Text all}
}

#
# GDB Callback:
#
#	gdbtk_tcl_readline (prompt) - Get one user input line
#
# Description:
#
#	GDB calls this to get one line of input from the user interaction
#	window, using "prompt" as the command line prompt.

proc gdbtk_tcl_readline {prompt} {
    global readline_text

    .rl.text insert end $prompt
    .rl.text mark set cmdstart insert
    .rl.text mark gravity cmdstart left
    .rl.text see insert

    # Make this window the current one for input.
    focus .rl.text
    grab .rl
    tkwait variable readline_text
    grab release .rl
    return $readline_text
}

#
# GDB Callback:
#
#	gdbtk_tcl_readline_end  - Terminate a user interaction
#
# Description:
#
#	GDB calls this when it is done getting interactive user input.
#	Destroy the interaction window.

proc gdbtk_tcl_readline_end {} {
    if {[winfo exists .rl]} { destroy .rl }
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
	scrollbar .breakpoints.scrollx -orient horizontal \
		-command {.breakpoints.c xview} -relief sunken
	canvas .breakpoints.c -relief sunken -bd 2 \
		-cursor hand2 \
	        -yscrollcommand {.breakpoints.scroll set} \
	        -xscrollcommand {.breakpoints.scrollx set}
	.breakpoints.scroll configure -command {.breakpoints.c yview}

	pack .breakpoints.scrollx -side bottom -fill x -in .breakpoints.info
	pack .breakpoints.c -side left -expand yes -fill both \
		-in .breakpoints.info

	set bpframe_lasty 0

# Create a frame for each breakpoint

	foreach bpnum [gdb_get_breakpoint_list] {
		add_breakpoint_frame $bpnum
	}
}

proc command_prev { w } {
    global command_stack_ptr

    if { $command_stack_ptr != 0 } {
	_command_update_line $w
	decr command_stack_ptr
    }
}

proc command_next { w } {
    global command_stack_ptr
    global command_stack_top

    if { $command_stack_ptr < $command_stack_top } { incr command_stack_ptr }
    _command_update_line $w
}

proc command_first { w } {
    global command_stack_ptr

    set command_stack_ptr 0
    _command_update_line $w
}

proc command_last { w } {
    global command_stack_ptr
    global command_stack_top

    set command_stack_ptr $command_stack_top
    _command_update_line $w
 }

proc _command_update_line { w } {
    global command_line
    global command_stack
    global command_stack_ptr
    global gdb_prompt

    set tmp [string length $gdb_prompt]
    $w delete "insert linestart + $tmp chars" "insert lineend"

   if [info exists command_stack($command_stack_ptr)] {
	set command_line $command_stack($command_stack_ptr)
	$w insert end $command_line
	$w see end
    } else {
	$w see end
	set command_line {}
    }
}

proc command_push { } {
    global command_line
    global command_stack
    global command_stack_top
    global command_stack_ptr

    # just a plain CR should repeat last command
    if {[string length $command_line] == 0} {
	if [info exists command_stack($command_stack_top)] {
	    set command_line $command_stack($command_stack_top)
	}
    } else {
	incr command_stack_top
	set command_stack($command_stack_top) $command_line
    }
    set command_stack_ptr $command_stack_top
}