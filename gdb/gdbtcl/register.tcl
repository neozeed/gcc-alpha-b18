# Local procedure:
#
#	create_registers_window - Open up the register display window.
#
# Description:
#
#	Create the register display window, with automatic updates.
#

proc create_registers_window {} {
    global reg_format_natural
    global reg_format_decimal
    global reg_format_hex
    global reg_format_octal
    global reg_format_raw
    global reg_format_binary
    global reg_format_unsigned

    # If we already have a register window, just use that one.

    if {[winfo exists .reg]} {raise .reg ; return}

    # Create an initial register display list consisting of all registers

    init_reg_info

    build_framework .reg Registers

    # First, delete all the old menu entries

    .reg.menubar.view.menu delete 0 last

    # Natural menu item
    .reg.menubar.view.menu add checkbutton -label $reg_format_natural(label) \
	    -variable reg_format_natural(enable) -onvalue on -offvalue off \
	    -command {update_registers redraw}

    # Decimal menu item
    .reg.menubar.view.menu add checkbutton -label $reg_format_decimal(label) \
	    -variable reg_format_decimal(enable) -onvalue on -offvalue off \
	    -command {update_registers redraw}

    # Hex menu item
    .reg.menubar.view.menu add checkbutton -label $reg_format_hex(label) \
	    -variable reg_format_hex(enable) -onvalue on -offvalue off \
	    -command {update_registers redraw}

    # Octal menu item
    .reg.menubar.view.menu add checkbutton -label $reg_format_octal(label) \
	    -variable reg_format_octal(enable) -onvalue on -offvalue off \
	    -command {update_registers redraw}

    # Binary menu item
    .reg.menubar.view.menu add checkbutton -label $reg_format_binary(label) \
	    -variable reg_format_binary(enable) -onvalue on -offvalue off \
	    -command {update_registers redraw}

    # Unsigned menu item
    .reg.menubar.view.menu add checkbutton -label $reg_format_unsigned(label) \
	    -variable reg_format_unsigned(enable) -onvalue on -offvalue off \
	    -command {update_registers redraw}

    # Raw menu item
    .reg.menubar.view.menu add checkbutton -label $reg_format_raw(label) \
	    -variable reg_format_raw(enable) -onvalue on -offvalue off \
	    -command {update_registers redraw}

    # Config menu item
    .reg.menubar.view.menu add separator

    .reg.menubar.view.menu add command -label Config \
	    -command { reg_config_menu }

    destroy .reg.label

    # Install the reg names

    populate_reg_window
    update_registers all
}

proc init_reg_info {} {
    global reg_format_natural
    global reg_format_decimal
    global reg_format_hex
    global reg_format_octal
    global reg_format_raw
    global reg_format_binary
    global reg_format_unsigned
    global long_size
    global double_size

    if {![info exists reg_format_hex]} {
	global reg_display_list
	global changed_reg_list
	global regena

	set long_size [lindex [gdb_cmd {p sizeof(long)}] 2]
	set double_size [lindex [gdb_cmd {p sizeof(double)}] 2]

	# The natural format may print floats or doubles as floating point,
	# which typically takes more room that printing ints on the same
	# machine.  We assume that if longs are 8 bytes that this is
	# probably a 64 bit machine.  (FIXME)
	set reg_format_natural(label) Natural
	set reg_format_natural(enable) on
	set reg_format_natural(format) {}
	if {$long_size == 8} then {
	    set reg_format_natural(width) 25
	} else {
	    set reg_format_natural(width) 16
	}

	set reg_format_decimal(label) Decimal
	set reg_format_decimal(enable) off
	set reg_format_decimal(format) d
	if {$long_size == 8} then {
	    set reg_format_decimal(width) 21
	} else {
	    set reg_format_decimal(width) 12
	}

	set reg_format_hex(label) Hex
	set reg_format_hex(enable) off
	set reg_format_hex(format) x
	set reg_format_hex(width) [expr $long_size * 2 + 3]

	set reg_format_octal(label) Octal
	set reg_format_octal(enable) off
	set reg_format_octal(format) o
	set reg_format_octal(width) [expr $long_size * 8 / 3 + 3]

	set reg_format_raw(label) Raw
	set reg_format_raw(enable) off
	set reg_format_raw(format) r
	set reg_format_raw(width) [expr $double_size * 2 + 3]

	set reg_format_binary(label) Binary
	set reg_format_binary(enable) off
	set reg_format_binary(format) t
	set reg_format_binary(width) [expr $long_size * 8 + 1]

	set reg_format_unsigned(label) Unsigned
	set reg_format_unsigned(enable) off
	set reg_format_unsigned(format) u
	if {$long_size == 8} then {
	    set reg_format_unsigned(width) 21
	} else {
	    set reg_format_unsigned(width) 11
	}

	set num_regs [llength [gdb_regnames]]
	for {set regnum 0} {$regnum < $num_regs} {incr regnum} {
	    set regena($regnum) 1
	}
	recompute_reg_display_list $num_regs
	#set changed_reg_list $reg_display_list
	set changed_reg_list {}
    }
}

# Convert regena into a list of the enabled $regnums

proc recompute_reg_display_list {num_regs} {
	global reg_display_list
	global regmap
	global regena

	catch {unset reg_display_list}
	set reg_display_list {}

	set line 2
	for {set regnum 0} {$regnum < $num_regs} {incr regnum} {

		if {[set regena($regnum)] != 0} {
			lappend reg_display_list $regnum
			set regmap($regnum) $line
			incr line
		}
	}
}

# Fill out the register window with the names of the regs specified in
# reg_display_list.

proc populate_reg_window {} {
    global reg_format_natural
    global reg_format_decimal
    global reg_format_hex
    global reg_format_octal
    global reg_format_raw
    global reg_format_binary
    global reg_format_unsigned
    global max_regname_width
    global reg_display_list

    set win .reg.text
    $win configure -state normal

    # Clear the entire widget and insert a blank line at the top where
    # the column labels will appear.
    $win delete 0.0 end
    $win insert end "\n"

    if {[llength $reg_display_list] > 0} {
	set regnames [eval gdb_regnames $reg_display_list]
    } else {
	set regnames {}
    }

    # Figure out the longest register name

    set max_regname_width 0

    foreach reg $regnames {
	set len [string length $reg]
	if {$len > $max_regname_width} {set max_regname_width $len}
    }

    set width [expr $max_regname_width + 15]

    set height [expr [llength $regnames] + 1]

    if {$height > 60} {set height 60}

    $win configure -height $height -width $width
    foreach reg $regnames {
	$win insert end [format "%-*s\n" $width ${reg}]
    }

    #Delete the blank line left at end by last insertion.
    if {[llength $regnames] > 0} {
	$win delete {end - 1 char} end
    }
    $win yview 0
    $win configure -state disabled
}

#
# Local procedure:
#
#	update_registers - Update the registers window.
#
# Description:
#
#	This procedure updates the registers window according to the value of
#	the "which" arg.
#

proc update_registers {which} {
    global max_regname_width
    global reg_format_natural
    global reg_format_decimal
    global reg_format_hex
    global reg_format_octal
    global reg_format_binary
    global reg_format_unsigned
    global reg_format_raw
    global reg_display_list
    global changed_reg_list
    global highlight
    global regmap

    # margin is the column where we start printing values
    set margin [expr $max_regname_width + 1]
    set win .reg.text
    $win configure -state normal

    if {$which == "all" || $which == "redraw"} {
	set display_list $reg_display_list
	$win delete 1.0 1.end
	$win insert 1.0 [format "%*s" $max_regname_width " "]
	foreach format {natural decimal unsigned hex octal raw binary } {
	    set field (enable)
	    set var reg_format_$format$field
	    if {[set $var] == "on"} {
		set field (label)
		set var reg_format_$format$field
		set label [set $var]
		set field (width)
		set var reg_format_$format$field
		set var [format "%*s" [set $var] $label]
		$win insert 1.end $var
	    }
	}
    } else {
	# Unhighlight the old values
	foreach regnum $changed_reg_list {
	    $win tag delete $win.$regnum
	}
	set changed_reg_list [eval gdb_changed_register_list $reg_display_list]
	set display_list $changed_reg_list
    }
    foreach regnum $display_list {
	set lineindex $regmap($regnum)
	$win delete $lineindex.$margin "$lineindex.0 lineend"
	foreach format {natural decimal unsigned hex octal raw binary } {
	    set field (enable)
	    set var reg_format_$format$field
	    if {[set $var] == "on"} {
		set field (format)
		set var reg_format_$format$field
		set regval [gdb_fetch_registers [set $var] $regnum]
		set field (width)
		set var reg_format_$format$field
		set regval [format "%*s" [set $var] $regval]
		$win insert $lineindex.end $regval
	    }
	}
    }
    # Now, highlight the changed values of the interesting registers
    if {$which != "all"} {
	foreach regnum $changed_reg_list {
	    set lineindex $regmap($regnum)
	    $win tag add $win.$regnum $lineindex.0 "$lineindex.0 lineend"
	    eval $win tag configure $win.$regnum $highlight
	}
    }
    set winwidth $margin
    foreach format {natural decimal unsigned hex octal raw binary} {
	set field (enable)
	set var reg_format_$format$field
	if {[set $var] == "on"} {
	    set field (width)
	    set var reg_format_$format$field
	    set winwidth [expr $winwidth + [set $var]]
	}
    }
    $win configure -width $winwidth
    $win configure -state disabled
}

proc reg_config_menu {} {
    	catch {destroy .reg.config}
	toplevel .reg.config
	wm geometry .reg.config +300+300
	wm title .reg.config "Register configuration"
	wm iconname .reg.config "Reg config"
	set regnames [gdb_regnames]
	set num_regs [llength $regnames]

	frame .reg.config.buts

	button .reg.config.done -text " Done " -command "
		recompute_reg_display_list $num_regs
		populate_reg_window
		update_registers all
		destroy .reg.config "

	button .reg.config.update -text Update -command "
		recompute_reg_display_list $num_regs
		populate_reg_window
		update_registers all "

	pack .reg.config.buts -side bottom -fill x

	pack .reg.config.done -side left -fill x -expand yes -in .reg.config.buts
	pack .reg.config.update -side right -fill x -expand yes -in .reg.config.buts

# Since there can be lots of registers, we build the window with no more than
# 32 rows, and as many columns as needed.

# First, figure out how many columns we need and create that many column frame
# widgets

	set ncols [expr ($num_regs + 31) / 32]

	for {set col 0} {$col < $ncols} {incr col} {
		frame .reg.config.col$col
		pack .reg.config.col$col -side left -anchor n
	}

# Now, create the checkbutton widgets and pack them in the appropriate columns

	set col 0
	set row 0
	for {set regnum 0} {$regnum < $num_regs} {incr regnum} {
		set regname [lindex $regnames $regnum]
		checkbutton .reg.config.col$col.$row -text $regname -pady 0 \
			-variable regena($regnum) -relief flat -anchor w -bd 1

		pack .reg.config.col$col.$row -side top -fill both

		incr row
		if {$row >= 32} {
			incr col
			set row 0
		}
	}
}

