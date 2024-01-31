# GDB GUI setup for GDB, the GNU debugger.
# Copyright 1994, 1995, 1996, 1997
# Free Software Foundation, Inc.

# Written by Stu Grossman <grossman@cygnus.com> of Cygnus Support.

# This file is part of GDB.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

set cfile Blank
set wins($cfile) .src.text
set current_label {}
set cfunc NIL
set line_numbers 1
set breakpoint_file(-1) {[garbage]}
set disassemble_with_source nosource
set gdb_prompt "(gdb) "

# Hint: The following can be toggled from a tclsh window after
# using the gdbtk "tk tclsh" command to open the window.
set debug_interface 0

#option add *Foreground Black
#option add *Background White
#option add *Font -*-*-medium-r-normal--18-*-*-*-m-*-*-1

proc echo {string} {
    puts stdout $string
}

# Assign elements from LIST to variables named in ARGS.  
proc lassign {list args} {
    set len [expr {[llength $args] - 1}]
    while {$len >= 0} {
	upvar [lindex $args $len] local
	set local [lindex $list $len]
	decr len
    }
}

#
# Local procedure:
#
#	decr (var val) - compliment to incr
#
# Description:
#
#
proc decr {var {val 1}} {
    upvar $var num
    set num [expr {$num - $val}]
    return $num
}

#
# Center a window on the screen.
#
proc center_window {toplevel} {
    # Withdraw and update, to ensure geometry computations are finished.
    wm withdraw $toplevel
    update idletasks
    
    set x [expr {[winfo screenwidth $toplevel] / 2
		 - [winfo reqwidth $toplevel] / 2
		 - [winfo vrootx $toplevel]}]
    set y [expr {[winfo screenheight $toplevel] / 2
		 - [winfo reqheight $toplevel] / 2
		 - [winfo vrooty $toplevel]}]
    wm geometry $toplevel +${x}+${y}
    wm deiconify $toplevel
}

#
# Rearrange the bindtags so the widget comes after the class.  I was
# always for Ousterhout putting the class bindings first, but no...
#
proc bind_widget_after_class {widget} {
    set class [winfo class $widget]
    set newList {}
    foreach tag [bindtags $widget] {
	if {$tag == $widget} {
	    # Nothing.
	} {
	    lappend newList $tag
	    if {$tag == $class} {
		lappend newList $widget
	    }
	}
    }
    bindtags $widget $newList
}


if {[info exists env(EDITOR)]} then {
    set editor $env(EDITOR)
} else {
    set editor emacs
}

# GDB callbacks
#
#  These functions are called by GDB (from C code) to do various things in
#  TK-land.  All start with the prefix `gdbtk_tcl_' to make them easy to find.
#

#
# GDB Callback:
#
#	gdbtk_tcl_fputs (text) - Output text to the command window
#
# Description:
#
#	GDB calls this to output TEXT to the GDB command window.  The text is
#	placed at the end of the text widget.  Note that output may not occur,
#	due to buffering.  Use gdbtk_tcl_flush to cause an immediate update.
#

proc gdbtk_tcl_fputs {arg} {
    .cmd.text insert end "$arg"
    .cmd.text see end
}

proc gdbtk_tcl_fputs_error {arg} {
    .cmd.text insert end "$arg"
    .cmd.text see end
}

#
# GDB Callback:
#
#	gdbtk_tcl_flush () - Flush output to the command window
#
# Description:
#
#	GDB calls this to force all buffered text to the GDB command window.
#

proc gdbtk_tcl_flush {} {
    .cmd.text see end
    update idletasks
}

#
# GDB Callback:
#
#	gdbtk_tcl_query (message) - Create a yes/no query dialog box
#
# Description:
#
#	GDB calls this to create a yes/no dialog box containing MESSAGE.  GDB
#	is hung while the dialog box is active (ie: no commands will work),
#	however windows can still be refreshed in case of damage or exposure.
#

proc gdbtk_tcl_query {message} {
    # FIXME We really want a Help button here.  But Tk's brain-damaged
    # modal dialogs won't really allow it.  Should have async dialog
    # here.
    set result [tk_dialog .query "gdb : query" "$message" questhead 0 Yes No]
    return [expr {!$result}]
}

#
# GDB Callback:
#
#	gdbtk_start_variable_annotation (args ...) - 
#
# Description:
#
#	Not yet implemented.
#

proc gdbtk_tcl_start_variable_annotation {valaddr ref_type stor_cl
					  cum_expr field type_cast} {
    echo "gdbtk_tcl_start_variable_annotation $valaddr $ref_type $stor_cl $cum_expr $field $type_cast"
}

#
# GDB Callback:
#
#	gdbtk_end_variable_annotation (args ...) - 
#
# Description:
#
#	Not yet implemented.
#

proc gdbtk_tcl_end_variable_annotation {} {
    echo gdbtk_tcl_end_variable_annotation
}




proc gdbtk_tcl_busy {} {
    if {[winfo exists .cmd]} {
	.cmd.text configure -state disabled
    }
    if {[winfo exists .src]} {
	.src.start configure -state disabled
	.src.stop configure -state normal
	.src.step configure -state disabled
	.src.next configure -state disabled
	.src.continue configure -state disabled
	.src.finish configure -state disabled
	.src.up configure -state disabled
	.src.down configure -state disabled
	.src.bottom configure -state disabled
    }
    if {[winfo exists .asm]} {
	.asm.stepi configure -state disabled
	.asm.nexti configure -state disabled
	.asm.continue configure -state disabled
	.asm.finish configure -state disabled
	.asm.up configure -state disabled
	.asm.down configure -state disabled
	.asm.bottom configure -state disabled
    }
    return
}

proc gdbtk_tcl_idle {} {
    if {[winfo exists .cmd]} {
	.cmd.text configure -state normal
    }
    if {[winfo exists .src]} {
	.src.start configure -state normal
	.src.stop configure -state disabled
	.src.step configure -state normal
	.src.next configure -state normal
	.src.continue configure -state normal
	.src.finish configure -state normal
	.src.up configure -state normal
	.src.down configure -state normal
	.src.bottom configure -state normal
    }
    if {[winfo exists .asm]} {
	.asm.stepi configure -state normal
	.asm.nexti configure -state normal
	.asm.continue configure -state normal
	.asm.finish configure -state normal
	.asm.up configure -state normal
	.asm.down configure -state normal
	.asm.bottom configure -state normal
    }
    return
}

#
# Local procedure:
#
#	pc_to_line (pclist pc) - convert PC to a line number.
#
# Description:
#
#	Convert PC to a line number from PCLIST.  If exact line isn't found,
#	we return the first line that starts before PC.
#
proc pc_to_line {pclist pc} {
    set line [lsearch -exact $pclist $pc]
    
    if {$line >= 1} { return $line }
    
    set line 1
    foreach linepc [lrange $pclist 1 end] {
	if {$pc < $linepc} { decr line ; return $line }
	incr line
    }
    return [expr {$line - 1}]
}

#
# Menu:
#
#	file popup menu - Define the file popup menu.
#
# Description:
#
#	This menu just contains a bunch of buttons that do various things to
#	the line under the cursor.
#
# Items:
#
#	Edit - Run the editor (specified by the environment variable EDITOR) on
#	       this file, at the current line.
#	Breakpoint - Set a breakpoint at the current line.  This just shoves
#		a `break' command at GDB with the appropriate file and line
#		number.  Eventually, GDB calls us back (at gdbtk_tcl_breakpoint)
#		to notify us of where the breakpoint needs to show up.
#

menu .file_popup -cursor hand2 -tearoff 0
.file_popup add command -label "Not yet set" -state disabled
.file_popup add separator
.file_popup add command -label "Edit" \
    -command {exec $editor +$selected_line $selected_file &}
.file_popup add command -label "Set breakpoint" \
    -command {gdb_cmd "break $selected_file:$selected_line"}

# Use this procedure to get the GDB core to execute the string `cmd'.  This is
# a wrapper around gdb_cmd, which will catch errors, and send output to the
# command window.  It will also cause all of the other windows to be updated.

proc interactive_cmd {cmd} {
    catch {gdb_cmd "$cmd"} result
    .cmd.text insert end $result
    .cmd.text see end
    update_ptr
}


#
# Local procedure:
#
#	do_nothing - Does absolutely nothing.
#
# Description:
#
#	This procedure does nothing.  It is used as a placeholder to allow
#	the disabling of bindings that would normally be inherited from the
#	parent widget.  I can't think of any other way to do this.
#

proc do_nothing {} {}

#
# Local procedure:
#
#	not_implemented_yet - warn that a feature is unavailable
#
# Description:
#
#	This procedure warns that something doesn't actually work yet.
#

proc not_implemented_yet {message} {
    tk_dialog .unimpl "gdb : unimpl" \
	"$message: not implemented in the interface yet" \
	warning 0 "OK"
}


# Make toplevel window disappear
wm withdraw .


button .files -text Files -command files_command

proc apply_filespec {label default command} {
    set filename [tk_getOpenFile -title $label -initialfile $default]
    if {$filename != ""} {
	if {[catch {gdb_cmd "$command $filename"} retval]} {
	    tk_dialog .filespec_error "gdb : $label error" \
		"Error in command \"$command $filename\"" error \
		0 Dismiss
	    return
	}
	update_ptr
    }
}

# Run editor.
proc run_editor {editor file} {
    # FIXME should use index of line in middle of window, not line at
    # top.
    global wins
    set lineNo [lindex [split [$wins($file) index @0,0] .] 0]
    exec $editor +$lineNo $file
}

# Setup command window
proc build_framework {win {title GDBtk} {label {}}} {
    global ${win}.label
    
    toplevel ${win}
    wm title ${win} $label
    wm minsize ${win} 1 1
    
    frame ${win}.menubar
    
    menubutton ${win}.menubar.file -padx 12 -text File \
	-menu ${win}.menubar.file.menu -underline 0
    
    menu ${win}.menubar.file.menu
    ${win}.menubar.file.menu add command -label File... \
	-command {apply_filespec File a.out file}
    ${win}.menubar.file.menu add command -label Target... \
	-command { not_implemented_yet "target" }
    ${win}.menubar.file.menu add command -label Edit \
	-command {run_editor $editor $cfile}
    ${win}.menubar.file.menu add separator
    ${win}.menubar.file.menu add command -label "Exec File..." \
	-command {apply_filespec {Exec File} a.out exec-file}
    ${win}.menubar.file.menu add command -label "Symbol File..." \
	-command {apply_filespec {Symbol File} a.out symbol-file}
    ${win}.menubar.file.menu add command -label "Add Symbol File..." \
	-command { not_implemented_yet "menu item, add symbol file" }
    ${win}.menubar.file.menu add command -label "Core File..." \
	-command {apply_filespec {Core File} core core-file}
    
    ${win}.menubar.file.menu add separator
    ${win}.menubar.file.menu add command -label Close \
	-command "destroy ${win}"
    ${win}.menubar.file.menu add separator
    ${win}.menubar.file.menu add command -label Quit \
	-command {interactive_cmd quit}
    
    menubutton ${win}.menubar.commands -padx 12 -text Commands \
	-menu ${win}.menubar.commands.menu -underline 0
    
    menu ${win}.menubar.commands.menu
    ${win}.menubar.commands.menu add command -label Run \
	-command {interactive_cmd run}
    ${win}.menubar.commands.menu add command -label Step \
	-command {interactive_cmd step}
    ${win}.menubar.commands.menu add command -label Next \
	-command {interactive_cmd next}
    ${win}.menubar.commands.menu add command -label Continue \
	-command {interactive_cmd continue}
    ${win}.menubar.commands.menu add separator
    ${win}.menubar.commands.menu add command -label Stepi \
	-command {interactive_cmd stepi}
    ${win}.menubar.commands.menu add command -label Nexti \
	-command {interactive_cmd nexti}
    
    menubutton ${win}.menubar.view -padx 12 -text Options \
	-menu ${win}.menubar.view.menu -underline 0
    
    menu ${win}.menubar.view.menu
    ${win}.menubar.view.menu add command -label Hex \
	-command {echo Hex}
    ${win}.menubar.view.menu add command -label Decimal \
	-command {echo Decimal}
    ${win}.menubar.view.menu add command -label Octal \
	-command {echo Octal}
    
    menubutton ${win}.menubar.window -padx 12 -text Window \
	-menu ${win}.menubar.window.menu -underline 0
    
    menu ${win}.menubar.window.menu
    ${win}.menubar.window.menu add command -label Command \
	-command create_command_window
    ${win}.menubar.window.menu add separator
    ${win}.menubar.window.menu add command -label Source \
	-command create_source_window
    ${win}.menubar.window.menu add command -label Assembly \
	-command create_asm_window
    ${win}.menubar.window.menu add separator
    ${win}.menubar.window.menu add command -label Registers \
	-command create_registers_window
    ${win}.menubar.window.menu add command -label Expressions \
	-command create_expr_window
    ${win}.menubar.window.menu add command -label "Auto Command" \
	-command create_autocmd_window
    ${win}.menubar.window.menu add command -label Breakpoints \
	-command create_breakpoints_window
    
    #	${win}.menubar.window.menu add separator
    #	${win}.menubar.window.menu add command -label Files \
	#		-command { not_implemented_yet "files window" }
    
    menubutton ${win}.menubar.help -padx 12 -text Help \
	-menu ${win}.menubar.help.menu -underline 0
    
    menu ${win}.menubar.help.menu
    ${win}.menubar.help.menu add command -label "with GDBtk" \
	-command {echo "with GDBtk"}
    ${win}.menubar.help.menu add command -label "with this window" \
	-command {echo "with this window"}
    ${win}.menubar.help.menu add command -label "Report bug" \
	-command {exec send-pr}
    
    pack ${win}.menubar.file ${win}.menubar.view \
	${win}.menubar.window -side left
    pack ${win}.menubar.help -side right
    
    frame ${win}.info
    text ${win}.text -height 25 -width 80 -relief sunken -borderwidth 2 \
	-setgrid true -cursor hand2 -yscrollcommand [list ${win}.yscroll set] \
	-xscrollcommand [list ${win}.xscroll set] -wrap none
    
#    set ${win}.label $label
    label ${win}.label -textvariable ${win}.label -borderwidth 2 -relief sunken
    
    scrollbar ${win}.yscroll -orient vertical \
	-command [list ${win}.text yview] -relief sunken
    scrollbar ${win}.xscroll -orient horizontal \
	-command [list ${win}.text xview] -relief sunken
    
    bind $win <Key-Alt_R> do_nothing
    bind $win <Key-Alt_L> do_nothing

    pack ${win}.xscroll -side bottom -fill x -in ${win}.info
#    pack ${win}.label -side bottom -fill x -in ${win}.info
    pack ${win}.yscroll -side right -fill y -in ${win}.info
    pack ${win}.text -side left -expand true -fill both -in ${win}.info

    pack ${win}.menubar -side top -fill x
    pack ${win}.info -side top -fill both -expand true
}


proc update_autocmd {} {
    global .autocmd.label
    global accumulate_output
    
    catch {gdb_cmd "${.autocmd.label}"} result
    if {!$accumulate_output} { .autocmd.text delete 0.0 end }
    .autocmd.text insert end $result
    .autocmd.text see end
}

proc create_autocmd_window {} {
    global .autocmd.label
    
    if {[winfo exists .autocmd]} {raise .autocmd ; return}
    
    build_framework .autocmd "Auto Command" ""
    
    # First, delete all the old view menu entries
    
    .autocmd.menubar.view.menu delete 0 last
    
    # Accumulate output option
    
    .autocmd.menubar.view.menu add checkbutton \
	-variable accumulate_output \
	-label "Accumulate output" -onvalue 1 -offvalue 0
    
    # Now, create entry widget with label
    
    frame .autocmd.entryframe
    
    entry .autocmd.entry -borderwidth 2 -relief sunken
    bind .autocmd.entry <Key-Return> {
	set .autocmd.label [.autocmd.entry get]
    .autocmd.entry delete 0 end
    }
    
    label .autocmd.entrylab -text "Command: "
    
    pack .autocmd.entrylab -in .autocmd.entryframe -side left
    pack .autocmd.entry -in .autocmd.entryframe -side left -fill x -expand yes
    
    pack .autocmd.entryframe -side bottom -fill x -before .autocmd.info
}

# Return the longest common prefix in SLIST.  Can be empty string.

proc find_lcp slist {
    # Handle trivial cases where list is empty or length 1
    if {[llength $slist] <= 1} {return [lindex $slist 0]}
    
    set prefix [lindex $slist 0]
    set prefixlast [expr [string length $prefix] - 1]
    
    foreach str [lrange $slist 1 end] {
	set test_str [string range $str 0 $prefixlast]
	while {[string compare $test_str $prefix] != 0} {
	    decr prefixlast
	    set prefix [string range $prefix 0 $prefixlast]
	    set test_str [string range $str 0 $prefixlast]
	}
	if {$prefixlast < 0} break
    }
    return $prefix
}

# Look through COMPLETIONS to generate the suffix needed to do command
# completion on CMD.

proc find_completion {cmd completions} {
    # Get longest common prefix
    set lcp [find_lcp $completions]
    set cmd_len [string length $cmd]
    # Return suffix beyond end of cmd
    return [string range $lcp $cmd_len end]
}



# Begin support primarily for debugging the tcl/tk portion of gdbtk.  You can
# start gdbtk, and then issue the command "tk tclsh" and a window will pop up
# giving you direct access to the tcl interpreter.  With this, it is very easy
# to examine the values of global variables, directly invoke routines that are
# part of the gdbtk interface, replace existing proc's with new ones, etc.
# This code was inspired from example 11-3 in Brent Welch's "Practical
# Programming in Tcl and Tk"

set tcl_prompt "tcl> "

# Get the current command that user has typed, from cmdstart to end of text
# widget.  Evaluate it, insert result back into text widget, issue a new
# prompt, update text widget and update command start mark.

proc evaluate_tcl_command { twidget } {
    global tcl_prompt
    
    set command [$twidget get cmdstart end]
    if [info complete $command] {
	set err [catch {uplevel #0 $command} result]
        $twidget insert insert \n$result\n
	$twidget insert insert $tcl_prompt
	$twidget see insert
	$twidget mark set cmdstart insert
	return
    }
}
	
# Create the evaluation window and set up the keybindings to evaluate the
# last single line entered by the user.  FIXME: allow multiple lines?
	
proc tclsh {} {
    global tcl_prompt

    # If another evaluation window already exists, just bring it to the front.
    if {[winfo exists .eval]} {raise .eval ; return}

    # Create top level frame with scrollbar and text widget.
    toplevel .eval
    wm title .eval "Tcl Evaluation"
    wm iconname .eval "Tcl"
    text .eval.text -width 80 -height 20 -setgrid true -cursor hand2 \
	    -yscrollcommand {.eval.scroll set}
    scrollbar .eval.scroll -command {.eval.text yview}
    pack .eval.scroll -side right -fill y
    pack .eval.text -side left -fill both -expand true

    # Insert the tcl_prompt and initialize the cmdstart mark
    .eval.text insert insert $tcl_prompt
    .eval.text mark set cmdstart insert
    .eval.text mark gravity cmdstart left

    # Make this window the current one for input.
    focus .eval.text

    # Keybindings that limit input and evaluate things
    bind .eval.text <Return> { evaluate_tcl_command .eval.text ; break }
    bind .eval.text <BackSpace> {
	if [%W compare insert > cmdstart] {
	    %W delete {insert - 1 char} insert
	} else {
	    bell
	}
	break
    }
    bind .eval.text <Any-Key> {
	if [%W compare insert < cmdstart] {
	    %W mark set insert end
	}
    }
    bind .eval.text <Control-u> {
	%W delete cmdstart "insert lineend"
	%W see insert
    }
    bindtags .eval.text {.eval.text Text all}
}

# This proc is executed just prior to falling into the Tk main event loop.
proc gdbtk_tcl_preloop {} {
    global gdb_prompt
    .cmd.text insert end "$gdb_prompt"
    .cmd.text see end
    update
}

# FIXME need to handle mono here.  In Tk4 that is more complicated.
set highlight "-background red2 -borderwidth 2 -relief sunken"

set BreakImage [image create photo -file [file join $GDBTK_LIBRARY stop2.gif]]

# Setup the initial windows
create_command_window
create_source_window


# Make this last so user actually sees it.
create_copyright_window
# Refresh.
update

if {[file exists ~/.gdbtkinit]} {
  source ~/.gdbtkinit
}
