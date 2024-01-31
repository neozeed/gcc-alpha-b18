#
# Local procedure:
#
#	create_file_win (filename) - Create a win for FILENAME.
#
# Return value:
#
#	The new text widget.
#
# Description:
#
#	This procedure creates a text widget for FILENAME.  It returns the
#	newly created widget.  First, a text widget is created, and given basic
#	configuration info.  Second, all the bindings are setup.  Third, the
#	file FILENAME is read into the text widget.  Fourth, margins and line
#	numbers are added.
#

proc create_file_win {filename debug_file} {
    global breakpoint_file
    global breakpoint_line
    global line_numbers
    global debug_interface
    
    # Replace all the dirty characters in $filename with clean ones, and 
    # generate a unique name for the text widget.
    
    regsub -all {\.} $filename {} temp
    set win .src.text$temp
    
    # Open the file, and read it into the text widget
    
    set filename [gdb_path_conv $filename]
    if {[catch "open $filename" fh]} {
	# File can't be read.  Put error message into .src.nofile window 
	# and return.
	catch {destroy .src.nofile}
	text .src.nofile -height 25 -width 88 -relief sunken \
	    -borderwidth 2 -yscrollcommand ".src.yscroll set" \
	    -setgrid true -cursor hand2
	.src.nofile insert 0.0 $fh
	.src.nofile configure -state disabled
	bind .src.nofile <1> do_nothing
	bind .src.nofile <B1-Motion> do_nothing
	return .src.nofile
    }
    
    # Actually create and do basic configuration on the text widget.
    
    text $win -height 25 -width 88 -relief sunken -borderwidth 2 \
	-yscrollcommand ".src.yscroll set" -xscrollcommand ".src.xscroll set" \
	-setgrid true -cursor hand2 -wrap none -tabs { 1c }
    
    # Setup all the bindings
    
    bind $win <Enter> {focus %W}
    bind $win <1> do_nothing
    bind $win <B1-Motion> do_nothing
    
    bind $win <Key-Alt_R> do_nothing
    bind $win <Key-Alt_L> do_nothing
    bind $win <Key-Prior> "$win yview {@0,0 - 10 lines}"
    bind $win <Key-Next> "$win yview {@0,0 + 10 lines}"
    bind $win <Key-Up> "$win yview {@0,0 - 1 lines}"
    bind $win <Key-Down> "$win yview {@0,0 + 1 lines}"
    bind $win <Key-Home> {update_listing [gdb_loc]}
    bind $win <Key-End> "$win see end"
    
    bind $win n {interactive_cmd next}
    bind $win s {interactive_cmd step}
    bind $win c {interactive_cmd continue}
    bind $win f {interactive_cmd finish}
    bind $win u {interactive_cmd up}
    bind $win d {interactive_cmd down}
    
    if $debug_interface {
	bind $win <Control-C> {
	    puts stdout burp
	}
    }
    
    $win delete 1.0 end
    
    set linenum 1
    foreach line [split [read $fh] \n] {
	if {$line_numbers} {
	    $win insert $linenum.0 [format " \t%4d  %s\n" $linenum "$line"]
	    $win tag add source $linenum.8 "$linenum.0 lineend"
	} else {
	    $win insert $linenum.0 " \t$line\n"
	    $win tag add source $linenum.2 "$linenum.0 lineend"
	}
	incr linenum
    }
    close $fh
    
    # Add the breakdots
    foreach i [gdb_sourcelines $debug_file] {
	$win delete $i.0
	$win insert $i.0 "-"
	$win tag add margin $i.0 $i.2
    }
    
    # A debugging trick to highlight sensitive regions.
    if $debug_interface {
	$win tag bind source <Enter> {
	    %W tag configure source -background yellow
	}
	$win tag bind source <Leave> {
	    %W tag configure source -background maroon
	}
	$win tag bind margin <Enter> {
	    %W tag configure margin -background red
	}
	$win tag bind margin <Leave> {
	    %W tag configure margin -background skyblue
	}
    }
    
    $win tag bind margin <1> {
	toggle_breakpoint %W %X %Y %x %y
    }

    $win tag bind source <1> {
	%W mark set anchor "@%x,%y wordstart"
	set last [%W index "@%x,%y wordend"]
	%W tag remove sel 0.0 anchor
	%W tag remove sel $last end
	%W tag add sel anchor $last
    }
    $win tag bind source <Double-Button-1> {
	%W mark set anchor "@%x,%y wordstart"
	set last [%W index "@%x,%y wordend"]
	%W tag remove sel 0.0 anchor
	%W tag remove sel $last end
	%W tag add sel anchor $last
	echo "Selected [selection get]"
    }
    $win tag bind source <B1-Motion> {
	%W tag remove sel 0.0 anchor
	%W tag remove sel $last end
	%W tag add sel anchor @%x,%y
    }
    $win tag bind sel <1> break
    $win tag bind sel <Double-Button-1> {
	display_expression [selection get]
	break
    }
    $win tag bind sel <B1-Motion> break
    $win tag lower sel
    
    $win tag bind source <2> {
	listing_window_popup %W %X %Y %x %y
    }
    
    # Make these bindings do nothing on the text window -- they
    # are completely handled by the tag bindings above.
    bind $win <1> break
    bind $win <B1-Motion> break
    bind $win <Double-Button-1> break
    
    # Scan though the breakpoint data base and install any destined for this file

    foreach bpnum [array names breakpoint_file] {
	if {$breakpoint_file($bpnum) == $filename} {
	    insert_breakpoint_tag $win $breakpoint_line($bpnum) $bpnum
	}
    }
    
# Disable the text widget to prevent user modifications

    $win configure -state disabled
    return $win
}

proc files_command {} {
    toplevel .files_window
    
    wm minsize .files_window 1 1
    #	wm overrideredirect .files_window true
    listbox .files_window.list -width 30 -height 20 -setgrid true \
	-yscrollcommand {.files_window.scroll set} \
	-relief sunken -borderwidth 2
    scrollbar .files_window.scroll -orient vertical \
	-command {.files_window.list yview} -relief sunken
    button .files_window.close -text Close -command {destroy .files_window}
    .files_window.list configure -selectmode single
    
    # Get the file list from GDB, sort it, and insert into the widget.
    eval .files_window.list insert 0 [lsort [gdb_listfiles]]
    
    pack .files_window.close -side bottom -fill x -expand no -anchor s
    pack .files_window.scroll -side right -fill both
    pack .files_window.list -side left -fill both -expand yes
    bind .files_window.list <ButtonRelease-1> {
	set file [%W get [%W curselection]]
	gdb_cmd "list $file:1,0"
	update_listing [gdb_loc $file:1]
	destroy .files_window
    }
    # We must execute the listbox binding first, because it
    # references the widget that will be destroyed by the widget
    # binding for Button-Release-1.  Otherwise we try to use
    # .files_window.list after the .files_window is destroyed.
    bind_widget_after_class .files_window.list
}

#
# Bindings:
#
#	file popup menu - Define the file popup menu bindings.
#
# Description:
#
#	This defines the binding for the file popup menu.  It simply
#       unhighlights the line under the cursor.
#

bind .file_popup <Any-ButtonRelease-1> {
  global selected_win
  # Unhighlight the selected line
  $selected_win tag delete breaktag
}

